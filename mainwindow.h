#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QVector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

#include "piecebutton.h"
#include "playground.h"
#include "piece.h"
#include "player.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void onPieceLocated(int positionX, int positionY);
private slots:
    void onButtonPressed(int positionX, int positionY) {
        //if((m_currentPlayer == Piece::BLACK && m_blackPlayer == Player::PLAYER)
        //        || (m_currentPlayer == Piece::WHITE && m_whitePlayer == Player::PLAYER)) {
            PieceButton* button = qobject_cast<PieceButton*>(sender());
            if(button->isPlaced()) {
                QMessageBox *messageBox = new QMessageBox(this);
                messageBox->setText("這個位置已經放置。");
                messageBox->setWindowTitle("Oooops!");
                messageBox->show();
                return;
            }
            qDebug() << "Column: " << positionX << ", Row: " << positionY;
            if(this->m_state == Piece::STATUS::BLACK) {
                button->setBlack();
                m_playground->updateSlot(positionX, positionY, this->m_state);
                this->actionCount ++;
                if(this->actionCount == 2) {
                    m_state = Piece::STATUS::WHITE;
                    this->actionCount = 0;
                    m_playground->printStatus();
                    emit onPieceLocated(positionX, positionY);
                    m_playground->aiPlay(this->m_state, 2 - actionCount);
                    return;
                }
            } else {
                button->setWhite();
                this->actionCount ++;
                m_playground->updateSlot(positionX, positionY, this->m_state);
                if(this->actionCount == 2) {
                    m_state = Piece::STATUS::BLACK;
                    this->actionCount = 0;
                    m_playground->printStatus();
                    emit onPieceLocated(positionX, positionY);
                    m_playground->aiPlay(this->m_state, 2 - actionCount);
                    return;
                }
            }


        }
    //}
    void onNewPieceLocated(int x, int y, Piece::STATUS status) {
        if(status == Piece::STATUS::BLACK) {
            m_buttons[x][y]->setBlack();
            this->actionCount ++;
            if(this->actionCount == 2) {
                m_state = Piece::STATUS::WHITE;
                m_playground->printStatus();
                this->actionCount = 0;
                if(m_whitePlayer == Player::TYPE::AI) {
                    m_playground->aiPlay(this->m_state, 2);
                }
            }
        } else if(status == Piece::STATUS::WHITE) {
            m_buttons[x][y]->setWhite();
            this->actionCount ++;
            if(this->actionCount == 2) {
                m_state = Piece::STATUS::BLACK;
                m_playground->printStatus();
                this->actionCount = 0;
                if(m_blackPlayer == Player::TYPE::AI) {
                    m_playground->aiPlay(this->m_state, 2);
                }
            }
        }
    }
    void onBlackPlayerRoleChosen(QAbstractButton *button);
    void onWhitePlayerRoleChosen(QAbstractButton *button);
private:
    Ui::MainWindow *ui;
    QVector<QHBoxLayout*> m_layout;
    QVector<QVector<PieceButton*>> m_buttons;
    Piece::STATUS m_state;
    int actionCount = 1;
    PlayGround *m_playground;
    Piece::STATUS m_currentPlayer;
    Player::TYPE m_blackPlayer;
    Player::TYPE m_whitePlayer;
    QMessageBox* m_blackPlayerSelector;
    QMessageBox* m_whitePlayerSelector;
};

#endif // MAINWINDOW_H
