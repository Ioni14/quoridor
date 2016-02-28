#ifndef ABSTRACTPATHFINDING_H
#define ABSTRACTPATHFINDING_H

class Board;

class AbstractPathfinding
{
public:
    AbstractPathfinding(const Board& board);

    virtual bool hasPath(const int& iSource,
                         const int& jSource,
                         const int& iDest,
                         const int& jDest) = 0;

protected:
    const Board& m_board;
};

#endif // ABSTRACTPATHFINDING_H
