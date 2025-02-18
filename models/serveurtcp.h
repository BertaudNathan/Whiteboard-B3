#ifndef SERVEURTCP_H
#define SERVEURTCP_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>

class ServeurTCP : public QTcpServer
{
    Q_OBJECT

public:
    explicit ServeurTCP(QObject *parent = nullptr);
    ~ServeurTCP();
    void startServer(quint16 port = 8000);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onClientReadyRead();
    void onClientDisconnected();

private:
    QList<QTcpSocket *> clients;
};

#endif // SERVEURTCP_H
