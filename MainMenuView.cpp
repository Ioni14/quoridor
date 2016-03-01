#include "MainMenuView.h"

#include <iostream>
#include "MainMenuState.h"

MainMenuView::MainMenuView(State &model) :
    View(model)
{
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
            std::cout << "Quoridor by Sweetdreams - 2016" << std::endl;
            std::cout << "Bienvenue sur Quoridor." << std::endl;
            state.setTitleEnded(true);
            break;
        case MainMenuState::SUB_STATE::MENU:
            std::cout << "----- Menu -----" << std::endl;
            std::cout << "1 - Jouer" << std::endl;
            std::cout << "2 - Quitter" << std::endl;
            std::cout << "Votre choix ? ";
            state.setWaitingChoiceMenu(true);
            break;
        case MainMenuState::SUB_STATE::PLAY:
            std::cout << "----- Jouer -----" << std::endl;
            std::cout << "1 - 2 joueurs" << std::endl;
            std::cout << "2 - 4 joueurs" << std::endl;
            std::cout << "3 - Retour" << std::endl;
            std::cout << "Votre choix ? ";
            state.setWaitingChoicePlay(true);
            break;
        case MainMenuState::SUB_STATE::PLAYERS:
            std::cout << "----- " << state.getNbPlayers() << " Joueurs : J" << state.getPlayerActual() << " -----" << std::endl;
            std::cout << "1 - Joueur reel" << std::endl;
            std::cout << "2 - IA" << std::endl;
            std::cout << "3 - Retour" << std::endl;
            std::cout << "Votre choix ? ";
            state.setWaitingChoicePlayers(true);
            break;
        case MainMenuState::SUB_STATE::BOARD_SIZE:
            std::cout << "----- Taille du plateau -----" << std::endl;
            std::cout << "0 - Retour" << std::endl;
            std::cout << "Entrez la taille du plateau [5-19]" << std::endl;
            std::cout << "Votre choix ? ";
            state.setWaitingChoiceBoardSize(true);
            break;
        case MainMenuState::SUB_STATE::SUMMARY:
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
            break;
    }
}
