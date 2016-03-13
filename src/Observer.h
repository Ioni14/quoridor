#ifndef OBSERVER_H
#define OBSERVER_H

/**
 * \file Observer.h
 * \brief Définition de la classe Observer
 * \author J. Keenens
 * \version 0.2
 * \date 13/03/2016
 */

#include <memory>
#include <list>
#include "Player.h"
#include "Board.h"

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

class Observable;

/**
 * \class Observer
 * \brief Représente un observateur qui a besoin d'être averti lorsqu'un observable est modifié
 */
class Observer
{
public:
    typedef std::shared_ptr<Observer> ObserverPtr;

public:
    /**
     * \brief Destructeur généré par le compilateur
     */
    virtual ~Observer() = default;

    /**
     * \brief Appelé lorsque l'observateur a été activé par la classe principale Quoridor
     */
    virtual void onActivated() = 0;

    /**
     * \brief Appelé lorsque les joueurs ont été créés et positionnés sur leur case de départ
     * \param players : les joueurs initialisés
     */
    virtual void onPlayersInitialized(const std::list<Player>& players) = 0;
    /**
     * \brief Appelé lorsque qu'un joueur s'est déplacé sur le plateau
     * \param player : le joueur concerné
     */
    virtual void onPlayerMove(const Player& player) = 0;

    /**
     * \brief Appelé lorsque qu'un mur a été construit sur le plateau
     * \param i : la colonne du mur
     * \param j : la ligne du mur
     * \param orientation : l'orientation du mur
     */
    virtual void onPutWall(const int& i, const int& j, const Board::WALL_ORIENTATION& orientation) = 0;

    /**
     * \brief Appelé lorsqu'un joueur a gagné la partie
     * \param player : le joueur concerné
     */
    virtual void onPlayerWon(const Player& player) = 0;
};

}

#endif // OBSERVER_H
