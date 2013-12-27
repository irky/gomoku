#include "game.h"

Game::Game() :
    gameFinished(false),
    firstCPUMove(true),
    gameBoardPoint(0,0)
{
    gameBoard.reserve(BOARD_SIZE);
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        std::vector<int> vect;
        vect.reserve(BOARD_SIZE);
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            vect.push_back(0);
        }
        gameBoard.push_back(vect);
    }

    pointBoard.reserve(BOARD_SIZE);
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        std::vector<int> vect;
        vect.reserve(BOARD_SIZE);
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            vect.push_back(0);
        }
        pointBoard.push_back(vect);
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
        stoneCounter = 0;
    }
    return false;
}

bool Game::checkWinVertical(const int& who)
{
    unsigned int stoneCounter = 0;
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int j = 0; j < BOARD_SIZE; j++)
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
        stoneCounter = 0;
    }
    return false;
}

bool Game::checkWinDiagonal(const int& who)
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int j = 0; j < BOARD_SIZE; j++)
        {
            if(gameBoard[i][j] == who)
            {
                unsigned int diagonalCounter = 1;
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
                if(j >= 4 && i <= 10)
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
                if(j <= 10 && i >= 4)
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
                if(j >= 4 && i >= 4)
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

void Game::makeFirstCPUMove()
{
    // TODO: look for user's first move and place rock nearby
    if(checkIfMovePossible(8,8))
    {
        setGameBoardPoint(4,4);
        makeCPUMove(gameBoardPoint.first,gameBoardPoint.second);
        firstCPUMove = false;
    }
    else
    {
        setGameBoardPoint(10,10);
        makeCPUMove(gameBoardPoint.first,gameBoardPoint.second);
        firstCPUMove = false;
    }
}

void Game::buildThreat()
{
    if(firstCPUMove)
    {
        makeFirstCPUMove();
        return;
    }
    else
    {
        if(lookForCPUTwo())
        {
            return;
        }
        else if(lookForCPUSingle())
        {
            return;
        }
    }
}

void Game::lookForFourVertical(const int &who, const int &points)
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // OOOO-
                if(gameBoard[i][j] == who && gameBoard[i][j+1] == who &&
                   gameBoard[i][j+2] == who && gameBoard[i][j+3] == who && gameBoard[i][j+4] == 0)
                {
                    pointBoard[i][j+4] += points;
                }
                // -OOOO
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == who &&
                        gameBoard[i][j+2] == who && gameBoard[i][j+3] == who && gameBoard[i][j+4] == who)
                {
                    pointBoard[i][j] += points;
                }
            }
        }
    }
}

void Game::lookForFourHorizontal(const int &who, const int &points)
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // OOOO-
                if(gameBoard[j][i] == who && gameBoard[j+1][i] == who &&
                   gameBoard[j+2][i] == who && gameBoard[j+3][i] == who && gameBoard[j+4][i] == 0)
                {
                    pointBoard[j+4][i] += points;
                }
                // -OOOO
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == who &&
                        gameBoard[j+2][i] == who && gameBoard[j+3][i] == who && gameBoard[j+4][i] == who)
                {
                    pointBoard[j][i] += points;
                }
            }
        }
    }
}

void Game::lookForCPUFourDiagonal(const int &who, const int &points)
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            // lewy gorny, prawy dolny rog
            if(j <= 10 && i <= 10)
            {
                // OOOO-
                if(gameBoard[i][j] == who && gameBoard[i+1][j+1] == who &&
                   gameBoard[i+2][j+2] == who && gameBoard[i+3][j+3] == who && gameBoard[i+4][j+4] == 0)
                {
                    pointBoard[i+4][j+4] += points;
                }
                // -OOOO
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == who &&
                        gameBoard[i+2][j+2] == who && gameBoard[i+3][j+3] == who && gameBoard[i+4][j+4] == who)
                {
                    pointBoard[i][j] += points;
                }
            }
            // lewy dolny, prawy gorny rog
            if(j <= 10 && i >= 4)
            {
                // OOOO-
                if(gameBoard[i][j] == who && gameBoard[i-1][j+1] == who &&
                   gameBoard[i-2][j+2] == who && gameBoard[i-3][j+3] == who && gameBoard[i-4][j+4] == 0)
                {
                    pointBoard[i-4][j+4] += points;
                }
                // -OOOO
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == who &&
                        gameBoard[i-2][j+2] == who && gameBoard[i-3][j+3] == who && gameBoard[i-4][j+4] == who)
                {
                    pointBoard[i][j] += points;
                }
            }
        }
    }
}

void Game::lookForFour()
{
    lookForFourVertical(CPU, CPU_4);
    lookForFourVertical(USER, USER_4);
    lookForFourHorizontal(CPU, CPU_4);
    lookForFourHorizontal(USER, USER_4);
    lookForCPUFourDiagonal(CPU, CPU_4);
    lookForCPUFourDiagonal(USER, USER_4);
}

void Game::lookForBrokenFour()
{
    lookForBrokenFourVertical(CPU, CPU_4);
    lookForBrokenFourVertical(USER, USER_4);
    lookForBrokenFourHorizontal(CPU, CPU_4);
    lookForBrokenFourHorizontal(USER, USER_4);
    lookForBrokenFourDiagonal(CPU, CPU_4);
    lookForBrokenFourDiagonal(USER, USER_4);
}

void Game::lookForBrokenFourVertical(const int &who, const int &points)
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // O-OOO
                if(gameBoard[i][j] == who && gameBoard[i][j+1] == 0 &&
                   gameBoard[i][j+2] == who && gameBoard[i][j+3] == who && gameBoard[i][j+4] == who)
                {
                    pointBoard[i][j+1] += points;
                }
                // OOO-O
                else if(gameBoard[i][j] == who && gameBoard[i][j+1] == who &&
                        gameBoard[i][j+2] == who && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == who)
                {
                    pointBoard[i][j+3] += points;
                }
                // OO-OO
                else if(gameBoard[i][j] == who && gameBoard[i][j+1] == who &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == who && gameBoard[i][j+4] == who)
                {
                    pointBoard[i][j+2] += points;
                }
            }
        }
    }
}

void Game::lookForBrokenFourHorizontal(const int &who, const int &points)
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                if(gameBoard[j][i] == who && gameBoard[j+1][i] == who &&
                   gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == who && gameBoard[j+4][i] == who)
                {
                    pointBoard[j+2][i] += points;
                }
                else if(gameBoard[j][i] == who && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == who && gameBoard[j+3][i] == who && gameBoard[j+4][i] == who)
                {
                    pointBoard[j+1][i] += points;
                }
                else if(gameBoard[j][i] == who && gameBoard[j+1][i] == who &&
                        gameBoard[j+2][i] == who && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == who)
                {
                    pointBoard[j+3][i] += points;
                }
            }
        }
    }
}

void Game::lookForBrokenFourDiagonal(const int &who, const int &points)
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            // lewy gorny, prawy dolny rog
            if(j <= 10 && i <= 10)
            {
                if(gameBoard[i][j] == who && gameBoard[i+1][j+1] == who &&
                   gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == who && gameBoard[i+4][j+4] == who)
                {
                    pointBoard[j+2][i+2] += points;
                }
                else if(gameBoard[i][j] == who && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == who && gameBoard[i+3][j+3] == who && gameBoard[i+4][j+4] == who)
                {
                    pointBoard[j+1][i+1] += points;
                }
                else if(gameBoard[i][j] == who && gameBoard[i+1][j+1] == who &&
                        gameBoard[i+2][j+2] == who && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == who)
                {
                    pointBoard[j+3][i+3] += points;
                }
            }
            // lewy dolny, prawy gorny rog
            if(j <= 10 && i >= 4)
            {
                if(gameBoard[i][j] == who && gameBoard[i-1][j+1] == who &&
                   gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == who && gameBoard[i-4][j+4] == who)
                {
                    pointBoard[j-2][i+2] += points;
                }
                else if(gameBoard[i][j] == who && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == who && gameBoard[i-3][j+3] == who && gameBoard[i-4][j+4] == who)
                {
                    pointBoard[j-1][i+1] += points;
                }
                else if(gameBoard[i][j] == who && gameBoard[i-1][j+1] == who &&
                        gameBoard[i-2][j+2] == who && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == who)
                {
                    pointBoard[j-3][i+3] += points;
                }
            }
        }
    }
}


bool Game::lookForOpponentThree()
{
    if(lookForOpponentThreeHorizontal1Priority())
    {
        qDebug() << "Found opponent 3 horizontal";
        return true;
    }
    else if(lookForOpponentThreeVertical1Priority())
    {
        qDebug() << "Found opponent 3 vertical";
        return true;
    }
    else if(lookForOpponentThreeDiagonal1Priority())
    {
        qDebug() << "Found opponent 3 diagonal";
        return true;
    }
    else if(lookForOpponentThreeHorizontal2Priority())
    {
        qDebug() << "Found opponent 3 horizontal";
        return true;
    }
    else if(lookForOpponentThreeVertical2Priority())
    {
        qDebug() << "Found opponent 3 vertical";
        return true;
    }
    else if(lookForOpponentThreeDiagonal2Priority())
    {
        qDebug() << "Found opponent 3 diagonal";
        return true;
    }
    else if(lookForOpponentThreeHorizontal3Priority())
    {
        qDebug() << "Found opponent 3 horizontal";
        return true;
    }
    else if(lookForOpponentThreeVertical3Priority())
    {
        qDebug() << "Found opponent 3 vertical";
        return true;
    }
    else if(lookForOpponentThreeDiagonal3Priority())
    {
        qDebug() << "Found opponent 3 diagonal";
        return true;
    }
    else if(lookForOpponentThreeHorizontal4Priority())
    {
        qDebug() << "Found opponent 3 horizontal";
        return true;
    }
    else if(lookForOpponentThreeVertical4Priority())
    {
        qDebug() << "Found opponent 3 vertical";
        return true;
    }
    else if(lookForOpponentThreeDiagonal4Priority())
    {
        qDebug() << "Found opponent 3 diagonal";
        return true;
    }
    return false;
}

bool Game::lookForOpponentThreeHorizontal1Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 8)
            {
                // --OOO--
                if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                   gameBoard[i][j+2] == USER && gameBoard[i][j+3] == USER &&
                   gameBoard[i][j+4] == USER && gameBoard[i][j+5] == 0 && gameBoard[i][j+6] == 0)
                {
                    setGameBoardPoint(i,j+1);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForOpponentThreeVertical1Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 8)
            {
                // --OOO--
                if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                   gameBoard[j+2][i] == USER && gameBoard[j+3][i] == USER &&
                   gameBoard[j+4][i] == USER && gameBoard[j+5][i] == 0 && gameBoard[j+6][i] == 0)
                {
                    setGameBoardPoint(j+1,i);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForOpponentThreeDiagonal1Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 8 && i <= 8)
            {
                // --OOO--
                if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                   gameBoard[i+2][j+2] == USER && gameBoard[i+3][j+3] == USER &&
                   gameBoard[i+4][j+4] == USER && gameBoard[i+5][j+5] == 0 && gameBoard[i+6][j+6] == 0)
                {
                    setGameBoardPoint(i+5,j+5);
                    return true;
                }
            }
            if(j <=8 && i >= 6)
            {
                // --OOO--
                if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                   gameBoard[i-2][j+2] == USER && gameBoard[i-3][j+3] == USER &&
                   gameBoard[i-4][j+4] == USER && gameBoard[i-5][j+5] == 0 && gameBoard[i-6][j+6] == 0)
                {
                    setGameBoardPoint(i-5,j+5);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForOpponentThreeHorizontal2Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 9)
            {
                // --000-
                if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                   gameBoard[i][j+2] == USER && gameBoard[i][j+3] == USER &&
                   gameBoard[i][j+4] == USER && gameBoard[i][j+5] == 0)
                {
                    setGameBoardPoint(i,j+1);
                    return true;
                }
                // -000--
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == USER &&
                        gameBoard[i][j+2] == USER && gameBoard[i][j+3] == USER &&
                        gameBoard[i][j+4] == 0 && gameBoard[i][j+5] == 0)
                {
                    setGameBoardPoint(i,j+4);
                    return true;
                }
                // -00-0-
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == USER &&
                        gameBoard[i][j+2] == USER && gameBoard[i][j+3] == 0 &&
                        gameBoard[i][j+4] == USER && gameBoard[i][j+5] == 0)
                {
                    setGameBoardPoint(i,j+3);
                    return true;
                }
                // -0-00-
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == USER &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == USER &&
                        gameBoard[i][j+4] == USER && gameBoard[i][j+5] == 0)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForOpponentThreeVertical2Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 9)
            {
                // --000-
                if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                   gameBoard[j+2][i] == USER && gameBoard[j+3][i] == USER &&
                   gameBoard[j+4][i] == USER && gameBoard[j+5][i] == 0)
                {
                    setGameBoardPoint(j+1,i);
                    return true;
                }
                // -000--
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == USER &&
                        gameBoard[j+2][i] == USER && gameBoard[j+3][i] == USER &&
                        gameBoard[j+4][i] == 0 && gameBoard[j+5][i] == 0)
                {
                    setGameBoardPoint(j+4,i);
                    return true;
                }
                // -00-0-
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == USER &&
                        gameBoard[j+2][i] == USER && gameBoard[j+3][i] == 0 &&
                        gameBoard[j+4][i] == USER && gameBoard[j+5][i] == 0)
                {
                    setGameBoardPoint(j+3,i);
                    return true;
                }
                // -0-00-
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == USER &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == USER &&
                        gameBoard[j+4][i] == USER && gameBoard[j+5][i] == 0)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForOpponentThreeDiagonal2Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 9 && i <= 9)
            {
                // --000-
                if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                   gameBoard[i+2][j+2] == USER && gameBoard[i+3][j+3] == USER &&
                   gameBoard[i+4][j+4] == USER && gameBoard[i+5][j+5] == 0)
                {
                    setGameBoardPoint(i+1,j+1);
                    return true;
                }
                // -000--
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == USER &&
                        gameBoard[i+2][j+2] == USER && gameBoard[i+3][j+3] == USER &&
                        gameBoard[i+4][j+4] == 0 && gameBoard[i+5][j+5] == 0)
                {
                    setGameBoardPoint(i+4,j+4);
                    return true;
                }
                // -00-0-
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == USER &&
                        gameBoard[i+2][j+2] == USER && gameBoard[i+3][j+3] == 0 &&
                        gameBoard[i+4][j+4] == USER && gameBoard[i+5][j+5] == 0)
                {
                    setGameBoardPoint(i+3,j+3);
                    return true;
                }
                // -0-00-
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == USER &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == USER &&
                        gameBoard[i+4][j+4] == USER && gameBoard[i+5][j+5] == 0)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
            }
            if(j <= 9 && i >= 5)
            {
                // --000-
                if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                   gameBoard[i-2][j+2] == USER && gameBoard[i-3][j+3] == USER &&
                   gameBoard[i-4][j+4] == USER && gameBoard[i-5][j+5] == 0)
                {
                    setGameBoardPoint(i-1,j+1);
                    return true;
                }
                // -000--
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == USER &&
                        gameBoard[i-2][j+2] == USER && gameBoard[i-3][j+3] == USER &&
                        gameBoard[i-4][j+4] == 0 && gameBoard[i-5][j+5] == 0)
                {
                    setGameBoardPoint(i-4,j+4);
                    return true;
                }
                // -00-0-
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == USER &&
                        gameBoard[i-2][j+2] == USER && gameBoard[i-3][j+3] == 0 &&
                        gameBoard[i-4][j+4] == USER && gameBoard[i-5][j+5] == 0)
                {
                    setGameBoardPoint(i-3,j+3);
                    return true;
                }
                // -0-00-
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == USER &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == USER &&
                        gameBoard[i-4][j+4] == USER && gameBoard[i-5][j+5] == 0)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForOpponentThreeHorizontal3Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 8)
            {
                if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == USER &&
                   gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == USER &&
                   gameBoard[i][j+4] == 0 && gameBoard[i][j+5] == USER && gameBoard[i][j+6] == 0)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == USER &&
                        gameBoard[i][j+2] == USER && gameBoard[i][j+3] == 0 &&
                        gameBoard[i][j+4] == 0 && gameBoard[i][j+5] == USER && gameBoard[i][j+6] == 0)
                {
                    setGameBoardPoint(i,j+4);
                    return true;
                }
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == USER &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == 0 &&
                        gameBoard[i][j+4] == USER && gameBoard[i][j+5] == USER && gameBoard[i][j+6] == 0)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForOpponentThreeVertical3Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 8)
            {
                if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == USER &&
                   gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == USER &&
                   gameBoard[j+4][i] == 0 && gameBoard[j+5][i] == USER && gameBoard[j+6][i] == 0)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == USER &&
                        gameBoard[j+2][i] == USER && gameBoard[j+3][i] == 0 &&
                        gameBoard[j+4][i] == 0 && gameBoard[j+5][i] == USER && gameBoard[j+6][i] == 0)
                {
                    setGameBoardPoint(j+4,i);
                    return true;
                }
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == USER &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == 0 &&
                        gameBoard[j+4][i] == USER && gameBoard[j+5][i] == USER && gameBoard[j+6][i] == 0)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForOpponentThreeDiagonal3Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 8 && i <= 8)
            {
                if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == USER &&
                   gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == USER &&
                   gameBoard[i+4][j+4] == 0 && gameBoard[i+5][j+5] == USER && gameBoard[i+6][j+6] == 0)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == USER &&
                        gameBoard[i+2][j+2] == USER && gameBoard[i+3][j+3] == 0 &&
                        gameBoard[i+4][j+4] == 0 && gameBoard[i+5][j+5] == USER && gameBoard[i+6][j+6] == 0)
                {
                    setGameBoardPoint(i+4,j+4);
                    return true;
                }
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == USER &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == 0 &&
                        gameBoard[i+2][j+4] == USER && gameBoard[i+5][j+5] == USER && gameBoard[i+6][j+6] == 0)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
            }
            if(j <=8 && i >= 6)
            {
                if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == USER &&
                   gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == USER &&
                   gameBoard[i-4][j+4] == 0 && gameBoard[i-5][j+5] == USER && gameBoard[i-6][j+6] == 0)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == USER &&
                        gameBoard[i-2][j+2] == USER && gameBoard[i-3][j+3] == 0 &&
                        gameBoard[i-4][j+4] == 0 && gameBoard[i-5][j+5] == USER && gameBoard[i-6][j+6] == 0)
                {
                    setGameBoardPoint(i-4,j+4);
                    return true;
                }
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == USER &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == 0 &&
                        gameBoard[i-2][j+4] == USER && gameBoard[i-5][j+5] == USER && gameBoard[i-6][j+6] == 0)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForOpponentThreeHorizontal4Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // -000-
                if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == USER &&
                   gameBoard[i][j+2] == USER && gameBoard[i][j+3] == USER &&
                   gameBoard[i][j+4] == 0)
                {
                    if(j >= 1)
                    {
                        setGameBoardPoint(i,j);
                        return true;
                    }
                    else
                    {
                        setGameBoardPoint(i,j+4);
                        return true;
                    }
                }
                // 000--
                else if(gameBoard[i][j] == USER && gameBoard[i][j+1] == USER &&
                        gameBoard[i][j+2] == USER && gameBoard[i][j+3] == 0 &&
                        gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+3);
                    return true;
                }
                // --000
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == USER && gameBoard[i][j+3] == USER &&
                        gameBoard[i][j+4] == USER)
                {
                    setGameBoardPoint(i,j+1);
                    return true;
                }
                // -0-00
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == USER &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == USER &&
                        gameBoard[i][j+4] == USER)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
                // 00-0-
                else if(gameBoard[i][j] == USER && gameBoard[i][j+1] == USER &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == USER &&
                        gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
                // 0-0-0
                else if(gameBoard[i][j] == USER && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == USER && gameBoard[i][j+3] == 0 &&
                        gameBoard[i][j+4] == USER)
                {
                    if(j >= 2)
                    {
                        setGameBoardPoint(i,j+1);
                        return true;
                    }
                    else
                    {
                        setGameBoardPoint(i,j+3);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Game::lookForOpponentThreeVertical4Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // -000-
                if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == USER &&
                   gameBoard[j+2][i] == USER && gameBoard[j+3][i] == USER &&
                   gameBoard[j+4][i] == 0)
                {
                    if(j >= 1)
                    {
                        setGameBoardPoint(j,i);
                        return true;
                    }
                    else
                    {
                        setGameBoardPoint(j+4,i);
                        return true;
                    }
                }
                // 000--
                else if(gameBoard[j][i] == USER && gameBoard[j+1][i] == USER &&
                        gameBoard[j+2][i] == USER && gameBoard[j+3][i] == 0 &&
                        gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+3,i);
                    return true;
                }
                // --000
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == USER && gameBoard[j+3][i] == USER &&
                        gameBoard[j+4][i] == USER)
                {
                    setGameBoardPoint(j+1,i);
                    return true;
                }
                // -0-00
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == USER &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == USER &&
                        gameBoard[j+4][i] == USER)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
                // 00-0-
                else if(gameBoard[j][i] == USER && gameBoard[j+1][i] == USER &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == USER &&
                        gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
                // 0-0-0
                else if(gameBoard[j][i] == USER && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == USER && gameBoard[j+3][i] == 0 &&
                        gameBoard[j+4][i] == USER)
                {
                    if(j >= 2)
                    {
                        setGameBoardPoint(j+1,i);
                        return true;
                    }
                    else
                    {
                        setGameBoardPoint(j+3,i);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Game::lookForOpponentThreeDiagonal4Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10 && i <= 10)
            {
                // -000-
                if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == USER &&
                   gameBoard[i+2][j+2] == USER && gameBoard[i+3][j+3] == USER &&
                   gameBoard[i+4][j+4] == 0)
                {
                    if(j >= 1)
                    {
                        setGameBoardPoint(i,j);
                        return true;
                    }
                    else
                    {
                        setGameBoardPoint(i+4,j+4);
                        return true;
                    }
                }
                // 000--
                else if(gameBoard[i][j] == USER && gameBoard[i+1][j+1] == USER &&
                        gameBoard[i+2][j+2] == USER && gameBoard[i+3][j+3] == 0 &&
                        gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+3,j+3);
                    return true;
                }
                // --000
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == USER && gameBoard[i+3][j+3] == USER &&
                        gameBoard[i+4][j+4] == USER)
                {
                    setGameBoardPoint(i+1,j+1);
                    return true;
                }
                // -0-00
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == USER &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == USER &&
                        gameBoard[i+4][j+4] == USER)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
                // 00-0-
                else if(gameBoard[i][j] == USER && gameBoard[i+1][j+1] == USER &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == USER &&
                        gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
                // 0-0-0
                else if(gameBoard[i][j] == USER && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == USER && gameBoard[i+3][j+3] == 0 &&
                        gameBoard[i+4][j+4] == USER)
                {
                    if(j >= 2)
                    {
                        setGameBoardPoint(i+1,j+1);
                        return true;
                    }
                    else
                    {
                        setGameBoardPoint(i+3,j+3);
                        return true;
                    }
                }
            }

            if(j <= 10 && i >= 4)
            {
                // -000-
                if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == USER &&
                   gameBoard[i-2][j+2] == USER && gameBoard[i-3][j+3] == USER &&
                   gameBoard[i-4][j+4] == 0)
                {
                    if(j >= 1)
                    {
                        setGameBoardPoint(i,j);
                        return true;
                    }
                    else
                    {
                        setGameBoardPoint(i-4,j+4);
                        return true;
                    }
                }
                // 000--
                else if(gameBoard[i][j] == USER && gameBoard[i-1][j+1] == USER &&
                        gameBoard[i-2][j+2] == USER && gameBoard[i-3][j+3] == 0 &&
                        gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-3,j+3);
                    return true;
                }
                // --000
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == USER && gameBoard[i-3][j+3] == USER &&
                        gameBoard[i-4][j+4] == USER)
                {
                    setGameBoardPoint(i-1,j+1);
                    return true;
                }
                // -0-00
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == USER &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == USER &&
                        gameBoard[i-4][j+4] == USER)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
                // 00-0-
                else if(gameBoard[i][j] == USER && gameBoard[i-1][j+1] == USER &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == USER &&
                        gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
                // 0-0-0
                else if(gameBoard[i][j] == USER && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == USER && gameBoard[i-3][j+3] == 0 &&
                        gameBoard[i-4][j+4] == USER)
                {
                    if(j >= 2)
                    {
                        setGameBoardPoint(i-1,j+1);
                        return true;
                    }
                    else
                    {
                        setGameBoardPoint(i-3,j+3);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUThree()
{
    if(lookForCPUThreeHorizontal1Priority())
    {
        qDebug() << "Found CPU 3 horizontal";
        return true;
    }
    else if(lookForCPUThreeVertical1Priority())
    {
        qDebug() << "Found CPU 3 vertical";
        return true;
    }
    else if(lookForCPUThreeDiagonal1Priority())
    {
        qDebug() << "Found CPU 3 diagonal";
        return true;
    }
    if(lookForCPUThreeHorizontal2Priority())
    {
        qDebug() << "Found CPU 3 horizontal";
        return true;
    }
    else if(lookForCPUThreeVertical2Priority())
    {
        qDebug() << "Found CPU 3 vertical";
        return true;
    }
    else if(lookForCPUThreeDiagonal2Priority())
    {
        qDebug() << "Found CPU 3 diagonal";
        return true;
    }
    if(lookForCPUThreeHorizontal3Priority())
    {
        qDebug() << "Found CPU 3 horizontal";
        return true;
    }
    else if(lookForCPUThreeVertical3Priority())
    {
        qDebug() << "Found CPU 3 vertical";
        return true;
    }
    else if(lookForCPUThreeDiagonal3Priority())
    {
        qDebug() << "Found CPU 3 diagonal";
        return true;
    }
    if(lookForCPUThreeHorizontal4Priority())
    {
        qDebug() << "Found CPU 3 horizontal";
        return true;
    }
    else if(lookForCPUThreeVertical4Priority())
    {
        qDebug() << "Found CPU 3 vertical";
        return true;
    }
    else if(lookForCPUThreeDiagonal4Priority())
    {
        qDebug() << "Found CPU 3 diagonal";
        return true;
    }
    return false;
}

bool Game::lookForCPUThreeHorizontal1Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 8)
            {
                // --OOO--
                if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                   gameBoard[i][j+2] == CPU && gameBoard[i][j+3] == CPU &&
                   gameBoard[i][j+4] == CPU && gameBoard[i][j+5] == 0 && gameBoard[i][j+6] == 0)
                {
                    setGameBoardPoint(i,j+1);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUThreeVertical1Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 8)
            {
                // --OOO--
                if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                   gameBoard[j+2][i] == CPU && gameBoard[j+3][i] == CPU &&
                   gameBoard[j+4][i] == CPU && gameBoard[j+5][i] == 0 && gameBoard[j+6][i] == 0)
                {
                    setGameBoardPoint(j+1,i);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUThreeDiagonal1Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 8 && i <= 8)
            {
                // --OOO--
                if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                   gameBoard[i+2][j+2] == CPU && gameBoard[i+3][j+3] == CPU &&
                   gameBoard[i+4][j+4] == CPU && gameBoard[i+5][j+5] == 0 && gameBoard[i+6][j+6] == 0)
                {
                    setGameBoardPoint(i+5,j+5);
                    return true;
                }
            }
            if(j <=8 && i >= 6)
            {
                // --OOO--
                if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                   gameBoard[i-2][j+2] == CPU && gameBoard[i-3][j+3] == CPU &&
                   gameBoard[i-4][j+4] == CPU && gameBoard[i-5][j+5] == 0 && gameBoard[i-6][j+6] == 0)
                {
                    setGameBoardPoint(i-5,j+5);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUThreeHorizontal2Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 9)
            {
                // --000-
                if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                   gameBoard[i][j+2] == CPU && gameBoard[i][j+3] == CPU &&
                   gameBoard[i][j+4] == CPU && gameBoard[i][j+5] == 0)
                {
                    setGameBoardPoint(i,j+1);
                    return true;
                }
                // -000--
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == CPU &&
                        gameBoard[i][j+2] == CPU && gameBoard[i][j+3] == CPU &&
                        gameBoard[i][j+4] == 0 && gameBoard[i][j+5] == 0)
                {
                    setGameBoardPoint(i,j+4);
                    return true;
                }
                // -00-0-
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == CPU &&
                        gameBoard[i][j+2] == CPU && gameBoard[i][j+3] == 0 &&
                        gameBoard[i][j+4] == CPU && gameBoard[i][j+5] == 0)
                {
                    setGameBoardPoint(i,j+3);
                    return true;
                }
                // -0-00-
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == CPU &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == CPU &&
                        gameBoard[i][j+4] == CPU && gameBoard[i][j+5] == 0)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUThreeVertical2Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 9)
            {
                // --000-
                if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                   gameBoard[j+2][i] == CPU && gameBoard[j+3][i] == CPU &&
                   gameBoard[j+4][i] == CPU && gameBoard[j+5][i] == 0)
                {
                    setGameBoardPoint(j+1,i);
                    return true;
                }
                // -000--
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == CPU &&
                        gameBoard[j+2][i] == CPU && gameBoard[j+3][i] == CPU &&
                        gameBoard[j+4][i] == 0 && gameBoard[j+5][i] == 0)
                {
                    setGameBoardPoint(j+4,i);
                    return true;
                }
                // -00-0-
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == CPU &&
                        gameBoard[j+2][i] == CPU && gameBoard[j+3][i] == 0 &&
                        gameBoard[j+4][i] == CPU && gameBoard[j+5][i] == 0)
                {
                    setGameBoardPoint(j+3,i);
                    return true;
                }
                // -0-00-
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == CPU &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == CPU &&
                        gameBoard[j+4][i] == CPU && gameBoard[j+5][i] == 0)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUThreeDiagonal2Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 9 && i <= 9)
            {
                // --000-
                if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                   gameBoard[i+2][j+2] == CPU && gameBoard[i+3][j+3] == CPU &&
                   gameBoard[i+4][j+4] == CPU && gameBoard[i+5][j+5] == 0)
                {
                    setGameBoardPoint(i+1,j+1);
                    return true;
                }
                // -000--
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == CPU &&
                        gameBoard[i+2][j+2] == CPU && gameBoard[i+3][j+3] == CPU &&
                        gameBoard[i+4][j+4] == 0 && gameBoard[i+5][j+5] == 0)
                {
                    setGameBoardPoint(i+4,j+4);
                    return true;
                }
                // -00-0-
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == CPU &&
                        gameBoard[i+2][j+2] == CPU && gameBoard[i+3][j+3] == 0 &&
                        gameBoard[i+4][j+4] == CPU && gameBoard[i+5][j+5] == 0)
                {
                    setGameBoardPoint(i+3,j+3);
                    return true;
                }
                // -0-00-
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == CPU &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == CPU &&
                        gameBoard[i+4][j+4] == CPU && gameBoard[i+5][j+5] == 0)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
            }
            if(j <= 9 && i >= 5)
            {
                // --000-
                if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                   gameBoard[i-2][j+2] == CPU && gameBoard[i-3][j+3] == CPU &&
                   gameBoard[i-4][j+4] == CPU && gameBoard[i-5][j+5] == 0)
                {
                    setGameBoardPoint(i-1,j+1);
                    return true;
                }
                // -000--
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == CPU &&
                        gameBoard[i-2][j+2] == CPU && gameBoard[i-3][j+3] == CPU &&
                        gameBoard[i-4][j+4] == 0 && gameBoard[i-5][j+5] == 0)
                {
                    setGameBoardPoint(i-4,j+4);
                    return true;
                }
                // -00-0-
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == CPU &&
                        gameBoard[i-2][j+2] == CPU && gameBoard[i-3][j+3] == 0 &&
                        gameBoard[i-4][j+4] == CPU && gameBoard[i-5][j+5] == 0)
                {
                    setGameBoardPoint(i-3,j+3);
                    return true;
                }
                // -0-00-
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == CPU &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == CPU &&
                        gameBoard[i-4][j+4] == CPU && gameBoard[i-5][j+5] == 0)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUThreeHorizontal3Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 8)
            {
                if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == CPU &&
                   gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == CPU &&
                   gameBoard[i][j+4] == 0 && gameBoard[i][j+5] == CPU && gameBoard[i][j+6] == 0)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == CPU &&
                        gameBoard[i][j+2] == CPU && gameBoard[i][j+3] == 0 &&
                        gameBoard[i][j+4] == 0 && gameBoard[i][j+5] == CPU && gameBoard[i][j+6] == 0)
                {
                    setGameBoardPoint(i,j+4);
                    return true;
                }
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == CPU &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == 0 &&
                        gameBoard[i][j+4] == CPU && gameBoard[i][j+5] == CPU && gameBoard[i][j+6] == 0)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUThreeVertical3Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 8)
            {
                if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == CPU &&
                   gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == CPU &&
                   gameBoard[j+4][i] == 0 && gameBoard[j+5][i] == CPU && gameBoard[j+6][i] == 0)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == CPU &&
                        gameBoard[j+2][i] == CPU && gameBoard[j+3][i] == 0 &&
                        gameBoard[j+4][i] == 0 && gameBoard[j+5][i] == CPU && gameBoard[j+6][i] == 0)
                {
                    setGameBoardPoint(j+4,i);
                    return true;
                }
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == CPU &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == 0 &&
                        gameBoard[j+4][i] == CPU && gameBoard[j+5][i] == CPU && gameBoard[j+6][i] == 0)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUThreeDiagonal3Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 8 && i <= 8)
            {
                if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == CPU &&
                   gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == CPU &&
                   gameBoard[i+4][j+4] == 0 && gameBoard[i+5][j+5] == CPU && gameBoard[i+6][j+6] == 0)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == CPU &&
                        gameBoard[i+2][j+2] == CPU && gameBoard[i+3][j+3] == 0 &&
                        gameBoard[i+4][j+4] == 0 && gameBoard[i+5][j+5] == CPU && gameBoard[i+6][j+6] == 0)
                {
                    setGameBoardPoint(i+4,j+4);
                    return true;
                }
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == CPU &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == 0 &&
                        gameBoard[i+2][j+4] == CPU && gameBoard[i+5][j+5] == CPU && gameBoard[i+6][j+6] == 0)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
            }
            if(j <=8 && i >= 6)
            {
                if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == CPU &&
                   gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == CPU &&
                   gameBoard[i-4][j+4] == 0 && gameBoard[i-5][j+5] == CPU && gameBoard[i-6][j+6] == 0)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == CPU &&
                        gameBoard[i-2][j+2] == CPU && gameBoard[i-3][j+3] == 0 &&
                        gameBoard[i-4][j+4] == 0 && gameBoard[i-5][j+5] == CPU && gameBoard[i-6][j+6] == 0)
                {
                    setGameBoardPoint(i-4,j+4);
                    return true;
                }
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == CPU &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == 0 &&
                        gameBoard[i-2][j+4] == CPU && gameBoard[i-5][j+5] == CPU && gameBoard[i-6][j+6] == 0)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUThreeHorizontal4Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // -000-
                if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == CPU &&
                   gameBoard[i][j+2] == CPU && gameBoard[i][j+3] == CPU &&
                   gameBoard[i][j+4] == 0)
                {
                    if(j >= 1)
                    {
                        setGameBoardPoint(i,j);
                        return true;
                    }
                    else
                    {
                        setGameBoardPoint(i,j+4);
                        return true;
                    }
                }
                // 000--
                else if(gameBoard[i][j] == CPU && gameBoard[i][j+1] == CPU &&
                        gameBoard[i][j+2] == CPU && gameBoard[i][j+3] == 0 &&
                        gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+3);
                    return true;
                }
                // --000
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == CPU && gameBoard[i][j+3] == CPU &&
                        gameBoard[i][j+4] == CPU)
                {
                    setGameBoardPoint(i,j+1);
                    return true;
                }
                // -0-00
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == CPU &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == CPU &&
                        gameBoard[i][j+4] == CPU)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
                // 00-0-
                else if(gameBoard[i][j] == CPU && gameBoard[i][j+1] == CPU &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == CPU &&
                        gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
                // 0-0-0
                else if(gameBoard[i][j] == CPU && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == CPU && gameBoard[i][j+3] == 0 &&
                        gameBoard[i][j+4] == CPU)
                {
                    if(j >= 2)
                    {
                        setGameBoardPoint(i,j+1);
                        return true;
                    }
                    else
                    {
                        setGameBoardPoint(i,j+3);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUThreeVertical4Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // -000-
                if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == CPU &&
                   gameBoard[j+2][i] == CPU && gameBoard[j+3][i] == CPU &&
                   gameBoard[j+4][i] == 0)
                {
                    if(j >= 1)
                    {
                        setGameBoardPoint(j,i);
                        return true;
                    }
                    else
                    {
                        setGameBoardPoint(j+4,i);
                        return true;
                    }
                }
                // 000--
                else if(gameBoard[j][i] == CPU && gameBoard[j+1][i] == CPU &&
                        gameBoard[j+2][i] == CPU && gameBoard[j+3][i] == 0 &&
                        gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+3,i);
                    return true;
                }
                // --000
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == CPU && gameBoard[j+3][i] == CPU &&
                        gameBoard[j+4][i] == CPU)
                {
                    setGameBoardPoint(j+1,i);
                    return true;
                }
                // -0-00
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == CPU &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == CPU &&
                        gameBoard[j+4][i] == CPU)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
                // 00-0-
                else if(gameBoard[j][i] == CPU && gameBoard[j+1][i] == CPU &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == CPU &&
                        gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
                // 0-0-0
                else if(gameBoard[j][i] == CPU && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == CPU && gameBoard[j+3][i] == 0 &&
                        gameBoard[j+4][i] == CPU)
                {
                    if(j >= 2)
                    {
                        setGameBoardPoint(j+1,i);
                        return true;
                    }
                    else
                    {
                        setGameBoardPoint(j+3,i);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUThreeDiagonal4Priority()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10 && i <= 10)
            {
                // -000-
                if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == CPU &&
                   gameBoard[i+2][j+2] == CPU && gameBoard[i+3][j+3] == CPU &&
                   gameBoard[i+4][j+4] == 0)
                {
                    if(j >= 1)
                    {
                        setGameBoardPoint(i,j);
                        return true;
                    }
                    else
                    {
                        setGameBoardPoint(i+4,j+4);
                        return true;
                    }
                }
                // 000--
                else if(gameBoard[i][j] == CPU && gameBoard[i+1][j+1] == CPU &&
                        gameBoard[i+2][j+2] == CPU && gameBoard[i+3][j+3] == 0 &&
                        gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+3,j+3);
                    return true;
                }
                // --000
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == CPU && gameBoard[i+3][j+3] == CPU &&
                        gameBoard[i+4][j+4] == CPU)
                {
                    setGameBoardPoint(i+1,j+1);
                    return true;
                }
                // -0-00
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == CPU &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == CPU &&
                        gameBoard[i+4][j+4] == CPU)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
                // 00-0-
                else if(gameBoard[i][j] == CPU && gameBoard[i+1][j+1] == CPU &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == CPU &&
                        gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
                // 0-0-0
                else if(gameBoard[i][j] == CPU && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == CPU && gameBoard[i+3][j+3] == 0 &&
                        gameBoard[i+4][j+4] == CPU)
                {
                    if(j >= 2)
                    {
                        setGameBoardPoint(i+1,j+1);
                        return true;
                    }
                    else
                    {
                        setGameBoardPoint(i+3,j+3);
                        return true;
                    }
                }
            }

            if(j <= 10 && i >= 4)
            {
                // -000-
                if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == CPU &&
                   gameBoard[i-2][j+2] == CPU && gameBoard[i-3][j+3] == CPU &&
                   gameBoard[i-4][j+4] == 0)
                {
                    if(j >= 1)
                    {
                        setGameBoardPoint(i,j);
                        return true;
                    }
                    else
                    {
                        setGameBoardPoint(i-4,j+4);
                        return true;
                    }
                }
                // 000--
                else if(gameBoard[i][j] == CPU && gameBoard[i-1][j+1] == CPU &&
                        gameBoard[i-2][j+2] == CPU && gameBoard[i-3][j+3] == 0 &&
                        gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-3,j+3);
                    return true;
                }
                // --000
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == CPU && gameBoard[i-3][j+3] == CPU &&
                        gameBoard[i-4][j+4] == CPU)
                {
                    setGameBoardPoint(i-1,j+1);
                    return true;
                }
                // -0-00
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == CPU &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == CPU &&
                        gameBoard[i-4][j+4] == CPU)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
                // 00-0-
                else if(gameBoard[i][j] == CPU && gameBoard[i-1][j+1] == CPU &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == CPU &&
                        gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
                // 0-0-0
                else if(gameBoard[i][j] == CPU && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == CPU && gameBoard[i-3][j+3] == 0 &&
                        gameBoard[i-4][j+4] == CPU)
                {
                    if(j >= 2)
                    {
                        setGameBoardPoint(i-1,j+1);
                        return true;
                    }
                    else
                    {
                        setGameBoardPoint(i-3,j+3);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUTwo()
{
    if(lookForCPUTwoHorizontal())
    {
        qDebug() << "Found CPU two side 2 horizontal";
        return true;
    }
    else if(lookForCPUTwoVertical())
    {
        qDebug() << "Found CPU two side 2 vertical";
        return true;
    }
    else if(lookForCPUTwoDiagonal())
    {
        qDebug() << "Found CPU two side 2 diagonal";
        return true;
    }
    return false;
}

bool Game::lookForCPUTwoHorizontal()
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // --OO-
                if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                   gameBoard[i][j+2] == CPU && gameBoard[i][j+3] == CPU && gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+1);
                    return true;
                }
                // -OO--
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == CPU &&
                        gameBoard[i][j+2] == CPU && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+3);
                    return true;
                }
                // -0-0-
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == CPU &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == CPU && gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
                // --0-0
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == CPU && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == CPU)
                {
                    setGameBoardPoint(i,j+3);
                    return true;
                }
                // 0-0--
                else if(gameBoard[i][j] == CPU && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == CPU && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+1);
                    return true;
                }
                // 00---
                else if(gameBoard[i][j] == CPU && gameBoard[i][j+1] == CPU &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
                // ---00
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == CPU && gameBoard[i][j+4] == CPU)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUTwoVertical()
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // --OO-
                if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                   gameBoard[j+2][i] == CPU && gameBoard[j+3][i] == CPU && gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+1,i);
                    return true;
                }
                // -OO--
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == CPU &&
                        gameBoard[j+2][i] == CPU && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+3,i);
                    return true;
                }
                // -0-0-
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == CPU &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == CPU && gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
                // --0-0
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == CPU && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == CPU)
                {
                    setGameBoardPoint(j+3,i);
                    return true;
                }
                // 0-0--
                else if(gameBoard[j][i] == CPU && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == CPU && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+1,i);
                    return true;
                }
                // 00---
                else if(gameBoard[j][i] == CPU && gameBoard[j+1][i] == CPU &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
                // ---00
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == CPU && gameBoard[j+4][i] == CPU)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUTwoDiagonal()
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            // lewy gorny, prawy dolny rog
            if(j <= 10 && i <= 10)
            {
                // --OO-
                if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                   gameBoard[i+2][j+2] == CPU && gameBoard[i+3][j+3] == CPU && gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+1,j+1);
                    return true;
                }
                // -OO--
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == CPU &&
                        gameBoard[i+2][j+2] == CPU && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+3,j+3);
                    return true;
                }
                // -0-0-
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == CPU &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == CPU && gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
                // --0-0
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == CPU && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == CPU)
                {
                    setGameBoardPoint(i+3,j+3);
                    return true;
                }
                // 0-0--
                else if(gameBoard[i][j] == CPU && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == CPU && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+1,j+1);
                    return true;
                }
                // 00---
                else if(gameBoard[i][j] == CPU && gameBoard[i+1][j+1] == CPU &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
                // ---00
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == CPU && gameBoard[i+4][j+4] == CPU)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
            }
            // lewy dolny, prawy gorny rog
            if(j <= 10 && i >= 4)
            {
                // --OO-
                if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                   gameBoard[i-2][j+2] == CPU && gameBoard[i-3][j+3] == CPU && gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-1,j+1);
                    return true;
                }
                // -OO--
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == CPU &&
                        gameBoard[i-2][j+2] == CPU && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-3,j+3);
                    return true;
                }
                // -0-0-
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == CPU &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == CPU && gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
                // --0-0
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == CPU && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == CPU)
                {
                    setGameBoardPoint(i-3,j+3);
                    return true;
                }
                // 0-0--
                else if(gameBoard[i][j] == CPU && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == CPU && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-1,j+1);
                    return true;
                }
                // 00---
                else if(gameBoard[i][j] == CPU && gameBoard[i-1][j+1] == CPU &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
                // ---00
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == CPU && gameBoard[i-4][j+4] == CPU)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUSingle()
{
    if(lookForCPUSingleHorizontal())
    {
        qDebug() << "Found CPU single horizontal";
        return true;
    }
    else if(lookForCPUSingleVertical())
    {
        qDebug() << "Found CPU single vertical";
        return true;
    }
    else if(lookForCPUSingleDiagonal())
    {
        qDebug() << "Found CPU single diagonal";
        return true;
    }
    return false;
}

bool Game::lookForCPUSingleHorizontal()
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // --O--
                if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                   gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == CPU && gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+3);
                    return true;
                }
                // -O---
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == CPU &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
                // ---0-
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == CPU && gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
                // ----0
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == CPU)
                {
                    setGameBoardPoint(i,j+3);
                    return true;
                }
                // 0----
                else if(gameBoard[i][j] == CPU && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+1);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUSingleVertical()
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // --O--
                if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                   gameBoard[j+2][i] == CPU && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+3,i);
                    return true;
                }
                // -0---
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == CPU &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
                // ---0-
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == CPU && gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
                // ----0
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == CPU)
                {
                    setGameBoardPoint(j+3,i);
                    return true;
                }
                // 0----
                else if(gameBoard[j][i] == CPU && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+1,i);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUSingleDiagonal()
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            // lewy gorny, prawy dolny rog
            if(j <= 10 && i <= 10)
            {
                // --O--
                if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                   gameBoard[i+2][j+2] == CPU && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+3,j+3);
                    return true;
                }
                // -O---
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == CPU &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
                // ---0-
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == CPU && gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
                // ----0
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == CPU)
                {
                    setGameBoardPoint(i+3,j+3);
                    return true;
                }
                // 0----
                else if(gameBoard[i][j] == CPU && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+1,j+1);
                    return true;
                }
            }
            // lewy dolny, prawy gorny rog
            if(j <= 10 && i >= 4)
            {
                // --O--
                if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                   gameBoard[i-2][j+2] == CPU && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-3,j+3);
                    return true;
                }
                // -O---
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == CPU &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
                // ---0-
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == CPU && gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
                // ----0
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == CPU)
                {
                    setGameBoardPoint(i-3,j+3);
                    return true;
                }
                // 0----
                else if(gameBoard[i][j] == CPU && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-1,j+1);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForOpponentTwo()
{
    if(lookForOpponentTwoHorizontal())
    {
        qDebug() << "Found Opponent two side 2 horizontal";
        return true;
    }
    else if(lookForOpponentTwoVertical())
    {
        qDebug() << "Found Opponent two side 2 vertical";
        return true;
    }
    else if(lookForOpponentTwoDiagonal())
    {
        qDebug() << "Found Opponent two side 2 diagonal";
        return true;
    }
    return false;
}

bool Game::lookForOpponentTwoHorizontal()
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // --OO-
                if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                   gameBoard[i][j+2] == USER && gameBoard[i][j+3] == USER && gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+1);
                    return true;
                }
                // -OO--
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == USER &&
                        gameBoard[i][j+2] == USER && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+3);
                    return true;
                }
                // -0-0-
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == USER &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == USER && gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
                // --0-0
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == USER && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == USER)
                {
                    setGameBoardPoint(i,j+3);
                    return true;
                }
                // 0-0--
                else if(gameBoard[i][j] == USER && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == USER && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+1);
                    return true;
                }
                // 00---
                else if(gameBoard[i][j] == USER && gameBoard[i][j+1] == USER &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
                // ---00
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == USER && gameBoard[i][j+4] == USER)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForOpponentTwoVertical()
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // --OO-
                if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                   gameBoard[j+2][i] == USER && gameBoard[j+3][i] == USER && gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+1,i);
                    return true;
                }
                // -OO--
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == USER &&
                        gameBoard[j+2][i] == USER && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+3,i);
                    return true;
                }
                // -0-0-
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == USER &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == USER && gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
                // --0-0
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == USER && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == USER)
                {
                    setGameBoardPoint(j+3,i);
                    return true;
                }
                // 0-0--
                else if(gameBoard[j][i] == USER && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == USER && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+1,i);
                    return true;
                }
                // 00---
                else if(gameBoard[j][i] == USER && gameBoard[j+1][i] == USER &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
                // ---00
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == USER && gameBoard[j+4][i] == USER)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForOpponentTwoDiagonal()
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            // lewy gorny, prawy dolny rog
            if(j <= 10 && i <= 10)
            {
                // --OO-
                if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                   gameBoard[i+2][j+2] == USER && gameBoard[i+3][j+3] == USER && gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+1,j+1);
                    return true;
                }
                // -OO--
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == USER &&
                        gameBoard[i+2][j+2] == USER && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+3,j+3);
                    return true;
                }
                // -0-0-
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == USER &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == USER && gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
                // --0-0
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == USER && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == USER)
                {
                    setGameBoardPoint(i+3,j+3);
                    return true;
                }
                // 0-0--
                else if(gameBoard[i][j] == USER && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == USER && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+1,j+1);
                    return true;
                }
                // 00---
                else if(gameBoard[i][j] == USER && gameBoard[i+1][j+1] == USER &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
                // ---00
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == USER && gameBoard[i+4][j+4] == USER)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
            }
            // lewy dolny, prawy gorny rog
            if(j <= 10 && i >= 4)
            {
                // --OO-
                if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                   gameBoard[i-2][j+2] == USER && gameBoard[i-3][j+3] == USER && gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-1,j+1);
                    return true;
                }
                // -OO--
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == USER &&
                        gameBoard[i-2][j+2] == USER && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-3,j+3);
                    return true;
                }
                // -0-0-
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == USER &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == USER && gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
                // --0-0
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == USER && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == USER)
                {
                    setGameBoardPoint(i-3,j+3);
                    return true;
                }
                // 0-0--
                else if(gameBoard[i][j] == USER && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == USER && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-1,j+1);
                    return true;
                }
                // 00---
                else if(gameBoard[i][j] == USER && gameBoard[i-1][j+1] == USER &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
                // ---00
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == USER && gameBoard[i-4][j+4] == USER)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForOpponentSingle()
{
    if(lookForOpponentSingleHorizontal())
    {
        qDebug() << "Found Opponent single horizontal";
        return true;
    }
    else if(lookForOpponentSingleVertical())
    {
        qDebug() << "Found Opponent single vertical";
        return true;
    }
    else if(lookForOpponentSingleDiagonal())
    {
        qDebug() << "Found Opponent single diagonal";
        return true;
    }
    return false;
}

bool Game::lookForOpponentSingleHorizontal()
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // --O--
                if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                   gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == USER && gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+3);
                    return true;
                }
                // -O---
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == USER &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
                // ---0-
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == USER && gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+2);
                    return true;
                }
                // ----0
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == USER)
                {
                    setGameBoardPoint(i,j+3);
                    return true;
                }
                // 0----
                else if(gameBoard[i][j] == USER && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == 0)
                {
                    setGameBoardPoint(i,j+1);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForOpponentSingleVertical()
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // --O--
                if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                   gameBoard[j+2][i] == USER && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+3,i);
                    return true;
                }
                // -0---
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == USER &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
                // ---0-
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == USER && gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+2,i);
                    return true;
                }
                // ----0
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == USER)
                {
                    setGameBoardPoint(j+3,i);
                    return true;
                }
                // 0----
                else if(gameBoard[j][i] == USER && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                {
                    setGameBoardPoint(j+1,i);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::lookForOpponentSingleDiagonal()
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            // lewy gorny, prawy dolny rog
            if(j <= 10 && i <= 10)
            {
                // --O--
                if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                   gameBoard[i+2][j+2] == USER && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+3,j+3);
                    return true;
                }
                // -O---
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == USER &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
                // ---0-
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == USER && gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+2,j+2);
                    return true;
                }
                // ----0
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == USER)
                {
                    setGameBoardPoint(i+3,j+3);
                    return true;
                }
                // 0----
                else if(gameBoard[i][j] == USER && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == 0)
                {
                    setGameBoardPoint(i+1,j+1);
                    return true;
                }
            }
            // lewy dolny, prawy gorny rog
            if(j <= 10 && i >= 4)
            {
                // --O--
                if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                   gameBoard[i-2][j+2] == USER && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-3,j+3);
                    return true;
                }
                // -O---
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == USER &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
                // ---0-
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == USER && gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-2,j+2);
                    return true;
                }
                // ----0
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == USER)
                {
                    setGameBoardPoint(i-3,j+3);
                    return true;
                }
                // 0----
                else if(gameBoard[i][j] == USER && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == 0)
                {
                    setGameBoardPoint(i-1,j+1);
                    return true;
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
void Game::makeCPUMove(int i, int j)
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
}

void Game::countCPUMove()
{
    // 1. look for CPU 4-s
    if(lookForFour())
    {
        makeCPUMove(gameBoardPoint.first, gameBoardPoint.second);
        return;
    }
    // 2. look for CPU special patterns OOO-O & 00-00 & 0-000
    else if(lookForBrokenFour())
    {
        makeCPUMove(gameBoardPoint.first, gameBoardPoint.second);
        return;
    }

    // 3. look for Opponent special patterns OOO-O & 00-00 & 0-000
    else if(lookForOpponentSpecialPattern())
    {
        makeCPUMove(gameBoardPoint.first, gameBoardPoint.second);
        return;
    }
    // 4. look for Opponent 4-s
    else if(lookForOpponentFour())
    {
        makeCPUMove(gameBoardPoint.first, gameBoardPoint.second);
        return;
    }

    // 4. look for Opponent 3-s
    else if(lookForOpponentThree())
    {
        makeCPUMove(gameBoardPoint.first, gameBoardPoint.second);
        return;
    }

    // 5. look for CPU 3-s
    else if(lookForCPUThree())
    {
        makeCPUMove(gameBoardPoint.first, gameBoardPoint.second);
        return;
    }
    // 6. build threat (2-s, 1-s)
    else
    {
        buildThreat();
        makeCPUMove(gameBoardPoint.first, gameBoardPoint.second);
        return;
    }
}

void Game::makeUserMove(std::pair<int, int> boardPoint, const int &row, const int &col)
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

void Game::countUserMove(const int &row, const int &col)
{
    std::pair<int, int> boardPoint = countGameBoardCoordinates(row, col);
    if(checkIfMovePossible(boardPoint.first, boardPoint.second))
    {
        makeUserMove(boardPoint, row, col);
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


void Game::setGameBoardPoint(const int &row, const int &col)
{
    gameBoardPoint.first = row;
    gameBoardPoint.second = col;
}

void Game::cleanPointBoard()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            pointBoard[i][j] = 0;
        }
    }
}
