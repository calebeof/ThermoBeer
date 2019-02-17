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
    qDebug() << valor << endl;
    if(valor.size()==5)
        return valor;
    return "NULL";
}

void Dados::salvarCerveja(Cerveja cerveja, QString nome, Cervejas lista_cervejas)
{

    QFile arquivo(nome);
    arquivo.open(QIODevice::WriteOnly);
    QTextStream out(&arquivo);
    for(int i=0; i<lista_cervejas.size(); i++){
        out<<"Nome: "<<lista_cervejas[i].getNome()<<endl;
        out<<"Tipo: "<<lista_cervejas[i].getTipo()<<endl;
        out<<"Link: "<<lista_cervejas[i].getLink()<<endl;
        out<<"Levedura: "<<lista_cervejas[i].getLevedura()<<endl;
        out<<"Quantidade produzida: "<<lista_cervejas[i].getQuantidade()<<endl;
        out<<"Teor alcoolico: "<<lista_cervejas[i].getTeor()<<endl;
    }
    out << endl;
    arquivo.close();
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
