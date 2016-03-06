#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <memory>
#include <vector>
#include "Observer.h"

class Observable
{
public:
    void addObserver(Observer::ObserverPtr observer);
    void removeObserver(Observer::ObserverPtr observer);

    virtual ~Observable() = default;

protected:
    std::vector<Observer::ObserverPtr> m_observers;
};

#endif // OBSERVABLE_H
