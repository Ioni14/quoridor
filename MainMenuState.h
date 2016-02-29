#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <list>
#include "Player.h"
#include "State.h"

class MainMenuState : public State
{
public:
    MainMenuState(Quoridor& app);

    void render();
    void update();
    void handleEvents();

private:
    enum SUB_STATE {TITLE, MENU, PLAY, PLAYERS, BOARD_SIZE, SUMMARY};

private:
    SUB_STATE m_subState;

    std::string m_error;
    bool m_titleEnded;
    bool m_waitingChoiceMenu;
    bool m_waitingChoicePlay;
    bool m_waitingChoicePlayers;
    bool m_waitingChoiceBoardSize;
    bool m_waitingChoiceSummary;

    int m_nbPlayers;
    int m_boardSize;
    int m_playerActual;

    std::list<Player> m_players;
};

#endif // MAINMENUSTATE_H
