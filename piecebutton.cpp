#include "piecebutton.h"

PieceButton::PieceButton(int positionX, int positionY, QWidget *parent)
    : QPushButton(parent)
    , positionX(positionX)
    , positionY(positionY)
{
    connect(this, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    this->setStyleSheet("background-color: #acacac; border-radius: 3px; width: 40px; height: 40px; max-height: 40px; max-width: 40px;");
}
