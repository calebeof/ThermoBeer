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

void MainWindow::dados()
{
    auto info=serial.readAll();
    QString temp = data.receberTemp(info);
    qDebug() << temp << endl;
    if(temp!="NULL")
        ui->lcd_temp->display(temp);
}

void MainWindow::on_pb_conectar_clicked()
{
    QString cor="yellow";
    QString status="Conectado";
    serial.setPortName(ui->cbox_serial->currentText());
    serial.setBaudRate(ui->cbox_veloc->currentText().toInt());
    if(serial.open(QIODevice::ReadWrite)){
        ui->lb_status->setText(status);
        ui->lb_status->setStyleSheet("color: "+cor);
    }
    else
     qDebug()<<"Sem sinal";
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
    if(ui->ledit_nome->text().isEmpty()){
        QMessageBox::warning(this,"Dados para cadastro","Insira o nome da cerveja!");
        return;
    }
    if(ui->ledit_link->text().isEmpty()){
        QMessageBox::warning(this,"Dados para cadastro","Insira o link da receita da cerveja!");
        return;
    }
    if(ui->ledit_tipo->text().isEmpty()){
        QMessageBox::warning(this,"Dados para cadastro","Insira o tipo de levedura da cerveja!");
        return;
    }
    if(ui->spbox_qtd->value()==0){
        QMessageBox::warning(this,"Dados para cadastro","Insira a quantidade de cerveja a ser produzida!");
        return;
    }
    if(ui->lev_combo->currentText()=="Escolha uma levedura..."){
        QMessageBox::warning(this,"Dados para cadastro","Insira a levedura da cerveja!");
        return;
    }
    cerveja.setNome(ui->ledit_nome->text());
    cerveja.setLink(ui->ledit_link->text());
    cerveja.setTipo(ui->ledit_tipo->text());
    cerveja.setLevedura(ui->lev_combo->currentText());
    cerveja.setTeor(ui->ledit_teor->text());
    cerveja.setQuantidade(ui->spbox_qtd->value());
    cerveja.setTemp();
    QString nome = QFileDialog::getSaveFileName(this, "lista_cervejas", "", "(*.txt)");
    lista_de_cervejas.addCerveja(cerveja);
    qDebug() << cerveja.getLowTemp() << " " << cerveja.getHighTemp() << endl;
    data.salvarCerveja(cerveja, nome, lista_de_cervejas);
    ui->cb_cerveja->addItem(cerveja.getNome());
    QMessageBox::information(this,"Salvar cadastro","Os dados foram salvos com sucesso!");
    data.envioLevedura("http://thermobeer.herokuapp.com/envio_levedura", cerveja);
    ui->ledit_nome->clear();
    ui->ledit_link->clear();
    ui->ledit_tipo->clear();
 }
void MainWindow::on_btn_mostrar_clicked()
{
    QString texto = ui->cb_cerveja->currentText();
    if(texto!="Escolha uma cerveja..."){
        Cerveja aux = lista_de_cervejas.find(texto);
        cerveja.setNome(aux.getNome());
        cerveja.setLink(aux.getLink());
        cerveja.setTipo(aux.getTipo());
        cerveja.setLevedura(aux.getLevedura());
        cerveja.setTeor(aux.getTeor());
        cerveja.setQuantidade(aux.getQuantidade());
        cerveja.setTemp();
        data.envioLevedura("http://thermobeer.herokuapp.com/envio_levedura", cerveja);
        ui->lb_tipo->setText(aux.getTipo());
        ui->lb_link->setText(aux.getLink());
        ui->lb_levedura->setText(aux.getLevedura());
        ui->lb_qtdprod->setText(QString::number(aux.getQuantidade()));
        ui->lb_teor->setText(aux.getTeor());
    }else
        QMessageBox::information(this, "Mostrar dados","Escolha uma cerveja!");
}

void MainWindow::on_btn_carregar_clicked()
{
    QString nome = QFileDialog::getOpenFileName(this, "lista_cervejas", "", "(*.txt)");
    if(data.carregarCervejas(nome, lista_de_cervejas)){
        for(int i=0; i<lista_de_cervejas.size(); i++)
            ui->cb_cerveja->addItem(lista_de_cervejas[i].getNome());
    }else
       QMessageBox::information(this, "Carregar dados","Não foi possível carregar os dados, tente novamente.");
}
