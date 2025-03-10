#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    this->socket = new QTcpSocket(this);

    // Connexion des signaux aux slots
    connect(this->socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(this->socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(this->socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(this->socket, &QTcpSocket::errorOccurred, this, &Client::onErrorOccurred);
    
}

Client::~Client()
{
    socket->close();
}

void Client::connectToServer(const QString &ip, quint16 port)
{
    //qDebug() << "Connexion au serveur sur" << ip << ":" << port;
    socket->connectToHost(ip, port);
}

void Client::sendMessage(const QByteArray &message)
{
    if (!this->socket) {
        return;
    }
    if (this->socket->state() != QAbstractSocket::ConnectedState) {
        return;
    }
    qint64 bytesWritten = this->socket->write(message);
    if (bytesWritten == -1) {
        qDebug() << "ERREUR: Échec d'envoi du message !";
    } else {
        //qDebug() << "Message envoyé avec succès (" << bytesWritten << " octets ):" << message;
    }
}

void Client::onConnected()
{
    qDebug() << "Connecté au serveur.";
}

void Client::onDisconnected()
{
    qDebug() << "Déconnecté du serveur.";
}

void Client::onReadyRead()
{
}

void Client::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Erreur de connexion:" << socket->errorString();
}

QTcpSocket *Client::getSocket() const
{
    return socket;
}

void Client::setSocket(QTcpSocket *newSocket)
{
    socket = newSocket;
}
