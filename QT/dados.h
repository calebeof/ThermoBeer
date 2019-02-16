#ifndef DADOS_H
#define DADOS_H

#include <QString>
#include <QNetworkRequest>
#include <cerveja.h>


class Dados
{
private:
    QString concat;
    bool first_barra = false;
public:
    Dados();
    void envioLevedura(QString value, Cerveja cerveja);
    QString receberTemp(QString info);
};

#endif // DADOS_H
