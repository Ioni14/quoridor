#ifndef STATE_H
#define STATE_H

/**
 * \file State.h
 * \brief Définition de la classe State
 * \author J. Keenens
 * \version 0.1
 * \date 07/03/2016
 */

#include <memory>
#include "Observable.h"

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

class Quoridor;

/**
 * \class State
 * \brief Classe représentant un état du jeu (menu, en jeu...)
 */
class State : public Observable
{
public:
    typedef std::unique_ptr<State> StatePtr;

public:
    /**
     * \brief Constructeur logique
     * \param app : Référence sur la classe principale du jeu
     */
    State(Quoridor& app);
    /**
     * \brief Destructeur généré par le compilateur
     */
    virtual ~State() = default;

    /**
     * \brief Procède à l'affichage du jeu
     */
    virtual void render() = 0;
    /**
     * \brief Procède à la mise-à-jour du modèle du jeu
     */
    virtual void update() = 0;
    /**
     * \brief Procède à lecture des entrées utilisateurs
     */
    virtual void handleEvents() = 0;

    /**
     * \brief Avertit les observateurs d'une mise-à-jour de l'état du jeu
     */
    void notifyObservers();

    /**
     * \brief Lit l'entrée standard
     * \return Le nombre entier écrit sinon -1
     */
    static int promptInteger();

    /**
     * \brief Avertit les observateurs que l'état a été activé par le gestionnaire
     */
    void fireActivated();

protected:
    Quoridor& m_app; /**< Référence sur la classe principale du jeu */
};

}

#endif // STATE_H
