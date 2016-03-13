#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <map>
#include "Player.h"
#include "Board.h"

class MainWindow;

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
    explicit BoardView(MainWindow& mainWindow, QWidget * parent = 0);

    void drawBoard(const int& size);
    void createPlayersItems(const std::list<G36631::Player> &players);
    void createPlayerProjectionItem(const G36631::Player& player, const int& i, const int& j);
    void createWallProjectionItem(const int& i, const int& j, const G36631::Board::WALL_ORIENTATION& orientation);
    void movePlayer(const G36631::Player& player);
    void putWall(const int& i, const int& j, const G36631::Board::WALL_ORIENTATION& orientation);

signals:

public slots:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void keyPressEvent(QKeyEvent* e);

private:
    /**
     * \brief Charge toutes les textures du jeu
     */
    void loadTextures();

    void doMouseEvent(const QPoint& mousePos, const bool& projection);

private:
    QGraphicsScene m_scene;
    MainWindow& m_mainWindow;

    std::map<TEXTURES, QPixmap> m_textures; /**< Liste des textures que le jeu utilise */
    std::map<int, QGraphicsPixmapItem*> m_playersItems; /**< Liste des sprites des joueurs (clé = numéro des joueurs) */
    std::vector<QGraphicsPixmapItem*> m_wallsItems; /**< Liste des sprites des murs */
    QGraphicsPixmapItem* m_projectionItem; /**< Sprite de projection (aperçu de l'action) */

    G36631::Board::WALL_ORIENTATION m_wallOrientation; /**< L'orientation du mur que l'on va poser au clic */

    static const int OFFSET_HORIZONTAL; /**< La taille de la bordure gauche et droite autour du plateau */
    static const int OFFSET_VERTICAL; /**< La taille de la bordure haute et basse autour du plateau */
};

#endif // BOARDVIEW_H
