#ifndef QUORIDOR_H
#define QUORIDOR_H

#include "State.h"

class Quoridor
{
public:
    Quoridor();

    void run();
    void quit();

    void setState(State::StatePtr newState);

private:
    void initialize();

private:
    State::StatePtr m_state;

    bool m_continue;
};

#endif // QUORIDOR_H
