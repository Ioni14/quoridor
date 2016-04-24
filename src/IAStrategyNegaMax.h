#ifndef IASTRATEGYNEGAMAX_H
#define IASTRATEGYNEGAMAX_H

/**
 * \file IAStrategy.h
 * \brief Définition de la classe IAStrategy
 * \author J. Keenens
 * \version 0.1
 * \date 20/04/2016
 */

#include <ostream>
#include <sstream>
#include <random>
#include "IAStrategy.h"

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

/**
 * \class IAStrategyNegaMax
 * \brief Représente l'algorithme NegaMax avec élagage alpha-bêta
 */
class IAStrategyNegaMax : public IAStrategy
{
public:
    explicit IAStrategyNegaMax();

    virtual IAResponse moveOrPutWall(Board& board, int playerActual, std::list<Player>& players);

private:
    IAResponse minimaxValue(int depth, int playerIndex, int alpha, int beta);
    int evaluation(int random) const;

private:
    int m_depth;
    Player* m_playerActual;
    std::list<Player>* m_players;
    Board* m_board;
    std::vector<IAResponse> m_bestActions;

    std::mt19937 m_rand;

    std::ostringstream m_log;
    int m_nodeCount;
};

}

#endif // IASTRATEGYNEGAMAX_H
