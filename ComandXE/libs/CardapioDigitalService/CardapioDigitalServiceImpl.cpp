#include "CardapioDigitalServiceImpl.h"
#include "CardapioDigitalServiceFactory.h"

// Singleton da implementação
CardapioDigitalServiceImpl* CardapioDigitalServiceImpl::getInstance() {
    static CardapioDigitalServiceImpl instance;
    return &instance;
}

// Construtor com carga inicial de itens
CardapioDigitalServiceImpl::CardapioDigitalServiceImpl(QObject *parent)
    : ICardapioDigitalService(parent) {
    // Carga estática de itens para a Sprint 1
    m_itens << ItemCardapio{101, "Refrigerante Lata", 5.00};
    m_itens << ItemCardapio{102, "Suco Natural", 8.00};
    m_itens << ItemCardapio{201, "Porção de Batata", 25.00};
    m_itens << ItemCardapio{202, "Hambúrguer", 30.00};
}

// Implementação da interface
QList<ItemCardapio> CardapioDigitalServiceImpl::getItens() const {
    return m_itens;
}


bool CardapioDigitalServiceImpl::getItemPorId(int id, ItemCardapio& item) const {
    for (const auto& i : m_itens) {
        if (i.id == id) {
            item = i;
            return true;
        }
    }
    return false;
}

// =======================================================
// Implementação da Fábrica
// =======================================================
ICardapioDigitalService* CardapioDigitalServiceFactory::create() {
    return CardapioDigitalServiceImpl::getInstance();
}

