#ifndef GAME_H
#define GAME_H

#include <QGenericMatrix>
#include "board.h"
#include <QObject>
#include <QMetaType>

class Game : public QObject
{
    Q_OBJECT

public:
    Game();
    Game(const Game&);
    Game(QObject *parent);

public slots:
    void userMove(const QPointF &point);
    void checkIfMovePossible();

signals:
    void allowUserMove(int x=0, int y=0);

private:
    bool userMoveAllowed;
    void cpuMove();
    void countCPUMove();
    void updateGameBoard();
    QGenericMatrix<15,15,int> *gameBoard;
};

#endif // GAME_H
