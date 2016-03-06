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
    typedef std::list<PathfindingAStarCell::AStarCellPtr> listCellPtr;

public:
    PathfindingAStar(const Board& board);

    bool hasPath(const int& iSource, const int& jSource, const int& iDest, const int& jDest);

private:
    std::vector<const BoardCell*> findWalkableCells(const BoardCell& cellActual);
    PathfindingAStarCell::AStarCellPtr
    createStartCell(const int& iSource, const int& jSource, const int& iDest, const int& jDest);

    listCellPtr::iterator findLowestCell();
    listCellPtr::iterator findCellInOpenList(const int& i, const int& j);
    listCellPtr::reverse_iterator findCellInCloseList(const int& i, const int& j);

private:
    listCellPtr m_openList;
    listCellPtr m_closeList;

    static const int COST_MOVEMENT;
};

#endif // PATHFINDINGASTAR_H
