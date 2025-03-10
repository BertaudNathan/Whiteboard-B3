#ifndef CURSEUR_H
#define CURSEUR_H

#include <QString>
#include <QDataStream>
using namespace std;

struct Curseur {
    int x;
    int y;
    int id;
    QString couleur;
    bool drawing;
    int taille;


    // Sérialisation
    friend QDataStream &operator<<(QDataStream &out, const Curseur &c) {
        out << c.drawing << c.id  << c.x << c.y << c.couleur << c.taille;
        return out;
    }

    // Désérialisation
    friend QDataStream &operator>>(QDataStream &in, Curseur &c) {
        in >> c.drawing >>c.id >> c.x >> c.y >> c.couleur >> c.taille;
        return in;
    }
};

#endif // CURSEUR_H