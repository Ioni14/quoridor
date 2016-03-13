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

    /**
     * \brief Récupère le type du mur nord
     * \return le type du mur nord
     */
    const WALL_POSITION& getWallNorth() const;
    /**
     * \brief Indique si la case a un mur nord
     * \return true si la case a un mur nord
     */
    bool hasWallNorth() const;
    /**
     * \brief Affecte un nouveau type au mur nord
     * \param val : le nouveau type
     */
    void setWallNorth(const WALL_POSITION& val);

    /**
     * \brief Récupère le type du mur sud
     * \return le type du mur sud
     */
    const WALL_POSITION& getWallSouth() const;
    /**
     * \brief Indique si la case a un mur sud
     * \return true si la case a un mur sud
     */
    bool hasWallSouth() const;
    /**
     * \brief Affecte un nouveau type au mur sud
     * \param val : le nouveau type
     */
    void setWallSouth(const WALL_POSITION& val);

    /**
     * \brief Récupère le type du mur est
     * \return le type du mur est
     */
    const WALL_POSITION& getWallEast() const;
    /**
     * \brief Indique si la case a un mur est
     * \return true si la case a un mur est
     */
    bool hasWallEast() const;
    /**
     * \brief Affecte un nouveau type au mur est
     * \param val : le nouveau type
     */
    void setWallEast(const WALL_POSITION& val);

    /**
     * \brief Récupère le type du mur ouest
     * \return le type du mur ouest
     */
    const WALL_POSITION& getWallWest() const;
    /**
     * \brief Indique si la case a un mur ouest
     * \return true si la case a un mur ouest
     */
    bool hasWallWest() const;
    /**
     * \brief Affecte un nouveau type au mur ouest
     * \param val : le nouveau type
     */
    void setWallWest(const WALL_POSITION& val);

    /**
     * \brief Récupère le joueur qui se trouve sur la case
     * \return le joueur ou nullptr s'il n'y a personne
     */
    const Player* getPlayer() const;
    /**
     * \brief Indique s'il y a un joueur sur la case
     * \return true s'il y a un joueur
     */
    bool hasPlayer() const;
    /**
     * \brief Affecte un joueur sur la case
     * \param player : le joueur qui doit se trouver sur la case
     */
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
