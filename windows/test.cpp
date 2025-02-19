#include "test.h"
#include "ui_test.h"



test::test(Client *serv,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::test)
{
    ui->setupUi(this);
    this->server = serv;
}

test::~test()
{
    delete ui;
}

void test::on_pushButton_2_clicked()
{
    QTcpSocket *soc = this->server->getSocket();
    QString ip = "127.0.0.1";
    QString message = "b1 click";
    quint16 port = 8000;
    Point p;
    p.x = 1;
    p.y = 2;
    p.couleur = "green";
    p.taille = 3;
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    quint8 type = 0x01;
    stream << type;  
    stream << p;
    soc->write(data);
    soc->flush();
    soc->waitForBytesWritten(1000);
}


void test::on_pushButton_clicked()
{
    QTcpSocket *soc = this->server->getSocket();
    QString ip = "127.0.0.1";
    QString message = "b1 click";
    quint16 port = 8000;
    Curseur p;
    p.x = 1;
    p.y = 2;
    p.id = 3;
    p.couleur = "red";
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    quint8 type = 0x02;
    stream << type;
    stream << p;
    soc->write(data);
    soc->flush();
    soc->waitForBytesWritten(1000);
}

