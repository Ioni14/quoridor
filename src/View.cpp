#include "View.h"

namespace G36631 {

View::View(State& model) :
    m_model(model)
{
}

void View::onNotify()
{
    render();
}

void View::onPlayersInitialized(const std::list<Player>& players)
{
}

}
