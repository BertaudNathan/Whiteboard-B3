#include "formulaireconnexion.h"
#include "ui_formulaireconnexion.h"

FormulaireConnexion::FormulaireConnexion(QWidget *parent)
    : QDialog(parent)    , ui(new Ui::FormulaireConnexion)
{
    ui->setupUi(this);
}

FormulaireConnexion::~FormulaireConnexion()
{
}

void FormulaireConnexion::on_buttonBox_accepted()
{
    this->ip = ui->ipInput->text();
    QString password = ui->passwordInput->text();
    this->client = new Client(this);
    QTcpSocket *socket = client->getSocket();
    connect(socket, &QTcpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError socketError) {
        qDebug() << "Erreur de connexion au serveur";
        this->client->getSocket()->close();
    });
    socket->connectToHost(ip, 8000);   
    if (socket->waitForConnected(1000)) {
        socket->write(password.toUtf8());   
    } else {
        qDebug() << "Connexion échouée";    
    } 
}

Client *FormulaireConnexion::getClient() const
{
    return client;
}

QString FormulaireConnexion::getIp()
{
    return ip;
}

void FormulaireConnexion::setClient(Client *newClient)
{
    client = newClient;
}

