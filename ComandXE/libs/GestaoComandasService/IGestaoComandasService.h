#pragma once
#include <QObject>
#include "GestaoComandasService_global.h"
#include <Entidades.h>

class GESTAOCOMANDASSERVICE_EXPORT IGestaoComandasService : public QObject {
    Q_OBJECT
public:
    // LINHA ADICIONADA: Construtor explícito
    explicit IGestaoComandasService(QObject *parent = nullptr) : QObject(parent) {}

    virtual ~IGestaoComandasService() = default;
    virtual Comanda criarComandaParaMesa(int idMesa) = 0;
    virtual bool adicionarItem(int idComanda, int idItemCardapio, int quantidade) = 0;
    virtual Comanda getComandaPorId(int idComanda) const = 0;
    virtual Comanda getComandaPorMesa(int idMesa) const = 0;

signals:
    void comandaAtualizada(const Comanda& comanda);
};
