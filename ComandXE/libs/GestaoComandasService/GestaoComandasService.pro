QT -= gui
TARGET = GestaoComandasService
TEMPLATE = lib

DEFINES += GESTAOCOMANDASSERVICE_LIBRARY

SOURCES += \
    GestaoComandasServiceImpl.cpp \

HEADERS += \
    GestaoComandasService_global.h \
    IGestaoComandasService.h \
    GestaoComandasServiceImpl.h \
    GestaoComandasServiceFactory.h

# Include paths para todas as libs dependentes
INCLUDEPATH += \
    $$PWD/../core \
    $$PWD/../GestaoSalaoService \
    $$PWD/../CardapioDigitalService

# Linkagem automática Debug/Release com todas as libs

    LIBS += -L$$PWD/../core -lcore
    LIBS += -L$$PWD/../GestaoSalaoService -lGestaoSalaoService
    LIBS += -L$$PWD/../CardapioDigitalService -lCardapioDigitalService

