#ifndef QUITSTATE_H
#define QUITSTATE_H

/**
 * \file QuitState.h
 * \brief Définition de la classe QuitState
 * \author J. Keenens
 * \version 0.1
 * \date 07/03/2016
 */

#include "State.h"

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

/**
 * \class QuitState
 * \brief Représente l'état de jeu "Quitter"
 * Permet au jeu de quitter proprement
 */
class QuitState : public State
{
public:
    /**
     * \brief Constructeur logique
     * \param app : Référence de la classe principale du jeu
     */
    QuitState(Quoridor& app);

    void render();
    void update();
    void handleEvents();
};

}

#endif // QUITSTATE_H
