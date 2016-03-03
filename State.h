#ifndef STATE_H
#define STATE_H

#include <memory>
#include "Observable.h"

class Quoridor;

class State : public Observable
{
public:
    typedef std::unique_ptr<State> StatePtr;

public:
    State(Quoridor& app);
    virtual ~State() = default;

    virtual void render() = 0;
    virtual void update() = 0;
    virtual void handleEvents() = 0;

    void notifyObservers();

protected:
    Quoridor& m_app;
};

#endif // STATE_H
