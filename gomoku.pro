#-------------------------------------------------
#
# Project created by QtCreator 20(DIAMETER/2)-10-09T23:34:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gomoku
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    board.cpp \
    game.cpp

HEADERS  += dialog.h \
    plansza.h \
    board.h \
    game.h \
    constants.h

FORMS    += dialog.ui
