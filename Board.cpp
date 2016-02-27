#include "Board.h"

Board::Board(const int& size):
    m_cells(0),
    m_size(size)
{
    create();
}

std::vector<std::vector<BoardCell>>& Board::getCells()
{
    return m_cells;
}
// Si on a un "const board" dans une méthode
const std::vector<std::vector<BoardCell>>& Board::getCells() const
{
    return m_cells;
}

void Board::create()
{
    for (int i = 0; i < m_size; ++i) {
        m_cells.push_back(std::vector<BoardCell>(0));
        for (int j = 0; j < m_size; ++j) {
            m_cells[i].push_back(BoardCell(i, j));

            // Détecte si la cellule est sur un bord du plateau et lui ajoute son mur
            putBorderWalls(i, j);
        }
    }

    for (int i = 0; i <= m_size - 2; i+=2) {
        m_cells[i][3].setWallSouth(BoardCell::WALL_POSITION::UP_LEFT);
        m_cells[i][4].setWallNorth(BoardCell::WALL_POSITION::UP_LEFT);
        m_cells[i+1][3].setWallSouth(BoardCell::WALL_POSITION::DOWN_RIGHT);
        m_cells[i+1][4].setWallNorth(BoardCell::WALL_POSITION::DOWN_RIGHT);
    }
    for (int j = 1; j <= m_size - 1; j+=2) {
        m_cells[3][j].setWallEast(BoardCell::WALL_POSITION::UP_LEFT);
        m_cells[4][j].setWallWest(BoardCell::WALL_POSITION::UP_LEFT);
        m_cells[3][j+1].setWallEast(BoardCell::WALL_POSITION::DOWN_RIGHT);
        m_cells[4][j+1].setWallWest(BoardCell::WALL_POSITION::DOWN_RIGHT);
    }

}

void Board::putBorderWalls(const int& i, const int& j)
{
    if (i == 0) {
        m_cells[i][j].setWallWest(BoardCell::WALL_POSITION::UP_LEFT);
    } else if (i == m_size - 1) {
        m_cells[i][j].setWallEast(BoardCell::WALL_POSITION::UP_LEFT);
    }
    if (j == 0) {
        m_cells[i][j].setWallNorth(BoardCell::WALL_POSITION::UP_LEFT);
    } else if (j == m_size - 1) {
        m_cells[i][j].setWallSouth(BoardCell::WALL_POSITION::UP_LEFT);
    }
}

void Board::putWall(Player& player, const int& i, const int& j, const Board::WALL_ORIENTATION& orientation)
{
    if (!canPutWall(player, i, j, orientation)) {
        return;
    }

    if (orientation == WALL_ORIENTATION::VERTICAL) {
        m_cells[i][j].setWallEast(BoardCell::WALL_POSITION::UP_LEFT);
        m_cells[i][j + 1].setWallEast(BoardCell::WALL_POSITION::DOWN_RIGHT);
        m_cells[i + 1][j].setWallWest(BoardCell::WALL_POSITION::UP_LEFT);
        m_cells[i + 1][j + 1].setWallWest(BoardCell::WALL_POSITION::DOWN_RIGHT);
    } else {
        m_cells[i][j].setWallSouth(BoardCell::WALL_POSITION::UP_LEFT);
        m_cells[i + 1][j].setWallSouth(BoardCell::WALL_POSITION::DOWN_RIGHT);
        m_cells[i][j + 1].setWallNorth(BoardCell::WALL_POSITION::UP_LEFT);
        m_cells[i + 1][j + 1].setWallNorth(BoardCell::WALL_POSITION::DOWN_RIGHT);
    }

    player.decrementWalls();
}

// Le mur se met en bas à droite de la cellule visée
bool Board::canPutWall(const Player& player, const int& i, const int& j, const Board::WALL_ORIENTATION& orientation) const
{
    if (!player.hasWalls()) {
        return false;
    }

    if (orientation == WALL_ORIENTATION::VERTICAL) {
        if (i < 0 || i >= m_size || j < 0 || j + 1 >= m_size) {
            return false;
        }
        if (m_cells[i][j].getWallSouth() == BoardCell::WALL_POSITION::UP_LEFT) {
            return false;
        }
        if (m_cells[i][j].hasWallEast() || m_cells[i][j + 1].hasWallEast()) {
            return false;
        }
    } else { // HORIZONTAL
        if (i < 0 || i + 1 >= m_size || j < 0 || j >= m_size) {
            return false;
        }
        if (m_cells[i][j].getWallEast() == BoardCell::WALL_POSITION::UP_LEFT) {
            return false;
        }
        if (m_cells[i][j].hasWallSouth() || m_cells[i + 1][j].hasWallSouth()) {
            return false;
        }
    }

    // Test pathfinding

    return true;
}
