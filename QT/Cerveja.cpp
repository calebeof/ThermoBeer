#include "cerveja.h"

Cerveja::Cerveja()
{

}

void Cerveja::setNome(QString value)
{
    nome=value;
}

void Cerveja::setTipo(QString value)
{
    tipo=value;
}

void Cerveja::setLink(QString value){
    link=value;
}

void Cerveja::setLevedura(QString value){
    tp_levedura=value;
}

void Cerveja::setTeor(QString value){
    teor=value;
}

void Cerveja::setTemp()
{
    if(getLevedura() == "Abbaye"){
        hightemp = 25;
        lowtemp = 17;
    } else if(getLevedura() == "Belle Saison"){
        hightemp = 35;
        lowtemp = 15;
    } else if(getLevedura() == "BRY-97"){
        hightemp = 22;
        lowtemp = 15;
    } else if(getLevedura() == "Diamond"){
        hightemp = 15;
        lowtemp = 10;
    } else if(getLevedura() == "Munich"){
        hightemp = 22;
        lowtemp = 17;
    } else if(getLevedura() == "Nottingham"){
        hightemp = 22;
        lowtemp = 10;
    } else if(getLevedura() == "Windsor"){
        hightemp = 22;
        lowtemp = 15;
    }
}

int Cerveja::getLowTemp()
{
    return lowtemp;
}

int Cerveja::getHighTemp()
{
    return hightemp;
}

void Cerveja::setQuantidade(int value){
    quantidade=value;
}

QString Cerveja::getNome() const
{
 return nome;
}


QString Cerveja::getLink() const
{
 return link;
}

QString Cerveja::getTeor() const
{
    return teor;
}


QString Cerveja::getTipo() const
{
 return tipo;
}

QString Cerveja::getLevedura() const
{
 return tp_levedura;
}

int Cerveja::getQuantidade() const
{
 return quantidade;
}
