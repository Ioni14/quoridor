#ifndef STATE_H
#define STATE_H

#include <memory>
class Quoridor;

class State
{
public:
    typedef std::unique_ptr<State> StatePtr;

public:
    State(Quoridor& app);

    virtual void render() = 0;
    virtual void update() = 0;
    virtual void handleEvents() = 0;

protected:
    Quoridor& m_app;
};

#endif // STATE_H