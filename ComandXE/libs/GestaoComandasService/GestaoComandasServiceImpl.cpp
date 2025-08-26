#include "GestaoComandasServiceImpl.h"
// Adicionamos o include da Fábrica aqui
#include "GestaoComandasServiceFactory.h"
#include <CardapioDigitalServiceFactory.h>
#include <GestaoSalaoServiceFactory.h>
#include <QDateTime>

GestaoComandasServiceImpl* GestaoComandasServiceImpl::getInstance() {
    static GestaoComandasServiceImpl instance;
    return &instance;
}

GestaoComandasServiceImpl::GestaoComandasServiceImpl(QObject* parent)
    : IGestaoComandasService(parent) {
    // Injeção de dependência via Singleton/Factory no construtor
    m_servicoCardapio = CardapioDigitalServiceFactory::create();
    m_servicoSalao = GestaoSalaoServiceFactory::create();
}

Comanda GestaoComandasServiceImpl::criarComandaParaMesa(int idMesa) {
    // Verifica se já existe comanda ativa para a mesa
    for(const auto& cmd : m_comandasAtivas) {
        if (cmd.idMesa == idMesa && cmd.ativa) {
            return cmd;
        }
    }

    Comanda novaComanda;
    novaComanda.id = m_proximoId++;
    novaComanda.idMesa = idMesa;
    novaComanda.abertura = QDateTime::currentDateTime();
    novaComanda.ativa = true;
    m_comandasAtivas[novaComanda.id] = novaComanda;

    m_servicoSalao->alterarStatusMesa(idMesa, Mesa::Ocupada);
    emit comandaAtualizada(novaComanda);
    return novaComanda;
}

bool GestaoComandasServiceImpl::adicionarItem(int idComanda, int idItemCardapio, int quantidade) {
    if (!m_comandasAtivas.contains(idComanda)) {
        return false;
    }

    ItemCardapio item;
    if (!m_servicoCardapio->getItemPorId(idItemCardapio, item)) {
        return false;
    }

    Comanda& comanda = m_comandasAtivas[idComanda];
    comanda.itens.append({item.id, item.nome, quantidade, item.preco});
    emit comandaAtualizada(comanda);
    return true;
}

Comanda GestaoComandasServiceImpl::getComandaPorId(int idComanda) const {
    return m_comandasAtivas.value(idComanda);
}

Comanda GestaoComandasServiceImpl::getComandaPorMesa(int idMesa) const {
    for(const auto& cmd : m_comandasAtivas) {
        if (cmd.idMesa == idMesa && cmd.ativa) {
            return cmd;
        }
    }
    return Comanda(); // Retorna comanda inválida/inativa
}

// =======================================================
// A IMPLEMENTAÇÃO DA FÁBRICA QUE FALTAVA VAI AQUI EMBAIXO
// =======================================================
IGestaoComandasService* GestaoComandasServiceFactory::create() {
    return GestaoComandasServiceImpl::getInstance();
}
