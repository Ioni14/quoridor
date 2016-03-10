#include "MainWindow.h"

#include <QMessageBox>
#include <iostream>
#include "MainMenuState.h"

MainWindow::MainWindow(G36631::Quoridor &model, QWidget *parent) :
    QMainWindow(parent),
    m_boardView(nullptr),
    m_model(model)
{
    m_ui.setupUi(this);

    connect(m_ui.actionNouvelle_partie, SIGNAL(triggered(bool)),
            this, SLOT(newGame()));
    connect(m_ui.actionQuitter, SIGNAL(triggered(bool)),
            this, SLOT(close()));

    connect(m_ui.launchGameButton, SIGNAL(clicked(bool)),
            this, SLOT(launchGame()));
}

MainWindow::~MainWindow()
{
    if (m_boardView != nullptr) {
        delete m_boardView;
    }
}

void MainWindow::newGame()
{
    m_model.reset();
    /*
    auto& state = m_model.getState();
    state->addObserver(*this);
    */
}

void MainWindow::onNotify()
{
    std::cout << "Je suis notifié" << std::endl;
}

void MainWindow::launchGame()
{
    // On récupère les valeurs entrées

    int nbPlayers(0);
    if (m_ui.players2RadioButton->isChecked()) {
        nbPlayers = 2;
    } else if (m_ui.players4RadioButton->isChecked()) {
        nbPlayers = 4;
    } else {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Vous ne pouvez choisir que 2 ou 4 joueurs !");
        msgBox.exec();
        return;
    }

    auto& stateBase = *(m_model.getState());
    auto& state = dynamic_cast<G36631::MainMenuState&>(stateBase);

    if (m_ui.player1RealRadioButton->isChecked()) {
        // créer la méthode :
        state.addPlayer(1);
    } else {
        // créer la méthode :
        state.addPlayer(1, true);
    }
    if (m_ui.player2RealRadioButton->isChecked()) {
        // créer la méthode :
        state.addPlayer(2);
    } else {
        // créer la méthode :
        state.addPlayer(2, true);
    }
    if (nbPlayers == 4) {
        if (m_ui.player3RealRadioButton->isChecked()) {
            // créer la méthode :
            state.addPlayer(3);
        } else {
            // créer la méthode :
            state.addPlayer(3, true);
        }
        if (m_ui.player4RealRadioButton->isChecked()) {
            // créer la méthode :
            state.addPlayer(4);
        } else {
            // créer la méthode :
            state.addPlayer(4, true);
        }
    }

    int boardSize = static_cast<int>(m_ui.boardSizeInput->text().toUInt());
    if (boardSize < 5 || boardSize > 19 || boardSize%2 == 0) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Vous devez choisir une taille de plateau impaire comprise entre 5 et 19 !");
        msgBox.exec();
        return;
    }

    state.setBoardSize(boardSize);

    // Changement de state et de vue (on hide tout et on show le QGraphics)
    m_boardView = new BoardView(*this, m_ui.baseWidget);
    m_ui.baseLayout->addWidget(m_boardView);
    m_boardView->drawBoard(boardSize);
    m_boardView->show();
    m_ui.mainMenuWidget->hide();
    state.launchGame();
}
