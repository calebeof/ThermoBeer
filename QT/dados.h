#ifndef DADOS_H
#define DADOS_H

#include <QString>
#include <QNetworkRequest>
#include <cerveja.h>
#include <cervejas.h>
#include <QFileDialog>
#include <QFile>

class Dados
{
private:
    QString concat;
    bool first_barra = false;
public:
    Dados();
    void envioLevedura(QString value, Cerveja cerveja);
    QString receberTemp(QString info);
    void salvarCerveja(Cerveja cerveja, QString nome, Cervejas &lista_cervejas);
    bool carregarCervejas(QString nome, Cervejas &lista_de_cervejas);
};

#endif // DADOS_H
