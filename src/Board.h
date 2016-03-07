#ifndef BOARD_H
#define BOARD_H

/**
 * \file Board.h
 * \brief Définition de la classe Board
 * \author J. Keenens
 * \version 0.1
 * \date 07/03/2016
 */

#include <vector>
#include <memory>
#include <list>
#include "AbstractPathfinding.h"
#include "BoardCell.h"

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

/**
 * \class Board
 * \brief Représente le plateau de jeu
 */
class Board
{
public:
    enum class WALL_ORIENTATION {
        VERTICAL, /**< Mur vertical */
        HORIZONTAL /**< Mur horizontal */
    };

    typedef std::unique_ptr<AbstractPathfinding> PathfindingPtr;

public:
    /**
     * \brief Constructeur logique
     * \param size : la taille du plateau
     */
    Board(const int& size);

    std::vector<std::vector<BoardCell>>& getCells();
    const std::vector<std::vector<BoardCell>>& getCells() const;
    /**
     * \brief Construit un mur à l'emplacement indiqué par le joueur indiqué
     * \param players : la liste des joueurs
     * \param player : le joueur qui veut mettre le mur
     * \param i : la colonne de la cellule visée
     * \param j : la ligne de la cellule visée
     * \param orientation : l'orientation du mur (vertical, horizontal)
     * \return true si le mur a été construit
     */
    bool putWall(const std::list<Player> &players, Player& player, const int& i, const int& j, const WALL_ORIENTATION& orientation);
    /**
     * \brief Indique si le joueur indiqué peut mettre un mur à l'emplacement indiqué
     * \param player : le joueur qui veut mettre le mur
     * \param i : la colonne de la cellule visée
     * \param j : la ligne de la cellule visée
     * \param orientation : l'orientation du mur (vertical, horizontal)
     * \return true si le mur peut être construit
     */
    bool canPutWall(const Player& player, const int& i, const int& j, const WALL_ORIENTATION& orientation) const;
    /**
     * \brief Indique si tous les joueurs ont un chemin jusqu'à leur arrivée
     * \param players : la liste des joueurs
     * \return true si tous les joueurs ont un chemin
     */
    bool havePaths(const std::list<Player> &players) const;

    const int& getSize() const {
        return m_size;
    }

    /**
     * \brief Change de stratégie de recherche du plus court chemin
     * \param strategy : la nouvelle stratégie
     */
    void setPathfindingStrategy(PathfindingPtr strategy) {
        m_pathfindingStrategy = std::move(strategy);
    }

private:
    void create();
    /**
     * \brief Ajoute les murs aux bords du plateau
     * \param i : La colonne de la cellule à traiter
     * \param j : La ligne de la cellule à traiter
     */
    void putBorderWalls(const int& i, const int& j);

private:
    std::vector<std::vector<BoardCell>> m_cells; /**< Les cellules du plateau */

    int m_size; /**< La taille du plateau */

    PathfindingPtr m_pathfindingStrategy; /**< la stratégie de pathfinding utilisée */
};

}

#endif // BOARD_H
