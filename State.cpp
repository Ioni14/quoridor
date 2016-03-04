#include "State.h"

#include <iostream>
#include <sstream>

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

/**
 * @brief Reads the input in console and returns the entered integer
 * @return The entered integer or -1 if there's no integer
 */
int State::promptInteger()
{
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    int choice(0);
    iss >> choice;
    if (!iss || ! iss.eof()) {
        choice = -1;
    }
    return choice;
}
