#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    this->socket = new QTcpSocket(this);
    this->id = 0;

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
        
    } else {
        
    }
}

void Client::onConnected()
{
    
}

void Client::onDisconnected()
{
    
}

void Client::onReadyRead()
{ 
}

void Client::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    LogHelper::WriteLog(socket->errorString().toStdString());
}

QTcpSocket *Client::getSocket() const
{
    return socket;
}

void Client::setSocket(QTcpSocket *newSocket)
{
    socket = newSocket;
}

int Client::getId() const
{
    return id;
}

void Client::setId(int newId)
{
    id = newId;
}
