#include "GameState.h"

#include <iostream>

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
    m_error(""),
    m_loadingEnded(false),
    m_waitingChoiceAction(false),
    m_waitingChoiceMove(false),
    m_waitingChoiceWallCol(false),
    m_waitingChoiceWallRow(false),
    m_waitingChoiceWallDir(false)
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

    /*
    m_board.putWall(m_players, *(m_players.begin()), 5, 4, Board::WALL_ORIENTATION::VERTICAL);
    m_board.putWall(m_players, *(m_players.begin()), 5, 6, Board::WALL_ORIENTATION::HORIZONTAL);

    for (auto it = m_players.begin(); it != m_players.end(); ++it) {
        it->move(m_board, 1, 0);
    }
    */
}

void GameState::handleEvents()
{
    if (m_waitingChoiceAction) {
        m_waitingChoiceAction = false;
        int choice(0);
        std::cin >> choice;
        switch (choice) {
            case 1:
                m_subState = SUB_STATE::MOVE;
                break;
            case 2:
                if (!getPlayerActual().hasWalls()) {
                    m_error = "Vous n'avez plus de mur.";
                } else {
                    m_subState = SUB_STATE::WALL_COL;
                }
                break;
            default:
                m_error = "Veuillez taper 1, 2 ou 3.";
        }
    } else if (m_waitingChoiceWallCol) {
        m_waitingChoiceWallCol = false;
        int choice(0);
        std::cin >> choice;
        if (choice < 1 || choice > m_board.getSize()) {
            m_error = "Vous devez indiquer une colonne comprise entre 1 et " + m_board.getSize();
        } else {
            m_wallCol = choice - 1;
            m_subState = SUB_STATE::WALL_ROW;
        }
    } else if (m_waitingChoiceWallRow) {
        m_waitingChoiceWallRow = false;
        int choice(0);
        std::cin >> choice;
        if (choice < 1 || choice > m_board.getSize()) {
            m_error = "Vous devez indiquer une ligne comprise entre 1 et " + m_board.getSize();
        } else {
            m_wallRow = choice - 1;
            m_subState = SUB_STATE::WALL_DIR;
        }
    } else if (m_waitingChoiceWallDir) {
        m_waitingChoiceWallDir = false;
        int choice(0);
        std::cin >> choice;
        switch (choice) {
            case 1:
                m_wallDir = Board::WALL_ORIENTATION::VERTICAL;
                break;
            case 2:
                m_wallDir = Board::WALL_ORIENTATION::HORIZONTAL;
                break;
            default:
                m_error = "Veuillez taper 1 ou 2.";
        }
        if (choice == 1 || choice == 2) {
            auto isPut = m_board.putWall(m_players, getPlayerActual(), m_wallCol, m_wallRow, m_wallDir);
            if (isPut) {
                m_playerActual = m_playerActual % m_nbPlayers + 1;
            } else {
                m_error = "Ce mur ne peut etre positionne a cet endroit.";
            }
            m_subState = SUB_STATE::ACTION;
        }
    }
}
