#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QObject>
#include <QVector>
#include <cstdlib>
#include <time.h>

#include "slot.h"
#include "piece.h"

#include <QDebug>

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
        } else if(status == Piece::STATUS::WHITE) {
            m_white.push_back(slot);
        }
    }
    void aiPlay(Piece::STATUS pieceColor, int actionAmount) {
        qDebug() << pieceColor << " " << actionAmount;
        srand(time(nullptr));
        for(int actionIndex = 0; actionIndex < actionAmount; actionIndex ++) {
            int x = rand() % 19;
            int y = rand() % 19;
            this->updateSlot(x, y, pieceColor);
            qDebug() << "Choose: " << x << " " << y;
            emit newPieceLocated(x, y, pieceColor);
        }
    }
signals:
    void newPieceLocated(int positionX, int positionY, Piece::STATUS status);
private:
    QVector<QVector<Slot*>> m_slots;
    QVector<Slot*> m_blacks;
    QVector<Slot*> m_white;
};

#endif // PLAYGROUND_H
