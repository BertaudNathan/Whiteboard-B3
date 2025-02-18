#ifndef FORMULAIREHEBERGEMENT_H
#define FORMULAIREHEBERGEMENT_H
#include "../models/logHelper.h"
#include <QDialog>


namespace Ui {
class FormulaireHebergement;
}

class FormulaireHebergement : public QDialog
{
    Q_OBJECT

public:
    explicit FormulaireHebergement(QWidget *parent = nullptr);
    ~FormulaireHebergement();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::FormulaireHebergement *ui;
};

#endif // FORMULAIREHEBERGEMENT_H
