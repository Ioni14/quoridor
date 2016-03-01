#ifndef GAME_HPP
#define GAME_HPP

#include <list>
#include "State.h"
#include "Board.h"
#include "Observable.h"

class GameState : public State
{
public:
    GameState(Quoridor& app, std::list<Player> players, const int &boardSize);

private:
    void render();
    void update();
    void handleEvents();

    void initPlayers();

private:
    Board m_board;
    std::list<Player> m_players;
    int m_nbPlayers;
    int m_nbWallsAtStart;

    bool m_loadingRendered;
};

#endif // GAME_HPP
