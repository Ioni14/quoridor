#ifndef QUORIDOR_H
#define QUORIDOR_H

#include "State.h"
#include "MainMenuView.h"

class Quoridor
{
public:
    Quoridor();

    void run();
    void quit();

    void setState(State::StatePtr newState);
    void setView(View::ViewPtr newView);

    void applyNewState();

private:
    void initialize();

private:
    State::StatePtr m_state;
    State::StatePtr m_newState;
    View::ViewPtr m_view;

    bool m_continue;
};

#endif // QUORIDOR_H
