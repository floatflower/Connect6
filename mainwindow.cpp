#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "piecebutton.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_state(MainWindow::STATE::BLACK)
{
    ui->setupUi(this);
    this->setWindowTitle("Connect6 by FloatFlower.Huang");
    PieceButton* button = new PieceButton(0, 0);
    connect(button, SIGNAL(buttonPressed(int, int)), this, SLOT(onButtonPressed(int, int)));
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

    int row = 0;
    for(QVector<QHBoxLayout*>::iterator it_layout = m_layout.begin();
        it_layout != m_layout.end();
        it_layout ++) {
        for(int column = 0; column < 15; column ++) {
            PieceButton* button = new PieceButton(column, row);
            connect(button, SIGNAL(buttonPressed(int, int)), this, SLOT(onButtonPressed(int, int)));
            (*it_layout)->addWidget(button);
        }
        row ++;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
