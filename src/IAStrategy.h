#ifndef IASTRATEGY_H
#define IASTRATEGY_H

/**
 * \file IAStrategy.h
 * \brief Définition de la classe IAStrategy
 * \author J. Keenens
 * \version 0.1
 * \date 20/04/2016
 */

#include <memory>
#include <list>
#include <vector>

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

class Board;
class Player;

struct IAResponse
{
    enum class Type { MOVE, WALL };
    enum class WallOrientation { VERTICAL, HORIZONTAL };

    int score;
    Type type;
    int bestI;
    int bestJ;
    WallOrientation orientation;
};

/**
 * \class IAStrategy
 * \brief Représente une stratégie d'IA
 */
class IAStrategy
{
public:
    typedef std::unique_ptr<IAStrategy> IAStrategyPtr;

public:
    /**
     * Destructeur généré par le compilateur
     */
    virtual ~IAStrategy() = default;

    /**
     * \brief Cherche la meilleure action possible pour le joueur IA et l'exécute
     */
    virtual IAResponse moveOrPutWall(Board& board, int playerActual, std::list<Player>& players) = 0;
};

}

#endif // IASTRATEGY_H
