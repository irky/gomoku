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
    if(lookForOpponentFourHorizontal())
    {
        qDebug() << "Found opponent one side 4 horizontal";
        return true;
    }
    else if(lookForOpponentFourVertical())
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

bool Game::lookForOpponentFourHorizontal()
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

bool Game::lookForOpponentFourVertical()
{
    unsigned int fourCounter = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(gameBoard[j][i] == USER)
            {
                fourCounter++;
                if(j >= fourCounter && gameBoard[j-fourCounter][i] == 0)
                {
                    setGameBoardPoint(j-fourCounter,i);
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
                setGameBoardPoint(j,i);
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

bool Game::lookForOpponentFourDiagonal()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(gameBoard[j][i] == USER)
            {
                unsigned int fourCounter = 1;
                if(j <= 9 && i <=9)
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
                if(j >= 5 && i <= 9)
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
                if(j <= 9 && i >= 5)
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

void Game::lookForOpponentTwoSideThree()
{

}

bool Game::lookForOpponentTwoSideThreeHorizontal()
{
    unsigned int threeCounter = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(gameBoard[i][j] == USER)
            {
                threeCounter++;
                if(threeCounter == 3)
                {
                    // wszystkie możliwe warianty trójek
                    // 1. --OOO-|
                    if(j == 13 && gameBoard[i][j+1] == 0 && gameBoard[i][j-3] == 0 && gameBoard[i][j-4] == 0)
                    {
                        setGameBoardPoint(i,j-4);
                        return true;
                    }
                    // 2. |-OOO--
                    else if(j == 3 && gameBoard[i][j-1] == 0 && gameBoard[i][j+3] == 0 && gameBoard[i][j+4] == 0)
                    {
                        setGameBoardPoint(i,j+4);
                        return true;
                    }
                    // 3. --OOO-X
                    else if(j >= 4 && j <= 12 && gameBoard[i][j-3] == 0 && gameBoard[i][j-4] == 0
                            && gameBoard[i][j+1] == 0 && gameBoard[i][j+2] == USER)
                    {
                        setGameBoardPoint(i,j-3);
                        return true;
                    }
                    // 4. X-OOO--
                    else if(j >= 4 && j <= 12 && gameBoard[i][j-3] == 0 && gameBoard[i][j-4] == USER
                            && gameBoard[i][j+1] == 0 && gameBoard[i][j+2] == 0)
                    {
                        setGameBoardPoint(i,j+1);
                        return true;
                    }
                    // 5. --OOO--
                    else if(j >= 4 && j <= 12 && gameBoard[i][j-3] == 0 && gameBoard[i][j-4] == 0
                            && gameBoard[i][j+1] == 0 && gameBoard[i][j+2] == 0)
                    {
                        setGameBoardPoint(i,j+1);
                        return true;
                    }
                }
                continue;
            }
            else
            {
                threeCounter = 0;
            }
        }
        threeCounter = 0;
    }
    return false;
}

bool Game::lookForOpponentTwoSideThreeVertical()
{
    unsigned int threeCounter = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(gameBoard[j][i] == USER)
            {
                threeCounter++;
                if(threeCounter == 3)
                {
                    // wszystkie możliwe warianty trójek
                    // 1. --OOO-|
                    if(j == 13 && gameBoard[j+1][i] == 0 && gameBoard[j-3][i] == 0 && gameBoard[j-4][i] == 0)
                    {
                        setGameBoardPoint(j-4,i);
                        return true;
                    }
                    // 2. |-OOO--
                    else if(j == 3 && gameBoard[j-1][i] == 0 && gameBoard[j+3][i] == 0 && gameBoard[j+4][i] == 0)
                    {
                        setGameBoardPoint(j+4,i);
                        return true;
                    }
                    // 3. --OOO-X
                    else if(j >= 4 && j <= 12 && gameBoard[j-3][i] == 0 && gameBoard[j-4][i] == 0
                            && gameBoard[j+1][i] == 0 && gameBoard[j+2][i] == CPU)
                    {
                        setGameBoardPoint(j-3,i);
                        return true;
                    }
                    // 4. X-OOO--
                    else if(j >= 4 && j <= 12 && gameBoard[j-3][i] == 0 && gameBoard[j-3][i] == CPU
                            && gameBoard[j+1][i] == 0 && gameBoard[j+2][i] == 0)
                    {
                        setGameBoardPoint(j+1,i);
                        return true;
                    }
                    // 5. --OOO--
                    else if(j >= 4 && j <= 12 && gameBoard[j-3][i] == 0 && gameBoard[j-4][i] == 0
                            && gameBoard[j+1][i] == 0 && gameBoard[j+2][i] == 0)
                    {
                        setGameBoardPoint(j+1,i);
                        return true;
                    }
                }
                continue;
            }
            else
            {
                threeCounter = 0;
            }
        }
        threeCounter = 0;
    }
    return false;
}

bool Game::lookForOpponentTwoSideThreeDiagonal()
{

    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(gameBoard[i][j] == USER)
            {
                unsigned int threeCounter = 1;

                // 1. na poczatku skosy przy brzegach

                // prawy dolny i lewy górny rog
                if(i <= 11 && j <= 11 && i >= 1 && j >= 1)
                {
                    while(gameBoard[i+threeCounter][j+threeCounter] == USER)
                    {
                        threeCounter++;
                    }
                    if(threeCounter == 3)
                    {
                        if((i == 11 || j == 11) && gameBoard[i+3][j+3] == 0 && gameBoard[i-1][j-1] == 0)
                        {
                            setGameBoardPoint(i-1,j-1);
                            return true;
                        }
                        else if((i == 1 || j == 1) && gameBoard[i+3][j+3] == 0 && gameBoard[i-1][j-1] == 0)
                        {
                            setGameBoardPoint(i+3,j+3);
                            return true;
                        }
                    }
                }
                threeCounter = 1;
                // prawy gorny i lewy dolny rog
                if(i <= 11 && j <= 13 && i >= 1 && j >= 3)
                {
                    while(gameBoard[i+threeCounter][j-threeCounter] == USER)
                    {
                        threeCounter++;
                    }
                    if(threeCounter == 3)
                    {
                        if((i == 1 || j == 13) && gameBoard[i-1][j+1] == 0 && gameBoard[i+3][j-3] == 0)
                        {
                            setGameBoardPoint(i+3,j-3);
                            return true;
                        }
                        else if((j == 3 || i == 11) && gameBoard[i-1][j+1] == 0 && gameBoard[i+3][j-3] == 0)
                        {
                            setGameBoardPoint(i-1,j+1);
                            return true;
                        }
                    }
                }
                threeCounter = 1;

                // 2. w sasiedztwie CPU
                // prawy dolny i lewy gowny rog
                if(i >= 2 && j >= 2 && i <= 10 && j <= 10)
                {
                    while(gameBoard[i+threeCounter][j+threeCounter] == USER)
                    {
                        threeCounter++;
                    }
                    if(threeCounter == 3)
                    {
                        if(gameBoard[i+3][j+3] == 0 && gameBoard[i-1][j-1] == 0 && gameBoard[i-2][j-2] == CPU)
                        {
                            setGameBoardPoint(i+3,j+3);
                            return true;
                        }
                        else if(gameBoard[i+3][j+3] == 0 && gameBoard[i-1][j-1] == 0 && gameBoard[i+4][j+4] == CPU)
                        {
                            setGameBoardPoint(i-1,j-1);
                            return true;
                        }
                    }
                }
                threeCounter = 1;

                // prawy gorny i lewy dolny rog
                if(i >= 2 && j >= 4 && i <= 10 && j <= 12)
                {
                    while(gameBoard[i+threeCounter][j-threeCounter] == USER)
                    {
                        threeCounter++;
                    }
                    if(threeCounter == 3)
                    {
                        if(gameBoard[i-1][j+1] == 0 && gameBoard[i-2][j+2] == CPU && gameBoard[i+3][j-3] == 0)
                        {
                            setGameBoardPoint(i+3,j-3);
                            return true;
                        }
                        else if(gameBoard[i-1][j+1] == 0 && gameBoard[i+3][j-3] == 0 && gameBoard[i+4][j-4] == CPU)
                        {
                            setGameBoardPoint(i-1,j+1);
                            return true;
                        }
                    }
                }
                // 3. ,,zwykla'' trojka obustronna

                threeCounter = 1;
                if(i >= 2 && j >= 2 && i <= 12 && j <= 12)
                {
                    // prawy dolny i lewy gowny rog
                    while(gameBoard[i+threeCounter][j+threeCounter] == USER)
                    {
                        threeCounter++;
                    }
                    if(threeCounter == 3)
                    {
                        if(gameBoard[i-1][j-1] == 0 && gameBoard[i-2][j-2] == 0 &&
                           gameBoard[i+4][j+4] == 0 && gameBoard[i+3][j+3] == 0)
                        {
                            // w sumie jest to obojetne, ale mozna dolozyc glebsza analize pozniej
                            setGameBoardPoint(i+3,j+3);
                            return true;
                        }
                    }

                    threeCounter = 1;
                    // prawy gorny i lewy dolny rog
                    while(gameBoard[i+threeCounter][j+threeCounter] == USER)
                    {
                        threeCounter++;
                    }
                    if(threeCounter == 3)
                    {
                        if(gameBoard[i-1][j-1] == 0 && gameBoard[i-2][j-2] == 0 &&
                           gameBoard[i+4][j+4] == 0 && gameBoard[i+3][j+3] == 0)
                        {
                            // w sumie jest to obojetne, ale mozna dolozyc glebsza analize pozniej
                            setGameBoardPoint(i+3,j+3);
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
    if(lookForCPUFour())
    {
        makeCPUMove(gameBoardPoint.first, gameBoardPoint.second);
        return;
    }
    // 2. look for Opponent 4-s
    if(lookForOpponentFour())
    {
        makeCPUMove(gameBoardPoint.first, gameBoardPoint.second);
        return;
    }
    // 3. look for Opponent spechal patterns 3-s OOO-O & 00-00 & 0-000

    // 4. look for Opponent two-side 3-s

    // 5. look for CPU two-side 3-s

    // 6. build threat
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
