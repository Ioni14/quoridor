#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "View.h"

class GameView : public View
{
public:
    GameView(State& model);

    void render();

private:
    void renderBoard();
};

#endif // GAMEVIEW_H
