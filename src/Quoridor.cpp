#include "Quoridor.h"

#include <memory>
#include "MainMenuState.h"

namespace G36631 {

Quoridor::Quoridor() :
    m_state(nullptr),
    m_newState(nullptr)
{
    initialize();
}

/**
 * @brief Quoridor::applyNewState
 * Procède au changement d'état après que l'ancien état a fini son travail
 */
void Quoridor::applyNewState()
{
    if (m_newState == nullptr) {
        return;
    }
    m_state = std::move(m_newState);
    m_newState = nullptr;

    m_state->fireActivated();
}

void Quoridor::setState(State::StatePtr newState)
{
    m_newState = std::move(newState);
}

State::StatePtr& Quoridor::getState()
{
    return m_state;
}

void Quoridor::initialize()
{
    auto newState = std::make_unique<MainMenuState>(*this);
    setState(std::move(newState));
    applyNewState();
}

void Quoridor::reset()
{
    initialize();
}

}
