#include "State.h"

#include <iostream>
#include <sstream>

namespace G36631 {

State::State(Quoridor &app) :
    m_app(app)
{
}

void State::notifyObservers()
{
    for (auto& observer : m_observers) {
        observer->onNotify();
    }
}

int State::promptInteger()
{
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    int choice(0);
    iss >> choice;
    if (!iss || !iss.eof()) {
        choice = -1;
    }
    return choice;
}

}
