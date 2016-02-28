#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"

class MainMenuState : public State
{
public:
    MainMenuState(Quoridor& app);

    void render();
    void update();
    void handleEvents();

private:
    enum SUB_STATE {TITLE, MENU, PLAY};

private:
    SUB_STATE m_subState;

    std::string m_error;
    bool m_titleEnded;
    bool m_waitingChoiceMenu;
};

#endif // MAINMENUSTATE_H
