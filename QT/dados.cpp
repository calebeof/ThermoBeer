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

void Dados::salvarCerveja(Cerveja cerveja, QString nome, Cervejas &lista_cervejas)
{

    QFile arquivo(nome);
    arquivo.open(QIODevice::WriteOnly);
    QTextStream out(&arquivo);
    for(int i=0; i<lista_cervejas.size(); i++){
        out<<lista_cervejas[i].getNome();
        out<<"," <<lista_cervejas[i].getTipo();
        out<<","<<lista_cervejas[i].getLink();
        out<<","<<lista_cervejas[i].getLevedura();
        out<<","<<lista_cervejas[i].getQuantidade();
        out<<","<<lista_cervejas[i].getTeor();
        out << endl;
    }
    arquivo.close();
}

bool Dados::carregarCervejas(QString nome, Cervejas &lista_de_cervejas)
{
    QFile file(nome);
    if(!file.open(QIODevice::ReadOnly))
        return false;
    QTextStream in(&file);
    QString line;
    while(in.readLineInto(&line)){
        QStringList data = line.split(",");
        Cerveja aux;
        if(data.size()==6){
            aux.setNome(data[0]);
            aux.setTipo(data[1]);
            aux.setLink(data[2]);
            aux.setLevedura(data[3]);
            aux.setQuantidade(data[4].toInt());
            aux.setTeor(data[5]);
            lista_de_cervejas.addCerveja(aux);
        }
     }
     file.close();
     return true;
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
