#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);

    // Connexion des signaux aux slots
    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred, this, &Client::onErrorOccurred);
}

Client::~Client()
{
    socket->close();
}

void Client::connectToServer(const QString &ip, quint16 port)
{
    qDebug() << "Connexion au serveur sur" << ip << ":" << port;
    socket->connectToHost(ip, port);
}

void Client::sendMessage(const QByteArray &message)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(message);
        socket->flush();
        qDebug() << "Message envoyé:" << message;
    } else {
        qDebug() << "Impossible d'envoyer, socket non connecté.";
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
    QByteArray data = socket->readAll();
    qDebug() << __FUNCTION__;
    QDataStream stream(&data, QIODevice::ReadOnly);
    quint8 type;
    stream >> type; // Désérialisation du type de message
    if (type == 0x01) {
        Point p;
        stream >> p;  // Désérialisation du Point
        qDebug() << "Point reçu -> X:" << p.x << ", Y:" << p.y 
                 << ", Couleur:" << p.couleur << ", Taille:" << p.taille;
    } else if (type == 0x02) {
        Curseur c;
    stream >> c;  // Désérialisation du Curseur
    qDebug() << "Point reçu -> X:" << c.x << ", Y:" << c.y;
    }
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
