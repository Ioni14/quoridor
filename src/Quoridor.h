#ifndef QUORIDOR_H
#define QUORIDOR_H

/**
 * \file Quoridor.h
 * \brief Définition de la classe Quoridor
 * \author J. Keenens
 * \version 0.1
 * \date 07/03/2016
 */

#include "State.h"
#include "MainMenuView.h"

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

/**
 * \class Quoridor
 * \brief Classe qui permet de lancer le jeu Quoridor
 */
class Quoridor
{
public:
    /**
     * \brief Constructeur par défaut
     */
    Quoridor();

    /**
     * \brief Lance la boucle événementielle du jeu
     */
    void run();
    /**
     * \brief Quitte le jeu
     */
    void quit();

    /**
     * \brief Prévois un changement d'état du jeu
     * \param newState : le prochain état
     */
    void setState(State::StatePtr newState);

    /**
     * \brief Récupère l'état du jeu actuel
     * \return l'état du jeu
     */
    State::StatePtr& getState();

    /**
     * \brief Change la vue actuelle du jeu
     * \param newView : la nouvelle vue
     */
    void setView(View::ViewPtr newView);

    /**
     * \brief Applique les changements du nouvel état
     */
    void applyNewState();

    /**
     * \brief Crée une nouvelle partie
     */
    void reset();

private:
    /**
     * \brief Initialise le jeu Quoridor
     */
    void initialize();

private:
    State::StatePtr m_state; /**< L'état courant du jeu (menu, en jeu...) */
    State::StatePtr m_newState; /**< Le prochain état du jeu */
    View::ViewPtr m_view; /**< La vue actuelle du jeu (affichage du menu...) */

    bool m_continue; /**< Flag qui permet l'exécution en continue du jeu */
};

}

#endif // QUORIDOR_H
