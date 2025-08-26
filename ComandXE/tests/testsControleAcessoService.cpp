#include <QtTest>
#include <QObject>

#include "IControleAcessoService.h"
#include "ControleAcessoServiceFactory.h"

class TestControleAcessoService : public QObject
{
    Q_OBJECT

public:
    TestControleAcessoService();
    ~TestControleAcessoService();

private slots:
    void testeDeAutenticacao_data();
    void testeDeAutenticacao();
};

TestControleAcessoService::TestControleAcessoService() {
    // setup opcional
}

TestControleAcessoService::~TestControleAcessoService() {
    // cleanup opcional
}

void TestControleAcessoService::testeDeAutenticacao_data()
{
    QTest::addColumn<QString>("usuario");
    QTest::addColumn<QString>("senha");
    QTest::addColumn<bool>("resultadoEsperado");

    QTest::newRow("login correto") << "garcom" << "123" << true;
    QTest::newRow("login com casing errado") << "Garcom" << "123" << true;
    QTest::newRow("senha incorreta") << "garcom" << "senhaerrada" << false;
    QTest::newRow("usuario incorreto") << "usuariox" << "123" << false;
    QTest::newRow("ambos incorretos") << "ninguem" << "senha" << false;
}

void TestControleAcessoService::testeDeAutenticacao()
{
    QFETCH(QString, usuario);
    QFETCH(QString, senha);
    QFETCH(bool, resultadoEsperado);

    // Usa a factory para criar a instância
    IControleAcessoService* servico = ControleAcessoServiceFactory::create();

    bool resultadoReal = servico->autenticar(usuario, senha);
    servico->logout();

    QCOMPARE(resultadoReal, resultadoEsperado);
}

QTEST_APPLESS_MAIN(TestControleAcessoService)

// ⚠️ Tem que bater com o nome do arquivo real .cpp
#include "TestControleAcessoService.moc"

