#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QObject>
#include <QJsonDocument>
#include <QString>
#include <QVector>
#include <cstdlib>
#include <time.h>
#include <QHash>

#include "slot.h"
#include "piece.h"

#include <QDebug>
#include "unistd.h"

class PlayGround : public QObject
{
    Q_OBJECT
public:
    explicit PlayGround(QObject *parent = nullptr);
    ~PlayGround();

    void printStatus();
    void updateSlot(int positionX, int positionY, Piece::STATUS status) {
        Slot* slot = m_slots[positionY][positionX];
        slot->setStatus(status);
        if(status == Piece::STATUS::BLACK) {
            m_blacks.push_back(slot);
            qDebug() << m_blacks;
        } else if(status == Piece::STATUS::WHITE) {
            m_white.push_back(slot);
            qDebug() << m_white;
        }
    }
    void aiPlay(Piece::STATUS pieceColor, int actionAmount);
signals:
    void newPieceLocated(int positionX, int positionY, Piece::STATUS status);
private:
    QVector<QVector<Slot*>> m_slots;
    QVector<Slot*> m_blacks;
    QVector<Slot*> m_white;
};

#endif // PLAYGROUND_H
