#ifndef IDCLIENT_H
#define IDCLIENT_H

#include <QString>
#include <QDataStream>
#include <QImage>
using namespace std;


// Represente l'id d'un client, et l'image du tableau, pour l'envoyer au client
struct IdClient {
    int id;
    QImage image;


    // Sérialisation
    friend QDataStream &operator<<(QDataStream &out, const IdClient &c) {
        out << c.id << c.image;
        return out;
    }

    // Désérialisation
    friend QDataStream &operator>>(QDataStream &in, IdClient &c) {
        in >>c.id >> c.image;
        return in;
    }
};

#endif // IDCLIENT_H