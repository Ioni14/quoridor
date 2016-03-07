#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "View.h"
#include "GameState.h"

class GameView : public View
{
public:
    GameView(GameState& model);

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
    void renderDraw();
};

#endif // GAMEVIEW_H
