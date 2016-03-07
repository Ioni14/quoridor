#ifndef MAINMENUVIEW_H
#define MAINMENUVIEW_H

/**
 * \file MainMenuView.h
 * \brief Définition de la classe MainMenuView
 * \author J. Keenens
 * \version 0.1
 * \date 07/03/2016
 */

#include "View.h"
#include "MainMenuState.h"

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

/**
 * \class Représente la Vue du menu principal du jeu
 */
class MainMenuView : public View
{
public:
    /**
     * \brief Constructeur logique
     * \param model : le modèle que la Vue doit afficher
     */
    MainMenuView(MainMenuState& model);

    void render();

private:
    /**
     * \brief Affiche le titre du jeu
     */
    void renderTitle();
    /**
     * \brief Affiche le menu principal
     */
    void renderMenu();
    /**
     * \brief Affiche la demande du nombre de joueur
     */
    void renderPlay();
    /**
     * \brief Affiche la demande du type de chaque joueur
     */
    void renderPlayers();
    /**
     * \brief Affiche la demande de la taille du plateau
     */
    void renderBoardSize();
    /**
     * \brief Affiche le résumé de la configuration de la partie
     */
    void renderSummary();
};

}

#endif // MAINMENUVIEW_H
