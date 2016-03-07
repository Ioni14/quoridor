#ifndef PATHFINDINGASTAR_H
#define PATHFINDINGASTAR_H

/**
 * \file PathfindingAStar.h
 * \brief Définition de la classe PathfindingAStar
 * \author J. Keenens
 * \version 0.1
 * \date 07/03/2016
 */

#include <list>
#include <memory>
#include <vector>
#include "AbstractPathfinding.h"
#include "PathfindingAStarCell.h"

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

/**
 * \class PathfindingAStar
 * \brief Représente la stratégie de l'algorithme A*
 */
class PathfindingAStar : public AbstractPathfinding
{
public:
    typedef std::list<PathfindingAStarCell::AStarCellPtr> listCellPtr;

public:
    /**
     * \brief Constructeur logique
     * \param board : le plateau du jeu
     */
    PathfindingAStar(const Board& board);

    bool hasPath(const int& iSource, const int& jSource, const int& iDest, const int& jDest);

private:
    /**
     * \brief Cherche les cellules où le joueur peut aller en un déplacement à partir de la cellule donnée
     * \param cellActual : la cellule de référence du déplacement
     * \return un tableau des cellules atteignables
     */
    std::vector<const BoardCell*> findWalkableCells(const BoardCell& cellActual);
    /**
     * \brief Crée la cellule A* de départ à partir de ses coordonnées
     * \param iSource : la colonne de la cellule de départ
     * \param jSource : la ligne de la cellule de départ
     * \param iDest : la colonne de la cellule de fin
     * \param jDest : la ligne de la cellule de fin
     * \return la cellule A* de départ
     */
    PathfindingAStarCell::AStarCellPtr
    createStartCell(const int& iSource, const int& jSource, const int& iDest, const int& jDest);

    /**
     * \brief Cherche dans la "open list" la cellule ayant le plus petit score
     * \return un itérateur sur la cellule trouvée ou non
     */
    listCellPtr::iterator findLowestCell();
    /**
     * \brief Cherche dans la "open list" une cellule spécifique
     * \param i : la colonne de la cellule à trouver
     * \param j : la ligne de la cellule à trouver
     * \return un itérateur sur la cellule trouvée ou non
     */
    listCellPtr::iterator findCellInOpenList(const int& i, const int& j);
    /**
     * \brief Cherche dans la "close list" une cellule spécifique
     * \param i : la colonne de la cellule à trouver
     * \param j : la ligne de la cellule à trouver
     * \return un itérateur sur la cellule trouvée ou non
     */
    listCellPtr::reverse_iterator findCellInCloseList(const int& i, const int& j);

private:
    listCellPtr m_openList; /**< La "open list" de A* */
    listCellPtr m_closeList; /**< La "close list" de A* */

    static const int COST_MOVEMENT; /**< Le coût de déplacement entre deux cellules adjacentes */
};

}

#endif // PATHFINDINGASTAR_H
