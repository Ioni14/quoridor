#ifndef GAME_HPP
#define GAME_HPP

#include <list>
#include <algorithm>
#include <cassert>
#include <map>
#include <sstream>
#include "State.h"
#include "Board.h"
#include "Observable.h"

class GameState : public State
{
public:
    enum class SUB_STATE {LOADING, ACTION, MOVE, WALL_COL, WALL_ROW, WALL_DIR, WIN, DRAW};

public:
    GameState(Quoridor& app, std::list<Player> players, const int &boardSize);

    const SUB_STATE& getSubState() const {
        return m_subState;
    }
    std::string getError() const {
        return m_error.str();
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
    void setWaitingChoiceWin(const bool& val) {
        m_waitingChoiceWin = val;
    }
    void setWaitingChoiceDraw(const bool& val) {
        m_waitingChoiceDraw = val;
    }

    const Board& getBoard() const {
        return m_board;
    }
    Player& getPlayerActual() {
        auto itPlayer = std::find_if(m_players.begin(), m_players.end(),
            [this](const Player& player) -> bool {
                return m_playerActual == player.getNumero();
            }
        );
        assert(itPlayer != m_players.end());
        return *itPlayer;
    }
    void addMoveChoice(const int& num, std::vector<int> coords) {
        m_moveChoices.insert(std::make_pair(num, coords));
    }

private:
    void render();
    void update();
    void handleEvents();

    void initPlayers();
    bool hasWon(const Player& player) const;

    void makeChoiceAction();
    void makeChoiceMove();
    void makeChoiceWallCol();
    void makeChoiceWallRow();
    void makeChoiceWallDir();
    void finishGame();

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
    std::map<int, std::vector<int>> m_moveChoices;

    std::ostringstream m_error;
    bool m_loadingEnded;
    bool m_waitingChoiceAction;
    bool m_waitingChoiceMove;
    bool m_waitingChoiceWallCol;
    bool m_waitingChoiceWallRow;
    bool m_waitingChoiceWallDir;
    bool m_waitingChoiceWin;
    bool m_waitingChoiceDraw;
};

#endif // GAME_HPP
