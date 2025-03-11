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
        if (form->getClient()->getSocket()->isOpen()) {
            this->hide();
            WhiteBoard *board = new WhiteBoard(this, form->getIp());
            board->show(); 
            board->setAttribute( Qt::WA_DeleteOnClose, true );
            QObject::connect( board, SIGNAL(destroyed(QObject*)), this, SLOT(show()) );  //in case you want to show the login window again once the window is closed
        }
    } 
}


void MainWindow::on_pushButton_clicked()
{
   WhiteBoard *board = new WhiteBoard(this);
   board->show(); 
            board->setWindowFlags( Qt::Window );
            board->setAttribute( Qt::WA_DeleteOnClose, true );
            this->hide();
            QObject::connect( board, SIGNAL(destroyed(QObject*)), this, SLOT(show()) );
}

void MainWindow::on_pushButton_2_clicked()
{
    FormulaireHebergement *form = new FormulaireHebergement(this);
    form->show();
}
