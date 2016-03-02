#include "GameView.h"

#include <iostream>
#include <sstream>
#include <string>
#include "GameState.h"

GameView::GameView(State &model) :
    View(model)
{
}

void GameView::renderBoard()
{
    GameState& state = static_cast<GameState&>(m_model);

    auto& board = state.getBoard();

    std::ostringstream oss;

    auto& size = board.getSize();
    auto& cells = board.getCells();

    for (int j = 0; j < size; ++j) {
        std::ostringstream ossLine;
        for (int i = 0; i < size; ++i) {
            auto& cell = cells[i][j];

            // On affiche les murs (ou pas)
            if (cell.hasWallNorth() || cell.hasWallWest() ||
                (j - 1 >= 0 && cells[i][j-1].hasWallWest()) ||
                (i - 1 >= 0 && cells[i-1][j].hasWallNorth())) {
                oss << "#";
            } else {
                oss << " ";
            }
            if (cell.hasWallNorth()) {
                oss << "#";
            } else {
                oss << " ";
            }
            if (cell.hasWallWest()) {
                ossLine << "#";
            } else {
                ossLine << " ";
            }

            // Contenu de la cellule
            if (cell.getPlayer() == nullptr) {
                ossLine << '-'; // Uniquement ASCII pour Windows
            } else {
                ossLine << cell.getPlayer()->getNumero();
            }

            // Les derniers murs
            if (i == size - 1 && cell.hasWallEast()) {
                oss << "#";
                ossLine << "#";
            }
        }
        oss << std::endl << ossLine.str() << std::endl;
    }

    // Les TOUS derniers murs
    for (int i = 0; i < size; ++i) {
        auto cell(cells[i][size - 1]);
        if (cell.hasWallSouth()) {
            oss << "##";
        }
        if (i == size - 1 && cell.hasWallEast()) {
            oss << "#";
        }
    }

    std::cout << oss.str() << std::endl;
}

void GameView::render()
{
    GameState& state = static_cast<GameState&>(m_model);

    std::cout << std::endl;
    if (!state.getError().empty()) {
        std::cerr << state.getError() << std::endl;
        state.getError().clear();
    }

    switch (state.getSubState()) {
        case GameState::SUB_STATE::LOADING:
            std::cout << "Lancement de la partie..." << std::endl;
            state.setWaitingChoiceEnded(true);
            break;
        case GameState::SUB_STATE::ACTION:
            renderBoard();
            std::cout << "----- Joueur " << state.getPlayerActual().getNumero() << " -----" << std::endl;
            std::cout << "1 - Se deplacer" << std::endl;
            std::cout << "2 - Poser un mur" << std::endl;
            std::cout << "Votre choix ? ";
            state.setWaitingChoiceAction(true);
            break;
        case GameState::SUB_STATE::MOVE:
            std::cout << "----- Joueur " << state.getPlayerActual().getNumero();
            std::cout << " : Se deplacer -----" << std::endl;
            std::cout << "1 - Retour" << std::endl;
            std::cout << "Votre choix ? ";
            state.setWaitingChoiceMove(true);
            break;
        case GameState::SUB_STATE::WALL_COL:
            std::cout << "----- Joueur " << state.getPlayerActual().getNumero();
            std::cout << " : Pose un mur -----" << std::endl;
            std::cout << "Le mur sera positionne en bas a droite de la case donnee." << std::endl;
            std::cout << "Quelle colonne ? ";
            state.setWaitingChoiceWallCol(true);
            break;
        case GameState::SUB_STATE::WALL_ROW:
            std::cout << "Quelle ligne ? ";
            state.setWaitingChoiceWallRow(true);
            break;
        case GameState::SUB_STATE::WALL_DIR:
            std::cout << "1 - Vertical" << std::endl;
            std::cout << "2 - Horizontal" << std::endl;
            std::cout << "Quelle orientation ? ";
            state.setWaitingChoiceWallDir(true);
            break;
    }

}
