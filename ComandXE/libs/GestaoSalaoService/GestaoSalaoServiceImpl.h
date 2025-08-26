#pragma once

#include "GestaoSalaoService_global.h"  // deve vir primeiro
#include "IGestaoSalaoService.h"
#include <QList>
#include "Entidades.h" // se 'Mesa' estiver aqui

class GESTAOSALAOSERVICE_EXPORT GestaoSalaoServiceImpl : public IGestaoSalaoService {
    Q_OBJECT
public:
    static GestaoSalaoServiceImpl* getInstance();
    QList<Mesa> getMesas() const override;
    bool alterarStatusMesa(int idMesa, Mesa::Status novoStatus) override;

private:
    GestaoSalaoServiceImpl(QObject *parent = nullptr);
    QList<Mesa> m_mesas;
};
