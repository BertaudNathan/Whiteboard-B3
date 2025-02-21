#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
    FormulaireConnexion *form = new FormulaireConnexion(this);
    form->show();
    if (form->exec() == QDialog::Accepted) {
        qDebug() << "on ferme derriere";
        if (form->getClient()->getSocket()->isOpen()) {
        test *t = new test(form->getClient(),this);
        t->show();
        hide();
        }
    } else {
        qDebug() << "on ferme pas";
    }
}


void MainWindow::on_pushButton_clicked()
{
   Board *board = new Board(this);
   board->show(); 
}

void MainWindow::on_pushButton_2_clicked()
{
    FormulaireHebergement *form = new FormulaireHebergement(this);
    form->show();
}
