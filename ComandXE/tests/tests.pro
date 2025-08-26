QT += testlib core
QT -= gui

TARGET = tst_comandx
TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle

SOURCES += \
    testsControleAcessoService.cpp

# Caminhos de includes
INCLUDEPATH += $$PWD/../app
INCLUDEPATH += $$PWD/../libs/core
INCLUDEPATH += $$PWD/../libs/ControleAcessoService/Headers
INCLUDEPATH += $$PWD/../libs/GestaoSalaoService/Headers
INCLUDEPATH += $$PWD/../libs/CardapioDigitalService/Headers
INCLUDEPATH += $$PWD/../libs/GestaoComandasService/Headers

# Linka bibliotecas
LIBS += -L$$OUT_PWD/../libs/core -lcore
LIBS += -L$$OUT_PWD/../libs/ControleAcessoService -lControleAcessoService
LIBS += -L$$OUT_PWD/../libs/GestaoSalaoService -lGestaoSalaoService
LIBS += -L$$OUT_PWD/../libs/CardapioDigitalService -lCardapioDigitalService
LIBS += -L$$OUT_PWD/../libs/GestaoComandasService -lGestaoComandasService

# Para testar a MainWindow
PRE_TARGETDEPS += $$OUT_PWD/../app/libComandXApp.a
LIBS += -L$$OUT_PWD/../app -lComandXApp
