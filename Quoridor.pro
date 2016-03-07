TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    src/AbstractPathfinding.h \
    src/Board.h \
    src/BoardCell.h \
    src/GameState.h \
    src/GameView.h \
    src/MainMenuState.h \
    src/MainMenuView.h \
    src/Observable.h \
    src/Observer.h \
    src/PathfindingAStar.h \
    src/PathfindingAStarCell.h \
    src/Player.h \
    src/QuitState.h \
    src/Quoridor.h \
    src/State.h \
    src/View.h

SOURCES += \
    src/AbstractPathfinding.cpp \
    src/Board.cpp \
    src/BoardCell.cpp \
    src/GameState.cpp \
    src/GameView.cpp \
    src/main.cpp \
    src/MainMenuState.cpp \
    src/MainMenuView.cpp \
    src/Observable.cpp \
    src/PathfindingAStar.cpp \
    src/PathfindingAStarCell.cpp \
    src/Player.cpp \
    src/QuitState.cpp \
    src/Quoridor.cpp \
    src/State.cpp \
    src/View.cpp
