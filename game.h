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
    void drawCPUMoveRequest(const int&, const int&);
    void drawUserMoveRequest(const int&, const int&);

private:
    void updateGameBoard(const int &x, const int &y, const int &who);
    bool checkIfMovePossible(const int &row, const int &col);
    int countSingleCoordinate(const int &row) const;
    QPointF countBoardPoint(const int &row, const int &col) const;
    bool checkIfWinConfiguration();

    std::vector< std::vector<int> > gameBoard;
    bool gameFinished;
    void setGameFinished(const bool &value);
};

#endif // GAME_H
