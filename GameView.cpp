#include "GameView.h"

#include <iostream>
#include "GameState.h"

GameView::GameView(State &model) :
    View(model)
{
}

void GameView::render()
{
    GameState& state = static_cast<GameState&>(m_model);

    std::cout << "toto" << std::endl;

    /*
    if (!m_loadingRendered) {
        m_loadingRendered = true;
        std::cout << "Lancement de la partie..." << std::endl;
        return;
    }

    std::ostringstream oss;

    auto size = m_board.getSize();
    auto cells = m_board.getCells();

    for (int j = 0; j < size; ++j) {
        std::ostringstream ossLine;
        for (int i = 0; i < size; ++i) {
            auto cell(cells[i][j]);

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
                ossLine << ' ';
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
    */
}
