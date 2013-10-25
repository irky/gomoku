#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include <cmath>
#include <cstdlib>

#include "game.h"

class Board : public QGraphicsScene
{
    Q_OBJECT
public:
    Board(QObject *parent);
    Board(const Board&);
    Board();

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void drawUserMove(int row, int column);

signals:
    void userMoveRequest();

protected:
   void drawBackground(QPainter * painter, const QRectF & rect);
   void drawGrid(QPainter * painter);
   void drawEmptyEllipses(QPainter *painter);
   void findClickedCircle(int row, int column, std::pair<int,int> &point) const;

private:
   std::vector< std::vector <std::pair<int,int> > > circlesTable;
   static const int BOARD_SIZE = 15;
   int getBoardSize() const;
   static const int GRID_STEP = 30;
   int getGridStep() const;

};

#endif // BOARD_H
