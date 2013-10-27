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
#include "constants.h"

class Board : public QGraphicsScene
{
    Q_OBJECT
public:
    Board(QObject *parent);

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void drawCPUMove(const int &row, const int &column);
    void drawUserMove(const int &row, const int &column);

signals:
    void CPUMoveRequest();
    void userMoveRequest(const int&, const int&);
    void updateGameBoardRequest(const int&,const int&, const int&);

protected:
   void drawBackground(QPainter * painter, const QRectF & rect);
   void drawGrid(QPainter * painter);
   void drawEmptyEllipses(QPainter *painter);
   void findClickedCircle(int row, int column, std::pair<int,int> &point);

private:
   std::vector< std::vector <std::pair<int,int> > > circlesTable;

   bool userMoveAllowed;
   void setUserMoveAllowed(bool value);
   bool isUserMoveAllowed() const;
};

#endif // BOARD_H
