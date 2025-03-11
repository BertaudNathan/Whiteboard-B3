#ifndef IMAGE_H
#define IMAGE_H

#include <QString>
#include <QDataStream>
#include <QImage>

struct Image {
    quint8 type = 0x06;
    QImage image;


    // Sérialisation
    friend QDataStream &operator<<(QDataStream &out, const Image &c) {
        out << c.type << c.image;
        return out;
    }

    // Désérialisation
    friend QDataStream &operator>>(QDataStream &in, Image &c) {
        in >> c.type >>c.image;
        return in;
    }
};

#endif // IMAGE_H