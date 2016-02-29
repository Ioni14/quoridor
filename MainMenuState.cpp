#include "MainMenuState.h"

#include <iostream>
#include <memory>
#include "Quoridor.h"
#include "QuitState.h"
#include "GameState.h"

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
    std::cout << std::endl;
    if (!m_error.empty()) {
        std::cerr << m_error << std::endl;
        m_error.clear();
    }

    switch (m_subState) {
        case SUB_STATE::TITLE:
            std::cout << "Quoridor by Sweetdreams - 2016" << std::endl;
            std::cout << "Bienvenue sur Quoridor." << std::endl;
            m_titleEnded = true;
            break;
        case SUB_STATE::MENU:
            std::cout << "----- Menu -----" << std::endl;
            std::cout << "1 - Jouer" << std::endl;
            std::cout << "2 - Quitter" << std::endl;
            std::cout << "Votre choix ? ";
            m_waitingChoiceMenu = true;
            break;
        case SUB_STATE::PLAY:
            std::cout << "----- Jouer -----" << std::endl;
            std::cout << "1 - 2 joueurs" << std::endl;
            std::cout << "2 - 4 joueurs" << std::endl;
            std::cout << "3 - Retour" << std::endl;
            std::cout << "Votre choix ? ";
            m_waitingChoicePlay = true;
            break;
        case SUB_STATE::PLAYERS:
            std::cout << "----- " << m_nbPlayers << " Joueurs : J" << m_playerActual << " -----" << std::endl;
            std::cout << "1 - Joueur reel" << std::endl;
            std::cout << "2 - IA" << std::endl;
            std::cout << "3 - Retour" << std::endl;
            std::cout << "Votre choix ? ";
            m_waitingChoicePlayers = true;
            break;
        case SUB_STATE::BOARD_SIZE:
            std::cout << "----- Taille du plateau -----" << std::endl;
            std::cout << "0 - Retour" << std::endl;
            std::cout << "Entrez la taille du plateau [5-19]" << std::endl;
            std::cout << "Votre choix ? ";
            m_waitingChoiceBoardSize = true;
            break;
        case SUB_STATE::SUMMARY:
            std::cout << "----- Resume -----" << std::endl;
            std::cout << m_nbPlayers << " Joueurs : ";
            for (auto& player : m_players) {
                std::cout << (player.isIA() ? "IA" : "Reel");
                if (player.getNumero() < m_nbPlayers) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
            std::cout << "Taille du plateau : " << m_boardSize << std::endl;
            std::cout << "1 - Lancer la partie" << std::endl;
            std::cout << "2 - Retour" << std::endl;
            std::cout << "Votre choix ? ";
            m_waitingChoiceSummary = true;
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
    // On récupère ce que l'utilisateur écrit
    int choice(0);

    if (m_waitingChoiceMenu) {
        m_waitingChoiceMenu = false;
        std::cin >> choice;
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
    } else if (m_waitingChoicePlay) {
        m_waitingChoicePlay = false;
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
    } else if (m_waitingChoicePlayers) {
        m_waitingChoicePlayers = false;
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
    } else if (m_waitingChoiceBoardSize) {
        m_waitingChoiceBoardSize = false;
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
    } else if (m_waitingChoiceSummary) {
        m_waitingChoiceSummary = false;
        std::cin >> choice;
        switch (choice) {
            case 1:
                // Lancement de la Gameuuuh
                {
                    StatePtr newState = std::make_unique<GameState>(m_app, std::move(m_players), m_boardSize);
                    m_app.setState(std::move(newState));
                }
                break;
            case 2:
                m_subState = SUB_STATE::BOARD_SIZE;
                break;
            default:
                m_error = "Veuillez taper 1 ou 2.";
        }
    }
}
