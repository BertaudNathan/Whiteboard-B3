#ifndef FORMULAIRECONNEXION_H
#define FORMULAIRECONNEXION_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QTcpSocket>
#include <QDialog>
#include <QDebug>
#include <QByteArray>

#include "../models/logHelper.h"
#include "../models/serveurtcp.h"
#include "../models/client.h"
#include "test.h"

namespace Ui {
class FormulaireConnexion;
}

class FormulaireConnexion : public QDialog
{
    Q_OBJECT

public:
    explicit FormulaireConnexion(QWidget *parent = nullptr);
    ~FormulaireConnexion();

    Client *getClient() const;
    void setClient(Client *newClient);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::FormulaireConnexion *ui;
    Client *client;
};

#endif // FORMULAIRECONNEXION_H
