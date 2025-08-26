#pragma once

#include <QString>
#include <QList>
#include <QDateTime>
#include "core_global.h"

struct CORE_EXPORT Usuario {
    int id;
    QString login;
    QString nome;
};

struct CORE_EXPORT ItemCardapio {
    int id;
    QString nome;
    double preco;
};

struct CORE_EXPORT Mesa {
    enum Status { Livre, Ocupada };
    int id;
    QString nome;
    Status status;
};

struct CORE_EXPORT ItemComanda {
    int idItemCardapio;
    QString nomeProduto;
    int quantidade;
    double precoUnitario;
};

struct CORE_EXPORT Comanda {
    int id;
    int idMesa;
    QDateTime abertura;
    QList<ItemComanda> itens;
    bool ativa = false;
};
