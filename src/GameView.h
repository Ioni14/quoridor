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
    void renderLoading();
    void renderAction();
    void renderMove();
    void renderWallCol();
    void renderWallRow();
    void renderWallDir();
    void renderWin();
};

#endif // GAMEVIEW_H
