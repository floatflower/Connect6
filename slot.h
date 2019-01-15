#ifndef SLOT_H
#define SLOT_H

#include <QObject>
#include "piece.h"

class Slot : public QObject
{
    Q_OBJECT
public:
    explicit Slot(QObject *parent = nullptr);
    // status getter and setter.
    void setStatus(Piece::STATUS status) { m_status = status; }
    Piece::STATUS status() { return m_status; }
    void setPositionX(int x) { this->m_positionX = x; }
    int positionX() { return this->m_positionX; }
    void setPositionY(int y) { this->m_positionY = y; }
    int positionY() { return this->m_positionY; }
signals:

public slots:
private:
    Piece::STATUS m_status;
    int m_positionX;
    int m_positionY;
};

#endif // SLOT_H
