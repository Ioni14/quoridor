#include "GameState.h"

#include <iostream>
#include <sstream>
#include <string>

GameState::GameState(Quoridor& app, std::list<Player> players, const int& boardSize) :
    State(app),
    m_board(boardSize),
    m_players(std::move(players)),
    m_nbPlayers(m_players.size()),
    m_nbWallsAtStart((boardSize + 1) / (m_nbPlayers / 2)),
    m_loadingRendered(false)
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
    if (!m_loadingRendered) {
        m_loadingRendered = true;
        std::cout << "Lancement de la partie..." << std::endl;
        return;
    }

    std::ostringstream oss;

    auto size = m_board.getSize();
    auto cells = m_board.getCells();

    for (int j = 0; j < size; ++j) {
        std::ostringstream ossLine;
        for (int i = 0; i < size; ++i) {
            auto cell(cells[i][j]);

            // On affiche les murs (ou pas)
            if (cell.hasWallNorth() || cell.hasWallWest() ||
                (j - 1 >= 0 && cells[i][j-1].hasWallWest()) ||
                (i - 1 >= 0 && cells[i-1][j].hasWallNorth())) {
                oss << "#";
            } else {
                oss << " ";
            }
            if (cell.hasWallNorth()) {
                oss << "#";
            } else {
                oss << " ";
            }
            if (cell.hasWallWest()) {
                ossLine << "#";
            } else {
                ossLine << " ";
            }

            // Contenu de la cellule
            if (cell.getPlayer() == nullptr) {
                ossLine << ' ';
            } else {
                ossLine << cell.getPlayer()->getNumero();
            }

            // Les derniers murs
            if (i == size - 1 && cell.hasWallEast()) {
                oss << "#";
                ossLine << "#";
            }
        }
        oss << std::endl << ossLine.str() << std::endl;
    }

    // Les TOUS derniers murs
    for (int i = 0; i < size; ++i) {
        auto cell(cells[i][size - 1]);
        if (cell.hasWallSouth()) {
            oss << "##";
        }
        if (i == size - 1 && cell.hasWallEast()) {
            oss << "#";
        }
    }

    std::cout << oss.str() << std::endl;
}

void GameState::update()
{
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
    int choice(0);
    std::cin >> choice;
}
