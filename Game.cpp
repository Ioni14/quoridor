#include "Game.h"

#include <iostream>
#include <sstream>
#include <string>

Game::Game(const int& boardSize, const int &nbPlayers) :
    m_board(boardSize),
    m_players(0),
    m_nbPlayers(nbPlayers),
    m_continue(true)
{
    initPlayers();
}

void Game::initPlayers()
{
    auto size = m_board.getSize();

    for (int n = 0; n < m_nbPlayers; ++n) {
        m_players.push_back(Player(n+1));

        int i(0), j(0);

        // On récupère le n-ième Player de la liste
        auto it = m_players.begin();
        std::advance(it, n);

        switch (it->getNumero()) {
            case 1:
            default:
                i = size / 2;
                j = size - 1;
                break;
            case 2:
                i = size / 2;
                j = 0;
                break;
            case 3:
                i = size - 1;
                j = size / 2;
                break;
            case 4:
                i = 0;
                j = size / 2;
                break;
        }
        it->setIPos(i);
        it->setJPos(j);
        m_board.getCells()[i][j].setPlayer(&(*it));
    }
}

void Game::run()
{
    int iterations = 0;
    while (m_continue) {
        handleEvents();
        update();
        render();
        iterations++;
        if (iterations == 2) {
            m_continue = false;
        }
    }
}

void Game::render()
{
    //m_board.render();
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
                ossLine << " ";
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

void Game::update()
{

    m_board.putWall(5, 6, Board::WALL_ORIENTATION::VERTICAL);



    for (auto it = m_players.begin(); it != m_players.end(); ++it) {
        it->move(m_board, 1, 0);
    }
}

void Game::handleEvents()
{

}
