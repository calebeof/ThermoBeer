#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     QSerialPort serial;



private slots:
     void dados();
     void on_pb_conectar_clicked();

     void on_pb_reiniciar_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
