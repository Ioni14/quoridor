#ifndef PATHFINDINGASTARCELL_H
#define PATHFINDINGASTARCELL_H

#include <memory>
#include "BoardCell.h"

class PathfindingAStarCell
{
public:
    typedef std::unique_ptr<PathfindingAStarCell> PathfindingAStarCellPtr;

public:
    PathfindingAStarCell(const int &heuristic, const BoardCell& boardCell);
    PathfindingAStarCell(const int& costMovement, const int& heuristic, const PathfindingAStarCellPtr* parent, const BoardCell& boardCell);

    int calcScore() const {
        return m_costMovement + m_heuristic;
    }
    const int& getCostMovement() const {
        return m_costMovement;
    }
    void setCostMovement(const int& costMovement) {
        m_costMovement = costMovement;
    }

    const int& getHeuristic() const {
        return m_heuristic;
    }
    void setHeuristic(const int& heuristic) {
        m_heuristic = heuristic;
    }

    const PathfindingAStarCellPtr* getParent() const {
        return m_parent;
    }
    void setParent(const PathfindingAStarCellPtr* parent) {
        m_parent = parent;
    }

    const BoardCell& getBoardCell() const {
        return m_boardCell;
    }

private:
    int m_costMovement;
    int m_heuristic;

    const PathfindingAStarCellPtr* m_parent;
    const BoardCell& m_boardCell;
};

#endif // PATHFINDINGASTARCELL_H
