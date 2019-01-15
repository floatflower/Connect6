#include "playground.h"
#include <QDebug>

PlayGround::PlayGround(QObject *parent) : QObject(parent)
{
    for(int row = 0; row < 19; row ++) {
        QVector<Slot*> slotRow;
        for(int column = 0; column < 19; column ++) {
            slotRow.push_back(new Slot());
        }
        m_slots.push_back(slotRow);
    }
}

PlayGround::~PlayGround()
{
}

void PlayGround::printStatus()
{
    for(QVector<QVector<Slot*>>::iterator it_slots = m_slots.begin();
        it_slots != m_slots.end();
        it_slots ++) {
        QDebug deb = qDebug();
        for(QVector<Slot*>::iterator it_slotRow = (*it_slots).begin();
            it_slotRow != (*it_slots).end();
            it_slotRow ++) {
            deb << (*it_slotRow)->status();
        }
    }
}
