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
    enum class SUB_STATE {
        LOADING, /**< Chargement du jeu */
        ACTION, /**< Demande de l'action à effectuer pour le joueur */
        MOVE, /**< Demande du déplacement du joueur */
        WALL_COL, /**< Demande de la colonne du mur */
        WALL_ROW, /**< Demande de la ligne du mur */
        WALL_DIR, /**< Demande de la direction du mur */
        WIN, /**< Gagnant de la partie */
        DRAW /**< Partie nulle */
    };

public:
    /**
     * \brief Constructeur logique
     * \param app : référence sur la classe principale du jeu
     * \param players : la liste des joueurs
     * \param boardSize : la taille du plateau
     */
    GameState(Quoridor& app, std::list<Player> players, const int &boardSize);

    const SUB_STATE& getSubState() const {
        return m_subState;
    }
    std::string getError() const {
        return m_error.str();
    }
    void setWaitingChoiceEnded(const bool& val) {
        m_loadingEnded = val;
    }
    void setWaitingChoiceAction(const bool& val) {
        m_waitingChoiceAction = val;
    }
    void setWaitingChoiceMove(const bool& val) {
        m_waitingChoiceMove = val;
    }
    void setWaitingChoiceWallCol(const bool& val) {
        m_waitingChoiceWallCol = val;
    }
    void setWaitingChoiceWallRow(const bool& val) {
        m_waitingChoiceWallRow = val;
    }
    void setWaitingChoiceWallDir(const bool& val) {
        m_waitingChoiceWallDir = val;
    }
    void setWaitingChoiceWin(const bool& val) {
        m_waitingChoiceWin = val;
    }
    void setWaitingChoiceDraw(const bool& val) {
        m_waitingChoiceDraw = val;
    }

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
    void addMoveChoice(const int& num, std::vector<int> coords) {
        m_moveChoices.insert(std::make_pair(num, coords));
    }

    void firePlayersInitialized(const std::list<Player>& players);

    void initPlayers();

private:
    void render();
    void update();
    void handleEvents();

    bool hasWon(const Player& player) const;

    void makeChoiceAction();
    void makeChoiceMove();
    void makeChoiceWallCol();
    void makeChoiceWallRow();
    void makeChoiceWallDir();
    void finishGame();

private:
    SUB_STATE m_subState;

    Board m_board;
    std::list<Player> m_players;
    int m_nbPlayers;
    int m_nbWallsAtStart;
    int m_playerActual;
    int m_wallCol;
    int m_wallRow;
    Board::WALL_ORIENTATION m_wallDir;
    std::map<int, std::vector<int>> m_moveChoices; /**< Les choix possibles pour le déplacement du joueur actuel */

    std::ostringstream m_error;
    bool m_loadingEnded;
    bool m_waitingChoiceAction;
    bool m_waitingChoiceMove;
    bool m_waitingChoiceWallCol;
    bool m_waitingChoiceWallRow;
    bool m_waitingChoiceWallDir;
    bool m_waitingChoiceWin;
    bool m_waitingChoiceDraw;
};

}

#endif // GAME_HPP
