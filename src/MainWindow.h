#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "ui_Quoridor.h"
#include "Quoridor.h"
#include "Observer.h"
#include "BoardView.h"

class MainWindow : public QMainWindow, public G36631::Observer
{
    Q_OBJECT
public:
    explicit MainWindow(G36631::Quoridor &model, QWidget *parent = 0);
    ~MainWindow();

    virtual void onNotify();
    virtual void onActivated();

    virtual void onPlayersInitialized(const std::list<G36631::Player>& players);
    virtual void onPlayerMove(const G36631::Player& player);
    virtual void onPutWall(const int& i, const int& j, const G36631::Board::WALL_ORIENTATION& orientation);
    virtual void onPlayerWon(const G36631::Player& player);

    G36631::Quoridor& getModel() {
        return m_model;
    }

signals:

public slots:
    void newGame();
    void launchGame();
    void about();
    void howToPlay();

private:
    void updateDashboard();

private:
    Ui::Quoridor m_ui;
    BoardView* m_boardView;

    G36631::Quoridor &m_model;

    QPixmap m_caretTexture;
};

#endif // MAINWINDOW_H
