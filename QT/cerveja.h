#ifndef CERVEJA_H
#define CERVEJA_H

#include <QObject>
#include <QtNetwork>

class Cerveja
{
private:
    QString nome;
    QString tipo;
    QString link;
    QString tp_levedura;
    int quantidade;
    int lowtemp;
    int hightemp;
    QString teor;
public:
    explicit Cerveja();
    void setNome(QString value);
    void setTipo(QString value);
    void setLink(QString value);
    void setLevedura(QString value);
    void setQuantidade(int value);
    void setTeor(QString value);
    void setTemp();
    int getLowTemp();
    int getHighTemp();
    QString getNome()const;
    QString getTipo()const;
    QString getLink()const;
    QString getLevedura()const;
    int getQuantidade()const;
    QString getTeor()const;
    bool envioLevedura(QString value);

signals:

public slots:
};

#endif // CERVEJA_H
