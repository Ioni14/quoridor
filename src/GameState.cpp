#include "GameState.h"

#include <iostream>
#include "Quoridor.h"
#include "MainMenuState.h"

namespace G36631 {

GameState::GameState(Quoridor& app, std::list<Player> players, const int& boardSize) :
    State(app),
    m_board(boardSize),
    m_players(std::move(players)),
    m_nbPlayers(m_players.size()),
    m_nbWallsAtStart((boardSize + 1) / (m_nbPlayers / 2)),
    m_playerActual(1)
{
}

void GameState::firePlayersInitialized(const std::list<Player>& players)
{
    for (auto& observer : m_observers) {
        observer->onPlayersInitialized(players);
    }
}

void GameState::firePlayerMove(const Player& player)
{
    for (auto& observer : m_observers) {
        observer->onPlayerMove(player);
    }
}

void GameState::firePlayerWon(const Player& player)
{
    for (auto& observer : m_observers) {
        observer->onPlayerWon(player);
    }
}

void GameState::firePutWall(const int& i, const int& j, const Board::WALL_ORIENTATION& orientation)
{
    for (auto& observer : m_observers) {
        observer->onPutWall(i, j, orientation);
    }
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

    firePlayersInitialized(m_players);
}

void GameState::nextPlayer()
{
    m_playerActual = m_playerActual % m_nbPlayers + 1;
}

void GameState::finishGame()
{
    // La partie est finie : on revient sur le menu principal
    auto newState = std::make_unique<MainMenuState>(m_app);
    m_app.setState(std::move(newState));
    m_app.applyNewState();
}

bool GameState::hasWon(const Player& player) const
{
    return ((player.getNumero() == 1 && player.getJPos() == 0)
            || (player.getNumero() == 2 && player.getJPos() == m_board.getSize() - 1)
            || (player.getNumero() == 3 && player.getIPos() == 0)
            || (player.getNumero() == 4 && player.getIPos() == m_board.getSize() - 1));
}

void GameState::movePlayer(Player& player, const int& di, const int& dj)
{
    player.move(m_board, di, dj);
    firePlayerMove(player);

    // TODO : Match nul à check ici

    if (hasWon(player)) {
        firePlayerWon(player);
    }
}

bool GameState::canPutWall(Player& player, const int &i, const int &j, const Board::WALL_ORIENTATION &orientation)
{
    return m_board.canPutWall(m_players, player, i, j, orientation);
}

bool GameState::putWall(Player &player, const int &i, const int &j, const Board::WALL_ORIENTATION &orientation)
{
    if (m_board.putWall(m_players, player, i, j, orientation)) {
        firePutWall(i, j, orientation);
        return true;
    }
    return false;
}

}
