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
signals:

public slots:
    void newGame();
    void launchGame();

private:
    Ui::Quoridor m_ui;
    BoardView* m_boardView;

    G36631::Quoridor &m_model;
};

#endif // MAINWINDOW_H
