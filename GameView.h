#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "View.h"

class GameView : public View
{
public:
    GameView(State& model);

    void render();
};

#endif // GAMEVIEW_H
