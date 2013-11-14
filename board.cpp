#include "board.h"

Board::Board(QObject *parent) : QGraphicsScene(parent)
{
    userMoveAllowed = false;

    circlesTable.reserve(BOARD_SIZE);
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        std::vector<std::pair<int,int> > vect;
        vect.reserve(BOARD_SIZE);
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            std::pair<int,int> p;
            p.first = FIRST_GRID_CENTRE + i*GRID_STEP;
            p.second = FIRST_GRID_CENTRE + j*GRID_STEP;
            vect.push_back(p);
        }
        circlesTable.push_back(vect);
    }
}

void Board::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(isUserMoveAllowed())
    {
        std::pair<int,int> approxPoint;
        approxPoint.first = GRID_STEP;
        approxPoint.second = GRID_STEP;
        QPointF point = event->scenePos();
        findClickedCircle(point.x(), point.y(), approxPoint);
    }
}

void Board::drawBackground(QPainter *painter, const QRectF &rect)
{
    drawGrid(painter);
    drawEmptyEllipses(painter);
}

void Board::drawGrid(QPainter *painter)
{
    painter->setPen(QPen(QColor(0, 0, 0, 125)));
    for(int i = -225; i < BOARD_SIZE*GRID_STEP; i+= GRID_STEP)
    {
        painter->drawLine(i,-225,i,225);
        painter->drawLine(-225,i,225,i);
    }
}

void Board::drawEmptyEllipses(QPainter *painter)
{
    painter->setPen(QPen(QColor(255, 255, 255, 255)));
    for(int i = FIRST_GRID_CENTRE; i < BOARD_SIZE*GRID_STEP + FIRST_GRID_CENTRE; i+= GRID_STEP)
    {
        for(int j = FIRST_GRID_CENTRE; j < BOARD_SIZE*GRID_STEP + FIRST_GRID_CENTRE; j+= GRID_STEP)
        {
            addEllipse(i-(DIAMETER/2), j-(DIAMETER/2), DIAMETER, DIAMETER, painter->pen());
        }
    }
}

void Board::cleanBoardAndGameStatus()
{
    setUserMoveAllowed(false);
    for(int i = FIRST_GRID_CENTRE; i< BOARD_SIZE*GRID_STEP + FIRST_GRID_CENTRE; i+= GRID_STEP)
    {
        for(int j = FIRST_GRID_CENTRE; j< BOARD_SIZE*GRID_STEP + FIRST_GRID_CENTRE; j+= GRID_STEP)
        {
            addEllipse(i-(DIAMETER/2), j-(DIAMETER/2), DIAMETER, DIAMETER, QPen(QColor(255, 255, 255, 255)), QBrush(QColor(255, 255, 255, 255)));
        }
    }
    emit stopGame(true);
}

void Board::findClickedCircle(int x, int y, std::pair<int,int>& wynik)
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
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
    emit userMoveRequest(wynik.first, wynik.second);
}

void Board::setUserMoveAllowed(bool value)
{
    userMoveAllowed = value;
}

bool Board::isUserMoveAllowed() const
{
    return userMoveAllowed;
}

void Board::drawUserMove(const int &row, const int &column)
{
    addEllipse(row-(DIAMETER/2), column-(DIAMETER/2), DIAMETER, DIAMETER, QPen(Qt::blue), QBrush(Qt::blue));
    setUserMoveAllowed(false);
    emit CPUMoveRequest();
}

void Board::drawCPUMove(const int &row, const int &column)
{
    addEllipse(row-(DIAMETER/2), column-(DIAMETER/2) ,DIAMETER, DIAMETER, QPen(Qt::red), QBrush(Qt::red));
    setUserMoveAllowed(true);
}
