#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{   
    ui->setupUi(this);

    board = new Board(this);
    ui->graphicsView->setScene(board);

    resize(530,550);
}

Dialog::~Dialog()
{
    delete ui;
    delete view;
    delete board;
}

void Dialog::on_infoButton_clicked()
{
    QMessageBox::information(this, "Informacje o grze",
                             "Gomoku v1.0\n"
                             "Autor: Paulina Wolak\n"
                             "Projekt wykonany w ramach kursu Metody Sztucznej Inteligencji");
}
