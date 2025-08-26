QT -= gui
TARGET = GestaoSalaoService
TEMPLATE = lib

DEFINES += GESTAOSALAOSERVICE_LIBRARY

SOURCES += GestaoSalaoServiceImpl.cpp


HEADERS += \
    GestaoSalaoService_global.h \
    IGestaoSalaoService.h \
    GestaoSalaoServiceImpl.h \
    GestaoSalaoServiceFactory.h

# Include da dependência core
INCLUDEPATH += $$PWD/../core

# Linkagem automática Debug/Release com a lib core

LIBS += -L$$PWD/../core -lcore

