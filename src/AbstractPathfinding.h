#ifndef ABSTRACTPATHFINDING_H
#define ABSTRACTPATHFINDING_H

/**
 * \file AbstractPathfinding.h
 * \brief Définition de la classe AbstractPathfinding
 * \author J. Keenens
 * \version 0.1
 * \date 07/03/2016
 */

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

class Board;

/**
 * \class AbstractPathfinding
 * \brief Représente une stratégie de recherche du plus court chemin
 */
class AbstractPathfinding
{
public:
    /**
     * \brief Constructeur logique
     * \param board : le plateau de jeu
     */
    AbstractPathfinding(const Board& board);
    /**
     * Destructeur généré par le compilateur
     */
    virtual ~AbstractPathfinding() = default;

    /**
     * \brief Indique s'il existe un chemin entre la cellule source et de destination
     * \param iSource : la colonne source
     * \param jSource : la ligne source
     * \param iDest : la colonne destination
     * \param jDest : la ligne destination
     * \return true s'il existe un chemin
     */
    virtual bool hasPath(const int& iSource,
                         const int& jSource,
                         const int& iDest,
                         const int& jDest) = 0;

protected:
    const Board& m_board; /**< Le plateau de jeu */
};

}

#endif // ABSTRACTPATHFINDING_H
