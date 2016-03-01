#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <list>
#include "Player.h"
#include "State.h"

class MainMenuState : public State
{
public:
    enum SUB_STATE {TITLE, MENU, PLAY, PLAYERS, BOARD_SIZE, SUMMARY};

public:
    MainMenuState(Quoridor& app);

    void render();
    void update();
    void handleEvents();

    void makeChoiceMenu();
    void makeChoicePlay();
    void makeChoicePlayers();
    void makeChoiceBoardSize();
    void makeChoiceSummary();

    std::string& getError() {
        return m_error;
    }
    const SUB_STATE& getSubState() const {
        return m_subState;
    }
    void setTitleEnded(const bool& val) {
        m_titleEnded = val;
    }
    void setWaitingChoiceMenu(const bool& val) {
        m_waitingChoiceMenu = val;
    }
    void setWaitingChoicePlay(const bool& val) {
        m_waitingChoicePlay = val;
    }
    void setWaitingChoicePlayers(const bool& val) {
        m_waitingChoicePlayers = val;
    }
    void setWaitingChoiceBoardSize(const bool& val) {
        m_waitingChoiceBoardSize = val;
    }
    void setWaitingChoiceSummary(const bool& val) {
        m_waitingChoiceSummary = val;
    }
    const int& getNbPlayers() const {
        return m_nbPlayers;
    }
    const int& getPlayerActual() const {
        return m_playerActual;
    }
    const std::list<Player>& getPlayers() const {
        return m_players;
    }
    const int& getBoardSize() const {
        return m_boardSize;
    }

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
