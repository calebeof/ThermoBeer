#ifndef CERVEJAS_H
#define CERVEJAS_H

#include <QVector>
#include "cerveja.h"

class Cervejas
{
private:
    QVector<Cerveja> lista_cervejas;
public:
    Cervejas();
    Cerveja operator[](int i);
    void addCerveja(Cerveja a);
    QVector<Cerveja> getListaCervejas();
    int size();
    Cerveja find(QString nome);
};

#endif // CERVEJAS_H
