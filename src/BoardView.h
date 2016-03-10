#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QGraphicsView>
#include <map>

class MainWindow;

class BoardView : public QGraphicsView
{
public:
    enum class TEXTURES {
        CELL, /**< La texture d'une case du plateau */
        PAWN_BLUE, /**< La texture du pion bleu */
        PAWN_RED, /**< La texture du pion rouge */
        PAWN_YELLOW, /**< La texture du pion jaune */
        PAWN_GREEN, /**< La texture du pion green */
        WALL, /**< La texture d'un mur posé */
        WALL_PROJECTION /**< La texture d'un mur qui peut être posé */
    };

public:
    BoardView(MainWindow& mainWindow, QWidget * parent = 0);

    void drawBoard(const int& size);

private:
    /**
     * \brief Charge toutes les textures du jeu
     */
    void loadTextures();

private:
    QGraphicsScene m_scene;
    MainWindow& m_mainWindow;

    std::map<TEXTURES, QPixmap> m_textures;
};

#endif // BOARDVIEW_H
