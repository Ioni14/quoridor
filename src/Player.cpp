#include "Player.h"

#include "Board.h"

namespace G36631 {

Player::Player() :
    Player(0)
{
}

Player::Player(const int& numero, const bool& ia) :
    m_iPos(-1),
    m_jPos(-1),
    m_numero(numero),
    m_nbWalls(0),
    m_IA(ia)
{
}

void Player::move(Board& board, const int& di, const int& dj)
{
    board.getCells()[m_iPos][m_jPos].setPlayer(nullptr);

    m_iPos += di;
    m_jPos += dj;

    board.getCells()[m_iPos][m_jPos].setPlayer(this);
}

bool Player::canMove(const Board& board, const int& di, const int& dj) const
{
    // Tests si on ne sort pas du plateau
    if (m_iPos + di < 0 || m_iPos + di >= board.getSize()) {
        return false;
    }
    if (m_jPos + dj < 0 || m_jPos + dj >= board.getSize()) {
        return false;
    }

    auto cells = board.getCells();

    // Tests s'il n'y a pas de mur entre les deux cellules
    if (di == 0 && dj == -1 && cells[m_iPos][m_jPos].hasWallNorth()) { // mur Nord
        return false;
    }
    if (di == 0 && dj == 1 && cells[m_iPos][m_jPos].hasWallSouth()) { // mur Sud
        return false;
    }
    if (di == -1 && dj == 0 && cells[m_iPos][m_jPos].hasWallWest()) { // mur Ouest
        return false;
    }
    if (di == 1 && dj == 0 && cells[m_iPos][m_jPos].hasWallEast()) { // mur Est
        return false;
    }

    // Tests si la case d'arrivée est occupée
    if (cells[m_iPos + di][m_jPos + dj].hasPlayer()) {
        return false;
    }

    // Tests si joueur peut sauter un autre joueur (un joueur adjacent puis aucun mur)
    if (di == 0 && dj == -2 &&
        (!cells[m_iPos][m_jPos - 1].hasPlayer() ||
        cells[m_iPos + di][m_jPos + dj].hasWallSouth())) {
        return false;
    }
    if (di == 0 && dj == 2 &&
        (!cells[m_iPos][m_jPos + 1].hasPlayer() ||
        cells[m_iPos + di][m_jPos + dj].hasWallNorth())) {
        return false;
    }
    if (di == -2 && dj == 0 &&
        (!cells[m_iPos - 1][m_jPos].hasPlayer() ||
        cells[m_iPos + di][m_jPos + dj].hasWallEast())) {
        return false;
    }
    if (di == 2 && dj == 0 &&
        (!cells[m_iPos + 1][m_jPos].hasPlayer() ||
        cells[m_iPos + di][m_jPos + dj].hasWallWest())) {
        return false;
    }

    // On peut aller tout droit si on veut
    if (di == 0 || dj == 0) {
        return true;
    }

    // Tests si la diagonale est possible (tests sur les deux directions adjacentes
    // => joueur sur la 1ère case puis mur ou joueur

    // cas horizontaux
    if (cells[m_iPos + di][m_jPos].hasPlayer()
        && ((di == -1 && (cells[m_iPos + di][m_jPos].hasWallWest() || cells[m_iPos + di*2][m_jPos].hasPlayer()))
        || (di == 1 && (cells[m_iPos + di][m_jPos].hasWallEast() || cells[m_iPos + di*2][m_jPos].hasPlayer()))))
    {
        if (dj == -1 &&
            cells[m_iPos + di][m_jPos].hasWallNorth() &&
            cells[m_iPos][m_jPos].hasWallNorth()) {
            return false;
        } else if (dj == 1 &&
            cells[m_iPos + di][m_jPos].hasWallSouth() &&
            cells[m_iPos][m_jPos].hasWallSouth()) {
            return false;
        }
        return true;
    }

    // cas verticaux
    if (cells[m_iPos][m_jPos + dj].hasPlayer()
        && ((dj == -1 && (cells[m_iPos][m_jPos + dj].hasWallNorth() || cells[m_iPos][m_jPos + dj*2].hasPlayer()))
        || (dj == 1 && (cells[m_iPos][m_jPos + dj].hasWallSouth() || cells[m_iPos][m_jPos + dj*2].hasPlayer()))))
    {
        if (di == -1 &&
            cells[m_iPos][m_jPos + dj].hasWallWest() &&
            cells[m_iPos][m_jPos].hasWallWest()) {
            return false;
        } else if (di == 1 &&
            cells[m_iPos][m_jPos + dj].hasWallEast() &&
            cells[m_iPos][m_jPos].hasWallEast()) {
            return false;
        }
        return true;
    }

    // Aucun cas trouvé
    return false;
}

}
