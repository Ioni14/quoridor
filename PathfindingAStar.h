#ifndef PATHFINDINGASTAR_H
#define PATHFINDINGASTAR_H

#include <list>
#include <memory>
#include <vector>
#include "AbstractPathfinding.h"
#include "PathfindingAStarCell.h"

class PathfindingAStar : public AbstractPathfinding
{
public:
    PathfindingAStar(const Board& board);

    bool hasPath(const int& iSource, const int& jSource, const int& iDest, const int& jDest);

private:
    std::vector<const BoardCell*> findWalkableCells(const BoardCell& cellActual);

    std::list<PathfindingAStarCell::PathfindingAStarCellPtr>::reverse_iterator
    findCellInCloseList(const int& i, const int& j);

private:
    std::list<PathfindingAStarCell::PathfindingAStarCellPtr> m_openList;
    std::list<PathfindingAStarCell::PathfindingAStarCellPtr> m_closeList;

    static const int COST_MOVEMENT;
};

#endif // PATHFINDINGASTAR_H
