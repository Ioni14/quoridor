TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Board.cpp \
    Player.cpp \
    BoardCell.cpp \
    AbstractPathfinding.cpp \
    PathfindingAStar.cpp \
    PathfindingAStarCell.cpp \
    Quoridor.cpp \
    State.cpp \
    MainMenuState.cpp \
    QuitState.cpp \
    GameState.cpp

HEADERS += \
    Board.h \
    Player.h \
    BoardCell.h \
    AbstractPathfinding.h \
    PathfindingAStar.h \
    PathfindingAStarCell.h \
    Quoridor.h \
    State.h \
    MainMenuState.h \
    QuitState.h \
    GameState.h
