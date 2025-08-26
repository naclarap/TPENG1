// libs/CardapioDigitalService/CardapioDigitalServiceFactory.h

#pragma once

#include "ICardapioDigitalService.h"
#include "cardapiodigitalservice_global.h"
#include "CardapioDigitalServiceFactory.h"

// Esta classe serve como uma "fábrica" para criar o serviço.
class CARDIAPIODIGITALSERVICE_EXPORT CardapioDigitalServiceFactory {
public:
    // O método estático que a aplicação vai chamar para obter o serviço
    static ICardapioDigitalService* create();
};
