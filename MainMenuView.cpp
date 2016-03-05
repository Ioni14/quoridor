#include "MainMenuView.h"

#include <iostream>
#include "MainMenuState.h"

MainMenuView::MainMenuView(State &model) :
    View(model)
{
}

void MainMenuView::renderTitle()
{
    MainMenuState& state = static_cast<MainMenuState&>(m_model);
    std::cout << "Quoridor realise par Sweetdreams - 2016" << std::endl;
    std::cout << "Bienvenue sur Quoridor." << std::endl;
    state.setTitleEnded(true);
}

void MainMenuView::renderMenu()
{
    MainMenuState& state = static_cast<MainMenuState&>(m_model);
    std::cout << "----- Menu -----" << std::endl;
    std::cout << "1 - Jouer" << std::endl;
    std::cout << "2 - Quitter" << std::endl;
    std::cout << "Votre choix ? ";
    state.setWaitingChoiceMenu(true);
}

void MainMenuView::renderPlay()
{
    MainMenuState& state = static_cast<MainMenuState&>(m_model);
    std::cout << "----- Jouer -----" << std::endl;
    std::cout << "1 - 2 joueurs" << std::endl;
    std::cout << "2 - 4 joueurs" << std::endl;
    std::cout << "3 - Retour" << std::endl;
    std::cout << "Votre choix ? ";
    state.setWaitingChoicePlay(true);
}

void MainMenuView::renderPlayers()
{
    MainMenuState& state = static_cast<MainMenuState&>(m_model);
    std::cout << "----- " << state.getNbPlayers() << " Joueurs : J" << state.getPlayerActual() << " -----" << std::endl;
    std::cout << "1 - Joueur reel" << std::endl;
    std::cout << "2 - IA" << std::endl;
    std::cout << "3 - Retour" << std::endl;
    std::cout << "Votre choix ? ";
    state.setWaitingChoicePlayers(true);
}

void MainMenuView::renderBoardSize()
{
    MainMenuState& state = static_cast<MainMenuState&>(m_model);
    std::cout << "----- Taille du plateau -----" << std::endl;
    std::cout << "0 - Retour" << std::endl;
    std::cout << "Entrez la taille du plateau [5-19]" << std::endl;
    std::cout << "Votre choix ? ";
    state.setWaitingChoiceBoardSize(true);
}

void MainMenuView::renderSummary()
{
    MainMenuState& state = static_cast<MainMenuState&>(m_model);
    std::cout << "----- Resume -----" << std::endl;
    std::cout << state.getNbPlayers() << " Joueurs : ";
    for (auto& player : state.getPlayers()) {
        std::cout << (player.isIA() ? "IA" : "Reel");
        if (player.getNumero() < state.getNbPlayers()) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Taille du plateau : " << state.getBoardSize() << std::endl;
    std::cout << "1 - Lancer la partie" << std::endl;
    std::cout << "2 - Retour" << std::endl;
    std::cout << "Votre choix ? ";
    state.setWaitingChoiceSummary(true);
}

void MainMenuView::render()
{
    MainMenuState& state = static_cast<MainMenuState&>(m_model);

    std::cout << std::endl;
    if (!state.getError().empty()) {
        std::cerr << state.getError() << std::endl;
        state.getError().clear();
    }

    switch (state.getSubState()) {
        case MainMenuState::SUB_STATE::TITLE:
            renderTitle();
            break;
        case MainMenuState::SUB_STATE::MENU:
            renderMenu();
            break;
        case MainMenuState::SUB_STATE::PLAY:
            renderPlay();
            break;
        case MainMenuState::SUB_STATE::PLAYERS:
            renderPlayers();
            break;
        case MainMenuState::SUB_STATE::BOARD_SIZE:
            renderBoardSize();
            break;
        case MainMenuState::SUB_STATE::SUMMARY:
            renderSummary();
            break;
    }
}
