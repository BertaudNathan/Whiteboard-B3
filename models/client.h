#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QObject>
#include <QDebug>

#include "point.h"
#include "curseur.h"

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    void connectToServer(const QString &ip, quint16 port);
    void sendMessage(const QByteArray &message);

    QTcpSocket *getSocket() const;
    void setSocket(QTcpSocket *newSocket);

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *socket;
};

#endif // CLIENT_H
