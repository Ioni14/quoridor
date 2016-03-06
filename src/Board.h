#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <list>
#include "AbstractPathfinding.h"
#include "BoardCell.h"

class Board
{
public:
    enum class WALL_ORIENTATION {VERTICAL, HORIZONTAL};

    typedef std::unique_ptr<AbstractPathfinding> PathfindingPtr;

public:
    Board(const int& size);

    void render();
    std::vector<std::vector<BoardCell>>& getCells();
    const std::vector<std::vector<BoardCell>>& getCells() const;
    bool putWall(const std::list<Player> &players, Player& player, const int& i, const int& j, const WALL_ORIENTATION& orientation);
    bool canPutWall(const Player& player, const int& i, const int& j, const WALL_ORIENTATION& orientation) const;
    bool havePaths(const std::list<Player> &players) const;

    const int& getSize() const {
        return m_size;
    }

    void setPathfindingStrategy(PathfindingPtr strategy) {
        m_pathfindingStrategy = std::move(strategy);
    }

private:
    void create();
    void putBorderWalls(const int& i, const int& j);

private:
    std::vector<std::vector<BoardCell>> m_cells;

    int m_size;

    PathfindingPtr m_pathfindingStrategy;
};

#endif // BOARD_H
