#pragma once

#include <QObject>
#include <QList>
#include "CardapioDigitalService_global.h"   // tem que ser exatamente esse nome!
#include "Entidades.h"

class CARDAPIODIGITALSERVICE_EXPORT ICardapioDigitalService : public QObject {
    Q_OBJECT
public:
    explicit ICardapioDigitalService(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~ICardapioDigitalService() = default;

    virtual QList<ItemCardapio> getItens() const = 0;
    virtual bool getItemPorId(int id, ItemCardapio& item) const = 0;
};
