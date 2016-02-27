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

    for (int i = 0; i <= m_size - 2; ++i) {
        m_cells[i][3].setWallSouth(true);
        m_cells[i][4].setWallNorth(true);
    }
    for (int j = 1; j <= m_size - 1; ++j) {
        m_cells[3][j].setWallEast(true);
        m_cells[4][j].setWallWest(true);
    }

}

void Board::putBorderWalls(const int& i, const int& j)
{
    if (i == 0) {
        m_cells[i][j].setWallWest(true);
    } else if (i == m_size - 1) {
        m_cells[i][j].setWallEast(true);
    }
    if (j == 0) {
        m_cells[i][j].setWallNorth(true);
    } else if (j == m_size - 1) {
        m_cells[i][j].setWallSouth(true);
    }
}

void Board::render()
{
}
