#ifndef FORMULAIRECONNEXION_H
#define FORMULAIRECONNEXION_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QTcpSocket>
#include <QDialog>
#include "../models/logHelper.h"

namespace Ui {
class FormulaireConnexion;
}

class FormulaireConnexion : public QDialog
{
    Q_OBJECT

public:
    explicit FormulaireConnexion(QWidget *parent = nullptr);
    ~FormulaireConnexion();

private:
    QLineEdit *ipInput;
    QLineEdit *passwordInput;
    QPushButton *submitButton;
};

#endif // FORMULAIRECONNEXION_H
