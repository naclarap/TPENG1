QT -= gui
TARGET = ControleAcessoService
TEMPLATE = lib

DEFINES += CONTROLEACESSOSERVICE_LIBRARY

SOURCES += \
    ControleAcessoServiceImpl.cpp

HEADERS += \
    ControleAcessoService_global.h \
    IControleAcessoService.h \
    ControleAcessoServiceImpl.h \
    ControleAcessoServiceFactory.h

# Onde encontrar os cabeçalhos de 'core'
INCLUDEPATH += $$PWD/../core

# Onde encontrar a lib compilada de 'core'
LIBS += -L$$PWD/../core -lcore
