#include "PathfindingAStar.h"

#include <algorithm>
#include "Board.h"
#include "BoardCell.h"
#include "PathfindingAStarCell.h"

const int PathfindingAStar::COST_MOVEMENT = 1;

PathfindingAStar::PathfindingAStar(const Board& board) :
    AbstractPathfinding(board)
{
}

/*
 * Nous aurions pu utiliser des std::weak_ptr et std::shared_ptr au lieu de std::unique_ptr
 * Pour éviter d'avoir des pointeurs de std::unique_ptr
 * Mais nous avons privilégié les performances
 */
bool PathfindingAStar::hasPath(const int& iSource, const int& jSource, const int& iDest, const int& jDest)
{
    auto& cells = m_board.getCells();

    {
        int heuristic = static_cast<int>(std::abs(iDest - iSource) + std::abs(jDest - jSource));
        PathfindingAStarCell::PathfindingAStarCellPtr aStarCell = std::make_unique<PathfindingAStarCell>(
            heuristic,
            cells[iSource][jSource]
        );
        m_openList.push_back(std::move(aStarCell));
    }

    while (!m_openList.empty())
    {
        // On parcourt la openList et on récupère la cellule au plus petit score
        auto itMinCell = m_openList.end();
        int minScore(-1);
        for (auto it = m_openList.begin(); it != m_openList.end(); ++it) {
            auto score = (*it)->calcScore();
            if (itMinCell == m_openList.end() || score < minScore) {
                minScore = score;
                itMinCell = it;
            }
        }

        if (itMinCell == m_openList.end()) {
            // Pas de chemin
            return false;
        }

        // On a trouvé la prochaine cellule qui semble être la plus proche de l'arrivée
        // => On l'ajoute à la closeList et on l'enlève de la openList
        m_closeList.push_back(std::move(*itMinCell));
        m_openList.erase(itMinCell);

        {
            // On vérifie si la destination se trouve dans la closeList
            auto itCloseListDest = findCellInCloseList(iDest, jDest);
            // A-t-on trouvé un chemin ?
            if (itCloseListDest != m_closeList.rend()) {
                return true;
            }
        }

        // On récupère la cellule actuelle (la dernière ajoutée à closeList)
        auto& minCell = m_closeList.back();
        auto& cellActual = minCell->getBoardCell();

        // Pour chaque cellules qu'on peut atteindre
        auto walkableCells = findWalkableCells(cellActual);

        // => On calcule son score et on l'ajoute dans la openList si pas déjà fait
        for (auto itBoardCell = walkableCells.begin(); itBoardCell != walkableCells.end(); ++itBoardCell) {

            // Dans closeList ?
            {
                auto itCloseList = findCellInCloseList((*itBoardCell)->getIPos(), (*itBoardCell)->getJPos());
                // On l'ignore si elle est dans la closeList
                if (itCloseList != m_closeList.rend()) {
                    continue;
                }
            }

            // Dans openList ?
            auto itOpenList = std::find_if(m_openList.begin(), m_openList.end(),
                // Lambda fonction pour trouver si la cellule est dans la openList
                [itBoardCell](const PathfindingAStarCell::PathfindingAStarCellPtr& cell) -> bool {
                    return (*itBoardCell)->getIPos() == cell->getBoardCell().getIPos() &&
                           (*itBoardCell)->getJPos() == cell->getBoardCell().getJPos();
                }
            );

            int costMovementActual = minCell->getCostMovement() + COST_MOVEMENT;
            // Heuristique simple : distance Manhattan entre la cellule joignable et l'arrivée
            int heuristicActual = static_cast<int>(std::abs(iDest - (*itBoardCell)->getIPos()) + std::abs(jDest - (*itBoardCell)->getJPos()));

            if (itOpenList == m_openList.end()) {
                // Pas dans la openList
                PathfindingAStarCell::PathfindingAStarCellPtr aStarCell = std::make_unique<PathfindingAStarCell>(
                    costMovementActual,
                    heuristicActual,
                    &minCell,
                    *(*itBoardCell)
                );
                m_openList.push_back(std::move(aStarCell));
            } else {
                // Déjà dans la openList
                if (costMovementActual + heuristicActual < minCell->calcScore()) {
                    // On a trouvé un meilleur chemin qui passe par cette cellule
                    (*itOpenList)->setCostMovement(costMovementActual);
                    (*itOpenList)->setHeuristic(heuristicActual);
                    (*itOpenList)->setParent(&minCell);
                }
            }
        }
    } // fin while

    return false;
}

std::vector<const BoardCell*> PathfindingAStar::findWalkableCells(const BoardCell& cellActual)
{
    auto& cells = m_board.getCells();

    // On groupe les cellules atteignables
    std::vector<const BoardCell*> walkableCells(0);
    if (cellActual.getIPos() + 1 < m_board.getSize() && !cellActual.hasWallEast()) {
        // On peut aller à droite
        walkableCells.push_back(&(cells[cellActual.getIPos() + 1][cellActual.getJPos()]));
    }
    if (cellActual.getJPos() + 1 < m_board.getSize() && !cellActual.hasWallSouth()) {
        // On peut aller en bas
        walkableCells.push_back(&(cells[cellActual.getIPos()][cellActual.getJPos() + 1]));
    }
    if (cellActual.getIPos() - 1 >= 0 && !cellActual.hasWallWest()) {
        // On peut aller à gauche
        walkableCells.push_back(&(cells[cellActual.getIPos() - 1][cellActual.getJPos()]));
    }
    if (cellActual.getJPos() - 1 >= 0 && !cellActual.hasWallNorth()) {
        // On peut aller en haut
        walkableCells.push_back(&(cells[cellActual.getIPos()][cellActual.getJPos() - 1]));
    }

    return walkableCells;
}

std::list<PathfindingAStarCell::PathfindingAStarCellPtr>::reverse_iterator
PathfindingAStar::findCellInCloseList(const int& i, const int& j)
{
    return std::find_if(m_closeList.rbegin(), m_closeList.rend(),
        // Lambda fonction pour trouver si la cellule est dans la openList
        [i, j](const PathfindingAStarCell::PathfindingAStarCellPtr& cell) -> bool {
            return i == cell->getBoardCell().getIPos() &&
                   j == cell->getBoardCell().getJPos();
        }
    );
}
