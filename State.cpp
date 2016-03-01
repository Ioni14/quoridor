#include "State.h"

State::State(Quoridor &app) :
    m_app(app)
{
}

void State::notifyObservers()
{
    for (auto& observer : m_observers) {
        observer->onNotify(*this);
    }
}
