#ifndef PIECE_H
#define PIECE_H

#include <QObject>

class Piece : public QObject
{
    Q_OBJECT
public:
    explicit Piece(QObject *parent = nullptr);
    enum STATUS {
        BLACK,
        WHITE,
        UNDEFINED
    };
signals:

public slots:
};

#endif // PIECE_H
