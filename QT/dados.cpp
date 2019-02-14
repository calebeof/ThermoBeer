#include "dados.h"

Dados::Dados(QObject *parent) : QObject(parent)
{

}

void Dados::set_name(QString value)
{
name=value;
}

void Dados::set_tipo(QString value)
{
tipo=value;
}

void Dados::set_link(QString value){
    link=value;
}

void Dados::set_levedura(QString value){
    tp_levedura=value;
}

void Dados::set_teor(QString value){
    teor=value;
}

void Dados::set_quantidade(int value){
    quantidade=value;
}


QString Dados::get_name() const
{
 return name;
}

QString Dados::get_link() const
{
 return link;
}

QString Dados::get_teor() const
{
    return teor;
}

bool Dados::envio_levedura(QString value)
{
    QNetworkRequest request((QUrl(value)));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QJsonObject json;
    json.insert("NOMECERVEJA",get_name());
    QNetworkAccessManager thermo;
    QNetworkReply *reply = thermo.post(request, QJsonDocument(json).toJson());
    return true;

}

QString Dados::get_tipo() const
{
 return tipo;
}

QString Dados::get_levedura() const
{
 return tp_levedura;
}

int Dados::get_quantidade() const
{
 return quantidade;
}
