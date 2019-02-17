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
    if(tp_levedura == "Abbaye"){
        hightemp = 25;
        lowtemp = 17;
    } else if(tp_levedura == "Belle Saison"){
        hightemp = 35;
        lowtemp = 15;
    } else if(tp_levedura == "BRY-97"){
        hightemp = 22;
        lowtemp = 15;
    } else if(tp_levedura == "Diamond"){
        hightemp = 15;
        lowtemp = 10;
    } else if(tp_levedura == "Munich"){
        hightemp = 22;
        lowtemp = 17;
    } else if(tp_levedura == "Nottingham"){
        hightemp = 22;
        lowtemp = 10;
    } else if(tp_levedura == "Windsor"){
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
