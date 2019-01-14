#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QVector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

#include "piecebutton.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum STATE {
        BLACK,
        WHITE
    };
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void onPieceLocated(int positionX, int positionY);
private slots:
    void onButtonPressed(int positionX, int positionY) {
        PieceButton* button = qobject_cast<PieceButton*>(sender());
        if(button->isPlaced()) {
            QMessageBox *messageBox = new QMessageBox;
            messageBox->setText("這個位置已經放置。");
            messageBox->setWindowTitle("Oooops!");
            messageBox->show();
            return;
        }
        qDebug() << "Column: " << positionX << ", Row: " << positionY;
        if(this->m_state == STATE::BLACK) {
            button->setBlack();
            m_state = STATE::WHITE;
        } else {
            button->setWhite();
            m_state = STATE::BLACK;
        }

        emit onPieceLocated(positionX, positionY);
    }
private:
    Ui::MainWindow *ui;
    QVector<QHBoxLayout*> m_layout;
    STATE m_state;
};

#endif // MAINWINDOW_H
