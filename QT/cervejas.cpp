#include "cervejas.h"

Cervejas::Cervejas()
{

}

void Cervejas::addCerveja(Cerveja a)
{
    lista_cervejas.push_back(a);
}

int Cervejas::size()
{
    return lista_cervejas.size();
}

Cerveja Cervejas::find(QString nome)
{
    for(int i=0; i<lista_cervejas.size(); i++){
        if(lista_cervejas[i].getNome()==nome)
            return lista_cervejas[i];
    }
}

Cerveja Cervejas::operator[](int i)
{
    return lista_cervejas[i];
}
