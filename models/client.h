#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QObject>
#include <QDebug>

#include "curseur.h"
#include "idClient.h"

// Classe représentant un client, gère la connexion au serveur, la reception de message connectée au board grace a un emitter
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
    int getId() const;
    void setId(int newId);

public slots:
    void onReadyRead();

private slots:
    void onConnected();
    void onDisconnected();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *socket;
    int id;
};

#endif // CLIENT_H
