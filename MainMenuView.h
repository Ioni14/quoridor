#ifndef MAINMENUVIEW_H
#define MAINMENUVIEW_H

#include "View.h"

class MainMenuView : public View
{
public:
    MainMenuView(State& model);

    void render();

private:
    void renderTitle();
    void renderMenu();
    void renderPlay();
    void renderPlayers();
    void renderBoardSize();
    void renderSummary();

};

#endif // MAINMENUVIEW_H
