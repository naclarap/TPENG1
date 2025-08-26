#pragma once

#include <QMainWindow>
#include <QMap>

// Os includes de widgets individuais não são mais estritamente necessários aqui,
// mas podem ser mantidos para conveniência.
#include <QStackedWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QListWidget>
#include <QLabel>

// Includes dos serviços permanecem os mesmos
#include <IControleAcessoService.h>
#include <IGestaoSalaoService.h>
#include <ICardapioDigitalService.h>
#include <IGestaoComandasService.h>

// ADICIONADO: Declaração necessária para o ponteiro 'ui'
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slots permanecem os mesmos
    void onLoginClicked();
    void onLogoutClicked();
    void onMesaClicked(int idMesa);
    void onAdicionarItemClicked();
    void onVoltarParaSalaoClicked();

    void handleStatusLogin(bool logado);
    void handleStatusMesa(int idMesa, Mesa::Status novoStatus);
    void handleComandaAtualizada(const Comanda& comanda);

private:
    // MÉTODOS PRIVADOS:
    // void setupUI(); // REMOVIDO: A UI agora é criada pelo Qt Designer

    // Estes métodos permanecem
    void setupServices();
    void setupConnections();
    void showLoginPage();
    void showSalaoPage();
    void showComandaPage(int idMesa);
    void popularMesas();
    void popularCardapio();
    void atualizarDisplayComanda(const Comanda& comanda);

    // MEMBROS:
    // ADICIONADO: Ponteiro único para a interface gráfica do Qt Designer
    Ui::MainWindow *ui;

    // Ponteiros de serviço permanecem os mesmos
    IControleAcessoService* m_servicoAcesso;
    IGestaoSalaoService* m_servicoSalao;
    ICardapioDigitalService* m_servicoCardapio;
    IGestaoComandasService* m_servicoComandas;

    // REMOVIDO: A longa lista de ponteiros de widgets foi removida.
    // Eles agora são acessados através do ponteiro 'ui' (ex: ui->loginLineEdit)

    // A lógica de controle ainda precisa destes membros:
    QMap<int, QPushButton*> m_botoesMesa;
    int m_comandaAtualId = -1;
};
