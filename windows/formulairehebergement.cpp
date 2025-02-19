#include "formulairehebergement.h"
#include "ui_formulairehebergement.h"


FormulaireHebergement::FormulaireHebergement(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FormulaireHebergement)
{
    ui->setupUi(this);
}

FormulaireHebergement::~FormulaireHebergement()
{
    delete ui;
}

void FormulaireHebergement::on_buttonBox_accepted()
{
    QString ip = ui->inputNomTableau->text();
    QString password = ui->inputPasswordTableau->text();
    LogHelper::WriteLog("IP " + ip.toStdString()+ " PORT " + password.toStdString());
    server = new ServeurTCP(this);
    server->setPassword(password);
    server->startServer(8000);
}

