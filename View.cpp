#include "View.h"

View::View(State& model) :
    m_model(model)
{
    //m_model.addObserver(shared_from_this()); // shared_ptr<this>
}

void View::onNotify(const Observable& listener)
{
    render();
}
