#ifndef PATHFINDINGASTARCELL_H
#define PATHFINDINGASTARCELL_H

/**
 * \file PathfindingAStarCell.h
 * \brief Définition de la classe PathfindingAStarCell
 * \author J. Keenens
 * \version 0.1
 * \date 07/03/2016
 */

#include <memory>
#include "BoardCell.h"

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

/**
 * \class PathfindingAStarCell
 * \brief Représente une cellule parcourue par l'algorithme A*
 */
class PathfindingAStarCell
{
public:
    typedef std::unique_ptr<PathfindingAStarCell> AStarCellPtr;

public:
    /**
     * \brief Constructeur logique
     * \param heuristic : le coût heuristique
     * \param boardCell : le plateau du jeu
     */
    PathfindingAStarCell(const int& heuristic, const BoardCell& boardCell);
    /**
     * \brief Constructeur logique
     * \param costMovement : le coût de déplacement
     * \param heuristic : le coût heuristique
     * \param parent : le parent
     * \param boardCell : le plateau du jeu
     */
    PathfindingAStarCell(const int& costMovement, const int& heuristic, const AStarCellPtr* parent, const BoardCell& boardCell);

    /**
     * \brief Calcule le score de la cellule
     * \return le score
     */
    int calcScore() const {
        return m_costMovement + m_heuristic;
    }
    /**
     * \brief Récupère le coût de déplacement de la cellule
     * \return le coût de déplacement
     */
    const int& getCostMovement() const {
        return m_costMovement;
    }
    /**
     * \brief Affecte le coût de déplacement de la cellule
     * \param costMovement : le coût de déplacement
     */
    void setCostMovement(const int& costMovement) {
        m_costMovement = costMovement;
    }

    /**
     * \brief Affecte le coût heuristique de la cellule
     * \param heuristic : le coût heuristique
     */
    void setHeuristic(const int& heuristic) {
        m_heuristic = heuristic;
    }

    /**
     * \brief Affecte la cellule parente
     * \param parent : le nouveau parent
     */
    void setParent(const AStarCellPtr* parent) {
        m_parent = parent;
    }

    /**
     * \brief Récupère la cellule du plateau
     * \return la cellule du plateau
     */
    const BoardCell& getBoardCell() const {
        return m_boardCell;
    }

private:
    int m_costMovement; /**< Coût de déplacement entre la cellule et le départ */
    int m_heuristic; /**< Coût heuristique entre la cellule et l'arrivée */

    const AStarCellPtr* m_parent; /**< La cellule qui permet d'atteindre celle-ci dans le plus court chemin */
    const BoardCell& m_boardCell; /**< La cellule du plateau que surcouche celle-ci */
};

}

#endif // PATHFINDINGASTARCELL_H
