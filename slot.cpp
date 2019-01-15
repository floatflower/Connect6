#include "slot.h"

Slot::Slot(QObject *parent)
    : QObject(parent)
    , m_status(Piece::STATUS::UNDEFINED)
{

}
