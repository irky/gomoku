#include "dialog.h"
#include "game.h"
#include "board.h"
#include <QApplication>
#include <QMetaType>
#include <QDebug>

Q_DECLARE_METATYPE(Game)
Q_DECLARE_METATYPE(Board)
int bla = qRegisterMetaType<Game>("Game");
int ble = qRegisterMetaType<Board>("Board");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}
