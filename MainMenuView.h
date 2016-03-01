#ifndef MAINMENUVIEW_H
#define MAINMENUVIEW_H

#include "View.h"

class MainMenuView : public View
{
public:
    MainMenuView(State& model);

    void render();
};

#endif // MAINMENUVIEW_H
