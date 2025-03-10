#ifndef IDCLIENT_H
#define IDCLIENT_H

#include <QString>
#include <QDataStream>
using namespace std;

struct IdClient {
    int id;


    // Sérialisation
    friend QDataStream &operator<<(QDataStream &out, const IdClient &c) {
        out << c.id;
        return out;
    }

    // Désérialisation
    friend QDataStream &operator>>(QDataStream &in, IdClient &c) {
        in >>c.id;
        return in;
    }
};

#endif // IDCLIENT_H