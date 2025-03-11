#include "serveurtcp.h"
#include "logHelper.h"
#include <QDebug>

void ServeurTCP::setPassword(const QString &newPassword)
{
    this->password = newPassword;
}
ServeurTCP::ServeurTCP(QObject *parent, QString imagePath) : QTcpServer(parent)
{
    qDebug() << "📂 Chemin de l'image reçu :" << imagePath;
    
    if (!QFile::exists(imagePath)) {
        qDebug() << "❌ L'image n'existe pas !";
    } else {
        this->image = QImage(imagePath);
        if (this->image.isNull()) {
            qDebug() << "⚠️ Échec du chargement de l'image !";
        } else {
            qDebug() << "✅ Image chargée avec succès - Taille :" << this->image.size();
        }
    }

    this->isAdmin = false;
    this->order = 1;
}

ServeurTCP::ServeurTCP(bool isAdmin, QObject *parent) : QTcpServer(parent)
{
    this->isAdmin = isAdmin;
    this->order = 0;
}

void ServeurTCP::startServer(quint16 port)
{
    if (!this->listen(QHostAddress::Any, port))
    {
        LogHelper::WriteLog("Le serveur n'a pas pu démarrer !");
    }
    else
    {
        LogHelper::WriteLog("Serveur démarré sur le port");
    }
}


void ServeurTCP::broadcastCurseur(const Curseur &c)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    quint8 type = 0x02;  // Identifiant pour Point
    stream << type << c; // Sérialiser le Point
    for (QTcpSocket *client : clients)
    {
        if (client->state() == QAbstractSocket::ConnectedState)
        {
            client->write(data);
            client->flush();   
        }
    }
}

bool ServeurTCP::sendTo(const QString &ip, quint16 port, const QByteArray &bytes)
{
    QTcpSocket *socket = new QTcpSocket(this);
    socket->connectToHost(ip, port);
    if (socket->waitForConnected(3000))
    {
        socket->write(bytes);
        socket->flush();
        socket->waitForBytesWritten(3000);
        socket->disconnectFromHost();
        return true;
    }
    else
    {
        return false;
    }
}

ServeurTCP::~ServeurTCP()
{
    LogHelper::WriteLog("Fermeture du serveur");
    for (QTcpSocket *client : clients)
    {
        client->disconnectFromHost();
        client->waitForDisconnected();
        delete client;
    }
}

void ServeurTCP::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *clientSocket = new QTcpSocket(this);
    connect(clientSocket, &QTcpSocket::readyRead, this, &ServeurTCP::onClientReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &ServeurTCP::onClientDisconnected);
    if (clientSocket->setSocketDescriptor(socketDescriptor))
    {
        IdClient idc;
        idc.id = clients.size() + 1;
        idc.image = this->image;
        clients.append(clientSocket);
        LogHelper::WriteLog("Nouveau client connecté !");
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        quint8 type = 0x05;
        stream << type << idc;
        clientSocket->write(data);
        clientSocket->flush();     
    }
    else
    {
        delete clientSocket;
    }
}

void ServeurTCP::onClientReadyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (clients.contains(clientSocket))
    {
        QByteArray requestData = clientSocket->readAll();
        QDataStream stream(&requestData, QIODevice::ReadOnly);
        quint8 type;
        stream >> type; // Désérialisation du type de message
        qDebug() << "Type de message reçu : " << type;
        if (type == 0x02)
        {
            Curseur c;
            stream >> c; // Désérialisation du Curseur
            broadcastCurseur(c);
            // qDebug() << "Point reçu -> X:" << c.x << ", Y:" << c.y;
        }
    }
}

void ServeurTCP::receiveRequest(QTcpSocket *clientSocket)
{
    QByteArray requestData = clientSocket->readAll();

    // Exemple de réponse
    QString response = "Requête reçue et traitée";
    clientSocket->write(response.toUtf8());
    sendTo(clientSocket->peerAddress().toString(), clientSocket->peerPort(), response.toUtf8());
    clientSocket->flush();
}

void ServeurTCP::onClientDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (clientSocket)
    {
        clients.removeAll(clientSocket);
        clientsValides.removeAll(clientSocket);
        clientSocket->deleteLater();
        LogHelper::WriteLog("deconnexion du client");
    }
}
