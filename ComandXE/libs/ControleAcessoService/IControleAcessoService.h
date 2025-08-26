#pragma once
#include <QObject>
#include <QString>
#include "ControleAcessoService_global.h"
#include <Entidades.h>

class CONTROLEACESSOSERVICE_EXPORT IControleAcessoService : public QObject {
    Q_OBJECT
public:
    explicit IControleAcessoService(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IControleAcessoService() = default;

    virtual bool autenticar(const QString& login, const QString& senha) = 0;
    virtual void logout() = 0;
    virtual bool isLogado() const = 0;
    virtual Usuario usuarioLogado() const = 0;

signals:
    void statusLoginAlterado(bool logado);
};
