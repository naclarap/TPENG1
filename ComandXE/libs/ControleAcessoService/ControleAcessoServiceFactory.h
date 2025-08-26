#pragma once
#include "IControleAcessoService.h"
#include "ControleAcessoServiceImpl.h"
#include "ControleAcessoService_global.h"

class CONTROLEACESSOSERVICE_EXPORT ControleAcessoServiceFactory {
public:
    static IControleAcessoService* create() {
        return ControleAcessoServiceImpl::getInstance();
    }
};
