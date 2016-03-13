#ifndef GAME_HPP
#define GAME_HPP

/**
 * \file GameState.h
 * \brief Définition de la classe GameState
 * \author J. Keenens
 * \version 0.1
 * \date 07/03/2016
 */

#include <list>
#include <algorithm>
#include <cassert>
#include <map>
#include <sstream>
#include "State.h"
#include "Board.h"

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

/**
 * \class GameState
 * \brief Représente l'état du jeu en cours de partie
 */
class GameState : public State
{
public:
    /**
     * \brief Constructeur logique
     * \param app : référence sur la classe principale du jeu
     * \param players : la liste des joueurs
     * \param boardSize : la taille du plateau
     */
    GameState(Quoridor& app, std::list<Player> players, const int &boardSize);

    const Board& getBoard() const {
        return m_board;
    }
    Player& getPlayerActual() {
        auto itPlayer = std::find_if(m_players.begin(), m_players.end(),
            [this](const Player& player) -> bool {
                return m_playerActual == player.getNumero();
            }
        );
        assert(itPlayer != m_players.end());
        return *itPlayer;
    }
    const std::list<Player>& getPlayers() const {
        return m_players;
    }

    void firePlayersInitialized(const std::list<Player>& players);
    void firePlayerMove(const Player& player);
    void firePutWall(const int& i, const int& j, const Board::WALL_ORIENTATION& orientation);
    void firePlayerWon(const Player& player);

    void initPlayers();

    void movePlayer(Player& player, const int& di, const int& dj);
    bool putWall(Player& player, const int& i, const int& j, const Board::WALL_ORIENTATION& orientation);
    bool canPutWall(Player& player, const int &i, const int &j, const Board::WALL_ORIENTATION &orientation);
    void nextPlayer();

private:
    bool hasWon(const Player& player) const;
    void finishGame();

private:
    Board m_board;
    std::list<Player> m_players;
    int m_nbPlayers;
    int m_nbWallsAtStart;
    int m_playerActual;
};

}

#endif // GAME_HPP
