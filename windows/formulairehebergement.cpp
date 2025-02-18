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
    LogHelper::WriteLog("click");
}

