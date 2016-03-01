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
    notifyObservers();
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
