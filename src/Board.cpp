#include "Board.h"

#include <iostream>
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

bool Board::putWall(Player& player, const int& i, const int& j, const Board::WALL_ORIENTATION& orientation)
{
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
    return true;
}

void Board::destroyWall(Player& player, const int& i, const int& j, const Board::WALL_ORIENTATION& orientation)
{
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

    player.incrementWalls();
}

bool Board::syncShortestPathByPlayer(Player& playerForPath)
{
    bool pathsFound = true;
    bool needRecalculate = false;
    std::list<const BoardCell*> path = playerForPath.getLastShortestPath();
    if (path.size() == 0) {
        needRecalculate = true;
    } else {
        const BoardCell* firstBc = *(path.rbegin());
        if (firstBc->getIPos() != playerForPath.getIPos()
            || firstBc->getJPos() != playerForPath.getJPos()) {
            needRecalculate = true;
        } else {
            for (auto it = path.rbegin(); it != std::prev(path.rend(), 1); it++) {
                const BoardCell* bc = *it;
                const BoardCell* bc2 = *(std::next(it, 1));
                if (!Player::canMove(*this, bc->getIPos(), bc->getJPos(), bc2->getIPos() - bc->getIPos(), bc2->getJPos() - bc->getJPos())) {
                    needRecalculate = true;
                    break;
                }
            }
        }
    }
    if (needRecalculate) { // on recalcule le chemin le plus court
        //std::cout << "recalculate" << std::endl;
        playerForPath.setLastShortestPath(calculateShortestPath(playerForPath));
        pathsFound &= playerForPath.getLastShortestPath().size() != 0;
    }
    return pathsFound;
}

bool Board::syncShortestPath(std::list<Player>& players)
{
    // On regarde si le shortestPath est toujours ouvert
    bool pathsFound = true;
    for (auto& playerForPath : players) {
        pathsFound &= syncShortestPathByPlayer(playerForPath);
    }
    return pathsFound;
}

// Le mur se met en bas à droite de la cellule visée
bool Board::canPutWall(std::list<Player>& players, const Player& player, const int& i, const int& j, const Board::WALL_ORIENTATION& orientation)
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

    // On prépare le terrain pour calculer un chemin
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

    // On regarde si le shortestPath est toujours ouvert
    bool pathsFound = syncShortestPath(players);
    //bool pathsFound = havePaths(players);

    // On remet les chemins comme avant
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

    return pathsFound;
}

std::list<const BoardCell*> Board::calculateShortestPath(const Player& player)
{
    std::list<const BoardCell*> shortestPath;

    switch (player.getNumero()) {
        case 1:
        default:
            for (int i = 0; i < m_size; ++i) {
                std::list<const BoardCell*> shortestPathTmp;

                // On enlève le joueur
                const Player* playerInCell = m_cells[player.getIPos()][player.getJPos()].getPlayer();
                m_cells[player.getIPos()][player.getJPos()].setPlayer(nullptr);
                int hasPath = m_pathfindingStrategy->hasPath(player.getIPos(), player.getJPos(), i, 0, shortestPathTmp);
                // On remet le joueur
                m_cells[player.getIPos()][player.getJPos()].setPlayer(playerInCell);

                if (hasPath && (shortestPathTmp.size() < shortestPath.size() || shortestPath.size() == 0)) {
                    shortestPath = shortestPathTmp;
                }
            }
            break;
        case 2:
            for (int i = 0; i < m_size; ++i) {
                std::list<const BoardCell*> shortestPathTmp;

                // On enlève le joueur
                const Player* playerInCell = m_cells[player.getIPos()][player.getJPos()].getPlayer();
                m_cells[player.getIPos()][player.getJPos()].setPlayer(nullptr);
                int hasPath = m_pathfindingStrategy->hasPath(player.getIPos(), player.getJPos(), i, m_size - 1, shortestPathTmp);
                // On remet le joueur
                m_cells[player.getIPos()][player.getJPos()].setPlayer(playerInCell);

                if (hasPath && (shortestPathTmp.size() < shortestPath.size() || shortestPath.size() == 0)) {
                    shortestPath = shortestPathTmp;
                }
            }
            break;
        case 3:
            for (int j = 0; j < m_size; ++j) {
                std::list<const BoardCell*> shortestPathTmp;

                // On enlève le joueur
                const Player* playerInCell = m_cells[player.getIPos()][player.getJPos()].getPlayer();
                m_cells[player.getIPos()][player.getJPos()].setPlayer(nullptr);
                int hasPath = m_pathfindingStrategy->hasPath(player.getIPos(), player.getJPos(), 0, j, shortestPathTmp);
                // On remet le joueur
                m_cells[player.getIPos()][player.getJPos()].setPlayer(playerInCell);

                if (hasPath && (shortestPathTmp.size() < shortestPath.size() || shortestPath.size() == 0)) {
                    shortestPath = shortestPathTmp;
                }
            }
            break;
        case 4:
            for (int j = 0; j < m_size; ++j) {
                std::list<const BoardCell*> shortestPathTmp;

                // On enlève le joueur
                const Player* playerInCell = m_cells[player.getIPos()][player.getJPos()].getPlayer();
                m_cells[player.getIPos()][player.getJPos()].setPlayer(nullptr);
                int hasPath = m_pathfindingStrategy->hasPath(player.getIPos(), player.getJPos(), m_size - 1, j, shortestPathTmp);
                // On remet le joueur
                m_cells[player.getIPos()][player.getJPos()].setPlayer(playerInCell);

                if (hasPath && (shortestPathTmp.size() < shortestPath.size() || shortestPath.size() == 0)) {
                    shortestPath = shortestPathTmp;
                }
            }
            break;
    }

    return shortestPath;
}

/*
bool Board::havePaths(const std::list<Player>& players)
{
    // Test pathfinding
    for (auto& player : players) {
        bool hasPath = false;
        switch (player.getNumero()) {
            case 1:
            default:
                for (int i = 0; i < m_size; ++i) {
                    std::list<const BoardCell*> shortestPath;

                    // On enlève le joueur
                    const Player* playerInCell = m_cells[player.getIPos()][player.getJPos()].getPlayer();
                    m_cells[player.getIPos()][player.getJPos()].setPlayer(nullptr);
                    hasPath |= m_pathfindingStrategy->hasPath(player.getIPos(), player.getJPos(), i, 0, shortestPath);
                    // On remet le joueur
                    m_cells[player.getIPos()][player.getJPos()].setPlayer(playerInCell);

                    if (hasPath) {
                        break;
                    }
                }
                break;
            case 2:
                for (int i = 0; i < m_size; ++i) {
                    std::list<const BoardCell*> shortestPath;

                    // On enlève le joueur
                    const Player* playerInCell = m_cells[player.getIPos()][player.getJPos()].getPlayer();
                    m_cells[player.getIPos()][player.getJPos()].setPlayer(nullptr);
                    hasPath |= m_pathfindingStrategy->hasPath(player.getIPos(), player.getJPos(), i, m_size - 1, shortestPath);
                    // On remet le joueur
                    m_cells[player.getIPos()][player.getJPos()].setPlayer(playerInCell);

                    if (hasPath) {
                        break;
                    }
                }
                break;
            case 3:
                for (int j = 0; j < m_size; ++j) {
                    std::list<const BoardCell*> shortestPath;

                    // On enlève le joueur
                    const Player* playerInCell = m_cells[player.getIPos()][player.getJPos()].getPlayer();
                    m_cells[player.getIPos()][player.getJPos()].setPlayer(nullptr);
                    hasPath |= m_pathfindingStrategy->hasPath(player.getIPos(), player.getJPos(), 0, j, shortestPath);
                    // On remet le joueur
                    m_cells[player.getIPos()][player.getJPos()].setPlayer(playerInCell);

                    if (hasPath) {
                        break;
                    }
                }
                break;
            case 4:
                for (int j = 0; j < m_size; ++j) {
                    std::list<const BoardCell*> shortestPath;

                    // On enlève le joueur
                    const Player* playerInCell = m_cells[player.getIPos()][player.getJPos()].getPlayer();
                    m_cells[player.getIPos()][player.getJPos()].setPlayer(nullptr);
                    hasPath |= m_pathfindingStrategy->hasPath(player.getIPos(), player.getJPos(), m_size - 1, j, shortestPath);
                    // On remet le joueur
                    m_cells[player.getIPos()][player.getJPos()].setPlayer(playerInCell);

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
*/

}
