#include "game.h"

Game::Game()
{
    userMoveAllowed = false;
    gameBoard = new QGenericMatrix<15,15,int>();
}

Game::Game(const Game &)
{
}

Game::Game(QObject *parent) : QObject(parent)
{
}

void Game::userMove(const QPointF &point)
{

}

void Game::checkIfMovePossible()
{
    qDebug() << "Checking if move possible";
    emit allowUserMove();
}

void Game::allowUserMove(int x, int y)
{
    qDebug() << "User move allowed";
}

void Game::cpuMove()
{
}

void Game::countCPUMove()
{
}

void Game::updateGameBoard()
{
}
