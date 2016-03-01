#include "Quoridor.h"

#include <memory>
#include "MainMenuState.h"

Quoridor::Quoridor() :
    m_state(nullptr),
    m_newState(nullptr),
    m_view(nullptr),
    m_continue(true)
{
    initialize();
}

void Quoridor::quit()
{
    m_continue = false;
}

/**
 * @brief Quoridor::applyNewState
 * Procède au changement d'état après que l'ancien état ait fini son travail
 */
void Quoridor::applyNewState()
{
    if (m_newState == nullptr) {
        return;
    }
    m_state = std::move(m_newState);
    m_newState = nullptr;
}

void Quoridor::setState(State::StatePtr newState)
{
    m_newState = std::move(newState);
}

void Quoridor::setView(View::ViewPtr newView)
{
    m_view = newView;
}

void Quoridor::initialize()
{
    m_state = std::make_unique<MainMenuState>(*this);
    m_view = std::make_shared<MainMenuView>(*m_state);
    m_state->addObserver(m_view);
}

void Quoridor::run()
{
    while (m_continue) {
        m_state->handleEvents();
        m_state->update();
        m_state->render();
    }
}
