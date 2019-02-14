#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&serial, SIGNAL(readyRead()),this,SLOT(dados()));
    for(auto& item : QSerialPortInfo::availablePorts()){
     ui->cbox_serial->addItem(item.portName());
    }

    for(auto& item : QSerialPortInfo::standardBaudRates()){
     ui->cbox_veloc->addItem(QString::number(item) );
}
}

MainWindow::~MainWindow()
{
    serial.close();
    delete ui;
}

bool first_barra = false;
QString concat;
void MainWindow::dados()
{
    auto info=serial.readAll();
    QString valor;
    qDebug() << info << endl;
    if(info.contains("{") and concat.isEmpty() and !first_barra){
        concat+=info;
        first_barra = true;
    }
    if(!info.contains("{") and first_barra)
        concat+=info;
    if(info.contains("}") and !concat.isEmpty() and first_barra){
        concat+=info;
        first_barra = false;
        qDebug() << concat << endl;
        for(int i=0; i<concat.size() and valor.size()<5; i++){
            if(concat[i]>='0' and concat[i]<='9' or concat[i]=='.')
                valor+=concat[i];
        }
        concat.clear();
    }
    //auto inform = QJsonDocument::fromJson(info).object().toVariantMap();
    if(valor.size()==5)
            ui->lcd_temp->display(valor);
    /*if(inform.contains("T1")){
        ui->lcd_temp->display(inform["T1"].toString());
        qDebug()<<"entrei";
    }
    if(inform.contains("STATUS"))
        ui->lb_status->setText(inform["STATUS"].toString());*/
    /*for (QVariantMap::const_iterator iter = inform.begin(); iter!=inform.end(); iter++)
        qDebug() << iter.key() << " " << iter.value() << endl;*/
}

void MainWindow::on_pb_conectar_clicked()
{
    QString cor="yellow";
    QString status="Conectado";
     serial.setPortName(ui->cbox_serial->currentText());
     serial.setBaudRate(ui->cbox_veloc->currentText().toInt());
     qDebug() << serial.portName() << " " << serial.baudRate() << endl;
    if(serial.open(QIODevice::ReadOnly)){
        ui->lb_status->setText(status);
        ui->lb_status->setStyleSheet("color: "+cor);
    }
    else {
     qDebug()<<"Sem sinal";
    }
}



void MainWindow::on_pb_reiniciar_clicked()
{
    serial.clear();
    ui->cbox_serial->clearEditText();
    ui->cbox_veloc->clearEditText();
    QString cor_2="red";
    QString status_2="Aguardando Conexão...";
    ui->lb_status->setText(status_2);
    ui->lb_status->setStyleSheet("color: "+cor_2);
}






void MainWindow::on_save_button_clicked()
{
    levedura.set_name(ui->ledit_nome->text());
    levedura.set_link(ui->ledit_link->text());
    levedura.set_tipo(ui->ledit_tipo->text());
    levedura.set_levedura(ui->lev_combo->currentText());
    levedura.set_teor(ui->lb_teor->text());
    levedura.set_quantidade(ui->spbox_qtd->value());


    QString lev=QFileDialog::getSaveFileName(this,"levedura","","Texto Puro(*.txt)");
    QFile arquivo(lev);
    arquivo.open(QIODevice::WriteOnly);
    QTextStream out(&arquivo);
    out<<"Nome: "<<levedura.get_name()<<endl;
    out<<"Tipo: "<<levedura.get_tipo()<<endl;
    out<<"Link: "<<levedura.get_link()<<endl;
    out<<"Levedura: "<<levedura.get_levedura()<<endl;
    out<<"Quantidade produzida: "<<levedura.get_quantidade()<<endl;
    out<<"Teor alcoolico: "<<levedura.get_teor()<<endl;
    arquivo.close();
    QMessageBox::information(this,"Salvar cadastro","Os dados foram salvos com sucesso!");
    levedura.envio_levedura("http://thermobeer.herokuapp.com/envio_levedura");
    ui->ledit_nome->clear();
    ui->ledit_link->clear();
    ui->ledit_tipo->clear();


  }

