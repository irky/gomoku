#include "board.h"

Board::Board(QObject *parent) : QGraphicsScene(parent)
{
    game = new Game();

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

    connect(this, SIGNAL(CPUMoveRequest()), game, SLOT(countCPUMove()));
    connect(game, SIGNAL(drawCPUMoveRequest()), this, SLOT(drawCPUMove()));

}

Board::~Board()
{
    delete game;
}

void Board::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(game->isUserMoveAllowed())
    {
        std::pair<int,int> approxPoint;
        approxPoint.first = getGridStep();
        approxPoint.second = getGridStep();
        QPointF point = event->scenePos();
        findClickedCircle(point.x(), point.y(), approxPoint);
        drawUserMove(approxPoint.first, approxPoint.second);
        emit CPUMoveRequest();
    }
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
    qDebug() << " x " << row << " y " << column;
    addEllipse(row-13,column-13,getGridStep()-4,getGridStep()-4, QPen(Qt::blue), QBrush(Qt::blue));
    std::pair<int,int> boardPoint = game->countGameBoardCoordinates(row, column);
    qDebug() << "przeliczone x " << boardPoint.first << " przeliczone y " << boardPoint.second;
    game->updateGameBoard(boardPoint.first-1, boardPoint.second-1, game->getUserValue());
    game->setUserMoveAllowed(false);
    qDebug() << "drawing user move finished";
}

void Board::drawCPUMove()
{
    qDebug() << "drawing CPU Move";
    QPointF point = game->countCPUBoardPoint();
    qDebug() << " x " << point.x() << " y " << point.y();
    addEllipse(point.x()+2,point.y()+2,getGridStep()-4,getGridStep()-4, QPen(Qt::red), QBrush(Qt::red));
    std::pair<int,int> boardPoint = game->countGameBoardCoordinates(point.x(), point.y());
    game->updateGameBoard(boardPoint.first, boardPoint.second, game->getCPUValue());
    game->setUserMoveAllowed(true);
}

int Board::getBoardSize() const
{
    return BOARD_SIZE;
}
