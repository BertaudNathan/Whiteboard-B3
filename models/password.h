#ifndef PASSWORD_H
#define PASSWORD_H

#include <QString>
#include <QDataStream>

struct Password {
    QString password;


    // Sérialisation
    friend QDataStream &operator<<(QDataStream &out, const Password &c) {
        out << c.password;
        return out;
    }

    // Désérialisation
    friend QDataStream &operator>>(QDataStream &in, Password &c) {
        in >> c.password;
        return in;
    }
};

#endif // PASSWORD_H