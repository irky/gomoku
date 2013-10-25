#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include <vector>

#include <QObject>
#include <QMetaType>
#include <QPointF>
#include <QDebug>

class Game : public QObject
{
    Q_OBJECT
    friend class Board;

public:
    Game();

    int getCPUValue() const;
    int getUserValue() const;
    std::pair<int,int> getCPUCoordinates() const;
    std::pair<int,int> countGameBoardCoordinates(const int &row, const int &column) const;

public slots:
    void countCPUMove();

signals:
    void drawCPUMoveRequest();

private:
    void setUserMoveAllowed(bool value);
    bool isUserMoveAllowed() const;
    void updateGameBoard(const int &x, const int &y, const int &who);
    bool checkIfMovePossible(const int &row, const int &col);
    void cpuMove();

    bool userMoveAllowed;

    std::vector< std::vector<int> > gameBoard;

    std::pair<int,int> CPUCoordinates;
    void setCPUCoordinates(const std::pair<int, int> &coord);
    QPointF countCPUBoardPoint() const;

    const static int USER = 1;
    const static int CPU = -1;

};

#endif // GAME_H
