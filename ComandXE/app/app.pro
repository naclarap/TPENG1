FORMS += mainwindow.ui \
    mainwindow.ui
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ComandXApp
TEMPLATE = app

SOURCES += \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h

# Path para encontrar os headers de todas as libs
INCLUDEPATH += $$PWD/../libs/core
INCLUDEPATH += $$PWD/../libs/ControleAcessoService
INCLUDEPATH += $$PWD/../libs/GestaoSalaoService
INCLUDEPATH += $$PWD/../libs/CardapioDigitalService
INCLUDEPATH += $$PWD/../libs/GestaoComandasService

# Path para encontrar os arquivos .dll/.so e linkar com eles
LIBS += -L$$PWD/../libs/core -lcore
LIBS += -L$$PWD/../libs/ControleAcessoService -lControleAcessoService
LIBS += -L$$PWD/../libs/GestaoSalaoService -lGestaoSalaoService
LIBS += -L$$PWD/../libs/CardapioDigitalService -lCardapioDigitalService
LIBS += -L$$PWD/../libs/GestaoComandasService -lGestaoComandasService
