#ifndef DADOS_H
#define DADOS_H

#include <QObject>
#include <QtNetwork>

class Dados : public QObject
{
private:
    QString name;
    QString tipo;
    QString link;
    QString tp_levedura;
    int quantidade;
    QString teor;
    Q_OBJECT
public:
    explicit Dados(QObject *parent = nullptr);
    void set_name(QString value);
    void set_tipo(QString value);
    void set_link(QString value);
    void set_levedura(QString value);
    void set_quantidade(int value);
    void set_teor(QString value);
    QString get_name()const;
    QString get_tipo()const;
    QString get_link()const;
    QString get_levedura()const;
    int get_quantidade()const;
    QString get_teor()const;
    bool envio_levedura(QString value);

signals:

public slots:
};

#endif // DADOS_H
