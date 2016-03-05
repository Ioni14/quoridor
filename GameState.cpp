#include "GameState.h"

#include <iostream>
#include "Quoridor.h"
#include "MainMenuState.h"
#include "MainMenuView.h"

GameState::GameState(Quoridor& app, std::list<Player> players, const int& boardSize) :
    State(app),
    m_subState(SUB_STATE::LOADING),
    m_board(boardSize),
    m_players(std::move(players)),
    m_nbPlayers(m_players.size()),
    m_nbWallsAtStart((boardSize + 1) / (m_nbPlayers / 2)),
    m_playerActual(1),
    m_wallCol(0),
    m_wallRow(0),
    m_wallDir(Board::WALL_ORIENTATION::VERTICAL),
    m_moveChoices(),
    m_error(),
    m_loadingEnded(false),
    m_waitingChoiceAction(false),
    m_waitingChoiceMove(false),
    m_waitingChoiceWallCol(false),
    m_waitingChoiceWallRow(false),
    m_waitingChoiceWallDir(false),
    m_waitingChoiceWin(false)
{
    initPlayers();
}

void GameState::initPlayers()
{
    auto size = m_board.getSize();

    for (auto& player : m_players) {
        // On lui donne ses murs
        player.setWalls(m_nbWallsAtStart);

        // On positionne le joueur selon son numéro
        int i(0), j(0);
        switch (player.getNumero()) {
            case 1:
            default:
                i = size / 2;
                j = size - 1;
                break;
            case 2:
                i = size / 2;
                j = 0;
                break;
            case 3:
                i = size - 1;
                j = size / 2;
                break;
            case 4:
                i = 0;
                j = size / 2;
                break;
        }
        player.setIPos(i);
        player.setJPos(j);
        m_board.getCells()[i][j].setPlayer(&player);
    }
}

void GameState::render()
{
    notifyObservers();
}

void GameState::update()
{
    if (m_loadingEnded) {
        m_loadingEnded = false;
        m_subState = SUB_STATE::ACTION;
    }
}

void GameState::makeChoiceAction()
{
    int choice = State::promptInteger();
    switch (choice) {
        case 1:
            m_subState = SUB_STATE::MOVE;
            m_moveChoices.clear();
            break;
        case 2:
            if (!getPlayerActual().hasWalls()) {
                m_error << "Vous n'avez plus de mur.";
            } else {
                m_subState = SUB_STATE::WALL_COL;
            }
            break;
        case -1:
        default:
            m_error << "Veuillez taper 1 ou 2.";
    }
}

void GameState::makeChoiceMove()
{
    int choice = State::promptInteger();
    if (choice == 0) {
        m_subState = SUB_STATE::ACTION;
    } else {
        auto itMoveChoice = m_moveChoices.find(choice);
        auto& playerActual = getPlayerActual();
        if (itMoveChoice == m_moveChoices.end()) {
            m_error << "Veuillez taper un nombre entre 0 et " << m_moveChoices.size() << " compris.";
        } else {
            playerActual.move(m_board, itMoveChoice->second[0], itMoveChoice->second[1]);
        }

        // Check si un joueur a gagné
        if (hasWon(playerActual)) {
            m_subState = SUB_STATE::WIN;
        } else {
            m_playerActual = m_playerActual % m_nbPlayers + 1;
            m_subState = SUB_STATE::ACTION;
        }
    }
}

void GameState::makeChoiceWallCol()
{
    int choice = State::promptInteger();
    if (choice < 1 || choice > m_board.getSize()) {
        m_error << "Vous devez indiquer une colonne comprise entre 1 et " << m_board.getSize();
    } else {
        m_wallCol = choice - 1;
        m_subState = SUB_STATE::WALL_ROW;
    }
}

void GameState::makeChoiceWallRow()
{
    int choice = State::promptInteger();
    if (choice < 1 || choice > m_board.getSize()) {
        m_error << "Vous devez indiquer une ligne comprise entre 1 et " << m_board.getSize();
    } else {
        m_wallRow = choice - 1;
        m_subState = SUB_STATE::WALL_DIR;
    }
}

void GameState::makeChoiceWallDir()
{
    int choice = State::promptInteger();
    switch (choice) {
        case 1:
            m_wallDir = Board::WALL_ORIENTATION::VERTICAL;
            break;
        case 2:
            m_wallDir = Board::WALL_ORIENTATION::HORIZONTAL;
            break;
        case -1:
        default:
            m_error << "Veuillez taper 1 ou 2.";
    }
    if (choice == 1 || choice == 2) {
        auto isPut = m_board.putWall(m_players, getPlayerActual(), m_wallCol, m_wallRow, m_wallDir);
        if (isPut) {
            m_playerActual = m_playerActual % m_nbPlayers + 1;
        } else {
            m_error << "Ce mur ne peut etre positionne a cet endroit.";
        }
        m_subState = SUB_STATE::ACTION;
    }
}

void GameState::makeChoiceWin()
{
    // La partie est finie : on revient sur le menu principal
    StatePtr newState = std::make_unique<MainMenuState>(m_app);
    View::ViewPtr newView = std::make_shared<MainMenuView>(*newState);
    newState->addObserver(newView);
    m_app.setState(std::move(newState));
    m_app.setView(newView);
    m_app.applyNewState();
}

void GameState::handleEvents()
{
    m_error.str(""); // On vide la précédente erreur
    if (m_waitingChoiceAction) {
        m_waitingChoiceAction = false;
        makeChoiceAction();
    } else if (m_waitingChoiceMove) {
        m_waitingChoiceMove = false;
        makeChoiceMove();
    } else if (m_waitingChoiceWallCol) {
        m_waitingChoiceWallCol = false;
        makeChoiceWallCol();
    } else if (m_waitingChoiceWallRow) {
        m_waitingChoiceWallRow = false;
        makeChoiceWallRow();
    } else if (m_waitingChoiceWallDir) {
        m_waitingChoiceWallDir = false;
        makeChoiceWallDir();
    } else if (m_waitingChoiceWin) {
        m_waitingChoiceWin = false;
        makeChoiceWin();
    }
}

bool GameState::hasWon(const Player& player) const
{
    return ((player.getNumero() == 1 && player.getJPos() == 0)
            || (player.getNumero() == 2 && player.getJPos() == m_board.getSize() - 1)
            || (player.getNumero() == 3 && player.getIPos() == m_board.getSize() - 1)
            || (player.getNumero() == 4 && player.getJPos() == 0));
}
