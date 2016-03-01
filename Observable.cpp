#include "Observable.h"

#include <algorithm>

void Observable::addObserver(Observer::ObserverPtr observer)
{
    m_observers.push_back(observer);
}

void Observable::removeObserver(Observer::ObserverPtr observer)
{
    auto it = std::find(m_observers.begin(), m_observers.end(), observer);
    if (it == m_observers.end()) {
        return;
    }
    m_observers.erase(it);
}
