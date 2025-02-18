#include "formulaireconnexion.h"

FormulaireConnexion::FormulaireConnexion(QWidget *parent)
    : QDialog(parent)
{
    QWidget *centralWidget = new QWidget(this);
   //setCentralWidget(centralWidget); // QDialog does not have setCentralWidget
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    QLabel *ipLabel = new QLabel("Adresse IP:", this);
    ipInput = new QLineEdit(this);
    QLabel *passwordLabel = new QLabel("Mot de passe:", this);
    passwordInput = new QLineEdit(this);
    passwordInput->setEchoMode(QLineEdit::Password);

    submitButton = new QPushButton("Valider", this);

    layout->addWidget(ipLabel);
    layout->addWidget(ipInput);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordInput);
    layout->addWidget(submitButton);
    setLayout(layout);

    connect(submitButton, &QPushButton::clicked, this, [=]() {
        QString ip = ipInput->text();
        QString password = passwordInput->text();
        LogHelper::WriteLog("IP " + ip.toStdString()+ " PORT " + password.toStdString());
        QTcpSocket *socket = new QTcpSocket(this);
        socket->connectToHost(ip, 8000);
        if (socket->waitForConnected(3000)) {
            socket->write(password.toUtf8());
            socket->flush();
            socket->waitForBytesWritten(3000);
            socket->close();
        } else {
            LogHelper::WriteLog("failed");
        }
    });
}

FormulaireConnexion::~FormulaireConnexion()
{
}
