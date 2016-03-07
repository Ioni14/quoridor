#ifndef GAMEVIEW_H
#define GAMEVIEW_H

/**
 * \file GameView.h
 * \brief Définition de la classe GameView
 * \author J. Keenens
 * \version 0.1
 * \date 07/03/2016
 */

#include "View.h"
#include "GameState.h"

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

/**
 * \class GameView
 * \brief Représente l'affichage du jeu
 */
class GameView : public View
{
public:
    /**
     * \brief Constructeur logique
     * \param model : le modèle du jeu
     */
    GameView(GameState& model);

    void render();

private:
    /**
     * \brief Affiche le contenu du plateau de jeu
     */
    void renderBoard();
    /**
     * \brief Affiche le chargement du jeu
     */
    void renderLoading();
    /**
     * \brief Affiche la demande d'action (déplacement ou mur) du joueur actuel
     */
    void renderAction();
    /**
     * \brief Affiche la demande de déplacement du joueur actuel
     */
    void renderMove();
    /**
     * \brief Affiche la demande de colonne du mur
     */
    void renderWallCol();
    /**
     * \brief Affiche la demande de ligne du mur
     */
    void renderWallRow();
    /**
     * \brief Affiche la demande de direction du mur
     */
    void renderWallDir();
    /**
     * \brief Affiche le gagnant
     */
    void renderWin();
    /**
     * \brief Affiche la partie nulle
     */
    void renderDraw();
};

}

#endif // GAMEVIEW_H
