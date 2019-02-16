#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <cerveja.h>
#include <dados.h>
#include<QVariantMap>
#include <QtNetwork>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Cerveja cerveja;
    Dados data;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     QSerialPort serial;



private slots:
     void dados();
     void on_pb_conectar_clicked();

     void on_pb_reiniciar_clicked();
     void on_save_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
