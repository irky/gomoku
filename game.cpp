#include "game.h"

Game::Game()
{
    userMoveAllowed = true;

    gameBoard.reserve(15);
    for(int i = 0; i < 15; i++)
    {
        std::vector<int> vect;
        vect.reserve(15);
        for(int j = 0; j < 15; j++)
        {
            vect.push_back(0);
        }
        gameBoard.push_back(vect);
    }
}

int Game::getCPUValue() const
{
    return CPU;
}

int Game::getUserValue() const
{
    return USER;
}

void Game::setUserMoveAllowed(bool value)
{
    userMoveAllowed = value;
}

bool Game::isUserMoveAllowed() const
{
    return userMoveAllowed;
}

bool Game::checkIfMovePossible(const int &row, const int &col)
{
    qDebug() << "Checking if move possible";
    if(!gameBoard[row][col])
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Game::setCPUCoordinates(const std::pair<int, int> &coord)
{
    CPUCoordinates = coord;
}

// row and col in game board
QPointF Game::countCPUBoardPoint() const
{
    QPointF point(-225+(30*CPUCoordinates.first), -225+(30*CPUCoordinates.second));
    qDebug() << " coordinate x " << point.x() << " coordinate y " << point.y();
    return point;
}

void Game::cpuMove()
{
    emit drawCPUMoveRequest();
}

// algorithm to CPU's move
// returns best possible move coordinates
void Game::countCPUMove()
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(checkIfMovePossible(i,j))
            {
                qDebug() << " row " << i << " col " << j;
                setCPUCoordinates(std::pair<int,int>(i,j));
                cpuMove();
                return;
            }
        }
    }
}

void Game::updateGameBoard(const int &x, const int &y, const int &who)
{
    gameBoard[x][y] = who;
}


std::pair<int, int> Game::countGameBoardCoordinates(const int &row, const int &column) const
{
    int coordinate_counter = -225;
    int x = 0;
    int y = 0;

    while(coordinate_counter < row)
    {
        x++;
        coordinate_counter += 30;
    }
    qDebug() << "point first " << x;

    coordinate_counter = -225;
    while(coordinate_counter < column)
    {
        y++;
        coordinate_counter += 30;
    }
    qDebug() << "point first " << y;

    std::pair<int, int> point(x,y);
    return point;
}
