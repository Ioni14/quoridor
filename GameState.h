#ifndef GAME_HPP
#define GAME_HPP

#include <list>
#include <algorithm>
#include <cassert>
#include "State.h"
#include "Board.h"
#include "Observable.h"

class GameState : public State
{
public:
    enum SUB_STATE {LOADING, ACTION, MOVE, WALL_COL, WALL_ROW, WALL_DIR};

public:
    GameState(Quoridor& app, std::list<Player> players, const int &boardSize);

    const SUB_STATE& getSubState() const {
        return m_subState;
    }
    std::string& getError() {
        return m_error;
    }
    void setWaitingChoiceEnded(const bool& val) {
        m_loadingEnded = val;
    }
    void setWaitingChoiceAction(const bool& val) {
        m_waitingChoiceAction = val;
    }
    void setWaitingChoiceMove(const bool& val) {
        m_waitingChoiceMove = val;
    }
    void setWaitingChoiceWallCol(const bool& val) {
        m_waitingChoiceWallCol = val;
    }
    void setWaitingChoiceWallRow(const bool& val) {
        m_waitingChoiceWallRow = val;
    }
    void setWaitingChoiceWallDir(const bool& val) {
        m_waitingChoiceWallDir = val;
    }

    const Board& getBoard() const {
        return m_board;
    }
    const Player& getPlayerActual() const {
        return getPlayerActual();
    }

private:
    void render();
    void update();
    void handleEvents();

    void initPlayers();

    Player& getPlayerActual() {
        auto itPlayer = std::find_if(m_players.begin(), m_players.end(),
            [this](const Player& player) -> bool {
                return m_playerActual == player.getNumero();
            }
        );
        assert(itPlayer != m_players.end());
        return *itPlayer;
    }

private:
    SUB_STATE m_subState;

    Board m_board;
    std::list<Player> m_players;
    int m_nbPlayers;
    int m_nbWallsAtStart;
    int m_playerActual;
    int m_wallCol;
    int m_wallRow;
    Board::WALL_ORIENTATION m_wallDir;

    std::string m_error;
    bool m_loadingEnded;
    bool m_waitingChoiceAction;
    bool m_waitingChoiceMove;
    bool m_waitingChoiceWallCol;
    bool m_waitingChoiceWallRow;
    bool m_waitingChoiceWallDir;
};

#endif // GAME_HPP
