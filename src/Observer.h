#ifndef OBSERVER_H
#define OBSERVER_H

#include <memory>

class Observable;

class Observer
{
public:
    typedef std::shared_ptr<Observer> ObserverPtr;

public:
    virtual ~Observer() = default;
    virtual void onNotify(const Observable& listener) = 0;
};

#endif // OBSERVER_H
