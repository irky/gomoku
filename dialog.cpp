#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{   
    ui->setupUi(this);

    board = new Board(this);
    ui->graphicsView->setScene(board);

    game = new Game();

    resize(530,550);

    connect(board, SIGNAL(userMoveRequest(int,int)), game, SLOT(countUserMove(int,int)));
    connect(game, SIGNAL(drawUserMoveRequest(int,int)), board, SLOT(drawUserMove(int,int)));
    connect(board, SIGNAL(CPUMoveRequest()), game, SLOT(countCPUMove()));
    connect(game, SIGNAL(drawCPUMoveRequest(int,int)), board, SLOT(drawCPUMove(int,int)));
    connect(board, SIGNAL(stopGame(bool)), game, SLOT(clearGameStatus(bool)));
    connect(this, SIGNAL(clearBoard()), board, SLOT(cleanBoardAndGameStatus()));
    connect(this, SIGNAL(letCPUBegin()), game, SLOT(countCPUMove()));
}

Dialog::~Dialog()
{
    delete ui;
    delete view;
    delete board;
    delete game;
}

void Dialog::on_infoButton_clicked()
{
    QMessageBox::information(this, "Informacje o grze",
                             "Gomoku v1.0\n"
                             "Autor: Paulina Wolak\n"
                             "Projekt wykonany w ramach kursu Metody Sztucznej Inteligencji");
}

void Dialog::on_stopButton_clicked()
{
    // stop game - clear all game data
    ui->startGameButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    emit clearBoard();
}

void Dialog::on_startGameButton_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Start Game", "Can CPU begin?", QMessageBox::Yes | QMessageBox::No);
    ui->startGameButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
    if(reply == QMessageBox::Yes)
    {
        // let CPU begin
        emit letCPUBegin();
    }
    else
    {
        // let user begin
        board->setUserMoveAllowed(true);
    }
}
