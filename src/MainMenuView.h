#ifndef MAINMENUVIEW_H
#define MAINMENUVIEW_H

#include "View.h"
#include "MainMenuState.h"

class MainMenuView : public View
{
public:
    MainMenuView(MainMenuState& model);

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
