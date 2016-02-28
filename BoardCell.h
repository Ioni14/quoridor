#ifndef BOARDCELL_H
#define BOARDCELL_H

#include "Player.h"

class BoardCell
{
public:
    enum WALL_POSITION {NONE, UP_LEFT, DOWN_RIGHT};

public:
    BoardCell();
    BoardCell(const int& i, const int& j);

    const WALL_POSITION& getWallNorth() const;
    bool hasWallNorth() const;
    void setWallNorth(const WALL_POSITION& val);

    const WALL_POSITION& getWallSouth() const;
    bool hasWallSouth() const;
    void setWallSouth(const WALL_POSITION& val);

    const WALL_POSITION& getWallEast() const;
    bool hasWallEast() const;
    void setWallEast(const WALL_POSITION& val);

    const WALL_POSITION& getWallWest() const;
    bool hasWallWest() const;
    void setWallWest(const WALL_POSITION& val);

    const Player* getPlayer() const;
    void setPlayer(const Player* player);
    bool hasPlayer() const;

    const int& getIPos() const;
    const int& getJPos() const;

private:
    WALL_POSITION m_wallNorth;
    WALL_POSITION m_wallSouth;
    WALL_POSITION m_wallEast;
    WALL_POSITION m_wallWest;

    int m_iPos;
    int m_jPos;

    const Player* m_player;
};

#endif // BOARDCELL_H
