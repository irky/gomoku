#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPointF>

#include <cmath>
#include <cstdlib>
#include <vector>

#include "game.h"

class Board : public QGraphicsScene
{
    Q_OBJECT
public:
    Board(QObject *parent);
    ~Board();

    int getBoardSize() const;
    int getGridStep() const;

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void drawCPUMove();

signals:
    void CPUMoveRequest();
    void updateGameBoardRequest();

protected:
   void drawBackground(QPainter * painter, const QRectF & rect);
   void drawGrid(QPainter * painter);
   void drawEmptyEllipses(QPainter *painter);
   void findClickedCircle(int row, int column, std::pair<int,int> &point) const;
   void drawUserMove(int row, int column);

private:
   std::vector< std::vector <std::pair<int,int> > > circlesTable;
   static const int BOARD_SIZE = 15;
   static const int GRID_STEP = 30;
   Game *game;

};

#endif // BOARD_H
