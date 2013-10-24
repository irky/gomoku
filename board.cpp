#include "board.h"

Board::Board(QObject *parent) : QGraphicsScene(parent)
{
    circlesTable.reserve(getBoardSize());
    for(int i = 0; i < getBoardSize(); i++)
    {
        std::vector<std::pair<int,int> > vect;
        vect.reserve(getBoardSize());
        for(int j = 0; j < getBoardSize(); j++)
        {
            std::pair<int,int> p;
            p.first = -210 + i*getGridStep();
            p.second = -210 + j*getGridStep();
            vect.push_back(p);
        }
        circlesTable.push_back(vect);
    }
}

void Board::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    std::pair<int,int> approxPoint;
    approxPoint.first = getGridStep();
    approxPoint.second = getGridStep();
    QPointF point = event->scenePos();
    findClickedCircle(point.x(), point.y(), approxPoint);

    // drawUserMove(approxPoint.first, approxPoint.second);
    // emit signal and send to game slot about user wants to move
    emit userMoveRequest();
    // check if move is possilbe
    // send from game to board information about possibility
    // draw move or not
}

void Board::drawBackground(QPainter *painter, const QRectF &rect)
{
    drawGrid(painter);
    drawEmptyEllipses(painter);
}

int Board::getGridStep() const
{
    return GRID_STEP;
}

void Board::drawGrid(QPainter *painter)
{
    painter->setPen(QPen(QColor(0, 0, 0, 125)));
    for(int i = -225; i < 15*getGridStep(); i+= getGridStep())
    {
        painter->drawLine(i,-225,i,225);
        painter->drawLine(-225,i,225,i);
    }
}

void Board::drawEmptyEllipses(QPainter *painter)
{
    painter->setPen(QPen(QColor(255, 255, 255, 255)));
    for(int i = -225; i < 15*getGridStep()-225; i+= getGridStep())
    {
        for(int j = -225; j < 15*getGridStep()-225; j+= getGridStep())
        {
            addEllipse(i+2,j+2,getGridStep()-4,getGridStep()-4, painter->pen());
        }
    }
}

void Board::findClickedCircle(int x, int y, std::pair<int,int>& wynik) const
{
    for(int i = 0; i < getBoardSize(); i++)
    {
        for(int j = 0; j < getBoardSize(); j++)
        {
            if(abs(circlesTable[i][j].first - x) < abs(wynik.first - x))
            {
                wynik.first = circlesTable[i][j].first;
            }
            if(abs(circlesTable[i][j].second - y) < abs(wynik.second - y))
            {
                wynik.second = circlesTable[i][j].second;
            }
        }
    }
}

void Board::drawUserMove(int row, int column)
{
    addEllipse(row-13,column-13,getGridStep()-4,getGridStep()-4, QPen(Qt::blue), QBrush(Qt::blue));
}

void Board::userMoveRequest()
{
    qDebug() << "User move request sent";
}

int Board::getBoardSize() const
{
    return BOARD_SIZE;
}
