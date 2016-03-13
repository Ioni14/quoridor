#include "BoardView.h"

#include <iostream>
#include <QGraphicsPixmapItem>
#include "MainWindow.h"
#include "GameState.h"

const int BoardView::OFFSET_HORIZONTAL = 20;
const int BoardView::OFFSET_VERTICAL = 20;

BoardView::BoardView(MainWindow& mainWindow, QWidget *parent) :
    QGraphicsView(parent),
    m_scene(this),
    m_mainWindow(mainWindow),
    m_projectionItem(nullptr),
    m_wallOrientation(G36631::Board::WALL_ORIENTATION::HORIZONTAL)
{
    setMouseTracking(true);
    setAlignment(Qt::AlignTop | Qt::AlignLeft);
    setBackgroundBrush(Qt::black);
    m_scene.setSceneRect(0, 0, width(), height());
    setScene(&m_scene);

    loadTextures();
}

void BoardView::doMouseEvent(const QPoint& mousePos, const bool& projection)
{
    if (mousePos.x() < OFFSET_HORIZONTAL || mousePos.y() < OFFSET_VERTICAL) {
        // On est en dehors du plateau (trop en haut ou gauche)
        return;
    }

    auto itCellTexture = m_textures.find(TEXTURES::CELL);
    auto itWallTexture = m_textures.find(TEXTURES::WALL);
    if (itCellTexture == m_textures.end()
        || itWallTexture == m_textures.end()) {
        return;
    }

    auto sizeCell = itCellTexture->second.width();
    auto sizeWall = itWallTexture->second.height();

    int x = static_cast<int>( (mousePos.x() - OFFSET_HORIZONTAL) / (sizeCell + sizeWall) );
    int y = static_cast<int>( (mousePos.y() - OFFSET_VERTICAL) / (sizeCell + sizeWall) );
    int xInCell = (mousePos.x() - OFFSET_HORIZONTAL) % (sizeCell + sizeWall);
    int yInCell = (mousePos.y() - OFFSET_VERTICAL) % (sizeCell + sizeWall);

    auto& stateBase = *(m_mainWindow.getModel().getState());
    auto& state = dynamic_cast<G36631::GameState&>(stateBase);
    if (x >= state.getBoard().getSize() || y >= state.getBoard().getSize()) {
        return;
    }

    bool inCell = (xInCell < sizeCell && yInCell < sizeCell);
    bool intersection = (xInCell >= sizeCell && yInCell >= sizeCell);
    bool rightWall = (xInCell >= sizeCell);
    bool bottomWall = (yInCell >= sizeCell);

    // Dans case = on veut se déplacer
    auto& player = state.getPlayerActual();
    int di = x - player.getIPos();
    int dj = y - player.getJPos();
    if (inCell && player.canMove(state.getBoard(), di, dj)) {
        if (projection) {
            createPlayerProjectionItem(player, x, y);
        } else {
            state.nextPlayer();
            state.movePlayer(player, di, dj);
        }
    }
    if (inCell) {
        return;
    }

    int xFixed(x), yFixed(y);

    // Dans les murs adjacents à la case
    if ( intersection
        || (bottomWall && xInCell >= sizeCell / 2)
        || (rightWall && yInCell >= sizeCell / 2) ) {

        // Prise en compte si on clique à côté des bordures du plateau
        if (bottomWall && x == state.getBoard().getSize() - 1) {
            xFixed--;
        }
        if (rightWall && y == state.getBoard().getSize() - 1) {
            yFixed--;
        }

    } else if ((bottomWall && xInCell < sizeCell / 2)
               || (rightWall && yInCell < sizeCell / 2) ) {

        // Prise en compte si on clique à côté des bordures du plateau
        if (bottomWall) {
            if (x > 0) {
                xFixed--;
            }
        } else if (rightWall) {
            if (y > 0) {
                yFixed--;
            }
        }

    }

    auto canPutWall = state.canPutWall(player, xFixed, yFixed, m_wallOrientation);
    if (canPutWall) {
        if (projection) {
            createWallProjectionItem(xFixed, yFixed, m_wallOrientation);
        } else {
            state.nextPlayer();
            state.putWall(player, xFixed, yFixed, m_wallOrientation);
        }
    }
}

void BoardView::mouseMoveEvent(QMouseEvent* e)
{
    // On supprime la projection actuelle
    if (m_projectionItem != nullptr) {
        m_scene.removeItem(m_projectionItem);
        m_projectionItem = nullptr;
    }

    doMouseEvent(e->pos(), true);
}

void BoardView::mousePressEvent(QMouseEvent * e)
{
    // Clic gauche = changement orientation mur
    if (e->button() == Qt::RightButton) {
        // On switch l'orientation du mur que l'on veut poser
        m_wallOrientation = (m_wallOrientation == G36631::Board::WALL_ORIENTATION::HORIZONTAL
            ? G36631::Board::WALL_ORIENTATION::VERTICAL
            : G36631::Board::WALL_ORIENTATION::HORIZONTAL)
        ;
        if (m_projectionItem != nullptr) {
            m_scene.removeItem(m_projectionItem);
            m_projectionItem = nullptr;
        }
        doMouseEvent(e->pos(), true);
        return;
    }

    if (e->button() != Qt::LeftButton) {
        return;
    }

    // Bouton droite
    doMouseEvent(e->pos(), false);
}

void BoardView::keyPressEvent(QKeyEvent* e)
{
    if (e->key() != Qt::Key_Space) {
        return;
    }

    // On switch l'orientation du mur que l'on veut poser
    m_wallOrientation = m_wallOrientation == G36631::Board::WALL_ORIENTATION::HORIZONTAL
        ? G36631::Board::WALL_ORIENTATION::VERTICAL
        : G36631::Board::WALL_ORIENTATION::HORIZONTAL
    ;
}

void BoardView::movePlayer(const G36631::Player& player)
{
    auto itPlayerItem = m_playersItems.find(player.getNumero());
    auto itCellTexture = m_textures.find(TEXTURES::CELL);
    auto itWallTexture = m_textures.find(TEXTURES::WALL);
    if (itPlayerItem == m_playersItems.end()
        || itCellTexture == m_textures.end()
        || itWallTexture == m_textures.end()) {
        return;
    }

    int cellWidth = itCellTexture->second.width() + itWallTexture->second.height();
    int cellHeight = itCellTexture->second.height() + itWallTexture->second.height();
    itPlayerItem->second->setPos(
        player.getIPos() * cellWidth + OFFSET_HORIZONTAL,
        player.getJPos() * cellHeight + OFFSET_VERTICAL
    );
}

// Crée et affiche une sprite mur en bas à droite de la case visée
void BoardView::putWall(const int& i, const int& j, const G36631::Board::WALL_ORIENTATION& orientation)
{
    auto itCellTexture = m_textures.find(TEXTURES::CELL);
    auto itWallTexture = m_textures.find(TEXTURES::WALL);
    if (itWallTexture == m_textures.end()
        || itCellTexture == m_textures.end()) {
        return;
    }

    int cellWidth = itCellTexture->second.width() + itWallTexture->second.height();
    int cellHeight = itCellTexture->second.height() + itWallTexture->second.height();
    QGraphicsPixmapItem *wallSprite = m_scene.addPixmap(itWallTexture->second);
    if (orientation == G36631::Board::WALL_ORIENTATION::VERTICAL) {
        wallSprite->setRotation(90);
        wallSprite->setPos(
            i * cellWidth + OFFSET_HORIZONTAL + cellWidth, // car mur vertical
            j * cellHeight + OFFSET_VERTICAL
        );
    } else {
        wallSprite->setPos(
            i * cellWidth + OFFSET_HORIZONTAL,
            j * cellHeight + OFFSET_VERTICAL + itCellTexture->second.height() // car mur horizontal
        );
    }
    m_wallsItems.push_back(wallSprite);
}

void BoardView::drawBoard(const int& size)
{
    auto itCellTexture = m_textures.find(TEXTURES::CELL);
    auto itWallTexture = m_textures.find(TEXTURES::WALL);
    if (itCellTexture == m_textures.end()
        || itWallTexture == m_textures.end()) {
        return;
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            auto& cellTex = itCellTexture->second;
            auto sizeWall  = itWallTexture->second.height();
            QGraphicsPixmapItem *cellSprite = m_scene.addPixmap(cellTex);
            cellSprite->setPos(
                i * (cellTex.width() + sizeWall) + OFFSET_HORIZONTAL,
                j * (cellTex.height() + sizeWall) + OFFSET_VERTICAL
            );
        }
    }

    // On redimensionne la fenêtre pour qu'elle englobe tout le plateau
    m_mainWindow.resize(
        size * (itCellTexture->second.width() + itWallTexture->second.height()) + 2*OFFSET_HORIZONTAL + 15 + 230,
        size * (itCellTexture->second.height() + itWallTexture->second.height()) + 2*OFFSET_VERTICAL + 15 + 15
    );
}

void BoardView::createWallProjectionItem(const int& i, const int& j, const G36631::Board::WALL_ORIENTATION& orientation)
{
    auto itCellTexture = m_textures.find(TEXTURES::CELL);
    auto itWallTexture = m_textures.find(TEXTURES::WALL_PROJECTION);
    if (itWallTexture == m_textures.end()
        || itCellTexture == m_textures.end()) {
        return;
    }

    int cellWidth = itCellTexture->second.width() + itWallTexture->second.height();
    int cellHeight = itCellTexture->second.height() + itWallTexture->second.height();
    m_projectionItem = m_scene.addPixmap(itWallTexture->second);
    if (orientation == G36631::Board::WALL_ORIENTATION::VERTICAL) {
        m_projectionItem->setRotation(90);
        m_projectionItem->setPos(
            i * cellWidth + OFFSET_HORIZONTAL + cellWidth, // car mur vertical
            j * cellHeight + OFFSET_VERTICAL
        );
    } else {
        m_projectionItem->setPos(
            i * cellWidth + OFFSET_HORIZONTAL,
            j * cellHeight + OFFSET_VERTICAL + itCellTexture->second.height() // car mur horizontal
        );
    }
}

void BoardView::createPlayerProjectionItem(const G36631::Player& player, const int& i, const int& j)
{
    auto itCellTexture = m_textures.find(TEXTURES::CELL);
    auto itWallTexture = m_textures.find(TEXTURES::WALL);
    auto itPawnBlueTex = m_textures.find(TEXTURES::PAWN_BLUE_PROJ);
    auto itPawnRedTex = m_textures.find(TEXTURES::PAWN_RED_PROJ);
    auto itPawnGreenTex = m_textures.find(TEXTURES::PAWN_GREEN_PROJ);
    auto itPawnYellowTex = m_textures.find(TEXTURES::PAWN_YELLOW_PROJ);
    if (itPawnBlueTex == m_textures.end()
        || itPawnRedTex == m_textures.end()
        || itPawnGreenTex == m_textures.end()
        || itPawnYellowTex == m_textures.end()
        || itCellTexture == m_textures.end()
        || itWallTexture == m_textures.end()) {
        return;
    }

    int cellWidth = itCellTexture->second.width() + itWallTexture->second.height();
    int cellHeight = itCellTexture->second.height() + itWallTexture->second.height();

    QPixmap* pawnTex = nullptr;
    switch (player.getNumero()) {
        case 1:
            pawnTex = &(itPawnBlueTex->second);
            break;
        case 2:
            pawnTex = &(itPawnRedTex->second);
            break;
        case 3:
            pawnTex = &(itPawnGreenTex->second);
            break;
        case 4:
            pawnTex = &(itPawnYellowTex->second);
            break;
    }
    if (pawnTex == nullptr) {
        return;
    }

    int cellOffsetX = itCellTexture->second.width() / 2  - pawnTex->width() / 2;
    int cellOffsetY = itCellTexture->second.height() / 2  - pawnTex->width() / 2;

    m_projectionItem = m_scene.addPixmap(*pawnTex);
    m_projectionItem->setOffset(cellOffsetX, cellOffsetY);
    m_projectionItem->setPos(
        i * cellWidth + OFFSET_HORIZONTAL,
        j * cellHeight + OFFSET_VERTICAL
    );

}

void BoardView::createPlayersItems(const std::list<G36631::Player>& players)
{
    auto itCellTexture = m_textures.find(TEXTURES::CELL);
    auto itWallTexture = m_textures.find(TEXTURES::WALL);
    auto itPawnBlueTex = m_textures.find(TEXTURES::PAWN_BLUE);
    auto itPawnRedTex = m_textures.find(TEXTURES::PAWN_RED);
    auto itPawnGreenTex = m_textures.find(TEXTURES::PAWN_GREEN);
    auto itPawnYellowTex = m_textures.find(TEXTURES::PAWN_YELLOW);
    if (itPawnBlueTex == m_textures.end()
        || itPawnRedTex == m_textures.end()
        || itPawnGreenTex == m_textures.end()
        || itPawnYellowTex == m_textures.end()
        || itCellTexture == m_textures.end()
        || itWallTexture == m_textures.end()) {
        return;
    }

    int cellWidth = itCellTexture->second.width() + itWallTexture->second.height();
    int cellHeight = itCellTexture->second.height() + itWallTexture->second.height();
    for (auto& player : players) {

        QPixmap* pawnTex = nullptr;
        switch (player.getNumero()) {
            case 1:
                pawnTex = &(itPawnBlueTex->second);
                break;
            case 2:
                pawnTex = &(itPawnRedTex->second);
                break;
            case 3:
                pawnTex = &(itPawnGreenTex->second);
                break;
            case 4:
                pawnTex = &(itPawnYellowTex->second);
                break;
        }
        if (pawnTex == nullptr) {
            continue;
        }

        int cellOffsetX = itCellTexture->second.width() / 2  - pawnTex->width() / 2;
        int cellOffsetY = itCellTexture->second.height() / 2  - pawnTex->width() / 2;

        QGraphicsPixmapItem *playerSprite = m_scene.addPixmap(*pawnTex);
        playerSprite->setOffset(cellOffsetX, cellOffsetY);
        playerSprite->setPos(
            player.getIPos() * cellWidth + OFFSET_HORIZONTAL,
            player.getJPos() * cellHeight + OFFSET_VERTICAL
        );
        m_playersItems.insert(std::make_pair(player.getNumero(), playerSprite));

    }

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
        if (!tex.load("./res/pawn-blue-24-alpha.png")) {
            std::cerr << "./res/pawn-blue-24-alpha.png introuvable" << std::endl;
        }
        m_textures.insert(std::make_pair<TEXTURES, QPixmap>(TEXTURES::PAWN_BLUE_PROJ, std::move(tex)));
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
        if (!tex.load("./res/pawn-red-24-alpha.png")) {
            std::cerr << "./res/pawn-red-24-alpha.png introuvable" << std::endl;
        }
        m_textures.insert(std::make_pair<TEXTURES, QPixmap>(TEXTURES::PAWN_RED_PROJ, std::move(tex)));
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
        if (!tex.load("./res/pawn-yellow-24-alpha.png")) {
            std::cerr << "./res/pawn-yellow-24-alpha.png introuvable" << std::endl;
        }
        m_textures.insert(std::make_pair<TEXTURES, QPixmap>(TEXTURES::PAWN_YELLOW_PROJ, std::move(tex)));
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
        if (!tex.load("./res/pawn-green-24-alpha.png")) {
            std::cerr << "./res/pawn-green-24-alpha.png introuvable" << std::endl;
        }
        m_textures.insert(std::make_pair<TEXTURES, QPixmap>(TEXTURES::PAWN_GREEN_PROJ, std::move(tex)));
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
