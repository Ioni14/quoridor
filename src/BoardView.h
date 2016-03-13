#ifndef BOARDVIEW_H
#define BOARDVIEW_H

/**
 * \file BoardView.h
 * \brief Définition de la classe BoardView
 * \author J. Keenens
 * \version 0.1
 * \date 13/03/2016
 */

#include <QGraphicsView>
#include <QMouseEvent>
#include <map>
#include "Player.h"
#include "Board.h"

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

class MainWindow;

/**
 * \class BoardView
 * \brief Représente l'affichage du plateau de jeu
 */
class BoardView : public QGraphicsView
{
    Q_OBJECT

public:
    enum class TEXTURES {
        CELL, /**< La texture d'une case du plateau */
        PAWN_BLUE, /**< La texture du pion bleu */
        PAWN_BLUE_PROJ, /**< La projection du pion bleu */
        PAWN_RED, /**< La texture du pion rouge */
        PAWN_RED_PROJ, /**< La projection du pion rouge */
        PAWN_YELLOW, /**< La texture du pion jaune */
        PAWN_YELLOW_PROJ, /**< La projection du pion jaune */
        PAWN_GREEN, /**< La texture du pion vert */
        PAWN_GREEN_PROJ, /**< La projection du pion vert */
        WALL, /**< La texture d'un mur posé */
        WALL_PROJECTION /**< La texture d'un mur qui peut être posé */
    };

public:
    /**
     * \brief Constructeur logique
     * \param mainWindow : la fenêtre où elle se trouve
     * \param parent : le widget parent
     */
    explicit BoardView(MainWindow& mainWindow, QWidget * parent = 0);

    /**
     * \brief Affiche toutes les cases du plateau graphiquement
     * \param size : la taille du plateau à afficher
     */
    void drawBoard(const int& size);

    /**
     * \brief Crée et affiche les pions des joueurs
     * \param players : la liste des joueurs à afficher
     */
    void createPlayersItems(const std::list<Player> &players);
    /**
     * \brief Crée et affiche la projection des joueurs (aperçu du déplacement)
     * \param player : le joueur concerné
     * \param i : la colonne d'arrivée
     * \param j : la ligne d'arrivée
     */
    void createPlayerProjectionItem(const Player& player, const int& i, const int& j);
    /**
     * \brief Crée et affiche la projection des murs (aperçu de la pose de murs)
     * Le mur sera placé en bas à droite de la case visée
     * \param i : la colonne d'arrivée
     * \param j : la ligne d'arrivée
     * \param orientation : vertical ou horizontal
     */
    void createWallProjectionItem(const int& i, const int& j, const Board::WALL_ORIENTATION& orientation);
    /**
     * \brief Déplace le joueur graphiquement
     * \param player : le joueur concerné
     */
    void movePlayer(const Player& player);
    /**
     * \brief Pose un mur graphiquement
     * Le mur sera placé en bas à droite de la case visée
     * \param i : la colonne d'arrivée
     * \param j : la ligne d'arrivée
     * \param orientation : vertical ou horizontal
     */
    void putWall(const int& i, const int& j, const Board::WALL_ORIENTATION& orientation);

signals:

public slots:
    /**
     * \brief Détecte les actions du joueur
     * Se déplacer (clic sur une case) ou Pose de mur (clique entre les cases)
     * ou Pivotage du mur par clic droit
     * \param e : l'événement souris généré par Qt
     */
    void mousePressEvent(QMouseEvent* e);
    /**
     * \brief Permet d'afficher un aperçu de l'action du joueur comme s'il avait cliqué
     * \param e : l'événement souris généré par Qt
     */
    void mouseMoveEvent(QMouseEvent* e);
    /**
     * @brief Fait pivoter le mur avec la barre espace
     * @param e : l'événement clavier généré par Qt
     */
    void keyPressEvent(QKeyEvent* e);

private:
    /**
     * \brief Charge toutes les textures du jeu
     */
    void loadTextures();

    /**
     * \brief Effectue les actions liées à la souris (déplacement, pose de mur, aperçu des actions)
     * \param mousePos : la position de la souris
     * \param projection : true si c'est un aperçu d'action
     */
    void doMouseEvent(const QPoint& mousePos, const bool& projection);
    /**
     * \brief Crée et affiche le pion d'un joueur ou son aperçu de déplacement
     * \param player : le joueur concerné
     * \param i : la colonne d'arrivée
     * \param j : la ligne d'arrivée
     * \param projection : true si c'est un aperçu de déplacement
     */
    void createPlayerItem(const Player& player, const int& i, const int& j, const bool& projection);

private:
    QGraphicsScene m_scene; /**< La scène graphique où on ajoute les sprites */
    MainWindow& m_mainWindow; /**< La fenêtre de l'application */

    std::map<TEXTURES, QPixmap> m_textures; /**< Liste des textures que le jeu utilise */
    std::map<int, QGraphicsPixmapItem*> m_playersItems; /**< Liste des sprites des joueurs (clé = numéro des joueurs) */
    std::vector<QGraphicsPixmapItem*> m_wallsItems; /**< Liste des sprites des murs */
    QGraphicsPixmapItem* m_projectionItem; /**< Sprite de projection (aperçu de l'action) */

    Board::WALL_ORIENTATION m_wallOrientation; /**< L'orientation du mur que l'on va poser au clic */

    static const int OFFSET_HORIZONTAL; /**< La taille de la bordure gauche et droite autour du plateau */
    static const int OFFSET_VERTICAL; /**< La taille de la bordure haute et basse autour du plateau */
};

}

#endif // BOARDVIEW_H
