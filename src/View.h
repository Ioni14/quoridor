#ifndef VIEW_H
#define VIEW_H

/**
 * \file View.h
 * \brief Définition de la classe View
 * \author J. Keenens
 * \version 0.1
 * \date 07/03/2016
 */

#include "State.h"
#include "Observer.h"

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

/**
 * \class View
 * \brief Classe représentant une Vue du jeu
 */
class View : public Observer
{
public:
    typedef std::shared_ptr<View> ViewPtr;

public:
    /**
     * \brief Constructeur logique
     * Instancie une vue avec son modèle
     *
     * \param model : Le modèle que devra afficher la Vue
     */
    View(State& model);
    /**
     * \brief Destructeur généré par le compilateur
     */
    virtual ~View() = default;

    virtual void onNotify();
    /**
     * \brief Affichage du modèle
     */
    virtual void render() = 0;

    virtual void onPlayersInitialized(const std::list<Player>& players);

protected:
    State& m_model; /**< Le modèle que doit afficher la Vue */
};

}

#endif // VIEW_H
