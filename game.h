#ifndef GAME_H
#define GAME_H

#include <QGenericMatrix>
#include "board.h"
#include <QObject>

class Game : public QObject
{
    Q_OBJECT

public:
    Game();

public slots:
    void userMove(const QPointF &point);
    void checkIfMovePossible();

signals:
    void allowUserMove();

private:
    bool userMoveAllowed;
    void cpuMove();
    void countCPUMove();
    void updateGameBoard();
    QGenericMatrix<15,15,int> *gameBoard;
};

#endif // GAME_H
