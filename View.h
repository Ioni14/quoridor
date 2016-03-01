#ifndef VIEW_H
#define VIEW_H

#include "State.h"
#include "Observer.h"

class View : public Observer//, public std::enable_shared_from_this<View>
{
public:
    typedef std::shared_ptr<View> ViewPtr;

public:
    View(State& model);

    virtual void onNotify(const Observable& listener);
    virtual void render() = 0;

protected:
    State& m_model;
};

#endif // VIEW_H
