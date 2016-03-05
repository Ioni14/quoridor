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
    const auto& state = static_cast<GameState&>(m_model);
    const auto& board = state.getBoard();
    const auto& size = board.getSize();
    const auto& cells = board.getCells();

    std::ostringstream oss;
    for (int j = 0; j < size; ++j) {
        std::ostringstream ossLine;
        for (int i = 0; i < size; ++i) {
            const auto& cell = cells[i][j];

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

void GameView::renderLoading()
{
    std::cout << "Lancement de la partie..." << std::endl;
    auto& state = static_cast<GameState&>(m_model);
    state.setWaitingChoiceEnded(true);
}

void GameView::renderAction()
{
    auto& state = static_cast<GameState&>(m_model);
    const auto& playerActual = state.getPlayerActual();
    renderBoard();
    std::cout << "----- Joueur " << playerActual.getNumero() << " -----" << std::endl;
    std::cout << "1 - Se deplacer" << std::endl;
    std::cout << "2 - Poser un mur" << std::endl;
    std::cout << "Votre choix ? ";
    state.setWaitingChoiceAction(true);
}

void GameView::renderMove()
{
    auto& state = static_cast<GameState&>(m_model);
    const auto& playerActual = state.getPlayerActual();
    std::cout << "----- Joueur " << playerActual.getNumero();
    std::cout << " : Se deplacer -----" << std::endl;
    std::cout << "0 - Retour" << std::endl;

    const auto& board = state.getBoard();
    int numMove(1);
    if (playerActual.canMove(board, 1, 0)) {
        std::cout << numMove << " - Droite" << std::endl;
        state.addMoveChoice(numMove, std::vector<int>{1, 0});
        numMove++;
    }
    if (playerActual.canMove(board, -1, 0)) {
        std::cout << numMove << " - Gauche" << std::endl;
        state.addMoveChoice(numMove, std::vector<int>{-1, 0});
        numMove++;
    }
    if (playerActual.canMove(board, 0, 1)) {
        std::cout << numMove << " - Bas" << std::endl;
        state.addMoveChoice(numMove, std::vector<int>{0, 1});
        numMove++;
    }
    if (playerActual.canMove(board, 0, -1)) {
        std::cout << numMove << " - Haut" << std::endl;
        state.addMoveChoice(numMove, std::vector<int>{0, -1});
        numMove++;
    }
    if (playerActual.canMove(board, 2, 0)) {
        std::cout << numMove << " - Sauter droite" << std::endl;
        state.addMoveChoice(numMove, std::vector<int>{2, 0});
        numMove++;
    }
    if (playerActual.canMove(board, -2, 0)) {
        std::cout << numMove << " - Sauter gauche" << std::endl;
        state.addMoveChoice(numMove, std::vector<int>{-2, 0});
        numMove++;
    }
    if (playerActual.canMove(board, 0, 2)) {
        std::cout << numMove << " - Sauter bas" << std::endl;
        state.addMoveChoice(numMove, std::vector<int>{0, 2});
        numMove++;
    }
    if (playerActual.canMove(board, 0, -2)) {
        std::cout << numMove << " - Sauter haut" << std::endl;
        state.addMoveChoice(numMove, std::vector<int>{0, -2});
        numMove++;
    }
    if (playerActual.canMove(board, -1, -1)) {
        std::cout << numMove << " - Diagonale : Haut / Gauche" << std::endl;
        state.addMoveChoice(numMove, std::vector<int>{-1, -1});
        numMove++;
    }
    if (playerActual.canMove(board, 1, -1)) {
        std::cout << numMove << " - Diagonale : Haut / Droite" << std::endl;
        state.addMoveChoice(numMove, std::vector<int>{1, -1});
        numMove++;
    }
    if (playerActual.canMove(board, 1, 1)) {
        std::cout << numMove << " - Diagonale : Bas / Droite" << std::endl;
        state.addMoveChoice(numMove, std::vector<int>{1, 1});
        numMove++;
    }
    if (playerActual.canMove(board, -1, 1)) {
        std::cout << numMove << " - Diagonale : Bas / Gauche" << std::endl;
        state.addMoveChoice(numMove, std::vector<int>{-1, 1});
        numMove++;
    }
    std::cout << "Votre choix ? ";
    state.setWaitingChoiceMove(true);
}

void GameView::renderWallCol()
{
    auto& state = static_cast<GameState&>(m_model);
    const auto& playerActual = state.getPlayerActual();
    std::cout << "----- Joueur " << playerActual.getNumero();
    std::cout << " : Pose un mur -----" << std::endl;
    std::cout << "Le mur sera positionne en bas a droite de la case donnee." << std::endl;
    std::cout << "Quelle colonne ? ";
    state.setWaitingChoiceWallCol(true);
}

void GameView::renderWallRow()
{
    std::cout << "Quelle ligne ? ";
    auto& state = static_cast<GameState&>(m_model);
    state.setWaitingChoiceWallRow(true);
}

void GameView::renderWallDir()
{
    std::cout << "1 - Vertical" << std::endl;
    std::cout << "2 - Horizontal" << std::endl;
    std::cout << "Quelle orientation ? ";
    auto& state = static_cast<GameState&>(m_model);
    state.setWaitingChoiceWallDir(true);
}

void GameView::renderWin()
{
    renderBoard();
    auto& state = static_cast<GameState&>(m_model);
    const auto& playerActual = state.getPlayerActual();
    std::cout << "Le joueur " << playerActual.getNumero() << " gagne !" << std::endl;
    state.setWaitingChoiceWin(true);
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
            renderLoading();
            break;
        case GameState::SUB_STATE::ACTION:
            renderAction();
            break;
        case GameState::SUB_STATE::MOVE:
            renderMove();
            break;
        case GameState::SUB_STATE::WALL_COL:
            renderWallCol();
            break;
        case GameState::SUB_STATE::WALL_ROW:
            renderWallRow();
            break;
        case GameState::SUB_STATE::WALL_DIR:
            renderWallDir();
            break;
        case GameState::SUB_STATE::WIN:
            renderWin();
            break;
    }

}
