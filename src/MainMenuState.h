#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

/**
 * \file MainMenuState.h
 * \brief Définition de la classe MainMenuState
 * \author J. Keenens
 * \version 0.1
 * \date 07/03/2016
 */

#include <list>
#include <sstream>
#include "Player.h"
#include "State.h"

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

/**
 * \class MainMenuState
 * \brief Représente l'état du menu du jeu
 */
class MainMenuState : public State
{
public:
    /**
     * \brief Constructeur logique
     * \param app : Référence sur la classe principale du jeu
     */
    MainMenuState(Quoridor& app);

    /**
     * \brief Retourne le nombre de joueur
     * \return le nombre de joueur
     */
    const int& getNbPlayers() const {
        return m_nbPlayers;
    }

    /**
     * \brief Affecte le nombre de joueurs du jeu
     * \param nbPlayers : le nombre de joueurs
     */
    void setNbPlayers(const int& nbPlayers) {
        m_nbPlayers = nbPlayers;
        if (m_nbPlayers < 0) {
            m_nbPlayers = 0;
        }
    }

    /**
     * \brief Retourne l'identification du joueur en train d'être configuré
     * \return l'identification du joueur
     */
    const int& getPlayerActual() const {
        return m_playerActual;
    }
    /**
     * \brief Retourne la liste des joueurs
     * \return la liste des joueurs
     */
    const std::list<Player>& getPlayers() const {
        return m_players;
    }
    /**
     * \brief Retourne la taille du plateau
     * \return la taille du plateau
     */
    const int& getBoardSize() const {
        return m_boardSize;
    }

    /**
     * \brief Affecte la nouvelle taille du plateau
     * \param boardSize : la nouvelle taille (côté)
     */
    void setBoardSize(const int& boardSize) {
        m_boardSize = boardSize;
    }

    /**
     * \brief Ajoute un joueur au jeu (qui sera utilisé lors du lancement de la partie)
     * \param numero : l'identification du joueur
     * \param ia : true si le joueur est une IA
     */
    void addPlayer(const int& numero, const bool& ia = false);

    /**
     * \brief Lance la partie (change de State)
     */
    void launchGame(Observer *observer = nullptr);

private:
    int m_nbPlayers; /**< Le nombre de joueurs */
    int m_boardSize; /**< La taille du plateau */
    int m_playerActual; /**< L'identification du joueur en train d'être configuré */

    std::list<Player> m_players; /**< La liste des joueurs qui joueront la partie */
};

}

#endif // MAINMENUSTATE_H
