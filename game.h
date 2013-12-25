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

    void buildThreat();
    bool lookForCPUFour();
    bool lookForCPUFourHorizontal();
    bool lookForCPUFourVertical();
    bool lookForCPUFourDiagonal();

    bool lookForOpponentFour();
    bool lookForOpponentFourHorizontal();
    bool lookForOpponentFourVertical();
    bool lookForOpponentFourDiagonal();

    bool lookForCPUSpecialPattern();
    bool lookForCPUSpecialPatternHorizontal();
    bool lookForCPUSpecialPatternVertical();
    bool lookForCPUSpecialPatternDiagonal();

    bool lookForOpponentSpecialPattern();
    bool lookForOpponentSpecialPatternHorizontal();
    bool lookForOpponentSpecialPatternVertical();
    bool lookForOpponentSpecialPatternDiagonal();

    bool lookForOpponentThree();
    bool lookForOpponentThreeHorizontal1Priority();
    bool lookForOpponentThreeVertical1Priority();
    bool lookForOpponentThreeDiagonal1Priority();

    bool lookForOpponentThreeHorizontal2Priority();
    bool lookForOpponentThreeVertical2Priority();
    bool lookForOpponentThreeDiagonal2Priority();

    bool lookForOpponentThreeHorizontal3Priority();
    bool lookForOpponentThreeVertical3Priority();
    bool lookForOpponentThreeDiagonal3Priority();

    bool lookForOpponentThreeHorizontal4Priority();
    bool lookForOpponentThreeVertical4Priority();
    bool lookForOpponentThreeDiagonal4Priority();

    bool lookForCPUThree();
    bool lookForCPUThreeHorizontal1Priority();
    bool lookForCPUThreeVertical1Priority();
    bool lookForCPUThreeDiagonal1Priority();

    bool lookForCPUThreeHorizontal2Priority();
    bool lookForCPUThreeVertical2Priority();
    bool lookForCPUThreeDiagonal2Priority();

    bool lookForCPUThreeHorizontal3Priority();
    bool lookForCPUThreeVertical3Priority();
    bool lookForCPUThreeDiagonal3Priority();

    bool lookForCPUThreeHorizontal4Priority();
    bool lookForCPUThreeVertical4Priority();
    bool lookForCPUThreeDiagonal4Priority();

    bool lookForCPUTwo();
    bool lookForCPUTwoHorizontal();
    bool lookForCPUTwoVertical();
    bool lookForCPUTwoDiagonal();

    bool lookForCPUSingle();
    bool lookForCPUSingleHorizontal();
    bool lookForCPUSingleVertical();
    bool lookForCPUSingleDiagonal();

    bool gameFinished;
    void setGameFinished(const bool &value);

    bool firstCPUMove;

    std::pair<int,int> gameBoardPoint;
    void setGameBoardPoint(const int &row, const int &col);

    std::vector< std::vector<int> > gameBoard;

};

#endif // GAME_H
