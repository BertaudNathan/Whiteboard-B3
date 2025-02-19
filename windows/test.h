#ifndef TEST_H
#define TEST_H

#include <QMainWindow>
#include <QTcpSocket>
#include "../models/serveurtcp.h"
#include "../models/point.h"
#include "../models/curseur.h"
#include "../models/client.h"
namespace Ui {
class test;
}



class test : public QMainWindow
{
    Q_OBJECT

public:
    explicit test(Client *serv, QWidget *parent = nullptr);
    ~test();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::test *ui;
    Client *server;
};

#endif // TEST_H
