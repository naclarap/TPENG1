#pragma once
#include "IGestaoComandasService.h"
#include "GestaoComandasService_global.h"
class GESTAOCOMANDASSERVICE_EXPORT GestaoComandasServiceFactory {
public: static IGestaoComandasService* create();
};
