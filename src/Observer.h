#ifndef OBSERVER_H
#define OBSERVER_H

/**
 * \file Observer.h
 * \brief Définition de la classe Observer
 * \author J. Keenens
 * \version 0.1
 * \date 07/03/2016
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
     * \brief Appelée lorsque les observables observés sont modifiés
     */
    virtual void onNotify() = 0;
    virtual void onActivated() = 0;

    virtual void onPlayersInitialized(const std::list<Player>& players) = 0;
    virtual void onPlayerMove(const Player& player) = 0;
    virtual void onPutWall(const int& i, const int& j, const Board::WALL_ORIENTATION& orientation) = 0;
    virtual void onPlayerWon(const Player& player) = 0;
};

}

#endif // OBSERVER_H
