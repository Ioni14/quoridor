#include "MainWindow.h"

#include <QMessageBox>
#include <iostream>
#include "MainMenuState.h"
#include "GameState.h"

MainWindow::MainWindow(G36631::Quoridor &model, QWidget *parent) :
    QMainWindow(parent),
    m_boardView(nullptr),
    m_model(model)
{
    m_ui.setupUi(this);
    m_ui.gameWidget->hide();
    m_ui.player1ActualIcon->hide();
    m_ui.player2ActualIcon->hide();
    m_ui.player3ActualIcon->hide();
    m_ui.player4ActualIcon->hide();

    connect(m_ui.actionNouvelle_partie, SIGNAL(triggered(bool)),
            this, SLOT(newGame()));
    connect(m_ui.actionQuitter, SIGNAL(triggered(bool)),
            this, SLOT(close()));
    connect(m_ui.actionA_propos, SIGNAL(triggered(bool)),
            this, SLOT(about()));
    connect(m_ui.actionComment_jouer, SIGNAL(triggered(bool)),
            this, SLOT(howToPlay()));

    connect(m_ui.launchGameButton, SIGNAL(clicked(bool)),
            this, SLOT(launchGame()));
}

MainWindow::~MainWindow()
{
    if (m_boardView != nullptr) {
        delete m_boardView;
    }
}

void MainWindow::howToPlay()
{
    QString message;
    message += "But du jeu :\n";
    message += "Le premier joueur à atteindre le côté du plateau opposé à son départ gagne.\n\n";
    message += "Déroulement de la partie :\n";
    message += "Tour par tour, les joueurs devront, soit se déplacer de case en case,\n";
    message += "soit de poser un mur afin de ralentir les adversaires.\n\n";
    message += "Commandes :\n";
    message += "Clic gauche déplacera le pion du joueur actuel ou posera un mur.\n";
    message += "Clic droit ou Espace fera pivoter le mur de 90°.";
    QMessageBox::information(this, "Comment jouer ?", message);
}

void MainWindow::about()
{
    QString message;
    message += "Quoridor réalisé par J. Keenens\n\n";
    message += "Jeu de stratégie créé par Mirko Marchesi en 1997.";
    QMessageBox::information(this, "A propos", message);
}

void MainWindow::newGame()
{
    if (!m_ui.mainMenuWidget->isHidden()) {
        return;
    }
    m_model.reset();

    if (m_boardView != nullptr) {
        m_ui.gameGraphicsLayout->removeWidget(m_boardView);
        delete m_boardView;
        m_boardView = nullptr;
    }
    m_ui.gameWidget->hide();
    m_ui.mainMenuWidget->show();
}

void MainWindow::onNotify()
{
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
    m_boardView = new BoardView(*this, m_ui.gameGraphics);
    m_ui.gameGraphicsLayout->addWidget(m_boardView);
    m_boardView->drawBoard(boardSize);
    m_boardView->show();
    state.launchGame(this); // state n'est plus un MainMenuState
    m_ui.gridWidgetPlayers3_4->show();
    if (nbPlayers <= 2) {
        m_ui.gridWidgetPlayers3_4->hide();
    }
    m_ui.mainMenuWidget->hide();
    m_ui.gameWidget->show();
}

void MainWindow::onPlayersInitialized(const std::list<G36631::Player>& players)
{
    if (m_boardView == nullptr) {
        return;
    }
    m_boardView->createPlayersItems(players);
}

void MainWindow::onPlayerMove(const G36631::Player& player)
{
    if (m_boardView == nullptr) {
        return;
    }
    m_boardView->movePlayer(player);

    updateDashboard();
}

void MainWindow::onPutWall(const int& i, const int& j, const G36631::Board::WALL_ORIENTATION& orientation)
{
    if (m_boardView == nullptr) {
        return;
    }
    m_boardView->putWall(i, j, orientation);

    updateDashboard();
}

void MainWindow::onPlayerWon(const G36631::Player& player)
{
    if (m_boardView == nullptr) {
        return;
    }

    m_boardView->setDisabled(true);
    QString message;
    message += "Le joueur ";
    message += QString::number(player.getNumero());
    message += " gagne !";
    QMessageBox::information(this, "Partie terminée", message);
}

void MainWindow::onActivated()
{
    updateDashboard();
}

void MainWindow::updateDashboard()
{
    auto& stateBase = *(m_model.getState());
    auto& state = dynamic_cast<G36631::GameState&>(stateBase);

    // On met à jour le dashboard
    m_ui.player1ActualIcon->hide();
    m_ui.player2ActualIcon->hide();
    m_ui.player3ActualIcon->hide();
    m_ui.player4ActualIcon->hide();
    auto& playerActualNumero = state.getPlayerActual().getNumero();
    switch (playerActualNumero) {
        case 1:
            m_ui.player1ActualIcon->show();
            break;
        case 2:
            m_ui.player2ActualIcon->show();
            break;
        case 3:
            m_ui.player3ActualIcon->show();
            break;
        case 4:
            m_ui.player4ActualIcon->show();
            break;
    }

    auto& players = state.getPlayers();

    for (auto& player : players) {
        switch (player.getNumero()) {
            case 1:
                m_ui.player1NbWalls->setText(QString::number(player.getNbWalls()) + "x");
                break;
            case 2:
                m_ui.player2NbWalls->setText(QString::number(player.getNbWalls()) + "x");
                break;
            case 3:
                m_ui.player3NbWalls->setText(QString::number(player.getNbWalls()) + "x");
                break;
            case 4:
                m_ui.player4NbWalls->setText(QString::number(player.getNbWalls()) + "x");
                break;
        }
    }
}
