TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Game.cpp \
    Board.cpp \
    Player.cpp \
    BoardCell.cpp \
    AbstractPathfinding.cpp \
    PathfindingAStar.cpp \
    PathfindingAStarCell.cpp \
    Quoridor.cpp \
    State.cpp \
    MainMenuState.cpp \
    QuitState.cpp

HEADERS += \
    Game.h \
    Board.h \
    Player.h \
    BoardCell.h \
    AbstractPathfinding.h \
    PathfindingAStar.h \
    PathfindingAStarCell.h \
    Quoridor.h \
    State.h \
    MainMenuState.h \
    QuitState.h
