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
    enum class SUB_STATE {TITLE, MENU, PLAY, PLAYERS, BOARD_SIZE, SUMMARY};

public:
    /**
     * \brief Constructeur logique
     * \param app : Référence sur la classe principale du jeu
     */
    MainMenuState(Quoridor& app);

    void render();
    void update();
    void handleEvents();

    /**
     * \brief Traite le choix utilisateur sur le menu principal
     */
    void makeChoiceMenu();
    /**
     * \brief Traite le choix utilisateur sur le nombre de joueur
     */
    void makeChoicePlay();
    /**
     * \brief Traite le choix utilisateur sur le type de chaque joueur
     */
    void makeChoicePlayers();
    /**
     * \brief Traite le choix utilisateur sur la taille du plateau
     */
    void makeChoiceBoardSize();
    /**
     * \brief Traite le choix utilisateur sur le résumé de la config
     */
    void makeChoiceSummary();

    /**
     * \brief Retourne l'erreur que l'utilisateur a provoquée
     * \return le message d'erreur
     */
    std::string getError() const {
        return m_error.str();
    }
    /**
     * \brief Retourne le sous-menu actuel
     * \return le sous-menu
     */
    const SUB_STATE& getSubState() const {
        return m_subState;
    }
    /**
     * \brief Affecte le flag pour l'affichage du titre du jeu
     * \param val : true si le titre a été affiché
     */
    void setTitleEnded(const bool& val) {
        m_titleEnded = val;
    }
    /**
     * \brief Affecte le flag du choix pour le menu principal
     * \param val : true si le choix est en attente
     */
    void setWaitingChoiceMenu(const bool& val) {
        m_waitingChoiceMenu = val;
    }
    /**
     * \brief Affecte le flag du choix pour le nombre de joueur
     * \param val : true si le choix est en attente
     */
    void setWaitingChoicePlay(const bool& val) {
        m_waitingChoicePlay = val;
    }
    /**
     * \brief Affecte le flag du choix pour le type de chaque joueur
     * \param val : true si le choix est en attente
     */
    void setWaitingChoicePlayers(const bool& val) {
        m_waitingChoicePlayers = val;
    }
    /**
     * \brief Affecte le flag du choix pour la taille du plateau
     * \param val : true si le choix est en attente
     */
    void setWaitingChoiceBoardSize(const bool& val) {
        m_waitingChoiceBoardSize = val;
    }
    /**
     * \brief Affecte le flag du choix pour le résumé de la config
     * \param val : true si le choix est en attente
     */
    void setWaitingChoiceSummary(const bool& val) {
        m_waitingChoiceSummary = val;
    }

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
    void launchGame();

private:
    SUB_STATE m_subState; /**< Sous-menu en cours */

    std::ostringstream m_error; /**< Message d'erreur */
    bool m_titleEnded; /**< Flag indiquant si le titre a été affiché */
    bool m_waitingChoiceMenu; /**< Flag en attente du choix utilisateur pour le menu principal */
    bool m_waitingChoicePlay; /**< Flag en attente du choix utilisateur pour le nombre de joueurs */
    bool m_waitingChoicePlayers; /**< Flag en attente du choix utilisateur pour le type des joueurs */
    bool m_waitingChoiceBoardSize; /**< Flag en attente du choix utilisateur pour la taille du plateau */
    bool m_waitingChoiceSummary; /**< Flag en attente du choix utilisateur pour le résumé de la config */

    int m_nbPlayers; /**< Le nombre de joueurs */
    int m_boardSize; /**< La taille du plateau */
    int m_playerActual; /**< L'identification du joueur en train d'être configuré */

    std::list<Player> m_players; /**< La liste des joueurs qui joueront la partie */
};

}

#endif // MAINMENUSTATE_H
