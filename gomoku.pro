#-------------------------------------------------
#
# Project created by QtCreator 2013-10-09T23:34:25
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
    game.h

FORMS    += dialog.ui
