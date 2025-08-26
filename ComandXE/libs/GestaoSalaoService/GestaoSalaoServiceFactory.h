#pragma once
#include "IGestaoSalaoService.h"
#include "GestaoSalaoServiceImpl.h"
#include "GestaoSalaoService_global.h"

class GESTAOSALAOSERVICE_EXPORT GestaoSalaoServiceFactory {
public: static IGestaoSalaoService* create() {
        return GestaoSalaoServiceImpl::getInstance(); }
};
