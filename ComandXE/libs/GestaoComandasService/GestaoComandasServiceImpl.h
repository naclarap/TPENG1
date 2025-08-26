#pragma once

#include "IGestaoComandasService.h"
#include <QMap>
#include <ICardapioDigitalService.h>
#include <IGestaoSalaoService.h>

class GestaoComandasServiceImpl : public IGestaoComandasService {
    Q_OBJECT

public:
    static GestaoComandasServiceImpl* getInstance();

    // Métodos da interface
    Comanda criarComandaParaMesa(int idMesa) override;
    bool adicionarItem(int idComanda, int idItemCardapio, int quantidade) override;
    Comanda getComandaPorId(int idComanda) const override;
    Comanda getComandaPorMesa(int idMesa) const override;

private:
    GestaoComandasServiceImpl(QObject* parent = nullptr);
    ~GestaoComandasServiceImpl() override = default;
    GestaoComandasServiceImpl(const GestaoComandasServiceImpl&) = delete;
    GestaoComandasServiceImpl& operator=(const GestaoComandasServiceImpl&) = delete;

    QMap<int, Comanda> m_comandasAtivas;
    int m_proximoId = 1;

    // Dependências de outros serviços
    ICardapioDigitalService* m_servicoCardapio;
    IGestaoSalaoService* m_servicoSalao;
};
