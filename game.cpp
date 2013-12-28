#include "game.h"

Game::Game() :
    gameFinished(false),
    firstCPUMove(true),
    gameBoardPoint(7,7)
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
    firstCPUMove = false;
    lookForSingle();
    findMaxInPointBoard();
    makeCPUMove(gameBoardPoint.first, gameBoardPoint.second);
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

void Game::lookForThree()
{
    // priority 1
    lookForThreeVertical1Priority(CPU, CPU_3_PRIO_1_HIGH, CPU_3_PRIO_1_LOW);
    lookForThreeVertical1Priority(USER, USER_3_PRIO_1_HIGH, USER_3_PRIO_1_LOW);
    lookForThreeHorizontal1Priority(CPU, CPU_3_PRIO_1_HIGH, CPU_3_PRIO_1_LOW);
    lookForThreeHorizontal1Priority(USER, USER_3_PRIO_1_HIGH, USER_3_PRIO_1_LOW);
    lookForThreeDiagonal1Priority(CPU, CPU_3_PRIO_1_HIGH, CPU_3_PRIO_1_LOW);
    lookForThreeDiagonal1Priority(USER, USER_3_PRIO_1_HIGH, USER_3_PRIO_1_LOW);

    // priority 2
    lookForThreeVertical2Priority(CPU, CPU_3_PRIO_2_HIGH, CPU_3_PRIO_2_MEDIUM, CPU_3_PRIO_2_LOW);
    lookForThreeVertical2Priority(USER, USER_3_PRIO_2_HIGH, USER_3_PRIO_2_MEDIUM, USER_3_PRIO_2_LOW);
    lookForThreeHorizontal2Priority(CPU, CPU_3_PRIO_2_HIGH, CPU_3_PRIO_2_MEDIUM, CPU_3_PRIO_2_LOW);
    lookForThreeHorizontal2Priority(USER, USER_3_PRIO_2_HIGH, USER_3_PRIO_2_MEDIUM, USER_3_PRIO_2_LOW);
    lookForThreeDiagonal2Priority(CPU, CPU_3_PRIO_2_HIGH, CPU_3_PRIO_2_MEDIUM, CPU_3_PRIO_2_LOW);
    lookForThreeDiagonal2Priority(USER, USER_3_PRIO_2_HIGH, USER_3_PRIO_2_MEDIUM, USER_3_PRIO_2_LOW);

    // priority 3
    lookForThreeVertical3Priority(CPU, CPU_3_PRIO_3_HIGH, CPU_3_PRIO_3_LOW);
    lookForThreeVertical3Priority(USER, USER_3_PRIO_3_HIGH, USER_3_PRIO_3_LOW);
    lookForThreeHorizontal3Priority(CPU, CPU_3_PRIO_3_HIGH, CPU_3_PRIO_3_LOW);
    lookForThreeHorizontal3Priority(USER, USER_3_PRIO_3_HIGH, USER_3_PRIO_3_LOW);
    lookForThreeDiagonal3Priority(CPU, CPU_3_PRIO_3_HIGH, CPU_3_PRIO_3_LOW);
    lookForThreeDiagonal3Priority(USER, USER_3_PRIO_3_HIGH, USER_3_PRIO_3_LOW);

    // priority 4
    lookForThreeVertical4Priority(CPU, CPU_3_PRIO_4_HIGH);
    lookForThreeVertical4Priority(USER, USER_3_PRIO_4_HIGH);
    lookForThreeHorizontal4Priority(CPU, CPU_3_PRIO_4_HIGH);
    lookForThreeHorizontal4Priority(USER, USER_3_PRIO_4_HIGH);
    lookForThreeDiagonal4Priority(CPU, CPU_3_PRIO_4_HIGH);
    lookForThreeDiagonal4Priority(USER, USER_3_PRIO_4_HIGH);
}

void Game::lookForThreeVertical1Priority(const int &who, const int &pointsHigh, const int &pointsLow)
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 8)
            {
                // --OOO--
                if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                   gameBoard[i][j+2] == who && gameBoard[i][j+3] == who &&
                   gameBoard[i][j+4] == who && gameBoard[i][j+5] == 0 && gameBoard[i][j+6] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j+1] += pointsLow;
                        pointBoard[i][j+5] += pointsLow;
                        pointBoard[i][j] += pointsHigh;
                        pointBoard[i][j+6] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j+1] += pointsHigh;
                        pointBoard[i][j+5] += pointsHigh;
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i][j+6] += pointsLow;
                    }

                }
            }
        }
    }
}

void Game::lookForThreeHorizontal1Priority(const int &who, const int &pointsHigh, const int &pointsLow)
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 8)
            {
                // --OOO--
                if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                   gameBoard[j+2][i] == who && gameBoard[j+3][i] == who &&
                   gameBoard[j+4][i] == who && gameBoard[j+5][i] == 0 && gameBoard[j+6][i] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[j+1][i] += pointsLow;
                        pointBoard[j+5][i] += pointsLow;
                        pointBoard[j][i] += pointsHigh;
                        pointBoard[j+6][i] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[j+1][i] += pointsHigh;
                        pointBoard[j+5][i] += pointsHigh;
                        pointBoard[j][i] += pointsLow;
                        pointBoard[j+6][i] += pointsLow;
                    }
                }
            }
        }
    }
}

void Game::lookForThreeDiagonal1Priority(const int &who, const int &pointsHigh, const int &pointsLow)
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 8 && i <= 8)
            {
                // --OOO--
                if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                   gameBoard[i+2][j+2] == who && gameBoard[i+3][j+3] == who &&
                   gameBoard[i+4][j+4] == who && gameBoard[i+5][j+5] == 0 && gameBoard[i+6][j+6] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i+1][j+1] += pointsLow;
                        pointBoard[i+5][j+5] += pointsLow;
                        pointBoard[i][j] += pointsHigh;
                        pointBoard[i+6][j+6] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i+1][j+1] += pointsHigh;
                        pointBoard[i+5][j+5] += pointsHigh;
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i+6][j+6] += pointsLow;
                    }
                }
            }
            if(j <=8 && i >= 6)
            {
                // --OOO--
                if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                   gameBoard[i-2][j+2] == who && gameBoard[i-3][j+3] == who &&
                   gameBoard[i-4][j+4] == who && gameBoard[i-5][j+5] == 0 && gameBoard[i-6][j+6] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i-1][j+1] += pointsLow;
                        pointBoard[i-5][j+5] += pointsLow;
                        pointBoard[i][j] += pointsHigh;
                        pointBoard[i-6][j+6] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i-1][j+1] += pointsHigh;
                        pointBoard[i-5][j+5] += pointsHigh;
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i-6][j+6] += pointsLow;
                    }
                }
            }
        }
    }
}

void Game::lookForThreeVertical2Priority(const int &who, const int &pointsHigh, const int &pointsMedium, const int &pointsLow)
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 9)
            {
                // --000-
                if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                   gameBoard[i][j+2] == who && gameBoard[i][j+3] == who &&
                   gameBoard[i][j+4] == who && gameBoard[i][j+5] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsMedium;
                        pointBoard[i][j+5] += pointsMedium;
                        pointBoard[i][j+1] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j+1] += pointsHigh;
                        pointBoard[i][j+5] += pointsHigh;
                        pointBoard[i][j] += pointsLow;
                    }
                }
                // -000--
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == who &&
                        gameBoard[i][j+2] == who && gameBoard[i][j+3] == who &&
                        gameBoard[i][j+4] == 0 && gameBoard[i][j+5] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j+5] += pointsMedium;
                        pointBoard[i][j] += pointsMedium;
                        pointBoard[i][j+4] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j+4] += pointsHigh;
                        pointBoard[i][j] += pointsHigh;
                        pointBoard[i][j+5] += pointsLow;
                    }
                }
                // -00-0-
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == who &&
                        gameBoard[i][j+2] == who && gameBoard[i][j+3] == 0 &&
                        gameBoard[i][j+4] == who && gameBoard[i][j+5] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsMedium;
                        pointBoard[i][j+5] += pointsMedium;
                        pointBoard[i][j+3] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j+3] += pointsHigh;
                        pointBoard[i][j+5] += pointsLow;
                        pointBoard[i][j] += pointsLow;
                    }
                }
                // -0-00-
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == who &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == who &&
                        gameBoard[i][j+4] == who && gameBoard[i][j+5] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j+2] += pointsHigh;
                        pointBoard[i][j+5] += pointsMedium;
                        pointBoard[i][j] += pointsMedium;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j+2] += pointsHigh;
                        pointBoard[i][j+5] += pointsLow;
                        pointBoard[i][j] += pointsLow;
                    }
                }
            }
        }
    }
}

void Game::lookForThreeHorizontal2Priority(const int &who, const int &pointsHigh, const int &pointsMedium, const int &pointsLow)
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 9)
            {
                // --000-
                if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                   gameBoard[j+2][i] == who && gameBoard[j+3][i] == who &&
                   gameBoard[j+4][i] == who && gameBoard[j+5][i] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[j][i] += pointsMedium;
                        pointBoard[j+5][i] += pointsMedium;
                        pointBoard[j+1][i] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[j+1][i] += pointsHigh;
                        pointBoard[j+5][i] += pointsHigh;
                        pointBoard[j][i] += pointsLow;
                    }
                }
                // -000--
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == who &&
                        gameBoard[j+2][i] == who && gameBoard[j+3][i] == who &&
                        gameBoard[j+4][i] == 0 && gameBoard[j+5][i] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[j+5][i] += pointsMedium;
                        pointBoard[j][i] += pointsMedium;
                        pointBoard[j+4][i] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[j+4][i] += pointsHigh;
                        pointBoard[j][i] += pointsHigh;
                        pointBoard[j+5][i] += pointsLow;
                    }
                }
                // -00-0-
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == who &&
                        gameBoard[j+2][i] == who && gameBoard[j+3][i] == 0 &&
                        gameBoard[j+4][i] == who && gameBoard[j+5][i] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[j][i] += pointsMedium;
                        pointBoard[j+5][i] += pointsMedium;
                        pointBoard[j+3][i] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[j+3][i] += pointsHigh;
                        pointBoard[j+5][i] += pointsLow;
                        pointBoard[j][i] += pointsLow;
                    }
                }
                // -0-00-
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == who &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == who &&
                        gameBoard[j+4][i] == who && gameBoard[j+5][i] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[j+2][i] += pointsHigh;
                        pointBoard[j+5][i] += pointsMedium;
                        pointBoard[j][i] += pointsMedium;
                    }
                    else if(USER == who)
                    {
                        pointBoard[j+2][i] += pointsHigh;
                        pointBoard[j+5][i] += pointsLow;
                        pointBoard[j][i] += pointsLow;
                    }
                }
            }
        }
    }
}

void Game::lookForThreeDiagonal2Priority(const int &who, const int &pointsHigh, const int &pointsMedium, const int &pointsLow)
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 9 && i <= 9)
            {
                // --000-
                if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                   gameBoard[i+2][j+2] == who && gameBoard[i+3][j+3] == who &&
                   gameBoard[i+4][j+4] == who && gameBoard[i+5][j+5] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsMedium;
                        pointBoard[i+5][j+5] += pointsMedium;
                        pointBoard[i+1][j+1] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i+1][j+1] += pointsHigh;
                        pointBoard[i+5][j+5] += pointsHigh;
                        pointBoard[i][j] += pointsLow;
                    }
                }
                // -000--
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == who &&
                        gameBoard[i+2][j+2] == who && gameBoard[i+3][j+3] == who &&
                        gameBoard[i+4][j+4] == 0 && gameBoard[i+5][j+5] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i+5][j+5] += pointsMedium;
                        pointBoard[i][j] += pointsMedium;
                        pointBoard[i+4][j+4] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i+4][j+4] += pointsHigh;
                        pointBoard[i][j] += pointsHigh;
                        pointBoard[i+5][j+5] += pointsLow;
                    }
                }
                // -00-0-
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == who &&
                        gameBoard[i+2][j+2] == who && gameBoard[i+3][j+3] == 0 &&
                        gameBoard[i+4][j+4] == who && gameBoard[i+5][j+5] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsMedium;
                        pointBoard[i+5][j+5] += pointsMedium;
                        pointBoard[i+3][j+3] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i+3][j+3] += pointsHigh;
                        pointBoard[i+5][j+5] += pointsLow;
                        pointBoard[i][j] += pointsLow;
                    }
                }
                // -0-00-
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == who &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == who &&
                        gameBoard[i+4][j+4] == who && gameBoard[i+5][j+5] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i+2][j+2] += pointsHigh;
                        pointBoard[i+5][j+5] += pointsMedium;
                        pointBoard[i][j] += pointsMedium;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i+2][j+2] += pointsHigh;
                        pointBoard[i+5][j+5] += pointsLow;
                        pointBoard[i][j] += pointsLow;
                    }
                }
            }
            if(j <= 9 && i >= 5)
            {
                // --000-
                if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                   gameBoard[i-2][j+2] == who && gameBoard[i-3][j+3] == who &&
                   gameBoard[i-4][j+4] == who && gameBoard[i-5][j+5] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsMedium;
                        pointBoard[i-5][j+5] += pointsMedium;
                        pointBoard[i-1][j+1] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i-1][j+1] += pointsHigh;
                        pointBoard[i-5][j+5] += pointsHigh;
                        pointBoard[i][j] += pointsLow;
                    }
                }
                // -000--
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == who &&
                        gameBoard[i-2][j+2] == who && gameBoard[i-3][j+3] == who &&
                        gameBoard[i-4][j+4] == 0 && gameBoard[i-5][j+5] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i-5][j+5] += pointsMedium;
                        pointBoard[i][j] += pointsMedium;
                        pointBoard[i-4][j+4] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i-4][j+4] += pointsHigh;
                        pointBoard[i][j] += pointsHigh;
                        pointBoard[i-5][j+5] += pointsLow;
                    }
                }
                // -00-0-
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == who &&
                        gameBoard[i-2][j+2] == who && gameBoard[i-3][j+3] == 0 &&
                        gameBoard[i-4][j+4] == who && gameBoard[i-5][j+5] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsMedium;
                        pointBoard[i-5][j+5] += pointsMedium;
                        pointBoard[i-3][j+3] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i-3][j+3] += pointsHigh;
                        pointBoard[i-5][j+5] += pointsLow;
                        pointBoard[i][j] += pointsLow;
                    }
                }
                // -0-00-
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == who &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == who &&
                        gameBoard[i-4][j+4] == who && gameBoard[i-5][j+5] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i-2][j+2] += pointsHigh;
                        pointBoard[i-5][j+5] += pointsMedium;
                        pointBoard[i][j] += pointsMedium;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i-2][j+2] += pointsHigh;
                        pointBoard[i-5][j+5] += pointsLow;
                        pointBoard[i][j] += pointsLow;
                    }
                }
            }
        }
    }
}

void Game::lookForThreeVertical3Priority(const int &who, const int &pointsHigh, const int &pointsLow)
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 8)
            {
                // -0-0-0-
                if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == who &&
                   gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == who &&
                   gameBoard[i][j+4] == 0 && gameBoard[i][j+5] == who && gameBoard[i][j+6] == 0)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i][j+2] += pointsHigh;
                    pointBoard[i][j+4] += pointsHigh;
                    pointBoard[i][j+6] += pointsLow;
                }
                // -00--0-
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == who &&
                        gameBoard[i][j+2] == who && gameBoard[i][j+3] == 0 &&
                        gameBoard[i][j+4] == 0 && gameBoard[i][j+5] == who && gameBoard[i][j+6] == 0)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i][j+3] += pointsHigh;
                    pointBoard[i][j+4] += pointsHigh;
                    pointBoard[i][j+6] += pointsLow;
                }
                // -0--00-
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == who &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == 0 &&
                        gameBoard[i][j+4] == who && gameBoard[i][j+5] == who && gameBoard[i][j+6] == 0)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i][j+2] += pointsHigh;
                    pointBoard[i][j+3] += pointsHigh;
                    pointBoard[i][j+6] += pointsLow;
                }
            }
        }
    }
}

void Game::lookForThreeHorizontal3Priority(const int &who, const int &pointsHigh, const int &pointsLow)
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 8)
            {
                if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == who &&
                   gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == who &&
                   gameBoard[j+4][i] == 0 && gameBoard[j+5][i] == who && gameBoard[j+6][i] == 0)
                {
                    pointBoard[j][i] += pointsLow;
                    pointBoard[j+2][i] += pointsHigh;
                    pointBoard[j+4][i] += pointsHigh;
                    pointBoard[j+6][i] += pointsLow;
                }
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == who &&
                        gameBoard[j+2][i] == who && gameBoard[j+3][i] == 0 &&
                        gameBoard[j+4][i] == 0 && gameBoard[j+5][i] == who && gameBoard[j+6][i] == 0)
                {
                    pointBoard[j][i] += pointsLow;
                    pointBoard[j+3][i] += pointsHigh;
                    pointBoard[j+4][i] += pointsHigh;
                    pointBoard[j+6][i] += pointsLow;
                }
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == who &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == 0 &&
                        gameBoard[j+4][i] == who && gameBoard[j+5][i] == who && gameBoard[j+6][i] == 0)
                {
                    pointBoard[j][i] += pointsLow;
                    pointBoard[j+2][i] += pointsHigh;
                    pointBoard[j+3][i] += pointsHigh;
                    pointBoard[j+6][i] += pointsLow;
                }
            }
        }
    }
}

void Game::lookForThreeDiagonal3Priority(const int &who, const int &pointsHigh, const int &pointsLow)
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 8 && i <= 8)
            {
                if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == who &&
                   gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == who &&
                   gameBoard[i+4][j+4] == 0 && gameBoard[i+5][j+5] == who && gameBoard[i+6][j+6] == 0)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i+2][j+2] += pointsHigh;
                    pointBoard[i+4][j+4] += pointsHigh;
                    pointBoard[i+6][j+6] += pointsLow;
                }
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == who &&
                        gameBoard[i+2][j+2] == who && gameBoard[i+3][j+3] == 0 &&
                        gameBoard[i+4][j+4] == 0 && gameBoard[i+5][j+5] == who && gameBoard[i+6][j+6] == 0)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i+3][j+3] += pointsHigh;
                    pointBoard[i+4][j+4] += pointsHigh;
                    pointBoard[i+6][j+6] += pointsLow;
                }
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == who &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == 0 &&
                        gameBoard[i+2][j+4] == who && gameBoard[i+5][j+5] == who && gameBoard[i+6][j+6] == 0)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i+2][j+2] += pointsHigh;
                    pointBoard[i+3][j+3] += pointsHigh;
                    pointBoard[i+6][j+6] += pointsLow;
                }
            }
            if(j <=8 && i >= 6)
            {
                if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == who &&
                   gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == who &&
                   gameBoard[i-4][j+4] == 0 && gameBoard[i-5][j+5] == who && gameBoard[i-6][j+6] == 0)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i-2][j+2] += pointsHigh;
                    pointBoard[i-4][j+4] += pointsHigh;
                    pointBoard[i-6][j+6] += pointsLow;
                }
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == who &&
                        gameBoard[i-2][j+2] == who && gameBoard[i-3][j+3] == 0 &&
                        gameBoard[i-4][j+4] == 0 && gameBoard[i-5][j+5] == who && gameBoard[i-6][j+6] == 0)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i-3][j+3] += pointsHigh;
                    pointBoard[i-4][j+4] += pointsHigh;
                    pointBoard[i-6][j+6] += pointsLow;
                }
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == who &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == 0 &&
                        gameBoard[i-2][j+4] == who && gameBoard[i-5][j+5] == who && gameBoard[i-6][j+6] == 0)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i-2][j+2] += pointsHigh;
                    pointBoard[i-3][j+3] += pointsHigh;
                    pointBoard[i-6][j+6] += pointsLow;
                }
            }
        }
    }
}

void Game::lookForThreeVertical4Priority(const int &who, const int &points)
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // -000-
                if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == who &&
                   gameBoard[i][j+2] == who && gameBoard[i][j+3] == who &&
                   gameBoard[i][j+4] == 0)
                {
                    pointBoard[i][j] += points;
                    pointBoard[i][j+4] += points;
                }
                // 000--
                else if(gameBoard[i][j] == who && gameBoard[i][j+1] == who &&
                        gameBoard[i][j+2] == who && gameBoard[i][j+3] == 0 &&
                        gameBoard[i][j+4] == 0)
                {
                    pointBoard[i][j+3] += points;
                    pointBoard[i][j+4] += points;
                }
                // --000
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == who && gameBoard[i][j+3] == who &&
                        gameBoard[i][j+4] == who)
                {
                    pointBoard[i][j] += points;
                    pointBoard[i][j+1] += points;
                }
                // -0-00
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == who &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == who &&
                        gameBoard[i][j+4] == who)
                {
                    pointBoard[i][j] += points;
                    pointBoard[i][j+1] += points;
                }
                // 00-0-
                else if(gameBoard[i][j] == who && gameBoard[i][j+1] == who &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == who &&
                        gameBoard[i][j+4] == 0)
                {
                    pointBoard[i][j+2] += points;
                    pointBoard[i][j+4] += points;
                }
                // 0-0-0
                else if(gameBoard[i][j] == who && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == who && gameBoard[i][j+3] == 0 &&
                        gameBoard[i][j+4] == who)
                {
                    pointBoard[i][j+1] += points;
                    pointBoard[i][j+3] += points;
                }
            }
        }
    }
}

void Game::lookForThreeHorizontal4Priority(const int &who, const int &points)
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // -000-
                if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == who &&
                   gameBoard[j+2][i] == who && gameBoard[j+3][i] == who &&
                   gameBoard[j+4][i] == 0)
                {
                    pointBoard[j][i] += points;
                    pointBoard[j+4][i] += points;
                }
                // 000--
                else if(gameBoard[j][i] == who && gameBoard[j+1][i] == who &&
                        gameBoard[j+2][i] == who && gameBoard[j+3][i] == 0 &&
                        gameBoard[j+4][i] == 0)
                {
                    pointBoard[j+3][i] += points;
                    pointBoard[j+4][i] += points;
                }
                // --000
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == who && gameBoard[j+3][i] == who &&
                        gameBoard[j+4][i] == who)
                {
                    pointBoard[j][i] += points;
                    pointBoard[j+1][i] += points;
                }
                // -0-00
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == who &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == who &&
                        gameBoard[j+4][i] == who)
                {
                    pointBoard[j][i] += points;
                    pointBoard[j+2][i] += points;
                }
                // 00-0-
                else if(gameBoard[j][i] == who && gameBoard[j+1][i] == who &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == who &&
                        gameBoard[j+4][i] == 0)
                {
                    pointBoard[j+2][i] += points;
                    pointBoard[j+4][i] += points;
                }
                // 0-0-0
                else if(gameBoard[j][i] == who && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == who && gameBoard[j+3][i] == 0 &&
                        gameBoard[j+4][i] == who)
                {
                    pointBoard[j+1][i] += points;
                    pointBoard[j+3][i] += points;
                }
            }
        }
    }
}

void Game::lookForThreeDiagonal4Priority(const int &who, const int &points)
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10 && i <= 10)
            {
                // -000-
                if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == who &&
                   gameBoard[i+2][j+2] == who && gameBoard[i+3][j+3] == who &&
                   gameBoard[i+4][j+4] == 0)
                {
                    pointBoard[i][j] += points;
                    pointBoard[i+4][j+4] += points;
                }
                // 000--
                else if(gameBoard[i][j] == who && gameBoard[i+1][j+1] == who &&
                        gameBoard[i+2][j+2] == who && gameBoard[i+3][j+3] == 0 &&
                        gameBoard[i+4][j+4] == 0)
                {
                    pointBoard[i+3][j+3] += points;
                    pointBoard[i+4][j+4] += points;
                }
                // --000
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == who && gameBoard[i+3][j+3] == who &&
                        gameBoard[i+4][j+4] == who)
                {
                    pointBoard[i][j] += points;
                    pointBoard[i+1][j+1] += points;
                }
                // -0-00
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == who &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == who &&
                        gameBoard[i+4][j+4] == who)
                {
                    pointBoard[i][j] += points;
                    pointBoard[i+2][j+2] += points;
                }
                // 00-0-
                else if(gameBoard[i][j] == who && gameBoard[i+1][j+1] == who &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == who &&
                        gameBoard[i+4][j+4] == 0)
                {
                    pointBoard[i+2][j+2] += points;
                    pointBoard[i+4][j+4] += points;
                }
                // 0-0-0
                else if(gameBoard[i][j] == who && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == who && gameBoard[i+3][j+3] == 0 &&
                        gameBoard[i+4][j+4] == who)
                {
                    pointBoard[i+1][j+1] += points;
                    pointBoard[i+3][j+3] += points;
                }
            }

            if(j <= 10 && i >= 4)
            {
                // -000-
                if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == who &&
                   gameBoard[i-2][j+2] == who && gameBoard[i-3][j+3] == who &&
                   gameBoard[i-4][j+4] == 0)
                {
                    pointBoard[i][j] += points;
                    pointBoard[i-4][j+4] += points;
                }
                // 000--
                else if(gameBoard[i][j] == who && gameBoard[i-1][j+1] == who &&
                        gameBoard[i-2][j+2] == who && gameBoard[i-3][j+3] == 0 &&
                        gameBoard[i-4][j+4] == 0)
                {
                    pointBoard[i-3][j+3] += points;
                    pointBoard[i-4][j+4] += points;
                }
                // --000
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == who && gameBoard[i-3][j+3] == who &&
                        gameBoard[i-4][j+4] == who)
                {
                    pointBoard[i][j] += points;
                    pointBoard[i-1][j+1] += points;
                }
                // -0-00
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == who &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == who &&
                        gameBoard[i-4][j+4] == who)
                {
                    pointBoard[i][j] += points;
                    pointBoard[i-2][j+2] += points;
                }
                // 00-0-
                else if(gameBoard[i][j] == who && gameBoard[i-1][j+1] == who &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == who &&
                        gameBoard[i-4][j+4] == 0)
                {
                    pointBoard[i-2][j+2] += points;
                    pointBoard[i-4][j+4] += points;
                }
                // 0-0-0
                else if(gameBoard[i][j] == who && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == who && gameBoard[i-3][j+3] == 0 &&
                        gameBoard[i-4][j+4] == who)
                {
                    pointBoard[i-1][j+1] += points;
                    pointBoard[i-3][j+3] += points;
                }
            }
        }
    }
}

void Game::lookForTwo()
{
    lookForTwoVertical(CPU, CPU_2_HIGH, CPU_2_LOW);
    lookForTwoVertical(USER, USER_2_HIGH, USER_2_LOW);
    lookForTwoHorizontal(CPU, CPU_2_HIGH, CPU_2_LOW);
    lookForTwoHorizontal(USER, USER_2_HIGH, USER_2_LOW);
    lookForTwoDiagonal(CPU, CPU_2_HIGH, CPU_2_LOW);
    lookForTwoDiagonal(USER, USER_2_HIGH, USER_2_LOW);
}

void Game::lookForTwoVertical(const int &who, const int &pointsHigh, const int &pointsLow)
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // --OO-
                if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                   gameBoard[i][j+2] == who && gameBoard[i][j+3] == who && gameBoard[i][j+4] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsHigh;
                        pointBoard[i][j+1] += pointsLow;
                        pointBoard[i][j+4] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i][j+1] += pointsHigh;
                        pointBoard[i][j+4] += pointsHigh;
                    }
                }
                // -OO--
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == who &&
                        gameBoard[i][j+2] == who && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i][j+3] += pointsLow;
                        pointBoard[i][j+4] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j] += pointsHigh;
                        pointBoard[i][j+3] += pointsHigh;
                        pointBoard[i][j+4] += pointsLow;
                    }
                }
                // -0-0-
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == who &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == who && gameBoard[i][j+4] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsHigh;
                        pointBoard[i][j+2] += pointsLow;
                        pointBoard[i][j+4] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i][j+2] += pointsHigh;
                        pointBoard[i][j+4] += pointsLow;
                    }
                }
                // --0-0
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == who && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == who)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i][j+1] += pointsHigh;
                        pointBoard[i][j+3] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i][j+1] += pointsLow;
                        pointBoard[i][j+3] += pointsHigh;
                    }
                }
                // 0-0--
                else if(gameBoard[i][j] == who && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == who && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j+1] += pointsLow;
                        pointBoard[i][j+3] += pointsHigh;
                        pointBoard[i][j+4] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j+1] += pointsHigh;
                        pointBoard[i][j+3] += pointsLow;
                        pointBoard[i][j+4] += pointsLow;
                    }
                }
                // 00---
                else if(gameBoard[i][j] == who && gameBoard[i][j+1] == who &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j+2] += pointsLow;
                        pointBoard[i][j+3] += pointsHigh;
                        pointBoard[i][j+4] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j+2] += pointsHigh;
                        pointBoard[i][j+3] += pointsLow;
                        pointBoard[i][j+4] += pointsLow;
                    }
                }
                // ---00
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == who && gameBoard[i][j+4] == who)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i][j+1] += pointsHigh;
                        pointBoard[i][j+2] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i][j+1] += pointsLow;
                        pointBoard[i][j+2] += pointsHigh;
                    }
                }
            }
        }
    }
}

void Game::lookForTwoHorizontal(const int &who, const int &pointsHigh, const int &pointsLow)
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // --OO-
                if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                   gameBoard[j+2][i] == who && gameBoard[j+3][i] == who && gameBoard[j+4][i] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[j][i] += pointsHigh;
                        pointBoard[j+1][i] += pointsLow;
                        pointBoard[j+4][i] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[j][i] += pointsLow;
                        pointBoard[j+1][i] += pointsHigh;
                        pointBoard[j+4][i] += pointsHigh;
                    }
                }
                // -OO--
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == who &&
                        gameBoard[j+2][i] == who && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[j][i] += pointsLow;
                        pointBoard[j+3][i] += pointsLow;
                        pointBoard[j+4][i] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[j][i] += pointsHigh;
                        pointBoard[j+3][i] += pointsHigh;
                        pointBoard[j+4][i] += pointsLow;
                    }
                }
                // -0-0-
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == who &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == who && gameBoard[j+4][i] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[j][i] += pointsHigh;
                        pointBoard[j+2][i] += pointsLow;
                        pointBoard[j+4][i] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[j][i] += pointsLow;
                        pointBoard[j+2][i] += pointsHigh;
                        pointBoard[j+4][i] += pointsLow;
                    }
                }
                // --0-0
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == who && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == who)
                {
                    if(CPU == who)
                    {
                        pointBoard[j][i] += pointsLow;
                        pointBoard[j+1][i] += pointsHigh;
                        pointBoard[j+3][i] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[j][i] += pointsLow;
                        pointBoard[j+1][i] += pointsLow;
                        pointBoard[j+3][i] += pointsHigh;
                    }
                }
                // 0-0--
                else if(gameBoard[j][i] == who && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == who && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[j+1][i] += pointsLow;
                        pointBoard[j+3][i] += pointsHigh;
                        pointBoard[j+4][i] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[j+1][i] += pointsHigh;
                        pointBoard[j+3][i] += pointsLow;
                        pointBoard[j+4][i] += pointsLow;
                    }
                }
                // 00---
                else if(gameBoard[j][i] == who && gameBoard[j+1][i] == who &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[j+2][i] += pointsLow;
                        pointBoard[j+3][i] += pointsHigh;
                        pointBoard[j+4][i] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[j+2][i] += pointsHigh;
                        pointBoard[j+3][i] += pointsLow;
                        pointBoard[j+4][i] += pointsLow;
                    }
                }
                // ---00
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == who && gameBoard[j+4][i] == who)
                {
                    if(CPU == who)
                    {
                        pointBoard[j][i] += pointsLow;
                        pointBoard[j+1][i] += pointsHigh;
                        pointBoard[j+2][i] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[j][i] += pointsLow;
                        pointBoard[j+1][i] += pointsLow;
                        pointBoard[j+2][i] += pointsHigh;
                    }
                }
            }
        }
    }
}

void Game::lookForTwoDiagonal(const int &who, const int &pointsHigh, const int &pointsLow)
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
                   gameBoard[i+2][j+2] == who && gameBoard[i+3][j+3] == who && gameBoard[i+4][j+4] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsHigh;
                        pointBoard[i+1][j+1] += pointsLow;
                        pointBoard[i+4][j+4] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i+1][j+1] += pointsHigh;
                        pointBoard[i+4][j+4] += pointsHigh;
                    }
                }
                // -OO--
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == who &&
                        gameBoard[i+2][j+2] == who && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i+3][j+3] += pointsLow;
                        pointBoard[i+4][j+4] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j] += pointsHigh;
                        pointBoard[i+3][j+3] += pointsHigh;
                        pointBoard[i+4][j+4] += pointsLow;
                    }
                }
                // -0-0-
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == who &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == who && gameBoard[i+4][j+4] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsHigh;
                        pointBoard[i+2][j+2] += pointsLow;
                        pointBoard[i+4][j+4] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i+2][j+2] += pointsHigh;
                        pointBoard[i+4][j+4] += pointsLow;
                    }
                }
                // --0-0
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == who && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == who)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i+1][j+1] += pointsHigh;
                        pointBoard[i+3][j+3] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i][j+1] += pointsLow;
                        pointBoard[i][j+3] += pointsHigh;
                    }
                }
                // 0-0--
                else if(gameBoard[i][j] == who && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == who && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i+1][j+1] += pointsLow;
                        pointBoard[i+3][j+3] += pointsHigh;
                        pointBoard[i+4][j+4] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i+1][j+1] += pointsHigh;
                        pointBoard[i+3][j+3] += pointsLow;
                        pointBoard[i+4][j+4] += pointsLow;
                    }
                }
                // 00---
                else if(gameBoard[i][j] == who && gameBoard[i+1][j+1] == who &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i+2][j+2] += pointsLow;
                        pointBoard[i+3][j+3] += pointsHigh;
                        pointBoard[i+4][j+4] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i+2][j+2] += pointsHigh;
                        pointBoard[i+3][j+3] += pointsLow;
                        pointBoard[i+4][j+4] += pointsLow;
                    }
                }
                // ---00
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == who && gameBoard[i+4][j+4] == who)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i+1][j+1] += pointsHigh;
                        pointBoard[i+2][j+2] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i+1][j+1] += pointsLow;
                        pointBoard[i+2][j+2] += pointsHigh;
                    }
                }
            }
            // lewy dolny, prawy gorny rog
            if(j <= 10 && i >= 4)
            {
                // --OO-
                if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                   gameBoard[i-2][j+2] == who && gameBoard[i-3][j+3] == who && gameBoard[i-4][j+4] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsHigh;
                        pointBoard[i-1][j+1] += pointsLow;
                        pointBoard[i-4][j+4] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i-1][j+1] += pointsHigh;
                        pointBoard[i-4][j+4] += pointsHigh;
                    }
                }
                // -OO--
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == who &&
                        gameBoard[i-2][j+2] == who && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i-3][j+3] += pointsLow;
                        pointBoard[i-4][j+4] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j] += pointsHigh;
                        pointBoard[i-3][j+3] += pointsHigh;
                        pointBoard[i-4][j+4] += pointsLow;
                    }
                }
                // -0-0-
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == who &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == who && gameBoard[i-4][j+4] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsHigh;
                        pointBoard[i-2][j+2] += pointsLow;
                        pointBoard[i-4][j+4] += pointsHigh;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i-2][j+2] += pointsHigh;
                        pointBoard[i-4][j+4] += pointsLow;
                    }
                }
                // --0-0
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == who && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == who)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i-1][j+1] += pointsHigh;
                        pointBoard[i-3][j+3] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i-1][j+1] += pointsLow;
                        pointBoard[i-3][j+3] += pointsHigh;
                    }
                }
                // 0-0--
                else if(gameBoard[i][j] == who && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == who && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i-1][j+1] += pointsLow;
                        pointBoard[i-3][j+3] += pointsHigh;
                        pointBoard[i-4][j+4] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i-1][j+1] += pointsHigh;
                        pointBoard[i-3][j+3] += pointsLow;
                        pointBoard[i-4][j+4] += pointsLow;
                    }
                }
                // 00---
                else if(gameBoard[i][j] == who && gameBoard[i-1][j+1] == who &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == 0)
                {
                    if(CPU == who)
                    {
                        pointBoard[i-2][j+2] += pointsLow;
                        pointBoard[i-3][j+3] += pointsHigh;
                        pointBoard[i-4][j+4] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i-2][j+2] += pointsHigh;
                        pointBoard[i-3][j+3] += pointsLow;
                        pointBoard[i-4][j+4] += pointsLow;
                    }
                }
                // ---00
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == who && gameBoard[i-4][j+4] == who)
                {
                    if(CPU == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i-1][j+1] += pointsHigh;
                        pointBoard[i-2][j+2] += pointsLow;
                    }
                    else if(USER == who)
                    {
                        pointBoard[i][j] += pointsLow;
                        pointBoard[i-1][j+1] += pointsLow;
                        pointBoard[i-2][j+2] += pointsHigh;
                    }
                }
            }
        }
    }
}

void Game::lookForSingle()
{
    lookForSingleVertical(CPU, CPU_1_HIGH, CPU_1_MEDIUM, CPU_1_LOW);
    lookForSingleVertical(USER, USER_1_HIGH, USER_1_MEDIUM, USER_1_LOW);
    lookForSingleHorizontal(CPU, CPU_1_HIGH, CPU_1_MEDIUM, CPU_1_LOW);
    lookForSingleHorizontal(USER, USER_1_HIGH, USER_1_MEDIUM, USER_1_LOW);
    lookForSingleDiagonal(CPU, CPU_1_HIGH, CPU_1_MEDIUM, CPU_1_LOW);
    lookForSingleDiagonal(USER, USER_1_HIGH, USER_1_MEDIUM, USER_1_LOW);
}

void Game::lookForSingleVertical(const int &who, const int &pointsHigh, const int &pointsMedium, const int &pointsLow)
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // --O--
                if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                   gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == who && gameBoard[i][j+4] == 0)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i][j+1] += pointsHigh;
                    pointBoard[i][j+3] += pointsHigh;
                    pointBoard[i][j+4] += pointsLow;
                }
                // -O---
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == who &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == 0)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i][j+2] += pointsHigh;
                    pointBoard[i][j+3] += pointsMedium;
                    pointBoard[i][j+4] += pointsLow;
                }
                // ---0-
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == who && gameBoard[i][j+4] == 0)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i][j+1] += pointsMedium;
                    pointBoard[i][j+2] += pointsHigh;
                    pointBoard[i][j+4] += pointsLow;
                }
                // ----0
                else if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == who)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i][j+1] += pointsLow;
                    pointBoard[i][j+2] += pointsMedium;
                    pointBoard[i][j+3] += pointsHigh;
                }
                // 0----
                else if(gameBoard[i][j] == who && gameBoard[i][j+1] == 0 &&
                        gameBoard[i][j+2] == 0 && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == 0)
                {
                    pointBoard[i][j+1] += pointsHigh;
                    pointBoard[i][j+2] += pointsMedium;
                    pointBoard[i][j+3] += pointsLow;
                    pointBoard[i][j+4] += pointsLow;
                }
            }
        }
    }
}

void Game::lookForSingleHorizontal(const int &who, const int &pointsHigh, const int &pointsMedium, const int &pointsLow)
{
    for(unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for(unsigned int  j = 0; j < BOARD_SIZE; j++)
        {
            if(j <= 10)
            {
                // --O--
                if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                   gameBoard[j+2][i] == who && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                {
                    pointBoard[j][i] += pointsLow;
                    pointBoard[j+1][i] += pointsHigh;
                    pointBoard[j+3][i] += pointsHigh;
                    pointBoard[j+4][i] += pointsLow;
                }
                // -0---
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == who &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                {
                    pointBoard[j][i] += pointsLow;
                    pointBoard[j+2][i] += pointsHigh;
                    pointBoard[j+3][i] += pointsMedium;
                    pointBoard[j+4][i] += pointsLow;
                }
                // ---0-
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == who && gameBoard[j+4][i] == 0)
                {
                    pointBoard[j][i] += pointsLow;
                    pointBoard[j+1][i] += pointsMedium;
                    pointBoard[j+2][i] += pointsHigh;
                    pointBoard[j+4][i] += pointsLow;
                }
                // ----0
                else if(gameBoard[j][i] == 0 && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == who)
                {
                    pointBoard[j][i] += pointsLow;
                    pointBoard[j+1][i] += pointsLow;
                    pointBoard[j+2][i] += pointsMedium;
                    pointBoard[j+3][i] += pointsHigh;
                }
                // 0----
                else if(gameBoard[j][i] == who && gameBoard[j+1][i] == 0 &&
                        gameBoard[j+2][i] == 0 && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                {
                    pointBoard[j+1][i] += pointsHigh;
                    pointBoard[j+2][i] += pointsMedium;
                    pointBoard[j+3][i] += pointsLow;
                    pointBoard[j+4][i] += pointsLow;
                }
            }
        }
    }
}

void Game::lookForSingleDiagonal(const int &who, const int &pointsHigh, const int &pointsMedium, const int &pointsLow)
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
                   gameBoard[i+2][j+2] == who && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == 0)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i+1][j+1] += pointsHigh;
                    pointBoard[i+3][j+3] += pointsHigh;
                    pointBoard[i+4][j+4] += pointsLow;
                }
                // -O---
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == who &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == 0)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i+2][j+2] += pointsHigh;
                    pointBoard[i+3][j+3] += pointsMedium;
                    pointBoard[i+4][j+4] += pointsLow;
                }
                // ---0-
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == who && gameBoard[i+4][j+4] == 0)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i+1][j+1] += pointsMedium;
                    pointBoard[i+2][j+2] += pointsHigh;
                    pointBoard[i+4][j+4] += pointsLow;
                }
                // ----0
                else if(gameBoard[i][j] == 0 && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == who)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i+1][j+1] += pointsLow;
                    pointBoard[i+2][j+2] += pointsMedium;
                    pointBoard[i+3][j+3] += pointsHigh;
                }
                // 0----
                else if(gameBoard[i][j] == who && gameBoard[i+1][j+1] == 0 &&
                        gameBoard[i+2][j+2] == 0 && gameBoard[i+3][j+3] == 0 && gameBoard[i+4][j+4] == 0)
                {
                    pointBoard[i+1][j+1] += pointsHigh;
                    pointBoard[i+2][j+2] += pointsMedium;
                    pointBoard[i+3][j+3] += pointsLow;
                    pointBoard[i+4][j+4] += pointsLow;
                }
            }
            // lewy dolny, prawy gorny rog
            if(j <= 10 && i >= 4)
            {
                // --O--
                if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                   gameBoard[i-2][j+2] == who && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == 0)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i-1][j+1] += pointsHigh;
                    pointBoard[i-3][j+3] += pointsHigh;
                    pointBoard[i-4][j+4] += pointsLow;
                }
                // -O---
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == who &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == 0)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i-2][j+2] += pointsHigh;
                    pointBoard[i-3][j+3] += pointsMedium;
                    pointBoard[i-4][j+4] += pointsLow;
                }
                // ---0-
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == who && gameBoard[i-4][j+4] == 0)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i-1][j+1] += pointsMedium;
                    pointBoard[i-2][j+2] += pointsHigh;
                    pointBoard[i-4][j+4] += pointsLow;
                }
                // ----0
                else if(gameBoard[i][j] == 0 && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == who)
                {
                    pointBoard[i][j] += pointsLow;
                    pointBoard[i-1][j+1] += pointsLow;
                    pointBoard[i-2][j+2] += pointsMedium;
                    pointBoard[i-3][j+3] += pointsHigh;
                }
                // 0----
                else if(gameBoard[i][j] == who && gameBoard[i-1][j+1] == 0 &&
                        gameBoard[i-2][j+2] == 0 && gameBoard[i-3][j+3] == 0 && gameBoard[i-4][j+4] == 0)
                {
                    pointBoard[i-1][j+1] += pointsHigh;
                    pointBoard[i-2][j+2] += pointsMedium;
                    pointBoard[i-3][j+3] += pointsLow;
                    pointBoard[i-4][j+4] += pointsLow;
                }
            }
        }
    }
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
    cleanPointBoard();

    if(firstCPUMove)
    {
        makeFirstCPUMove();
    }
    else
    {
        lookForFour();
        lookForBrokenFour();
        lookForThree();
        lookForTwo();
        lookForSingle();

        findMaxInPointBoard();
        makeCPUMove(gameBoardPoint.first, gameBoardPoint.second);
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
    setGameBoardPoint(7+abs((7-gameBoardPoint.first)), 7+abs((7-gameBoardPoint.second)));
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

void Game::findMaxInPointBoard()
{
    int max = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(pointBoard[i][j] > max)
            {
                max = pointBoard[i][j];
                setGameBoardPoint(i,j);
            }
        }
    }
}
