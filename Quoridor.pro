TEMPLATE = app
QT += core widgets

CONFIG += console c++14
CONFIG -= app_bundle

HEADERS += \
    src/AbstractPathfinding.h \
    src/Board.h \
    src/BoardCell.h \
    src/GameState.h \
    src/MainMenuState.h \
    src/Observable.h \
    src/Observer.h \
    src/PathfindingAStar.h \
    src/PathfindingAStarCell.h \
    src/Player.h \
    src/Quoridor.h \
    src/State.h \
    src/View.h \
    src/MainWindow.h \
    src/BoardView.h

SOURCES += \
    src/AbstractPathfinding.cpp \
    src/Board.cpp \
    src/BoardCell.cpp \
    src/GameState.cpp \
    src/main.cpp \
    src/MainMenuState.cpp \
    src/Observable.cpp \
    src/PathfindingAStar.cpp \
    src/PathfindingAStarCell.cpp \
    src/Player.cpp \
    src/Quoridor.cpp \
    src/State.cpp \
    src/MainWindow.cpp \
    src/BoardView.cpp

FORMS += \
    Quoridor.ui

RESOURCES += \
    textures.qrc
