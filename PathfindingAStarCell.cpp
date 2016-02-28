#include "PathfindingAStarCell.h"

PathfindingAStarCell::PathfindingAStarCell(
        const int &heuristic,
        const BoardCell& boardCell) :
    PathfindingAStarCell(0, heuristic, nullptr, boardCell)
{
}

PathfindingAStarCell::PathfindingAStarCell(
        const int &costMovement,
        const int &heuristic,
        const std::unique_ptr<PathfindingAStarCell>* parent,
        const BoardCell& boardCell) :
    m_costMovement(costMovement),
    m_heuristic(heuristic),
    m_parent(parent),
    m_boardCell(boardCell)
{
}
