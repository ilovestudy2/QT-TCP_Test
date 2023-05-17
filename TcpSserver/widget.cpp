#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    tcpServer = new QTcpServer(this);
    tcpSocket = new QTcpSocket(this);


    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newConnection_Slot()));
}


void Widget::newConnection_Slot()
{
     tcpSocket = tcpServer->nextPendingConnection();
     connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead_Slot()));


}

void Widget:: readyRead_Slot()
{
    QString buf;

    buf = tcpSocket->readAll();

    ui->recvEdit->appendPlainText(buf);

}
Widget::~Widget()
{
    delete ui;
}

void Widget::on_openBt_clicked()
{
   tcpServer->listen(QHostAddress::Any,ui->portEdit->text().toUInt());
}

void Widget::on_closeBt_clicked()
{
    tcpServer->close();
}

void Widget::on_pushButton_3_clicked()
{
    tcpSocket->write(ui->sendEdit->text().toLocal8Bit().data());
}
