#include "dados.h"

Dados::Dados()
{
    first_barra = false;
}

QString Dados::receberTemp(QString info)
{
    QString valor;
    if(info.contains("{") and concat.isEmpty() and !first_barra){
        concat+=info;
        first_barra = true;
    }
    if(!info.contains("{") and first_barra)
        concat+=info;
    if(info.contains("}") and !concat.isEmpty() and first_barra){
        concat+=info;
        first_barra = false;
        for(int i=0; i<concat.size() and valor.size()<5; i++){
            if(concat[i]>='0' and concat[i]<='9' or concat[i]=='.')
                valor+=concat[i];
        }
        concat.clear();
    }
    if(valor.size()==5)
        return valor;
    return "NULL";
}

void Dados::envioLevedura(QString value, Cerveja cerveja)
{
    QNetworkRequest request((QUrl(value)));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QJsonObject json;
    json.insert("NOMECERVEJA",cerveja.getNome());
    json.insert("TIPOCERVEJA",cerveja.getTipo());
    json.insert("LEVEDURA",cerveja.getLevedura());
    json.insert("LOWTEMP",cerveja.getLowTemp());
    json.insert("HIGHTEMP",cerveja.getHighTemp());

    QNetworkAccessManager thermo;
    QNetworkReply *reply = thermo.post(request, QJsonDocument(json).toJson());

    while(!reply->isFinished())
        qApp->processEvents();
}
