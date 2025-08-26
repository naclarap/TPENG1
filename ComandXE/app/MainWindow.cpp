#include "MainWindow.h"
#include "ui_mainwindow.h" // ADICIONADO: Include do arquivo gerado pelo Qt Designer

#include <QMessageBox>
#include <QPushButton> // Incluído para a função popularMesas

// Inclusão das Fábricas (continua igual)
#include <ControleAcessoServiceFactory.h>
#include <GestaoSalaoServiceFactory.h>
#include <CardapioDigitalServiceFactory.h>
#include <GestaoComandasServiceFactory.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) // ADICIONADO: Inicialização do ponteiro 'ui'
{
    ui->setupUi(this); // ADICIONADO: Constrói a interface a partir do arquivo .ui

    // As chamadas de setup continuam, exceto a setupUI()
    setupServices();
    setupConnections();

    setWindowTitle("ComandX - Sprint 1");
    setMinimumSize(800, 600);

    // Estado inicial (continua igual)
    handleStatusLogin(m_servicoAcesso->isLogado());
}

MainWindow::~MainWindow()
{
    delete ui; // Adicionado para limpar a memória da UI
}

void MainWindow::setupServices() {
    // Esta função não muda
    m_servicoAcesso = ControleAcessoServiceFactory::create();
    m_servicoSalao = GestaoSalaoServiceFactory::create();
    m_servicoCardapio = CardapioDigitalServiceFactory::create();
    m_servicoComandas = GestaoComandasServiceFactory::create();
}

// REMOVIDO: A função setupUI() inteira é apagada daqui.

void MainWindow::setupConnections() {
    // Conexões dos serviços não mudam
    connect(m_servicoAcesso, &IControleAcessoService::statusLoginAlterado, this, &MainWindow::handleStatusLogin);
    connect(m_servicoSalao, &IGestaoSalaoService::statusMesaAlterado, this, &MainWindow::handleStatusMesa);
    connect(m_servicoComandas, &IGestaoComandasService::comandaAtualizada, this, &MainWindow::handleComandaAtualizada);

    // Conexões dos botões da UI agora usam o ponteiro 'ui'
    // Certifique-se de que os botões tenham esses 'objectName' no Qt Designer
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(ui->logoutButton, &QPushButton::clicked, this, &MainWindow::onLogoutClicked);
    connect(ui->btnAdicionarItem, &QPushButton::clicked, this, &MainWindow::onAdicionarItemClicked);
    connect(ui->btnVoltarSalao, &QPushButton::clicked, this, &MainWindow::onVoltarParaSalaoClicked);
}

void MainWindow::onLoginClicked() {
    // Acessamos os campos de texto através do 'ui'
    if (!m_servicoAcesso->autenticar(ui->loginLineEdit->text(), ui->senhaLineEdit->text())) {
        QMessageBox::warning(this, "Erro", "Usuário ou senha inválidos.");
    }
}

void MainWindow::onLogoutClicked() {
    m_servicoAcesso->logout();
}

void MainWindow::handleStatusLogin(bool logado) {
    if (logado) {
        showSalaoPage();
    } else {
        // Acessamos os campos de texto através do 'ui'
        ui->loginLineEdit->clear();
        ui->senhaLineEdit->clear();
        showLoginPage();
    }
}

void MainWindow::showLoginPage() {
    // Certifique-se de que sua página de login no .ui tenha o objectName 'loginPage'
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
}

void MainWindow::showSalaoPage() {
    popularMesas();
    // Certifique-se de que sua página do salão no .ui tenha o objectName 'salaoPage'
    ui->stackedWidget->setCurrentWidget(ui->salaoPage);
}

void MainWindow::popularMesas() {
    qDeleteAll(m_botoesMesa);
    m_botoesMesa.clear();

    // Limpa o layout antigo antes de adicionar novos botões
    QLayoutItem* item;
    // Certifique-se de que seu GridLayout no .ui tenha o objectName 'layoutMesas'
    while ((item = ui->layoutMesas->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    QList<Mesa> mesas = m_servicoSalao->getMesas();
    int row = 0, col = 0;
    for (const Mesa& mesa : mesas) {
        QPushButton* btn = new QPushButton(mesa.nome);
        btn->setMinimumSize(100, 80);
        m_botoesMesa[mesa.id] = btn;
        handleStatusMesa(mesa.id, mesa.status);

        connect(btn, &QPushButton::clicked, this, [this, id = mesa.id](){
            onMesaClicked(id);
        });

        ui->layoutMesas->addWidget(btn, row, col);
        col++;
        if (col >= 4) { col = 0; row++; }
    }
}

void MainWindow::handleStatusMesa(int idMesa, Mesa::Status novoStatus) {
    if (m_botoesMesa.contains(idMesa)) {
        QString style = "color: white; font-weight: bold;";
        if (novoStatus == Mesa::Livre) {
            style += "background-color: green;";
        } else {
            style += "background-color: red;";
        }
        m_botoesMesa[idMesa]->setStyleSheet(style);
    }
}

void MainWindow::onMesaClicked(int idMesa) {
    showComandaPage(idMesa);
}

void MainWindow::showComandaPage(int idMesa) {
    // Acessamos os widgets através do 'ui'
    // Certifique-se de ter os objectNames 'labelTituloComanda' e 'comandaPage' no .ui
    ui->labelTituloComanda->setText(QString("Gerenciando Comanda da Mesa %1").arg(idMesa));

    Comanda comanda = m_servicoComandas->getComandaPorMesa(idMesa);
    if (!comanda.ativa) {
        comanda = m_servicoComandas->criarComandaParaMesa(idMesa);
    }
    m_comandaAtualId = comanda.id;

    popularCardapio();
    atualizarDisplayComanda(comanda);
    ui->stackedWidget->setCurrentWidget(ui->comandaPage);
}

void MainWindow::popularCardapio() {
    // Acessamos o widget através do 'ui'
    // objectName: cardapioListWidget
    ui->cardapioListWidget->clear();
    QList<ItemCardapio> itens = m_servicoCardapio->getItens();
    for (const auto& item : itens) {
        QString texto = QString("%1 - R$ %2").arg(item.nome).arg(item.preco, 0, 'f', 2);
        QListWidgetItem* listItem = new QListWidgetItem(texto);
        listItem->setData(Qt::UserRole, item.id);
        ui->cardapioListWidget->addItem(listItem);
    }
}

void MainWindow::onAdicionarItemClicked() {
    // Acessamos o widget através do 'ui'
    QListWidgetItem* selected = ui->cardapioListWidget->currentItem();
    if (!selected || m_comandaAtualId == -1) return;

    int idItem = selected->data(Qt::UserRole).toInt();
    m_servicoComandas->adicionarItem(m_comandaAtualId, idItem, 1);
}

void MainWindow::handleComandaAtualizada(const Comanda& comanda) {
    if (comanda.id == m_comandaAtualId) {
        atualizarDisplayComanda(comanda);
    }
}

void MainWindow::atualizarDisplayComanda(const Comanda& comanda) {
    // Acessamos o widget através do 'ui'
    // objectName: comandaListWidget
    ui->comandaListWidget->clear();
    double total = 0.0;
    for (const auto& item : comanda.itens) {
        QString texto = QString("%1x %2 (R$ %3)")
        .arg(item.quantidade)
            .arg(item.nomeProduto)
            .arg(item.precoUnitario * item.quantidade, 0, 'f', 2);
        ui->comandaListWidget->addItem(texto);
        total += item.precoUnitario * item.quantidade;
    }
    ui->comandaListWidget->addItem("");
    ui->comandaListWidget->addItem(QString("TOTAL: R$ %1").arg(total, 0, 'f', 2));
}

void MainWindow::onVoltarParaSalaoClicked() {
    m_comandaAtualId = -1;
    showSalaoPage();
}
