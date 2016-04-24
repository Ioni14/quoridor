#include "PathfindingAStar.h"

#include <algorithm>
#include <iostream>
#include "Board.h"
#include "BoardCell.h"
#include "PathfindingAStarCell.h"

namespace G36631 {

int PathfindingAStar::count = 0;

const int PathfindingAStar::COST_MOVEMENT = 1;

PathfindingAStar::PathfindingAStar(const Board& board) :
    AbstractPathfinding(board)
{
}

PathfindingAStarCell::AStarCellPtr
PathfindingAStar::createStartCell(const int& iSource, const int& jSource, const int& iDest, const int& jDest)
{
    int heuristic = static_cast<int>(std::abs(iDest - iSource) + std::abs(jDest - jSource));
    return std::make_unique<PathfindingAStarCell>(
        heuristic,
        &(m_board.getCells()[iSource][jSource])
    );
}

PathfindingAStar::listCellPtr::iterator PathfindingAStar::findLowestCell()
{
    auto itMinCell = m_openList.end();
    int minScore(-1);
    for (auto it = m_openList.begin(); it != m_openList.end(); ++it) {
        auto score = (*it)->calcScore();
        if (itMinCell == m_openList.end() || score < minScore) {
            minScore = score;
            itMinCell = it;
        }
    }
    return itMinCell;
}

bool PathfindingAStar::hasPath(const int& iSource, const int& jSource, const int& iDest, const int& jDest, std::list<const BoardCell*>& shortestPath)
{
    count++;

    shortestPath.clear();
    m_openList.clear();
    m_closeList.clear();

    m_openList.push_back(createStartCell(iSource, jSource, iDest, jDest));

    // On stoppera quand il n'y aura plus de cellule à visiter
    while (!m_openList.empty())
    {
        // On parcourt la openList et on récupère la cellule au plus petit score
        auto itMinCell = findLowestCell();

        // On a trouvé la prochaine cellule qui semble être la plus proche de l'arrivée
        // => On l'ajoute à la closeList et on l'enlève de la openList
        m_closeList.push_back(std::move(*itMinCell));
        m_openList.erase(itMinCell);

        // On vérifie si la destination se trouve dans la closeList
        auto itCloseListDest = findCellInCloseList(iDest, jDest);
        if (itCloseListDest != m_closeList.rend()) {

            const PathfindingAStarCell::AStarCellPtr* cellParent = &(*itCloseListDest);
            shortestPath.push_back((*cellParent)->getBoardCell());
            while ((*cellParent)->getBoardCell()->getIPos() != iSource
                   || (*cellParent)->getBoardCell()->getJPos() != jSource) {
                cellParent = (*cellParent)->getParent();
                shortestPath.push_back((*cellParent)->getBoardCell());
            }

            return true;
        }

        // On récupère la cellule actuelle (la dernière ajoutée à closeList)
        auto& minCell = m_closeList.back();
        const BoardCell* cellActual = minCell->getBoardCell();

        auto walkableCells = findWalkableCells(cellActual);

        for (auto itBoardCell = walkableCells.begin(); itBoardCell != walkableCells.end(); ++itBoardCell) {

            auto itCloseList = findCellInCloseList((*itBoardCell)->getIPos(), (*itBoardCell)->getJPos());
            if (itCloseList != m_closeList.rend()) {
                continue;
            }

            auto itOpenList = findCellInOpenList((*itBoardCell)->getIPos(), (*itBoardCell)->getJPos());

            int costMovementActual = minCell->getCostMovement() + COST_MOVEMENT;
            // Heuristique simple : distance Manhattan entre la cellule joignable et l'arrivée
            int heuristicActual = static_cast<int>(std::abs(iDest - (*itBoardCell)->getIPos()) + std::abs(jDest - (*itBoardCell)->getJPos()));

            if (itOpenList == m_openList.end()) {
                PathfindingAStarCell::AStarCellPtr aStarCell = std::make_unique<PathfindingAStarCell>(
                    costMovementActual,
                    heuristicActual,
                    &minCell,
                    *itBoardCell
                );
                m_openList.push_back(std::move(aStarCell));
            } else {
                if (costMovementActual + heuristicActual < minCell->calcScore()) {
                    (*itOpenList)->setCostMovement(costMovementActual);
                    (*itOpenList)->setHeuristic(heuristicActual);
                    (*itOpenList)->setParent(&minCell);
                }
            }
        }
    } // fin while

    return false;
}

std::vector<const BoardCell*> PathfindingAStar::findWalkableCells(const BoardCell* cellActual)
{
    auto& cells = m_board.getCells();

    int moves[12][2] = {
        {-1, -1},
        { 0, -1},
        { 1, -1},
        {-1,  0},
        { 1,  0},
        {-1,  1},
        { 0,  1},
        { 1,  1},
        { 0, -2},
        { 0,  2},
        {-2,  0},
        { 2,  0},
    };

    // On groupe les cellules atteignables
    std::vector<const BoardCell*> walkableCells(0);
    for (int i = 0; i < 12; ++i) {
        if (Player::canMove(m_board, cellActual->getIPos(), cellActual->getJPos(), moves[i][0], moves[i][1])) {
            walkableCells.push_back(&(cells[cellActual->getIPos() + moves[i][0]][cellActual->getJPos() + moves[i][1]]));
        }
    }

    return walkableCells;
}

PathfindingAStar::listCellPtr::reverse_iterator
PathfindingAStar::findCellInCloseList(const int& i, const int& j)
{
    return std::find_if(m_closeList.rbegin(), m_closeList.rend(),
        // Lambda fonction pour trouver si la cellule est dans la closeList
        [i, j](const PathfindingAStarCell::AStarCellPtr& cell) -> bool {
            return i == cell->getBoardCell()->getIPos() &&
                   j == cell->getBoardCell()->getJPos();
        }
    );
}

PathfindingAStar::listCellPtr::iterator
PathfindingAStar::findCellInOpenList(const int& i, const int& j)
{
    return std::find_if(m_openList.begin(), m_openList.end(),
        // Lambda fonction pour trouver si la cellule est dans la openList
        [i, j](const PathfindingAStarCell::AStarCellPtr& cell) -> bool {
            return i == cell->getBoardCell()->getIPos() &&
                   j == cell->getBoardCell()->getJPos();
        }
    );
}

}
