#include "MainMenuState.h"

#include <iostream>
#include <memory>
#include "Quoridor.h"
#include "QuitState.h"
#include "GameState.h"
#include "GameView.h"

MainMenuState::MainMenuState(Quoridor& app) :
    State(app),
    m_subState(SUB_STATE::TITLE),
    m_error(""),
    m_titleEnded(false),
    m_waitingChoiceMenu(false),
    m_waitingChoicePlay(false),
    m_waitingChoicePlayers(false),
    m_waitingChoiceBoardSize(false),
    m_waitingChoiceSummary(false),
    m_nbPlayers(0),
    m_boardSize(0),
    m_playerActual(0),
    m_players(0)
{
}

void MainMenuState::render()
{
    notifyObservers();
}

void MainMenuState::update()
{
    if (m_titleEnded) {
        m_titleEnded = false;
        m_subState = SUB_STATE::MENU;
    }
}

void MainMenuState::makeChoiceMenu()
{
    int choice(0);
    std::cin >> choice;
    switch (choice) {
        case 1:
            m_subState = SUB_STATE::PLAY;
            break;
        case 2:
            {
                StatePtr newState = std::make_unique<QuitState>(m_app);
                m_app.setState(std::move(newState));
                m_app.applyNewState();
                return;
            }
            break;
        default:
            m_error = "Veuillez taper 1 ou 2.";
    }
}

void MainMenuState::makeChoicePlay()
{
    int choice(0);
    std::cin >> choice;
    switch (choice) {
        case 1:
            m_subState = SUB_STATE::PLAYERS;
            m_nbPlayers = 2;
            m_playerActual = 1;
            break;
        case 2:
            m_subState = SUB_STATE::PLAYERS;
            m_nbPlayers = 4;
            m_playerActual = 1;
            break;
        case 3:
            m_subState = SUB_STATE::MENU;
            break;
        default:
            m_error = "Veuillez taper 1, 2 ou 3.";
    }
}

void MainMenuState::makeChoicePlayers()
{
    int choice(0);
    std::cin >> choice;
    switch (choice) {
        case 1:
            m_players.push_back(Player(m_playerActual++));
            if (m_playerActual > m_nbPlayers) {
                // On a entré tous les joueurs
                m_subState = SUB_STATE::BOARD_SIZE;
            }
            break;
        case 2:
            m_error = "Desole, mais l'IA n'est pas encore implementee.";
            break;
        case 3:
            if (m_playerActual == 1) {
                m_subState = SUB_STATE::PLAY;
            } else {
                m_playerActual--;
                m_players.pop_back();
            }
            break;
        default:
            m_error = "Veuillez taper 1, 2 ou 3.";
    }
}

void MainMenuState::makeChoiceBoardSize()
{
    int choice(0);
    std::cin >> choice;
    if (choice == 0) {
        m_playerActual--;
        m_players.pop_back();
        m_subState = SUB_STATE::PLAYERS;
    } else if (choice >= 5 && choice <= 19) {
        if (choice % 2 == 0) {
            m_error = "Veuillez entrer une taille impaire comprise entre 5 et 19.";
        } else {
            m_boardSize = choice;
            m_subState = SUB_STATE::SUMMARY;
        }
    } else {
        m_error = "Veuillez taper une valeur entre 5 et 19 ou 0.";
    }
}

void MainMenuState::makeChoiceSummary()
{
    int choice(0);
    std::cin >> choice;
    switch (choice) {
        case 1:
            {
                StatePtr newState = std::make_unique<GameState>(m_app, std::move(m_players), m_boardSize);
                View::ViewPtr newView = std::make_shared<GameView>(*newState);
                newState->addObserver(newView);
                m_app.setState(std::move(newState));
                m_app.setView(newView);
                m_app.applyNewState();
                return;
            }
            break;
        case 2:
            m_subState = SUB_STATE::BOARD_SIZE;
            break;
        default:
            m_error = "Veuillez taper 1 ou 2.";
    }
}

void MainMenuState::handleEvents()
{
    // On récupère ce que l'utilisateur écrit
    if (m_waitingChoiceMenu) {
        m_waitingChoiceMenu = false;
        makeChoiceMenu();
    } else if (m_waitingChoicePlay) {
        m_waitingChoicePlay = false;
        makeChoicePlay();
    } else if (m_waitingChoicePlayers) {
        m_waitingChoicePlayers = false;
        makeChoicePlayers();
    } else if (m_waitingChoiceBoardSize) {
        m_waitingChoiceBoardSize = false;
        makeChoiceBoardSize();
    } else if (m_waitingChoiceSummary) {
        m_waitingChoiceSummary = false;
        makeChoiceSummary();
    }
}
