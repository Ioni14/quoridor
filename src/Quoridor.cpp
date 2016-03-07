#include "Quoridor.h"

#include <memory>
#include "MainMenuState.h"

namespace G36631 {

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
 * Procède au changement d'état après que l'ancien état a fini son travail
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
    auto newState = std::make_unique<MainMenuState>(*this);
    auto newView = std::make_shared<MainMenuView>(*newState);
    newState->addObserver(newView);
    setState(std::move(newState));
    setView(newView);
    applyNewState();
}

void Quoridor::run()
{
    while (m_continue) {
        m_state->handleEvents();
        m_state->update();
        m_state->render();
    }
}

}
