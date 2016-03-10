#include "BoardView.h"

#include <iostream>
#include <QGraphicsPixmapItem>
#include "MainWindow.h"

BoardView::BoardView(MainWindow& mainWindow, QWidget *parent) :
    QGraphicsView(parent),
    m_scene(this),
    m_mainWindow(mainWindow)
{
    setAlignment(Qt::AlignTop | Qt::AlignLeft);
    setBackgroundBrush(Qt::black);
    m_scene.setSceneRect(0, 0, width(), height());
    setScene(&m_scene);

    loadTextures();
}

void BoardView::drawBoard(const int& size)
{
    auto itCellTexture = m_textures.find(TEXTURES::CELL);
    auto itWallTexture = m_textures.find(TEXTURES::WALL);
    if (itCellTexture == m_textures.end()
        || itWallTexture == m_textures.end()) {
        return;
    }

    int offsetLeft(20), offsetTop(20); // Les bordures autour du plateau
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            auto& cellTex = itCellTexture->second;
            auto sizeWall  = itWallTexture->second.height();
            QGraphicsPixmapItem *cellSprite = m_scene.addPixmap(cellTex);
            cellSprite->setPos(
                i * (cellTex.width() + sizeWall) + offsetLeft,
                j * (cellTex.height() + sizeWall) + offsetTop
            );
        }
    }

    // On redimensionne la fenêtre pour qu'elle englobe tout le plateau
    m_mainWindow.resize(
        size * (itCellTexture->second.width() + itWallTexture->second.height()) + 2*offsetLeft + 15,
        size * (itCellTexture->second.height() + itWallTexture->second.height()) + 2*offsetTop + 15 + 15
    );


    /*
     * Afficher la position des joueurs
     * Pour un joueur donné : récup position souris (mouseover) et savoir si on est sur cellule ou entre
     *      => Si clique : soit on le déplace (avec vérifs) soit on place le mur (avec vérifs) : fireMove, fireWall
     *
     * Puis on ajoute les projections pour ERGONOMIE MAGUEULE !!
     */
}

void BoardView::loadTextures()
{
    {
        QPixmap tex;
        if (!tex.load("./res/board-cell.png")) {
            std::cerr << "./res/board-cell.png introuvable" << std::endl;
        }
        m_textures.insert(std::make_pair<TEXTURES, QPixmap>(TEXTURES::CELL, std::move(tex)));
    }
    {
        QPixmap tex;
        if (!tex.load("./res/pawn-blue-24.png")) {
            std::cerr << "./res/pawn-blue-24.png introuvable" << std::endl;
        }
        m_textures.insert(std::make_pair<TEXTURES, QPixmap>(TEXTURES::PAWN_BLUE, std::move(tex)));
    }
    {
        QPixmap tex;
        if (!tex.load("./res/pawn-red-24.png")) {
            std::cerr << "./res/pawn-red-24.png introuvable" << std::endl;
        }
        m_textures.insert(std::make_pair<TEXTURES, QPixmap>(TEXTURES::PAWN_RED, std::move(tex)));
    }
    {
        QPixmap tex;
        if (!tex.load("./res/pawn-yellow-24.png")) {
            std::cerr << "./res/pawn-yellow-24.png introuvable" << std::endl;
        }
        m_textures.insert(std::make_pair<TEXTURES, QPixmap>(TEXTURES::PAWN_YELLOW, std::move(tex)));
    }
    {
        QPixmap tex;
        if (!tex.load("./res/pawn-green-24.png")) {
            std::cerr << "./res/pawn-green-24.png introuvable" << std::endl;
        }
        m_textures.insert(std::make_pair<TEXTURES, QPixmap>(TEXTURES::PAWN_GREEN, std::move(tex)));
    }
    {
        QPixmap tex;
        if (!tex.load("./res/wall.png")) {
            std::cerr << "./res/wall.png introuvable" << std::endl;
        }
        m_textures.insert(std::make_pair<TEXTURES, QPixmap>(TEXTURES::WALL, std::move(tex)));
    }
    {
        QPixmap tex;
        if (!tex.load("./res/wall-projection.png")) {
            std::cerr << "./res/wall-projection.png introuvable" << std::endl;
        }
        m_textures.insert(std::make_pair<TEXTURES, QPixmap>(TEXTURES::WALL_PROJECTION, std::move(tex)));
    }
}
