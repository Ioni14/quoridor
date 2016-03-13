#ifndef PLAYER_H
#define PLAYER_H

/**
 * \file Player.h
 * \brief Définition de la classe Player
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
 * \class Player
 * \brief Représente un joueur dans le jeu
 */
class Player
{
public:
    /**
     * \brief Constructeur par défaut
     */
    Player();
    /**
     * \brief Constructeur logique
     * \param numero : l'identification du joueur
     * \param ia : true si le joueur est une IA (par défaut : false)
     */
    Player(const int& numero, const bool &ia = false);

    /**
     * \brief Bouge le joueur sur le plateau
     * \param board : le plateau du jeu
     * \param di : le nombre de colonne à traverser
     * \param dj : le nombre de ligne à traverser
     */
    void move(Board& board, const int &di, const int &dj);
    /**
     * \brief Indique si le joueur peut aller sur une certaine cellule du plateau
     * \param board : le plateau du jeu
     * \param di : le nombre de colonne à traverser
     * \param dj : le nombre de ligne à traverser
     * \return true si le joueur peut aller sur la cellule
     */
    bool canMove(const Board& board, const int& di, const int& dj) const;

    /**
     * \brief Récupère l'identification du joueur
     * \return l'identification du joueur
     */
    const int& getNumero() const {
        return m_numero;
    }

    /**
     * \brief Récupère la colonne du joueur
     * \return la colonne du joueur
     */
    const int& getIPos() const {
        return m_iPos;
    }
    /**
     * \brief Affecte la colonne du joueur
     * \param i : la nouvelle colonne du joueur
     */
    void setIPos(const int& i) {
        m_iPos = i;
    }

    /**
     * \brief Récupère la ligne du joueur
     * \return la ligne du joueur
     */
    const int& getJPos() const {
        return m_jPos;
    }
    /**
     * \brief Affecte la ligne du joueur
     * \param j : la nouvelle ligne du joueur
     */
    void setJPos(const int& j) {
        m_jPos = j;
    }
    /**
     * \brief Indique si le joueur est une IA ou non
     * \return true si le joueur est une IA
     */
    const bool& isIA() const {
        return m_IA;
    }

    /**
     * \brief Indique si le joueur a encore des murs ou non
     * \return true si le joueur a au moins un mur
     */
    bool hasWalls() const {
        return m_nbWalls > 0;
    }
    /**
     * \brief Récupère le nombre de murs que possède le joueur
     * \return le nombre de mur
     */
    const int& getNbWalls() const {
        return m_nbWalls;
    }
    /**
     * \brief Affecte un nombre de mur au joueur
     * \param walls : le nombre de murs à donner au joueur
     */
    void setWalls(const int& walls) {
        if (walls < 0) {
            m_nbWalls = 0;
            return;
        }
        m_nbWalls = walls;
    }
    /**
     * \brief Enlève un mur au joueur
     */
    void decrementWalls() {
        m_nbWalls--;
        if (m_nbWalls < 0) {
            m_nbWalls = 0;
        }
    }

private:
    int m_iPos; /**< La colonne où se trouve le joueur */
    int m_jPos; /**< La ligne où se trouve le joueur */

    int m_numero; /**< L'identification du joueur */
    int m_nbWalls; /**< Le nombre de murs que le joueur possède */

    bool m_IA; /**< Flag pour le type de joueur (IA ou non) */
};

}

#endif // PLAYER_H
