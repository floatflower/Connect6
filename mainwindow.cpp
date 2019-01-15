#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "piecebutton.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_state(Piece::STATUS::BLACK),
    m_playground(new PlayGround())
{
    ui->setupUi(this);
    this->setWindowTitle("Connect6 by FloatFlower.Huang");
    ui->statusBar->showMessage("");
    PieceButton* button = new PieceButton(0, 0);
    connect(button, SIGNAL(buttonPressed(int, int)), this, SLOT(onButtonPressed(int, int)));

    QPushButton* uselessButton = new QPushButton(this);
    uselessButton->setStyleSheet("background-color: #ff6600; border-radius: 3px; width: 40px; height: 40px; max-height: 40px; max-width: 40px;");
    ui->row_19->addWidget(uselessButton);
    for(int i = 0; i < 19; i ++) {
        QPushButton* indexButton = new QPushButton(this);
        indexButton->setStyleSheet("background-color: #ff6600; border-radius: 3px; width: 40px; height: 40px; max-height: 40px; max-width: 40px;");
        indexButton->setText(QString::number(i));
        ui->row_19->addWidget(indexButton);
    }

    m_layout.push_back(ui->row_0);
    m_layout.push_back(ui->row_1);
    m_layout.push_back(ui->row_2);
    m_layout.push_back(ui->row_3);
    m_layout.push_back(ui->row_4);
    m_layout.push_back(ui->row_5);
    m_layout.push_back(ui->row_6);
    m_layout.push_back(ui->row_7);
    m_layout.push_back(ui->row_8);
    m_layout.push_back(ui->row_9);
    m_layout.push_back(ui->row_10);
    m_layout.push_back(ui->row_11);
    m_layout.push_back(ui->row_12);
    m_layout.push_back(ui->row_13);
    m_layout.push_back(ui->row_14);
    m_layout.push_back(ui->row_15);
    m_layout.push_back(ui->row_16);
    m_layout.push_back(ui->row_17);
    m_layout.push_back(ui->row_18);

    int row = 0;
    for(QVector<QHBoxLayout*>::iterator it_layout = m_layout.begin();
        it_layout != m_layout.end();
        it_layout ++) {
        QPushButton* indexButton = new QPushButton(this);
        QVector<PieceButton*> rowPieceButtons;
        indexButton->setStyleSheet("background-color: #ff6600; border-radius: 3px; width: 40px; height: 40px; max-height: 40px; max-width: 40px;");
        indexButton->setText(QString::number(row));
        (*it_layout)->addWidget(indexButton);
        for(int column = 0; column < 19; column ++) {
            PieceButton* button = new PieceButton(column, row, this);
            rowPieceButtons.push_back(button);
            connect(button, SIGNAL(buttonPressed(int, int)), this, SLOT(onButtonPressed(int, int)));
            (*it_layout)->addWidget(button);
        }
        m_buttons.push_back(rowPieceButtons);
        row ++;
    }

    m_blackPlayerSelector = new QMessageBox(this);
    m_blackPlayerSelector->setText("執黑玩家為?");
    m_blackPlayerSelector->addButton("電腦", QMessageBox::YesRole);
    m_blackPlayerSelector->addButton("玩家", QMessageBox::NoRole);
    m_blackPlayerSelector->show();
    connect(m_blackPlayerSelector, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onPlayerRoleChosen(QAbstractButton*)));

    m_whitePlayerSelector = new QMessageBox(this);
    m_whitePlayerSelector->setText("執白玩家為?");
    m_whitePlayerSelector->addButton("電腦", QMessageBox::YesRole);
    m_whitePlayerSelector->addButton("玩家", QMessageBox::NoRole);
    m_whitePlayerSelector->show();
    connect(m_whitePlayerSelector, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onPlayerRoleChosen(QAbstractButton*)));

    connect(m_playground, SIGNAL(newPieceLocated(int, int, Piece::STATUS)), this, SLOT(onNewPieceLocated(int, int, Piece::STATUS)));
}

void MainWindow::onBlackPlayerRoleChosen(QAbstractButton *button)
{
    QMessageBox::ButtonRole role = m_blackPlayerSelector->buttonRole(button);
    if(role == QMessageBox::YesRole) {
        m_blackPlayer = Player::TYPE::AI;
        qDebug() << "[Log] 執黑者為AI";
    } else if (role == QMessageBox::NoRole) {
        m_blackPlayer = Player::TYPE::PLAYER;
        qDebug() << "[Log] 執黑者為玩家";
    }
}

void MainWindow::onWhitePlayerRoleChosen(QAbstractButton *button)
{
    QMessageBox::ButtonRole role = m_whitePlayerSelector->buttonRole(button);
    if(role == QMessageBox::YesRole) {
        m_whitePlayer = Player::TYPE::AI;
        qDebug() << "[Log] 執黑者為AI";
    } else if (role == QMessageBox::NoRole) {
        m_whitePlayer = Player::TYPE::PLAYER;
        qDebug() << "[Log] 執黑者為玩家";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
