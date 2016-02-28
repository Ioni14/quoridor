#include "MainMenuState.h"

#include <iostream>
#include <memory>
#include "Quoridor.h"
#include "QuitState.h"

MainMenuState::MainMenuState(Quoridor& app) :
    State(app),
    m_subState(SUB_STATE::TITLE),
    m_error(""),
    m_titleEnded(false),
    m_waitingChoiceMenu(false)
{
}

void MainMenuState::render()
{
    switch (m_subState) {
    case SUB_STATE::TITLE:
        std::cout << "Quoridor by Sweetdreams - 2016" << std::endl;
        std::cout << "Bienvenue sur Quoridor." << std::endl;
        m_titleEnded = true;
        break;
    case SUB_STATE::MENU:
        std::cout << std::endl;
        if (!m_error.empty()) {
            std::cout << m_error << std::endl;
        }
        std::cout << "----- Menu -----" << std::endl;
        std::cout << "1 - Jouer" << std::endl;
        std::cout << "2 - Quitter" << std::endl;
        std::cout << "Votre choix ? ";
        m_waitingChoiceMenu = true;
        break;
    case SUB_STATE::PLAY:







        break;
    }
}

void MainMenuState::update()
{
    if (m_titleEnded) {
        m_titleEnded = false;
        m_subState = SUB_STATE::MENU;
    }
}

void MainMenuState::handleEvents()
{
    int choice(0);

    if (m_waitingChoiceMenu) {
        std::cin >> choice;
        m_waitingChoiceMenu = false;
        switch (choice) {
        case 1:
            m_subState = SUB_STATE::PLAY;
            break;
        case 2:
            {
                StatePtr newState = std::make_unique<QuitState>(m_app);
                m_app.setState(std::move(newState));
            }
            break;
        default:
            m_error = "Veuillez taper 1 ou 2.";
        }
    }
}
