#include "formulaireconnexion.h"
#include "ui_formulaireconnexion.h"

FormulaireConnexion::FormulaireConnexion(QWidget *parent)
    : QDialog(parent)    , ui(new Ui::FormulaireConnexion)
{
    /* QWidget *centralWidget = new QWidget(this);
   //setCentralWidget(centralWidget); // QDialog does not have setCentralWidget
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    QLabel *ipLabel = new QLabel("Adresse IP:", this);
    ipInput = new QLineEdit(this);
    ipInput->setText("127.0.0.1");
    QLabel *passwordLabel = new QLabel("Mot de passe:", this);
    passwordInput = new QLineEdit(this);
    passwordInput->setEchoMode(QLineEdit::Password);

    submitButton = new QPushButton("Valider", this);

    layout->addWidget(ipLabel);
    layout->addWidget(ipInput);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordInput);
    layout->addWidget(submitButton);
    setLayout(layout); */
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

