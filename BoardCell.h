#ifndef BOARDCELL_H
#define BOARDCELL_H

#include "Player.h"

class BoardCell
{
public:
    BoardCell();
    BoardCell(const int& i, const int& j);

    const bool& hasWallNorth() const;
    void setWallNorth(const bool& val);

    const bool& hasWallSouth() const;
    void setWallSouth(const bool& val);

    const bool& hasWallEast() const;
    void setWallEast(const bool& val);

    const bool& hasWallWest() const;
    void setWallWest(const bool& val);

    const Player* getPlayer() const;
    void setPlayer(const Player* player);
    bool hasPlayer() const;

    const int& getIPos() const;
    const int& getJPos() const;

private:
    bool m_wallNorth;
    bool m_wallSouth;
    bool m_wallEast;
    bool m_wallWest;

    int m_iPos;
    int m_jPos;

    const Player* m_player;
};

#endif // BOARDCELL_H
