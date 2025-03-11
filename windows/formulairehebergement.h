#ifndef FORMULAIREHEBERGEMENT_H
#define FORMULAIREHEBERGEMENT_H
#include "../models/logHelper.h"
#include "../models/serveurtcp.h"
#include <QDialog>
#include <QFileDialog>


namespace Ui {
class FormulaireHebergement;
}


//formulaire d'hebergement permettant de choisir une image et un mot de passe pour heberger un tableau
class FormulaireHebergement : public QDialog
{
    Q_OBJECT

public:
    explicit FormulaireHebergement(QWidget *parent = nullptr);
    ~FormulaireHebergement(); 

    QString getImage() const;

private slots:
    void on_buttonBox_accepted();
    void on_FileOpen();
private:
    Ui::FormulaireHebergement *ui;
    ServeurTCP *server;
    QString image = ":fond.png";
};

#endif // FORMULAIREHEBERGEMENT_H
