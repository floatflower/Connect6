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
signals:

public slots:
private:
    Piece::STATUS m_status;
};

#endif // SLOT_H
