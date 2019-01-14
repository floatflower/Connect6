#ifndef PIECEBUTTON_H
#define PIECEBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QPalette>

class PieceButton : public QPushButton
{
    Q_OBJECT
public:
    enum COLOR {
        BLACK,
        WHTIE
    };
    PieceButton(int positionX, int positionY, QWidget *parent = nullptr);
    PieceButton* setPositionX(int x) {
        this->positionX = x;
        return this;
    }
    PieceButton* setPositiionY(int y) {
        this->positionY = y;
        return this;
    }
    PieceButton* setBlack() {
        this->setStyleSheet("background-color: #000; border-radius: 3px; width: 40px; height: 40px;");
        this->m_placed = true;
        return this;
    }
    PieceButton* setWhite() {
        this->setStyleSheet("background-color: #fff; border-radius: 3px; width: 40px; height: 40px;");
        this->m_placed = true;
        return this;
    }
    bool isPlaced() {
        return this->m_placed;
    }
    COLOR color() {
        return m_color;
    }
protected:
signals:
    void buttonPressed(int positionX, int positionY);
private slots:
    void onClicked() {
        emit buttonPressed(this->positionX, this->positionY);
    }
private:
    int positionX;
    int positionY;
    bool m_placed = false;
    COLOR m_color;
};

#endif // PIECEBUTTON_H
