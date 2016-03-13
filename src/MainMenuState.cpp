#include "MainMenuState.h"

#include <iostream>
#include <memory>
#include "Quoridor.h"
#include "GameState.h"

namespace G36631 {

MainMenuState::MainMenuState(Quoridor& app) :
    State(app),
    m_nbPlayers(0),
    m_boardSize(0),
    m_playerActual(0),
    m_players(0)
{
}

void MainMenuState::addPlayer(const int& numero, const bool& ia)
{
    m_players.push_back(Player(numero, ia));
}

void MainMenuState::launchGame(Observer* observer)
{
    auto newState = std::make_unique<GameState>(m_app, std::move(m_players), m_boardSize);
    newState->addObserver(observer);
    newState->initPlayers();
    m_app.setState(std::move(newState));
    m_app.applyNewState();
}

}
