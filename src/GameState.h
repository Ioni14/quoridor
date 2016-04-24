#ifndef GAME_HPP
#define GAME_HPP

/**
 * \file GameState.h
 * \brief Définition de la classe GameState
 * \author J. Keenens
 * \version 0.3
 * \date 13/03/2016
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

    /**
     * \brief Récupère le joueur qui doit jouer
     * \return le joueur actuel
     */
    Player& getPlayerActual();

    /**
     * \brief Récupère le plateau du jeu
     * \return le plateau du jeu
     */
    const Board& getBoard() const {
        return m_board;
    }

    /**
     * \brief Récupère les joueurs
     * \return la liste des joueurs
     */
    const std::list<Player>& getPlayers() const {
        return m_players;
    }

    /**
     * \brief Lance l'événement lorsque les joueurs ont été créés et initialisés
     * \param players : les joueurs affectés
     */
    void firePlayersInitialized(const std::list<Player>& players);
    /**
     * \brief Lance l'événement lorsqu'un joueur s'est déplacé
     * \param player : le joueur affecté
     */
    void firePlayerMove(const Player& player);
    /**
     * \brief Lance l'événement lorsqu'un joueur a posé un mur
     * Le mur est posé en bas à droite de la case
     * \param i : la colonne du mur
     * \param j : la ligne du mur
     * \param orientation : vertical ou horizontal
     */
    void firePutWall(const int& i, const int& j, const Board::WALL_ORIENTATION& orientation);
    /**
     * \brief Lance l'événement lorsqu'un joueur a gagné la partie
     * \param player : le joueur qui a gagné
     */
    void firePlayerWon(const Player& player);

    /**
     * \brief Initialise les joueurs (création et positionnement)
     * Lance l'événement firePlayersInitialized
     */
    void initPlayers();

    /**
     * \brief Déplace un joueur sur le plateau sans vérification
     * Lance l'événement firePlayerMove et firePlayerWon
     * \param player : le joueur concerné
     * \param di : le nombre de cases à parcourir horizontalement
     * \param dj : le nombre de cases à parcourir verticalement
     */
    void movePlayer(Player& player, const int& di, const int& dj);
    /**
     * \brief Pose un mur sur le plateau avec vérification
     * Le mur sera posé en bas à droite de la case cible
     * Lance l'événement firePutWall
     * \param player : le joueur qui pose le mur
     * \param i : la colonne cible
     * \param j : la ligne cible
     * \param orientation : vertical ou horizontal
     */
    void putWall(Player& player, const int& i, const int& j, const Board::WALL_ORIENTATION& orientation);
    /**
     * \brief Vérifie si un mur peut être posé à cet endroit et par ce joueur
     * \param player : le joueur concerné
     * \param i : la colonne cible
     * \param j : la ligne cible
     * \param orientation : vertical ou horizontal
     * \return true si le mur peut être posé
     */
    bool canPutWall(Player& player, const int &i, const int &j, const Board::WALL_ORIENTATION &orientation);

    /**
     * \brief Passe au joueur suivant
     */
    void nextPlayer();

    void executeIA();

private:
    /**
     * \brief Vérifie si un joueur a gagné la partie
     * \param player : le joueur concerné
     * \return true si le joueur a gagné
     */
    bool hasWon(const Player& player) const;

    /**
     * \brief Récupère le nombre de joueurs
     * \return le nombre de joueur
     */
    int getNbPlayers() const {
        return m_players.size();
    }

private:
    Board m_board; /**< Le plateau de jeu */
    std::list<Player> m_players; /**< Les joueurs */
    int m_nbWallsAtStart; /**< Le nombre de mur que chaque joueur recevra au départ */
    int m_playerActual; /**< L'identification du joueur actuel. 1 à 4 */
};

}

#endif // GAME_HPP
