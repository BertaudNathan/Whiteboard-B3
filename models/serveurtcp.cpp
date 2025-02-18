#include "serveurtcp.h"
#include "logHelper.h"
#include <QDebug>

ServeurTCP::ServeurTCP(QObject *parent) : QTcpServer(parent) {}

void ServeurTCP::startServer(quint16 port)
{
    if (!this->listen(QHostAddress::Any, port)) {
        LogHelper::WriteLog( "Le serveur n'a pas pu démarrer !");
    } else {
        LogHelper::WriteLog("Serveur démarré sur le port");
    }
}

ServeurTCP::~ServeurTCP()
{
    LogHelper::WriteLog("Fermeture du serveur");
    for (QTcpSocket *client : clients) {
        client->disconnectFromHost();
        client->waitForDisconnected();
        delete client;
    }
}

void ServeurTCP::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *clientSocket = new QTcpSocket(this);
    
    if (clientSocket->setSocketDescriptor(socketDescriptor)) {
        clients.append(clientSocket);
        LogHelper::WriteLog(  "Nouveau client connecté !");

        connect(clientSocket, &QTcpSocket::readyRead, this, &ServeurTCP::onClientReadyRead);
        connect(clientSocket, &QTcpSocket::disconnected, this, &ServeurTCP::onClientDisconnected);
    } else {
        delete clientSocket;
    }
}

void ServeurTCP::onClientReadyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (clientSocket) {
        QString data = QString::fromUtf8(clientSocket->readAll());
        qDebug() << "Données reçues:" << data;
        
        // Envoyer une réponse
        clientSocket->write("Message reçu !");
        clientSocket->flush();
    }
}

void ServeurTCP::onClientDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (clientSocket) {
        clients.removeAll(clientSocket);
        clientSocket->deleteLater();
        LogHelper::WriteLog("deconnexion du client");
    }
}
