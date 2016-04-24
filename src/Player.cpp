#include "Player.h"

#include <cassert>
#include <iostream>
#include "Board.h"

namespace G36631 {

Player::Player() :
    Player(0, false, nullptr)
{
}

Player::Player(const int& numero, const bool& ia, IAStrategy::IAStrategyPtr iaStrategy) :
    m_iPos(-1),
    m_jPos(-1),
    m_numero(numero),
    m_nbWalls(0),
    m_IA(ia),
    m_iaStrategy(std::move(iaStrategy))
{
}

IAResponse Player::executeIA(Board& board, std::list<Player>& players)
{
    assert(m_iaStrategy != nullptr);
    IAResponse bestMove = m_iaStrategy->moveOrPutWall(board, m_numero, players);
    if (bestMove.type == IAResponse::Type::MOVE) {
        move(board, bestMove.bestI, bestMove.bestJ);
    } else {
        board.putWall(
            *this,
            bestMove.bestI,
            bestMove.bestJ,
            (bestMove.orientation == IAResponse::WallOrientation::HORIZONTAL)
                ? Board::WALL_ORIENTATION::HORIZONTAL
                : Board::WALL_ORIENTATION::VERTICAL
        );
    }
    m_lastShortestPath = board.calculateShortestPath(*this);
    return bestMove;
}

void Player::move(Board& board, const int& di, const int& dj)
{
    board.getCells()[m_iPos][m_jPos].setPlayer(nullptr);

    m_iPos += di;
    m_jPos += dj;

    board.getCells()[m_iPos][m_jPos].setPlayer(this);
}

bool Player::canMove(const Board& board, const int& iSource, const int& jSource, const int& di, const int& dj)
{
    // Tests si on ne sort pas du plateau
    if (iSource + di < 0 || iSource + di >= board.getSize()) {
        return false;
    }
    if (jSource + dj < 0 || jSource + dj >= board.getSize()) {
        return false;
    }

    auto& cells = board.getCells();
    // Tests s'il n'y a pas de mur entre les deux cellules
    if (di == 0) {
        if (dj <= -1 && cells[iSource][jSource].hasWallNorth()) {
            return false;
        }
        if (dj <= -2 && cells[iSource][jSource - 1].hasWallNorth()) {
            return false;
        }
        if (dj >= 1 && cells[iSource][jSource].hasWallSouth()) {
            return false;
        }
        if (dj >= 2 && cells[iSource][jSource + 1].hasWallSouth()) {
            return false;
        }
    }
    if (dj == 0) {
        if (di <= -1 && cells[iSource][jSource].hasWallWest()) {
            return false;
        }
        if (di <= -2 && cells[iSource - 1][jSource].hasWallWest()) {
            return false;
        }
        if (di >= 1 && cells[iSource][jSource].hasWallEast()) {
            return false;
        }
        if (di >= 2 && cells[iSource + 1][jSource].hasWallEast()) {
            return false;
        }
    }

    // Tests si la case d'arrivée est occupée
    if (cells[iSource + di][jSource + dj].hasPlayer()) {
        return false;
    }

    // Tests si joueur peut sauter un autre joueur (un joueur adjacent puis aucun mur)
    if (di == 0 && dj == -2 &&
        (!cells[iSource][jSource - 1].hasPlayer() ||
        cells[iSource + di][jSource + dj].hasWallSouth())) {
        return false;
    }
    if (di == 0 && dj == 2 &&
        (!cells[iSource][jSource + 1].hasPlayer() ||
        cells[iSource + di][jSource + dj].hasWallNorth())) {
        return false;
    }
    if (di == -2 && dj == 0 &&
        (!cells[iSource - 1][jSource].hasPlayer() ||
        cells[iSource + di][jSource + dj].hasWallEast())) {
        return false;
    }
    if (di == 2 && dj == 0 &&
        (!cells[iSource + 1][jSource].hasPlayer() ||
        cells[iSource + di][jSource + dj].hasWallWest())) {
        return false;
    }

    // On peut aller tout droit si on veut
    if ((di == 0 && std::abs(dj) <= 2) || (dj == 0 && std::abs(di) <= 2)) {
        return true;
    }

    if (di < -1 || di > 1 || dj < -1 || dj > 1) {
        return false;
    }

    // Tests si la diagonale est possible (tests sur les deux directions adjacentes
    // => joueur sur la 1ère case puis mur ou joueur

    // cas horizontaux
    if (cells[iSource + di][jSource].hasPlayer()
        && ((di == -1 && !cells[iSource][jSource].hasWallWest() && (cells[iSource + di][jSource].hasWallWest() || cells[iSource + di*2][jSource].hasPlayer()))
        || (di == 1 && !cells[iSource][jSource].hasWallEast() && (cells[iSource + di][jSource].hasWallEast() || cells[iSource + di*2][jSource].hasPlayer()))))
    {
        if (dj == -1 &&
            cells[iSource + di][jSource].hasWallNorth() &&
            cells[iSource][jSource].hasWallNorth()) {
            return false;
        } else if (dj == 1 &&
            cells[iSource + di][jSource].hasWallSouth() &&
            cells[iSource][jSource].hasWallSouth()) {
            return false;
        }
        if (dj == -1 &&
            cells[iSource + di][jSource].hasWallNorth() &&
            ((di == -1 && cells[iSource][jSource + dj].hasWallWest()) || (di == 1 && cells[iSource][jSource + dj].hasWallEast()))) {
            return false;
        }
        if (dj == 1 &&
            cells[iSource + di][jSource].hasWallSouth() &&
            ((di == -1 && cells[iSource][jSource + dj].hasWallWest()) || (di == 1 && cells[iSource][jSource + dj].hasWallEast()))) {
            return false;
        }
        return true;
    }

    // cas verticaux
    if (cells[iSource][jSource + dj].hasPlayer()
        && ((dj == -1 && !cells[iSource][jSource].hasWallNorth() && (cells[iSource][jSource + dj].hasWallNorth() || cells[iSource][jSource + dj*2].hasPlayer()))
        || (dj == 1 && !cells[iSource][jSource].hasWallSouth() && (cells[iSource][jSource + dj].hasWallSouth() || cells[iSource][jSource + dj*2].hasPlayer()))))
    {
        if (di == -1 &&
            cells[iSource][jSource + dj].hasWallWest() &&
            cells[iSource][jSource].hasWallWest()) {
            return false;
        } else if (di == 1 &&
            cells[iSource][jSource + dj].hasWallEast() &&
            cells[iSource][jSource].hasWallEast()) {
            return false;
        }
        if (di == -1 &&
            cells[iSource][jSource + dj].hasWallWest() &&
            ((dj == 1 && cells[iSource + di][jSource].hasWallSouth()) || (dj == -1 && cells[iSource + di][jSource].hasWallNorth()))) {
            return false;
        }
        if (di == 1 &&
            cells[iSource][jSource + dj].hasWallEast() &&
            ((dj == 1 && cells[iSource + di][jSource].hasWallSouth()) || (dj == -1 && cells[iSource + di][jSource].hasWallNorth()))) {
            return false;
        }
        return true;
    }

    // Aucun cas trouvé
    return false;
}

bool Player::canMove(const Board& board, const int& di, const int& dj) const
{
    return Player::canMove(board, m_iPos, m_jPos, di, dj);
}

}
