#include "playground.h"
#include <QDebug>

PlayGround::PlayGround(QObject *parent) : QObject(parent)
{
    for(int row = 0; row <= 19; row ++) {
        QVector<Slot*> slotRow;
        for(int column = 0; column <= 19; column ++) {
            Slot* slot = new Slot();
            slot->setPositionX(column);
            slot->setPositionY(row);
            slotRow.push_back(slot);
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

void PlayGround::aiPlay(Piece::STATUS pieceColor, int actionAmount) {
    qDebug() << "Color: "<< pieceColor << " will do " << actionAmount << " time actions.";
    Piece::STATUS playerColor = (pieceColor == Piece::BLACK ? Piece::WHITE : Piece::BLACK);
    QVector<Slot*> ai = pieceColor == Piece::BLACK ? m_blacks : m_white;
    QVector<Slot*> player = pieceColor == Piece::BLACK ? m_white : m_blacks;
    QHash<int, QVector<Slot*>> playerThreaten;
    QHash<int, QVector<Slot*>> aiThreaten;
    for(int i = 0; i < 6; i ++) {
        QVector<Slot*> playerSlots;
        playerThreaten.insert(i, playerSlots);
        QVector<Slot*> aiSlots;
        aiThreaten.insert(i, aiSlots);
    }
    for(QVector<Slot*>::iterator it_slots = ai.begin();
        it_slots != ai.end();
        it_slots ++) {
        // original position
        int x = (*it_slots)->positionX();
        int y = (*it_slots)->positionY();

        // go right
        int goRight = x;
        int goDown = y;
        int goLeft = x;
        int pieceCount = 1;
        bool headAlive = true;
        bool tailAlive = true;
        while(1) {
            goRight = goRight + 1;
            if(goRight >= 19) {
                tailAlive = false;
                break;
            }
            // no piece at the location.

            // same color as ai
            if (m_slots[y][goRight]->status() == pieceColor) {
                pieceCount ++;
                if((x - 1) < 0 || m_slots[y][x - 1]->status() == playerColor) {
                    headAlive = false;
                } else if (m_slots[y][x - 1]->status() == pieceColor) {
                    headAlive = false;
                    break;
                } else if (m_slots[y][x - 1]->status() == Piece::UNDEFINED){
                    headAlive = true;
                }
            }
            else if(m_slots[y][goRight]->status() == Piece::UNDEFINED) {
                qDebug() << "Go Right, Find AI alive line, length: " << pieceCount;
                tailAlive = true;
                break;
            }
            // differend color as ai
            else {
                qDebug() << "Go Right, Find AI death line, length: " << pieceCount;
                tailAlive = false;
                break;
            }
        }

        if(pieceCount >= 4 && headAlive) {
            (aiThreaten.find(pieceCount))->push_back(m_slots[y][x - 1]);
        }
        if (pieceCount >= 4 && tailAlive) {
            (aiThreaten.find(pieceCount))->push_back(m_slots[y][goRight]);
        }
        if (pieceCount <= 3 && headAlive && m_slots[y][x - 1]->status() == Piece::UNDEFINED){
            (aiThreaten.find(pieceCount))->push_back(m_slots[y][x - 1]);
        }
        if (pieceCount <= 3 && tailAlive && m_slots[y][goRight]->status() == Piece::UNDEFINED) {
            (aiThreaten.find(pieceCount))->push_back(m_slots[y][goRight]);
        }

        // go down
        goRight = x;
        goDown = y;
        goLeft = x;
        pieceCount = 1;
        headAlive = true;
        tailAlive = true;
        while(1) {
            goDown = goDown + 1;
            if(goDown >= 19) {
                tailAlive = false;
                break;
            }
            // no piece at the location.

            // same color as ai
            if (m_slots[goDown][x]->status() == pieceColor) {
                pieceCount ++;
                if((y - 1) < 0 || m_slots[y - 1][x]->status() == playerColor) {
                    headAlive = false;
                } else if (m_slots[y - 1][x]->status() == pieceColor) {
                    headAlive = false;
                } else if (m_slots[y - 1][x]->status() == Piece::UNDEFINED){
                    headAlive = true;
                }
            }
            else if(m_slots[goDown][x]->status() == Piece::UNDEFINED) {
                qDebug() << "Go Down, Find AI alive line, length: " << pieceCount;
                tailAlive = true;
                break;
            }
            // differend color as ai
            else {
                qDebug() << "Go Down, Find AI death line, length: " << pieceCount;
                tailAlive = false;
                break;
            }
        }

        if(pieceCount >= 4 && headAlive) {
            (aiThreaten.find(pieceCount))->push_back(m_slots[y-1][x]);
        }
        if (pieceCount >= 4 && tailAlive) {
            (aiThreaten.find(pieceCount))->push_back(m_slots[goDown][x]);
        }
        if (pieceCount <= 3 && headAlive && m_slots[y-1][x]->status() == Piece::UNDEFINED){
            (aiThreaten.find(pieceCount))->push_back(m_slots[y-1][x]);
        }
        if (pieceCount <= 3 && tailAlive && m_slots[goDown][x]->status() == Piece::UNDEFINED) {
            (aiThreaten.find(pieceCount))->push_back(m_slots[goDown][x]);
        }

        // go right-down
        goRight = x;
        goDown = y;
        goLeft = x;
        pieceCount = 1;
        headAlive = true;
        tailAlive = true;
        while(1) {
            goRight = goRight + 1;
            goDown = goDown + 1;
            if(goRight >= 19 && goDown >= 19) {
                tailAlive = false;
                break;
            }
            // no piece at the location.

            // same color as ai
            if (m_slots[goDown][goRight]->status() == pieceColor) {
                pieceCount ++;
                if(((y - 1) < 0 && (x - 1) < 0) || m_slots[y - 1][x - 1]->status() == playerColor) {
                    headAlive = false;
                } else if (m_slots[y - 1][x - 1]->status() == pieceColor) {
                    headAlive = false;
                } else if (m_slots[y - 1][x - 1]->status() == Piece::UNDEFINED){
                    headAlive = true;
                }
            }
            else if(m_slots[goDown][goRight]->status() == Piece::UNDEFINED) {
                tailAlive = true;
                qDebug() << "Go Right-Down, Find AI alive line, length: " << pieceCount;
                break;
            }
            // differend color as ai
            else {
                tailAlive = false;
                qDebug() << "Go Right-Down, Find AI death line, length: " << pieceCount;
                break;
            }
        }

        if(pieceCount >= 4 && headAlive) {
            (aiThreaten.find(pieceCount))->push_back(m_slots[y-1][x - 1]);
        }
        if (pieceCount >= 4 && tailAlive) {
            (aiThreaten.find(pieceCount))->push_back(m_slots[goDown][goRight]);
        }
        if (pieceCount <= 3 && headAlive && m_slots[y - 1][x - 1]->status() == Piece::UNDEFINED){
            (aiThreaten.find(pieceCount))->push_back(m_slots[y-1][x - 1]);
        }
        if (pieceCount <= 3 && tailAlive && m_slots[goDown][goRight]->status() == Piece::UNDEFINED) {
            (aiThreaten.find(pieceCount))->push_back(m_slots[goDown][goRight]);
        }

        // go left-down
        goRight = x;
        goDown = y;
        goLeft = x;
        pieceCount = 1;
        headAlive = true;
        tailAlive = true;
        while(1) {
            goLeft = goLeft -1;
            goDown = goDown + 1;
            if(goLeft < 0 && goDown >= 19) {
                tailAlive = false;
                break;
            }
            // no piece at the location.

            // same color as ai
            if (m_slots[goDown][goLeft]->status() == pieceColor) {
                pieceCount ++;
                if(((y - 1) < 0 && (x + 1) > 19) || m_slots[y - 1][x + 1]->status() == playerColor) {
                    headAlive = false;
                } else if (m_slots[y - 1][x + 1]->status() == pieceColor) {
                    headAlive = false;
                } else if (m_slots[y - 1][x + 1]->status() == Piece::UNDEFINED){
                    headAlive = true;
                }
            }
            else if(m_slots[goDown][goLeft]->status() == Piece::UNDEFINED) {
                tailAlive = true;
                qDebug() << "Go Left-Down, Find AI alive line, length: " << pieceCount;
                break;
            }
            // differend color as ai
            else {
                tailAlive = false;
                qDebug() << "Go Left-Down, Find AI death line, length: " << pieceCount;
                break;
            }
        }

        if(pieceCount >= 4 && headAlive) {
            (aiThreaten.find(pieceCount))->push_back(m_slots[y-1][x + 1]);
        }
        if (pieceCount >= 4 && tailAlive) {
            (aiThreaten.find(pieceCount))->push_back(m_slots[goDown][goLeft]);
        }
        if (pieceCount <= 3 && headAlive && m_slots[y - 1][x + 1]->status() == Piece::UNDEFINED){
            (aiThreaten.find(pieceCount))->push_back(m_slots[y-1][x + 1]);
        }
        if (pieceCount <= 3 && tailAlive && m_slots[goDown][goLeft]->status() == Piece::UNDEFINED) {
            (aiThreaten.find(pieceCount))->push_back(m_slots[goDown][goLeft]);
        }

        for(QHash<int, QVector<Slot*>>::iterator it_aiThreaten = aiThreaten.begin();
            it_aiThreaten != aiThreaten.end();
            it_aiThreaten ++) {
            for(QVector<Slot*>::iterator it_slot = (*it_aiThreaten).begin();
                it_slot != (*it_aiThreaten).end();
                it_slot ++) {
                qDebug() << "Threaten Level: "
                         << it_aiThreaten.key()
                         << " x: "
                         << (*it_slot)->positionX()
                         << " y: "
                         << (*it_slot)->positionY();
            }
        }
    }
    for(QVector<Slot*>::iterator it_slots = player.begin();
        it_slots != player.end();
        it_slots ++) {
        // original position
        int x = (*it_slots)->positionX();
        int y = (*it_slots)->positionY();

        // go right
        int goRight = x;
        int goDown = y;
        int goLeft = x;
        int pieceCount = 1;
        bool headAlive = true;
        bool tailAlive = true;
        while(1) {
            goRight = goRight + 1;
            if(goRight >= 19) {
                tailAlive = false;
                break;
            }
            // no piece at the location.

            // same color as ai
            if (m_slots[y][goRight]->status() == playerColor) {
                pieceCount ++;
                if((x - 1) < 0 || m_slots[y][x - 1]->status() == playerColor) {
                    headAlive = false;
                    break;
                } else if (m_slots[y][x - 1]->status() == pieceColor) {
                    headAlive = false;
                } else if (m_slots[y][x - 1]->status() == Piece::UNDEFINED){
                    headAlive = true;
                }
            }
            else if(m_slots[y][goRight]->status() == Piece::UNDEFINED) {
                qDebug() << "Go Right, Find Player alive line, length: " << pieceCount;
                tailAlive = true;
                break;
            }
            // differend color as ai
            else {
                qDebug() << "Go Right, Find Player death line, length: " << pieceCount;
                tailAlive = false;
                break;
            }
        }

        if(pieceCount >= 4 && headAlive) {
            (playerThreaten.find(pieceCount))->push_back(m_slots[y][x - 1]);
        }
        if (pieceCount >= 4 && tailAlive) {
            (playerThreaten.find(pieceCount))->push_back(m_slots[y][goRight]);
        }
        if (pieceCount <= 3 && headAlive && m_slots[y][x - 1]->status() == Piece::UNDEFINED){
            (playerThreaten.find(pieceCount))->push_back(m_slots[y][x - 1]);
        }
        if (pieceCount <= 3 && tailAlive && m_slots[y][goRight]->status() == Piece::UNDEFINED) {
            (playerThreaten.find(pieceCount))->push_back(m_slots[y][goRight]);
        }

        // go down
        goRight = x;
        goDown = y;
        goLeft = x;
        pieceCount = 1;
        headAlive = true;
        tailAlive = true;
        while(1) {
            goDown = goDown + 1;
            if(goDown >= 19) {
                tailAlive = false;
                break;
            }

            // same color as ai
            if (m_slots[goDown][x]->status() == playerColor) {
                pieceCount ++;
                if((y - 1) < 0 || m_slots[y - 1][x]->status() == playerColor) {
                    headAlive = false;
                    break;
                } else if (m_slots[y - 1][x]->status() == pieceColor) {
                    headAlive = false;
                } else if (m_slots[y - 1][x]->status() == Piece::UNDEFINED){
                    headAlive = true;
                }
            }
            else if(m_slots[goDown][x]->status() == Piece::UNDEFINED) {
                qDebug() << "Go Down, Find Player alive line, length: " << pieceCount;
                break;
            }
            // differend color as ai
            else {
                qDebug() << "Go Down, Find Player death line, length: " << pieceCount;
                break;
            }
        }

        if(pieceCount >= 4 && headAlive) {
            (playerThreaten.find(pieceCount))->push_back(m_slots[y - 1][x]);
        }
        if (pieceCount >= 4 && tailAlive) {
            (playerThreaten.find(pieceCount))->push_back(m_slots[goDown][x]);
        }
        if (pieceCount <= 3 && headAlive && m_slots[y - 1][x]->status() == Piece::UNDEFINED){
            (playerThreaten.find(pieceCount))->push_back(m_slots[y - 1][x]);
        }
        if (pieceCount <= 3 && tailAlive && m_slots[goDown][x]->status() == Piece::UNDEFINED) {
            (playerThreaten.find(pieceCount))->push_back(m_slots[goDown][x]);
        }

        // go right-down
        goRight = x;
        goDown = y;
        goLeft = x;
        pieceCount = 1;
        while(1) {
            goRight = goRight + 1;
            goDown = goDown + 1;
            if(goRight >= 19 && goDown >= 19) {
                tailAlive = false;
                break;
            }
            // no piece at the location.

            // same color as ai
            if (m_slots[goDown][goRight]->status() == playerColor) {
                pieceCount ++;
                if(((y - 1) < 0 && (x - 1) < 0) || m_slots[y - 1][x - 1]->status() == playerColor) {
                    headAlive = false;
                    break;
                } else if (m_slots[y - 1][x - 1]->status() == pieceColor) {
                    headAlive = false;
                } else if (m_slots[y - 1][x - 1]->status() == Piece::UNDEFINED){
                    headAlive = true;
                }
            }
            else if(m_slots[goDown][goRight]->status() == Piece::UNDEFINED) {
                tailAlive = true;
                qDebug() << "Go Right-Down, Find Player alive line, length: " << pieceCount;
                break;
            }
            // differend color as ai
            else {
                tailAlive = false;
                qDebug() << "Go Right-Down, Find Player death line, length: " << pieceCount;
                break;
            }
        }
        qDebug() << "Right-Down player: " << pieceCount;
        if(pieceCount >= 4 && headAlive) {
            (playerThreaten.find(pieceCount))->push_back(m_slots[y - 1][x - 1]);
        }
        if (pieceCount >= 4 && tailAlive) {
            (playerThreaten.find(pieceCount))->push_back(m_slots[goDown][goRight]);
        }
        if (pieceCount <= 3 && headAlive && m_slots[y - 1][x - 1]->status() == Piece::UNDEFINED){
            (playerThreaten.find(pieceCount))->push_back(m_slots[y - 1][x - 1]);
        }
        if (pieceCount <= 3 && tailAlive && m_slots[goDown][goRight]->status() == Piece::UNDEFINED) {
            (playerThreaten.find(pieceCount))->push_back(m_slots[goDown][goRight]);
        }

        // go left-down
        goRight = x;
        goDown = y;
        goLeft = x;
        pieceCount = 1;
        headAlive = true;
        tailAlive = false;
        while(1) {
            goLeft = goLeft + 1;
            goDown = goDown - 1;
            if(goLeft >= 19 && goDown < 0) {
                tailAlive = false;
                break;
            }
            // no piece at the location.

            // same color as ai
            if (m_slots[goDown][goLeft]->status() == playerColor) {
                pieceCount ++;
                if(((y + 1) >= 19 && (x - 1) < 0) || m_slots[y + 1][x - 1]->status() == playerColor) {
                    headAlive = false;
                    break;
                } else if (m_slots[y + 1][x - 1]->status() == pieceColor) {
                    headAlive = false;
                } else if (m_slots[y + 1][x - 1]->status() == Piece::UNDEFINED){
                    headAlive = true;
                }
            }
            else if(m_slots[goDown][goLeft]->status() == Piece::UNDEFINED) {
                qDebug() << "Go Left-Down, Player Find alive line, length: " << pieceCount;
                tailAlive = true;
                break;
            }
            // differend color as ai
            else {
                qDebug() << "Go Left-Down, Player Find death line, length: " << pieceCount;
                tailAlive = false;
                break;
            }

            if(pieceCount >= 4 && headAlive) {
                (playerThreaten.find(pieceCount))->push_back(m_slots[y + 1][x - 1]);
            }
            if (pieceCount >= 4 && tailAlive) {
                (playerThreaten.find(pieceCount))->push_back(m_slots[goDown][goLeft]);
            }
            if (pieceCount <= 3 && headAlive && m_slots[y + 1][x - 1]->status() == Piece::UNDEFINED){
                (playerThreaten.find(pieceCount))->push_back(m_slots[y + 1][x - 1]);
            }
            if (pieceCount <= 3 && tailAlive && m_slots[goDown][goLeft]->status() == Piece::UNDEFINED) {
                (playerThreaten.find(pieceCount))->push_back(m_slots[goDown][goLeft]);
            }
        }
        for(QHash<int, QVector<Slot*>>::iterator it_playerThreaten = playerThreaten.begin();
            it_playerThreaten != playerThreaten.end();
            it_playerThreaten ++) {
            for(QVector<Slot*>::iterator it_slot = (*it_playerThreaten).begin();
                it_slot != (*it_playerThreaten).end();
                it_slot ++) {
                qDebug() << "Player Threaten Level: "
                         << it_playerThreaten.key()
                         << " x: "
                         << (*it_slot)->positionX()
                         << " y: "
                         << (*it_slot)->positionY();
            }
        }
    }
    for(int actionCount = 0; actionCount < actionAmount; actionCount ++) {
        bool acted = false;
        for(int i = 5; i >= 4; i --) {
            QHash<int, QVector<Slot*>>::iterator it_playerThreaten = playerThreaten.find(i);
            if((*it_playerThreaten).size() > 0) {
                Slot* slot = (*it_playerThreaten).takeFirst();
                this->updateSlot(slot->positionX(), slot->positionY(), pieceColor);
                emit newPieceLocated(slot->positionY(), slot->positionX(), pieceColor);
                qDebug() << "Located at x: " << slot->positionX() << ",y: " << slot->positionY();
                acted = true;
                break;
            }
        }

        if(acted) continue;

        for(int i = 5; i >= 3; i --) {
            QHash<int, QVector<Slot*>>::iterator it_aiThreaten = aiThreaten.find(i);
            if((*it_aiThreaten).size() > 0) {
                Slot* slot = (*it_aiThreaten).takeFirst();
                this->updateSlot(slot->positionX(), slot->positionY(), pieceColor);
                emit newPieceLocated(slot->positionY(), slot->positionX(), pieceColor);
                qDebug() << "Located at x: " << slot->positionX() << ",y: " << slot->positionY();
                acted = true;
                break;
            }
        }

        if(acted) continue;

        for(int i = 3; i >= 1; i --) {
            QHash<int, QVector<Slot*>>::iterator it_playerThreaten = playerThreaten.find(i);
            if((*it_playerThreaten).size() > 0) {
                Slot* slot = (*it_playerThreaten).takeFirst();
                this->updateSlot(slot->positionX(), slot->positionY(), pieceColor);
                emit newPieceLocated(slot->positionY(), slot->positionX(), pieceColor);
                qDebug() << "Located at x: " << slot->positionX() << ",y: " << slot->positionY();
                acted = true;
                break;
            }
        }

        if(acted) continue;

        for(int i = 2; i >= 1; i --) {
            QHash<int, QVector<Slot*>>::iterator it_aiThreaten = aiThreaten.find(i);
            if((*it_aiThreaten).size() > 0) {
                Slot* slot = (*it_aiThreaten).takeFirst();
                this->updateSlot(slot->positionX(), slot->positionY(), pieceColor);
                emit newPieceLocated(slot->positionY(), slot->positionX(), pieceColor);
                qDebug() << "Located at x: " << slot->positionX() << ",y: " << slot->positionY();
                acted = true;
                break;
            }
        }
    }

    qDebug() << "====================================================";
}
