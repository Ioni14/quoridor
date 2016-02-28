#include "Quoridor.h"

#include <memory>
#include "MainMenuState.h"

Quoridor::Quoridor() :
    m_state(nullptr),
    m_continue(true)
{
    initialize();
}

void Quoridor::quit()
{
    m_continue = false;
}

void Quoridor::setState(State::StatePtr newState)
{
    m_state = std::move(newState);
}

void Quoridor::initialize()
{
    m_state = std::make_unique<MainMenuState>(*this);
}

void Quoridor::run()
{
    while (m_continue) {
        m_state->handleEvents();
        m_state->update();
        m_state->render();
    }
}
