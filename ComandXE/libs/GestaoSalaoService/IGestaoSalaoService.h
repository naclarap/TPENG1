#pragma once
#include <QObject>
#include <QList>
#include "GestaoSalaoService_global.h"
#include <Entidades.h>

class GESTAOSALAOSERVICE_EXPORT IGestaoSalaoService : public QObject {
    Q_OBJECT
public:
    explicit IGestaoSalaoService(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IGestaoSalaoService() = default;

    virtual QList<Mesa> getMesas() const = 0;
    virtual bool alterarStatusMesa(int idMesa, Mesa::Status novoStatus) = 0;

signals:
    void statusMesaAlterado(int idMesa, Mesa::Status novoStatus);
};
