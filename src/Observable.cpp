#include "Observable.h"

#include <algorithm>

namespace G36631 {

void Observable::addObserver(Observer *observer)
{
    m_observers.push_back(observer);
}

void Observable::removeObserver(Observer *observer)
{
    auto it = std::find(m_observers.begin(), m_observers.end(), observer);
    if (it == m_observers.end()) {
        return;
    }
    m_observers.erase(it);
}

}
