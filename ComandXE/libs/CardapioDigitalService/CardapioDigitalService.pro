QT -= gui
TARGET = CardapioDigitalService
TEMPLATE = lib

DEFINES += CARDAPIODIGITALSERVICE_LIBRARY

# Adicione o .cpp da implementação aqui
SOURCES += \
    CardapioDigitalServiceImpl.cpp

# Garanta que todos os SEUS arquivos .h estejam listados aqui
HEADERS += \
    CardapioDigitalService_global.h \
    ICardapioDigitalService.h \
    CardapioDigitalServiceImpl.h \
    CardapioDigitalServiceFactory.h

# Links para a biblioteca 'core'
INCLUDEPATH += $$PWD/../core
LIBS += -L$$PWD/../core -lcore
