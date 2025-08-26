TEMPLATE = subdirs

SUBDIRS += \
    core \
    ControleAcessoService \
    GestaoSalaoService \
    CardapioDigitalService \
    GestaoComandasService

# Dependências entre libs
ControleAcessoService.depends = core
GestaoSalaoService.depends = core
CardapioDigitalService.depends = core
GestaoComandasService.depends = core GestaoSalaoService CardapioDigitalService
