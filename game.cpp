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
        vect.reserve(15);
        for(int j = 0; j < BOARD_SIZE; j++)
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


void Game::makeFirstCPUMove()
{
    // TODO: look for user's first move and place rock nearby
    if(checkIfMovePossible(8,8))
    {
        makeCPUMove(8,8);
    }
    else
    {
        makeCPUMove(7,7);
    }
}

// build threat tree
// used if opponent didn't build any threats (f.e. beginning of the game)
void Game::buildThreat()
{
    if(firstCPUMove)
    {
        makeFirstCPUMove();
    }
    else
    {
        if(lookForCPUFour())
        {
            return;
        }
    }
}

bool Game::lookForCPUFourHorizontal()
{
    unsigned int fourCounter = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(gameBoard[i][j] == CPU)
            {
                fourCounter++;
                if(fourCounter == 4)
                {
                    if(j >= fourCounter && gameBoard[i][j-fourCounter] == 0)
                    {
                        setGameBoardPoint(i,j-fourCounter);
                        return true;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            else if(gameBoard[i][j] == 0 && fourCounter == 4)
            {
                // tu nalezy postawic zwycieski ruch i zakonczyc wyszukiwanie
                setGameBoardPoint(i,j);
                return true;
            }
            else
            {
                fourCounter = 0;
            }
        }
        fourCounter = 0;
    }
    return false;
}

bool Game::lookForCPUFourVertical()
{
    unsigned int fourCounter = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(gameBoard[j][i] == CPU)
            {
                fourCounter++;
                if(i >= fourCounter && gameBoard[i-fourCounter][j] == 0)
                {
                    setGameBoardPoint(i-fourCounter,j);
                    return true;
                }
                else
                {
                    continue;
                }
            }
            else if(gameBoard[j][i] == 0 && fourCounter == 4)
            {
                // tu nalezy postawic zwycieski ruch i zakonczyc wyszukiwanie
                setGameBoardPoint(i,j);
                return true;
            }
            else
            {
                fourCounter = 0;
            }
        }
        fourCounter = 0;
    }
    return false;
}

bool Game::lookForCPUFourDiagonal()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(gameBoard[j][i] == CPU)
            {
                unsigned int fourCounter = 1;
                if(j <= 10 && i <=10)
                {
                    while(gameBoard[i+fourCounter][j+fourCounter] == CPU)
                    {
                        fourCounter++;
                    }
                    if(fourCounter == 4 && gameBoard[i+fourCounter][j+fourCounter] == 0)
                    {
                        setGameBoardPoint(i+5,j+5);
                        return true;
                    }
                }
                fourCounter = 1;
                if(j >= 5 && i <= 10)
                {
                    while(gameBoard[i+fourCounter][j-fourCounter] == CPU)
                    {
                        fourCounter++;
                    }
                    if(fourCounter == 4 && gameBoard[i+fourCounter][j-fourCounter] == 0)
                    {
                        setGameBoardPoint(i+5,j-5);
                        return true;
                    }
                }
                fourCounter = 1;
                if(j <= 10 && i >= 5)
                {
                    while(gameBoard[i-fourCounter][j+fourCounter] == CPU)
                    {
                        fourCounter++;
                    }
                    if(fourCounter == 4 && gameBoard[i-fourCounter][j+fourCounter] == 0)
                    {
                        setGameBoardPoint(i-5,j+5);
                        return true;
                    }
                }
                fourCounter = 1;
                if(j >= 5 && i >= 5)
                {
                    while(gameBoard[i-fourCounter][j-fourCounter] == CPU)
                    {
                        fourCounter++;
                    }
                    if(fourCounter == 4 && gameBoard[i-fourCounter][j-fourCounter] == 0)
                    {
                        setGameBoardPoint(i-5,j-5);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Game::lookForCPUFour()
{
    if(lookForCPUFourHorizontal())
    {
        qDebug() << "Found CPU 4 horizontal";
        return true;
    }
    else if(lookForCPUFourVertical())
    {
        qDebug() << "Found CPU 4 vertical";
        return true;
    }
    else if(lookForCPUFourDiagonal())
    {
        qDebug() << "Found CPU 4 diagonal";
        return true;
    }
    return false;
}

void Game::lookForOpponentThreat()
{
    lookForOpponentFour();
}

// ----------------------//
// Examples:             //
//  ___________________  //
// | O O O O + + + + + | //
// | X O O O O + + + + | //
// | + + + + + O O O O | //
// | + + + + O O O O X | //
//                       //
// Diagonal              //
// Vertical              //
// Horizontal            //
// ----------------------//
bool Game::lookForOpponentFour()
{
    if(lookForOpponenFourHorizontal())
    {
        qDebug() << "Found opponent one side 4 horizontal";
        return true;
    }
    else if(lookForOpponenFourVertical())
    {
        qDebug() << "Found opponent one side 4 vertical";
        return true;
    }
    else if(true)
    {
        qDebug() << "Found opponent one side 4 diagonal";
        return true;
    }
    return false;
}

bool Game::lookForOpponenFourHorizontal()
{
    unsigned int fourCounter = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(gameBoard[i][j] == USER)
            {
                fourCounter++;
                if(fourCounter == 4)
                {
                    if(j >= fourCounter && gameBoard[i][j-fourCounter] == 0)
                    {
                        // tu nalezy postawic blokujacy ruch ,,z tyłu'' czworki i zakonczyc wyszukiwanie
                        setGameBoardPoint(i,j-fourCounter);
                        return true;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            else if(gameBoard[i][j] == 0 && fourCounter == 4)
            {
                // tu nalezy postawic blokujacy ruch ,,z przodu'' czworki i zakonczyc wyszukiwanie
                setGameBoardPoint(i,j);
                return true;
            }
            else
            {
                fourCounter = 0;
            }
        }
        fourCounter = 0;
    }
    return false;
}

bool Game::lookForOpponenFourVertical()
{
    unsigned int fourCounter = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(gameBoard[j][i] == USER)
            {
                fourCounter++;
                if(i >= fourCounter && gameBoard[i-fourCounter][j] == 0)
                {
                    setGameBoardPoint(i-fourCounter,j);
                    return true;
                }
                else
                {
                    continue;
                }
            }
            else if(gameBoard[j][i] == 0 && fourCounter == 4)
            {
                // tu nalezy postawic zwycieski ruch i zakonczyc wyszukiwanie
                setGameBoardPoint(i,j);
                return true;
            }
            else
            {
                fourCounter = 0;
            }
        }
        fourCounter = 0;
    }
    return false;
}

bool Game::lookForOpponentOneSideFourDiagonal()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(gameBoard[j][i] == USER)
            {
                unsigned int fourCounter = 1;
                if(j <= 10 && i <=10)
                {
                    while(gameBoard[i+fourCounter][j+fourCounter] == USER)
                    {
                        fourCounter++;
                    }
                    if(fourCounter == 4 && gameBoard[i+fourCounter][j+fourCounter] == 0)
                    {
                        setGameBoardPoint(i+5,j+5);
                        return true;
                    }
                }
                fourCounter = 1;
                if(j >= 5 && i <= 10)
                {
                    while(gameBoard[i+fourCounter][j-fourCounter] == USER)
                    {
                        fourCounter++;
                    }
                    if(fourCounter == 4 && gameBoard[i+fourCounter][j-fourCounter] == 0)
                    {
                        setGameBoardPoint(i+5,j-5);
                        return true;
                    }
                }
                fourCounter = 1;
                if(j <= 10 && i >= 5)
                {
                    while(gameBoard[i-fourCounter][j+fourCounter] == USER)
                    {
                        fourCounter++;
                    }
                    if(fourCounter == 4 && gameBoard[i-fourCounter][j+fourCounter] == 0)
                    {
                        setGameBoardPoint(i-5,j+5);
                        return true;
                    }
                }
                fourCounter = 1;
                if(j >= 5 && i >= 5)
                {
                    while(gameBoard[i-fourCounter][j-fourCounter] == USER)
                    {
                        fourCounter++;
                    }
                    if(fourCounter == 4 && gameBoard[i-fourCounter][j-fourCounter] == 0)
                    {
                        setGameBoardPoint(i-5,j-5);
                        return true;
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

    // 2. look for Opponent one-side 4-s
    // 3. look for Opponent two-side 3-s
    // 4. look for Opponent two-side 3-s
    makeCPUMove(gameBoardPoint.first, gameBoardPoint.second);
    return;
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
