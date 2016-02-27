#include "BoardCell.h"

BoardCell::BoardCell() :
    m_wallNorth(WALL_POSITION::NONE),
    m_wallSouth(WALL_POSITION::NONE),
    m_wallEast(WALL_POSITION::NONE),
    m_wallWest(WALL_POSITION::NONE),
    m_player(nullptr)
{
}

BoardCell::BoardCell(const int& i, const int& j) :
    BoardCell()
{
    m_iPos = i;
    m_jPos = j;
}

const BoardCell::WALL_POSITION& BoardCell::getWallNorth() const {
    return m_wallNorth;
}
const bool& BoardCell::hasWallNorth() const {
    return m_wallNorth != WALL_POSITION::NONE;
}
void BoardCell::setWallNorth(const BoardCell::WALL_POSITION& val) {
    m_wallNorth = val;
}

const BoardCell::WALL_POSITION& BoardCell::getWallSouth() const {
    return m_wallSouth;
}
const bool& BoardCell::hasWallSouth() const {
    return m_wallSouth != WALL_POSITION::NONE;
}
void BoardCell::setWallSouth(const BoardCell::WALL_POSITION& val) {
    m_wallSouth = val;
}

const BoardCell::WALL_POSITION& BoardCell::getWallEast() const {
    return m_wallEast;
}
const bool& BoardCell::hasWallEast() const {
    return m_wallEast != WALL_POSITION::NONE;
}
void BoardCell::setWallEast(const BoardCell::WALL_POSITION& val) {
    m_wallEast = val;
}

const BoardCell::WALL_POSITION& BoardCell::getWallWest() const {
    return m_wallWest;
}
const bool& BoardCell::hasWallWest() const {
    return m_wallWest != WALL_POSITION::NONE;
}
void BoardCell::setWallWest(const BoardCell::WALL_POSITION& val) {
    m_wallWest = val;
}

const Player* BoardCell::getPlayer() const {
    return m_player;
}
void BoardCell::setPlayer(const Player* player) {
    m_player = player;
}
bool BoardCell::hasPlayer() const {
    return m_player != nullptr;
}

const int& BoardCell::getIPos() const {
    return m_iPos;
}
const int& BoardCell::getJPos() const {
    return m_jPos;
}
