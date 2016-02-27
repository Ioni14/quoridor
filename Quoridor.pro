TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Game.cpp \
    Board.cpp \
    Player.cpp \
    BoardCell.cpp

HEADERS += \
    Game.h \
    Board.h \
    Player.h \
    BoardCell.h
