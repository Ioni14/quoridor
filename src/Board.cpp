#include "Board.h"

#include "PathfindingAStar.h"

namespace G36631 {

Board::Board(const int& size):
    m_cells(0),
    m_size(size),
    m_pathfindingStrategy(std::make_unique<PathfindingAStar>(*this))
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

/**
 * @brief Board::putWall Ajoute un mur sur le plateau
 * @param players La liste des joueurs
 * @param player Le joueur actif
 * @param i La colonne de la cellule visée
 * @param j La ligne de la cellule visée
 * @param orientation L'orientation du mur à poser
 * @return true si le mur a été posé
 */
bool Board::putWall(const std::list<Player>& players, Player& player, const int& i, const int& j, const Board::WALL_ORIENTATION& orientation)
{
    if (!canPutWall(player, i, j, orientation)) {
        return false;
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

    if (!havePaths(players)) {
        // Pas de chemin pour les joueurs : on enlève les murs
        if (orientation == WALL_ORIENTATION::VERTICAL) {
            m_cells[i][j].setWallEast(BoardCell::WALL_POSITION::NONE);
            m_cells[i][j + 1].setWallEast(BoardCell::WALL_POSITION::NONE);
            m_cells[i + 1][j].setWallWest(BoardCell::WALL_POSITION::NONE);
            m_cells[i + 1][j + 1].setWallWest(BoardCell::WALL_POSITION::NONE);
        } else {
            m_cells[i][j].setWallSouth(BoardCell::WALL_POSITION::NONE);
            m_cells[i + 1][j].setWallSouth(BoardCell::WALL_POSITION::NONE);
            m_cells[i][j + 1].setWallNorth(BoardCell::WALL_POSITION::NONE);
            m_cells[i + 1][j + 1].setWallNorth(BoardCell::WALL_POSITION::NONE);
        }
        return false;
    }

    player.decrementWalls();
    return true;
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

    return true;
}

bool Board::havePaths(const std::list<Player>& players) const
{
    // Test pathfinding
    for (auto& player : players) {
        bool hasPath = false;
        switch (player.getNumero()) {
            case 1:
            default:
                for (int i = 0; i < m_size; ++i) {
                    hasPath |= m_pathfindingStrategy->hasPath(player.getIPos(), player.getJPos(), i, 0);
                    if (hasPath) {
                        break;
                    }
                }
                break;
            case 2:
                for (int i = 0; i < m_size; ++i) {
                    hasPath |= m_pathfindingStrategy->hasPath(player.getIPos(), player.getJPos(), i, m_size - 1);
                    if (hasPath) {
                        break;
                    }
                }
                break;
            case 3:
                for (int j = 0; j < m_size; ++j) {
                    hasPath |= m_pathfindingStrategy->hasPath(player.getIPos(), player.getJPos(), 0, j);
                    if (hasPath) {
                        break;
                    }
                }
                break;
            case 4:
                for (int j = 0; j < m_size; ++j) {
                    hasPath |= m_pathfindingStrategy->hasPath(player.getIPos(), player.getJPos(), m_size - 1, j);
                    if (hasPath) {
                        break;
                    }
                }
                break;
        }
        if (!hasPath) { // Si au moins un joueur n'a pas de chemin
            return false;
        }
    }

    return true;
}

}
