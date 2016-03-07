#include "PathfindingAStarCell.h"

namespace G36631 {

PathfindingAStarCell::PathfindingAStarCell(
        const int &heuristic,
        const BoardCell& boardCell) :
    PathfindingAStarCell(0, heuristic, nullptr, boardCell)
{
}

PathfindingAStarCell::PathfindingAStarCell(const int &costMovement,
        const int &heuristic,
        const AStarCellPtr *parent,
        const BoardCell& boardCell) :
    m_costMovement(costMovement),
    m_heuristic(heuristic),
    m_parent(parent),
    m_boardCell(boardCell)
{
}

}
