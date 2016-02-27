#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "BoardCell.h"

class Board
{
public:
    enum WALL_ORIENTATION {VERTICAL, HORIZONTAL};

public:
    Board(const int& size);

    void render();
    std::vector<std::vector<BoardCell>>& getCells();
    const std::vector<std::vector<BoardCell>>& getCells() const;
    const int& getSize() const {
        return m_size;
    }

    void putWall(Player& player, const int& i, const int& j, const WALL_ORIENTATION& orientation);
    bool canPutWall(const Player& player, const int& i, const int& j, const WALL_ORIENTATION& orientation) const;

private:
    void create();
    void putBorderWalls(const int& i, const int& j);

private:
    std::vector<std::vector<BoardCell>> m_cells;

    int m_size;
};

#endif // BOARD_H
