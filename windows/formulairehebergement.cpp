#include "formulairehebergement.h"
#include "ui_formulairehebergement.h"


FormulaireHebergement::FormulaireHebergement(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FormulaireHebergement)
{
    ui->setupUi(this);
    this->setWindowTitle("Heberger un whiteboard");
    connect(ui->buttonOuvrirImage, &QPushButton::clicked, this, &FormulaireHebergement::on_FileOpen);
}

FormulaireHebergement::~FormulaireHebergement()
{
    delete ui;
}

QString FormulaireHebergement::getImage() const
{
    return image;
}

void FormulaireHebergement::on_FileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("Images (*.png *.jpg)"));
    if (!fileName.isEmpty()) {
        this->image = fileName; 
        ui->inputNomTableau->setText(fileName);
    }
}

void FormulaireHebergement::on_buttonBox_accepted()
{
    QString ip = ui->inputNomTableau->text();
    QString password = ui->inputPasswordTableau->text();
    LogHelper::WriteLog("IP " + ip.toStdString()+ " PORT " + password.toStdString());
    if (!QFile::exists(this->image)) {
        this->image =  ":fond.png";
    }
    server = new ServeurTCP(this, this->image);
    server->setPassword(password);
    server->startServer(8000);
}



