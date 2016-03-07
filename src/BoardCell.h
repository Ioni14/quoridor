#ifndef BOARDCELL_H
#define BOARDCELL_H

/**
 * \file BoardCell.h
 * \brief Définition de la classe BoardCell
 * \author J. Keenens
 * \version 0.1
 * \date 07/03/2016
 */

#include "Player.h"

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

/**
 * \class BoardCell
 * \brief Représente une cellule du plateau
 */
class BoardCell
{
public:
    enum class WALL_POSITION {
        NONE, /**< Aucun mur */
        UP_LEFT, /**< La partie du mur la plus proche du coin haut gauche du plateau */
        DOWN_RIGHT /**< La partie du mur la plus proche du coin bas droite du plateau */
    };

public:
    /**
     * \brief Constructeur par défaut
     */
    BoardCell();
    /**
     * \brief Constructeur logique
     * \param i : la colonne de la cellule
     * \param j : la ligne de la cellule
     */
    BoardCell(const int& i, const int& j);

    const WALL_POSITION& getWallNorth() const;
    bool hasWallNorth() const;
    void setWallNorth(const WALL_POSITION& val);

    const WALL_POSITION& getWallSouth() const;
    bool hasWallSouth() const;
    void setWallSouth(const WALL_POSITION& val);

    const WALL_POSITION& getWallEast() const;
    bool hasWallEast() const;
    void setWallEast(const WALL_POSITION& val);

    const WALL_POSITION& getWallWest() const;
    bool hasWallWest() const;
    void setWallWest(const WALL_POSITION& val);

    const Player* getPlayer() const;
    bool hasPlayer() const;
    void setPlayer(const Player* player);

    /**
     * \brief Récupère la colonne de la cellule
     * \return la colonne de la cellule
     */
    const int& getIPos() const;
    /**
     * \brief Récupère la ligne de la cellule
     * \return la ligne de la cellule
     */
    const int& getJPos() const;

private:
    WALL_POSITION m_wallNorth; /**< La position du mur nord */
    WALL_POSITION m_wallSouth; /**< La position du mur sud */
    WALL_POSITION m_wallEast; /**< La position du mur est */
    WALL_POSITION m_wallWest; /**< La position du mur ouest */

    int m_iPos; /**< La colonne de la cellule */
    int m_jPos; /**< La ligne de la cellule */

    const Player* m_player; /**< Le joueur qui se trouve sur la cellule */
};

}

#endif // BOARDCELL_H
