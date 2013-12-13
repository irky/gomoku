#include "game.h"

Game::Game()
{
    gameBoard.reserve(BOARD_SIZE);
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        std::vector<int> vect;
        vect.reserve(15);
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            vect.push_back(0);
        }
        gameBoard.push_back(vect);
    }

    gameFinished = false;
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

bool Game::checkIfWinConfiguration(const int& who)
{
    if(checkWinHorizontal(who) || checkWinVertical(who) || checkWinDiagonal(who))
    {
        return true;
    }
    return false;
}

bool Game::checkWinHorizontal(const int& who)
{
    unsigned int stoneCounter = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(gameBoard[j][i] == who)
            {
                stoneCounter++;
                if(stoneCounter == 5)
                {
                    setGameFinished(true);
                    return true;
                }
                continue;
            }
            else
            {
                stoneCounter = 0;
            }
        }
    }
    return false;
}

bool Game::checkWinVertical(const int& who)
{
    unsigned int stoneCounter = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(gameBoard[i][j] == who)
            {
                stoneCounter++;
                if(stoneCounter == 5)
                {
                    setGameFinished(true);
                    return true;
                }
                continue;
            }
            else
            {
                stoneCounter = 0;
            }
        }
    }
    return false;
}

bool Game::checkWinDiagonal(const int& who)
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(gameBoard[i][j] == who)
            {
                int diagonalCounter = 1;
                if(j <= 10 && i <=10)
                {
                    while(gameBoard[i+diagonalCounter][j+diagonalCounter] == who)
                    {
                        diagonalCounter++;
                        if(diagonalCounter == 5)
                        {
                            setGameFinished(true);
                            return true;
                        }

                    }
                }
                diagonalCounter = 1;
                if(j >= 5 && i <= 10)
                {
                    while(gameBoard[i+diagonalCounter][j-diagonalCounter] == who)
                    {
                        diagonalCounter++;
                        if(diagonalCounter == 5)
                        {
                            setGameFinished(true);
                            return true;
                        }

                    }
                }
                diagonalCounter = 1;
                if(j <= 10 && i >= 5)
                {
                    while(gameBoard[i-diagonalCounter][j+diagonalCounter] == who)
                    {
                        diagonalCounter++;
                        if(diagonalCounter == 5)
                        {
                            setGameFinished(true);
                            return true;
                        }

                    }
                }
                diagonalCounter = 1;
                if(j >= 5 && i >= 5)
                {
                    while(gameBoard[i-diagonalCounter][j-diagonalCounter] == who)
                    {
                        diagonalCounter++;
                        if(diagonalCounter == 5)
                        {
                            setGameFinished(true);
                            return true;
                        }

                    }
                }
            }
        }
    }
    return false;
}

void Game::setGameFinished(const bool &value)
{
    gameFinished = value;
}

// algorithm to CPU's move
// returns best possible move coordinates
void Game::countCPUMove()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(checkIfMovePossible(i,j))
            {
                QPointF point = countBoardPoint(i,j);
                int value = updateGameBoard(i, j, CPU);
                if(0 == value)
                {
                    emit drawCPUMoveRequest(point.x(), point.y(), false);
                }
                else if(CPU == value) // cpu won
                {
                    emit drawCPUMoveRequest(point.x(), point.y(), true);
                    emit winGameFinishRequest(CPU);
                }
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
        int value = updateGameBoard(boardPoint.first, boardPoint.second, USER);
        if(0 == value)
        {
            emit drawUserMoveRequest(row, col, false);
        }
        else if(USER == value) // user won
        {
            emit drawUserMoveRequest(row, col, true);
            emit winGameFinishRequest(USER);
        }
    }
}

void Game::clearGameStatus(const bool &value)
{
    setGameFinished(value);
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            gameBoard[i][j] = 0;
        }
    }

}

int Game::updateGameBoard(const int &x, const int &y, const int &who)
{
    gameBoard[x][y] = who;

    if(checkIfWinConfiguration(who))
    {
        return who;
    }
    return 0;
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
