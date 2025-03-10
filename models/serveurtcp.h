#ifndef SERVEURTCP_H
#define SERVEURTCP_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include "point.h"
#include "curseur.h"
#include "idClient.h"

class ServeurTCP : public QTcpServer
{
    Q_OBJECT

public:
    explicit ServeurTCP(QObject *parent = nullptr);
    explicit ServeurTCP(bool isAdmin, QObject *parent = nullptr);
    ~ServeurTCP();
    
    void startServer(quint16 port = 8000);
    bool sendTo(const QString &ip, quint16 port, const QByteArray &bytes);
    void receiveRequest(QTcpSocket *clientSocket);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
    void broadcastPoint(const Point &p);
    void broadcastCurseur(const Curseur &c);

private slots:
    void onClientReadyRead();
    void onClientDisconnected();

public:
    void setPassword(const QString &newPassword);

private:
    QList<QTcpSocket *> clients;
    QList<QTcpSocket *> clientsValides;
    bool isAdmin;
    QString password;
    int order;

};

#endif // SERVEURTCP_H
