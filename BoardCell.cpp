#include "BoardCell.h"

BoardCell::BoardCell() :
    m_wallNorth(false),
    m_wallSouth(false),
    m_wallEast(false),
    m_wallWest(false),
    m_player(nullptr)
{
}

BoardCell::BoardCell(const int& i, const int& j) :
    BoardCell()
{
    m_iPos = i;
    m_jPos = j;
}

const bool& BoardCell::hasWallNorth() const {
    return m_wallNorth;
}
void BoardCell::setWallNorth(const bool& val) {
    m_wallNorth = val;
}

const bool& BoardCell::hasWallSouth() const {
    return m_wallSouth;
}
void BoardCell::setWallSouth(const bool& val) {
    m_wallSouth = val;
}

const bool& BoardCell::hasWallEast() const {
    return m_wallEast;
}
void BoardCell::setWallEast(const bool& val) {
    m_wallEast = val;
}

const bool& BoardCell::hasWallWest() const {
    return m_wallWest;
}
void BoardCell::setWallWest(const bool& val) {
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
