#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QMetaType>

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
    
private slots:

    void on_infoButton_clicked();

private:
    Ui::Dialog *ui;
    QGraphicsView *view;
    Board *board;
};

#endif // DIALOG_H
