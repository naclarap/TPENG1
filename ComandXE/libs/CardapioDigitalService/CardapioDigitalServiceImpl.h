// libs/CardapioDigitalService/CardapioDigitalServiceImpl.h

#pragma once

#include "ICardapioDigitalService.h"
#include <QList>

class CardapioDigitalServiceImpl : public ICardapioDigitalService {
    Q_OBJECT

public:
    static CardapioDigitalServiceImpl* getInstance();

    // Métodos da interface que serão implementados no .cpp
    QList<ItemCardapio> getItens() const override;
    bool getItemPorId(int id, ItemCardapio& item) const override;

private:
    // O construtor é privado para forçar o uso do Singleton (getInstance)
    CardapioDigitalServiceImpl(QObject *parent = nullptr);
    ~CardapioDigitalServiceImpl() override = default;

    // Proibir cópia
    CardapioDigitalServiceImpl(const CardapioDigitalServiceImpl&) = delete;
    CardapioDigitalServiceImpl& operator=(const CardapioDigitalServiceImpl&) = delete;

    // Membro onde os dados do cardápio serão guardados
    QList<ItemCardapio> m_itens;
};
