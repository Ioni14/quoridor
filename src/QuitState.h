#ifndef QUITSTATE_H
#define QUITSTATE_H

#include "State.h"

class QuitState : public State
{
public:
    QuitState(Quoridor& app);

    void render();
    void update();
    void handleEvents();
};

#endif // QUITSTATE_H
