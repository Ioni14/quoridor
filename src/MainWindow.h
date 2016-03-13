#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * \file MainWindow.h
 * \brief Définition de la classe MainWindow
 * \author J. Keenens
 * \version 0.1
 * \date 13/03/2016
 */

#include <QMainWindow>
#include <QGraphicsView>
#include "ui_Quoridor.h"
#include "Quoridor.h"
#include "Observer.h"
#include "BoardView.h"

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

/**
 * \class MainWindow
 * \brief Représente la fenêtre graphique de l'application
 */
class MainWindow : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    /**
     * \brief Constructeur logique
     * \param model : le modèle de l'application (classe principale)
     * \param parent : le parent de la fenêtre
     */
    explicit MainWindow(Quoridor &model, QWidget *parent = 0);
    /**
     * \brief Destructeur
     */
    ~MainWindow();

    virtual void onActivated();

    virtual void onPlayersInitialized(const std::list<Player>& players);
    virtual void onPlayerMove(const Player& player);
    virtual void onPutWall(const int& i, const int& j, const Board::WALL_ORIENTATION& orientation);
    virtual void onPlayerWon(const Player& player);

    /**
     * \brief Récupère le modèle lié à la fenêtre
     * \return le modèle
     */
    Quoridor& getModel() {
        return m_model;
    }

signals:

public slots:
    /**
     * \brief Action pour configurer une nouvelle partie
     */
    void newGame();
    /**
     * \brief Action pour lancer la partie
     */
    void launchGame();
    /**
     * \brief Action pour afficher "A propos"
     */
    void about();
    /**
     * \brief Action pour afficher les règles du jeu
     */
    void howToPlay();

private:
    /**
     * \brief Met à jour le tableau de bord en cours de partie
     */
    void updateDashboard();

private:
    Ui::Quoridor m_ui; /**< Les différents éléments composant la fenêtre */
    BoardView* m_boardView; /**< L'affichage graphique du plateau */

    Quoridor& m_model; /**< Le modèle lié à la fenêtre */

    QPixmap m_caretTexture; /**< La texture représentant le joueur actuel */
};

}

#endif // MAINWINDOW_H
