#include "QuitState.h"

#include <iostream>
#include "Quoridor.h"

QuitState::QuitState(Quoridor& app):
    State(app)
{
}

void QuitState::render()
{
}

void QuitState::update()
{
    m_app.quit();
}

void QuitState::handleEvents()
{
}
