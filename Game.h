#ifndef GAME_HPP
#define GAME_HPP

#include <list>
#include "Board.h"

class Game
{
public:
    Game(const int &boardSize, const int& nbPlayers);

    void run();

private:
    void render();
    void update();
    void handleEvents();

    void initPlayers();

private:
    Board m_board;
    std::list<Player> m_players;
    int m_nbPlayers;

    bool m_continue;
};

#endif // GAME_HPP
