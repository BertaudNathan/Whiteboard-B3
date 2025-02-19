#ifndef POINT_H
#define POINT_H

#include <QString>
#include <QDataStream>

struct Point {
    int x;
    int y;
    QString couleur;
    int taille;

    // Sérialisation
    friend QDataStream &operator<<(QDataStream &out, const Point &p) {
        out << p.x << p.y << p.couleur << p.taille;
        return out;
    }

    // Désérialisation
    friend QDataStream &operator>>(QDataStream &in, Point &p) {
        in >> p.x >> p.y >> p.couleur >> p.taille;
        return in;
    }
};

#endif // POINT_H