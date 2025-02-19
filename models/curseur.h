#ifndef CURSEUR_H
#define CURSEUR_H

#include <QString>
#include <QDataStream>

struct Curseur {
    int x;
    int y;
    int id;
    QString couleur;


    // Sérialisation
    friend QDataStream &operator<<(QDataStream &out, const Curseur &c) {
        out << c.x << c.y << c.id << c.couleur;
        return out;
    }

    // Désérialisation
    friend QDataStream &operator>>(QDataStream &in, Curseur &c) {
        in >> c.x >> c.y >> c.id >> c.couleur;
        return in;
    }
};

#endif // CURSEUR_H