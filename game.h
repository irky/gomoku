#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include <vector>

#include <QObject>
#include <QMetaType>
#include <QPointF>
#include <QDebug>

#include "constants.h"

class Game : public QObject
{
    Q_OBJECT
    friend class Board;

public:
    Game();

    std::pair<int,int> getCPUCoordinates() const;
    std::pair<int,int> countGameBoardCoordinates(const int &row, const int &column) const;

public slots:
    void countCPUMove();
    void countUserMove(const int &row, const int &col);
    void clearGameStatus(const bool &value);

signals:
    void drawCPUMoveRequest(const int&, const int&, const bool&);
    void drawUserMoveRequest(const int&, const int&, const bool&);
    void winGameFinishRequest(const int &whoWon);

private:    
    int updateGameBoard(const int &x, const int &y, const int &who);
    bool checkIfMovePossible(const int &row, const int &col);
    int countSingleCoordinate(const int &row) const;
    QPointF countBoardPoint(const int &row, const int &col) const;

    bool checkIfWinConfiguration(const int &who);
    bool checkWinHorizontal(const int &who);
    bool checkWinVertical(const int &who);
    bool checkWinDiagonal(const int &who);

    void makeFirstCPUMove();
    void makeCPUMove(int i, int j);
    void makeUserMove(std::pair<int, int> boardPoint, const int &row, const int &col);

    void lookForFour();
    void lookForFourVertical(const int &who, const int &points);
    void lookForFourHorizontal(const int &who, const int &points);
    void lookForCPUFourDiagonal(const int &who, const int &points);

    void lookForBrokenFour();
    void lookForBrokenFourVertical(const int &who, const int &points);
    void lookForBrokenFourHorizontal(const int &who, const int &points);
    void lookForBrokenFourDiagonal(const int &who, const int &points);

    void lookForThree();
    void lookForThreeVertical1Priority(const int &who, const int &pointsHigh, const int &pointsLow);
    void lookForThreeHorizontal1Priority(const int &who, const int &pointsHigh, const int &pointsLow);
    void lookForThreeDiagonal1Priority(const int &who, const int &pointsHigh, const int &pointsLow);

    void lookForThreeVertical2Priority(const int &who, const int &pointsHigh, const int &pointsMedium, const int &pointsLow);
    void lookForThreeHorizontal2Priority(const int &who, const int &pointsHigh, const int &pointsMedium, const int &pointsLow);
    void lookForThreeDiagonal2Priority(const int &who, const int &pointsHigh, const int &pointsMedium, const int &pointsLow);

    void lookForThreeVertical3Priority(const int &who, const int &pointsHigh, const int &pointsLow);
    void lookForThreeHorizontal3Priority(const int &who, const int &pointsHigh, const int &pointsLow);
    void lookForThreeDiagonal3Priority(const int &who, const int &pointsHigh, const int &pointsLow);

    void lookForThreeVertical4Priority(const int &who, const int &points);
    void lookForThreeHorizontal4Priority(const int &who, const int &points);
    void lookForThreeDiagonal4Priority(const int &who, const int &points);

    void lookForTwo();
    void lookForTwoVertical(const int &who, const int &pointsHigh, const int &pointsLow);
    void lookForTwoHorizontal(const int &who, const int &pointsHigh, const int &pointsLow);
    void lookForTwoDiagonal(const int &who, const int &pointsHigh, const int &pointsLow);

    void lookForSingle();
    void lookForSingleVertical(const int &who, const int &pointsHigh, const int &pointsMedium, const int &pointsLow);
    void lookForSingleHorizontal(const int &who, const int &pointsHigh, const int &pointsMedium, const int &pointsLow);
    void lookForSingleDiagonal(const int &who, const int &pointsHigh, const int &pointsMedium, const int &pointsLow);

    bool gameFinished;
    void setGameFinished(const bool &value);

    bool firstCPUMove;

    std::pair<int,int> gameBoardPoint;
    void setGameBoardPoint(const int &row, const int &col);

    std::vector< std::vector<int> > gameBoard;

    std::vector< std::vector<int> > pointBoard;
    void cleanPointBoard();
    void findMaxInPointBoard();
};

#endif // GAME_H
