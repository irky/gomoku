#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QPainter>

#include "board.h"
#include "game.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void gameFinishedbyWin(const int &whoWon);

signals:
    void clearBoard();
    void letCPUBegin();
    
private slots:

    void on_infoButton_clicked();

    void on_stopButton_clicked();

    void on_startGameButton_clicked();

private:
    Ui::Dialog *ui;
    QGraphicsView *view;
    Board *board;
    Game *game;
};

#endif // DIALOG_H
