#include "game.h"

Game::Game()
{
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

bool Game::checkIfMovePossible(const int &row, const int &col)
{
    if(!gameBoard[row][col])
    {
        return true;
    }
    else
    {
        return false;
    }
}

// row and col in game board
QPointF Game::countBoardPoint(const int &row, const int &col) const
{
    QPointF point(FIRST_GRID_CENTRE+(GRID_STEP*row), FIRST_GRID_CENTRE+(GRID_STEP*col));
    return point;
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
                updateGameBoard(i, j, CPU);
                QPointF point = countBoardPoint(i,j);
                emit drawCPUMoveRequest(point.x(), point.y());
                return;
            }
        }
    }
}

void Game::countUserMove(const int &row, const int &col)
{
    std::pair<int, int> boardPoint = countGameBoardCoordinates(row, col);
    if(checkIfMovePossible(boardPoint.first, boardPoint.second))
    {
        updateGameBoard(boardPoint.first, boardPoint.second, USER);
        emit drawUserMoveRequest(row, col);
    }
}

void Game::updateGameBoard(const int &x, const int &y, const int &who)
{
    gameBoard[x][y] = who;
}


int Game::countSingleCoordinate(const int &row) const
{
    int coordinateCounter = FIRST_GRID_CENTRE;
    int x = 0;
    while(coordinateCounter < row)
    {
        x++;
        coordinateCounter += GRID_STEP;
    }
    return x;
}

std::pair<int, int> Game::countGameBoardCoordinates(const int &row, const int &column) const
{
    std::pair<int, int> point(countSingleCoordinate(row), countSingleCoordinate(column));
    return point;
}
