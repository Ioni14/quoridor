#include "IAStrategyNegaMax.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
#include <ctime>
#include <ratio>
#include <chrono>
#include "Player.h"
#include "Board.h"
#include "PathfindingAStar.h"

namespace G36631 {

IAStrategyNegaMax::IAStrategyNegaMax() :
    m_depth(3),
    m_playerActual(nullptr),
    m_players(nullptr),
    m_board(nullptr),
    m_rand(std::chrono::high_resolution_clock::now().time_since_epoch().count())
{
}

IAResponse IAStrategyNegaMax::moveOrPutWall(Board& board, int playerActual, std::list<Player>& players)
{
    m_players = &players;
    m_board = &board;

    {
        auto itPlayer = std::find_if(players.begin(), players.end(),
            [playerActual](const Player& player) -> bool {
                return playerActual == player.getNumero();
            }
        );
        assert(itPlayer != players.end());
        m_playerActual = &(*itPlayer);
    }

    PathfindingAStar::count = 0;

    m_nodeCount = 0;
    m_bestActions.clear();
    IAResponse eval = minimaxValue(m_depth, playerActual, -10000, 10000);
    m_log << "node count : " << m_nodeCount << std::endl;
    m_log << "pf count : " << PathfindingAStar::count << std::endl;
    m_log << "result : " << eval.score << std::endl;
    m_log << "best action : ";
    if (eval.type == IAResponse::Type::MOVE) {
        m_log << "move ";
    } else {
        m_log << "wall ";
        if (eval.orientation == IAResponse::WallOrientation::HORIZONTAL) {
            m_log << "horizontal ";
        } else {
            m_log << "vertical ";
        }
    }
    m_log << eval.bestI << ", " << eval.bestJ << std::endl;

    m_log << "best actions : " << std::endl;
    for (auto& bestAction : m_bestActions) {
        m_log << bestAction.score << " ";
        if (bestAction.type == IAResponse::Type::MOVE) {
            m_log << "move ";
        } else {
            m_log << "wall ";
            if (bestAction.orientation == IAResponse::WallOrientation::HORIZONTAL) {
                m_log << "horizontal ";
            } else {
                m_log << "vertical ";
            }
        }
        m_log << bestAction.bestI << ", " << bestAction.bestJ << std::endl;
    }

    std::string logname = "log";
    logname += std::to_string(playerActual);
    logname += ".txt";
    std::ofstream file(logname);
    file << m_log.str();
    m_log.flush();

    assert(m_bestActions.size() != 0);

    int nbMoves = 0;
    for (auto& bestAction : m_bestActions) {
        if (bestAction.type == IAResponse::Type::MOVE) {
            nbMoves++;
        }
    }

    IAResponse response;
    if (nbMoves > 0) {
        std::uniform_int_distribution<int> dis(0, nbMoves - 1);
        response = m_bestActions[dis(m_rand)];
    } else {
        std::uniform_int_distribution<int> dis(0, m_bestActions.size() - 1);
        response = m_bestActions[dis(m_rand)];
    }

    m_log << "-- response -- " << std::endl;
    m_log << response.score << " ";
    if (response.type == IAResponse::Type::MOVE) {
        m_log << "move ";
    } else {
        m_log << "wall ";
        if (response.orientation == IAResponse::WallOrientation::HORIZONTAL) {
            m_log << "horizontal ";
        } else {
            m_log << "vertical ";
        }
    }
    m_log << response.bestI << ", " << response.bestJ << std::endl;
    m_log << "-------------------------------------" << std::endl;

    file << m_log.str();
    m_log.flush();

    return response;
    //return eval;
}

IAResponse IAStrategyNegaMax::minimaxValue(int depth, int playerIndex, int alpha, int beta)
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    std::string espaces = "";
    for (int i = depth; i < m_depth; ++i) {
        espaces += "  ";
    }

    m_log << espaces << "alpha : " << alpha << " beta : " << beta << std::endl;
    m_log << espaces << "player : " << playerIndex << std::endl;
    auto itPlayer = std::find_if(m_players->begin(), m_players->end(),
        [playerIndex](const Player& player) -> bool {
            return playerIndex == player.getNumero();
        }
    );
    assert(itPlayer != m_players->end());
    Player& player = *itPlayer;

    // fin du jeu ?
    bool somebodyWon = false;
    for (auto& player : *m_players) {
        if ((player.getNumero() == 1 && player.getJPos() == 0)
            || (player.getNumero() == 2 && player.getJPos() == m_board->getSize() - 1)
            || (player.getNumero() == 3 && player.getIPos() == 0)
            || (player.getNumero() == 4 && player.getIPos() == m_board->getSize() - 1)) {
            somebodyWon = true;
            break;
        }
    }

    IAResponse bestAction {-10000, IAResponse::Type::MOVE, 0, 0, IAResponse::WallOrientation::VERTICAL};
    if (m_playerActual->getNumero() == playerIndex) {
        bestAction.score = -10000; // début le plus loin possible
    } else {
        bestAction.score = 10000;
    }

    if (somebodyWon || depth == 0) {
        std::uniform_int_distribution<int> dis(-5, 5);
        bestAction.score = evaluation(dis(m_rand));
        return bestAction;
    }

    m_log << espaces << "depth : " << depth << std::endl;
    int nodeCount = 0;

    int moves[12][2] = {
        {-1, -1},
        { 0, -1},
        { 1, -1},
        {-1,  0},
        { 1,  0},
        {-1,  1},
        { 0,  1},
        { 1,  1},
        { 0, -2},
        { 0,  2},
        {-2,  0},
        { 2,  0},
    };

    m_log << espaces << "-- moves --" << std::endl;
    for (int i = 0; i < 12; ++i) {
        if (!player.canMove(*m_board, moves[i][0], moves[i][1])) {
            continue;
        }

        m_log << espaces << "move : " << moves[i][0] << ", " << moves[i][1] << std::endl;
        nodeCount++;
        m_nodeCount++;

        player.move(*m_board, moves[i][0], moves[i][1]);

        if (!m_board->syncShortestPath(*m_players)) {
            player.move(*m_board, moves[i][0] * -1, moves[i][1] * -1); // on le replace
            continue;
        }

        int score = minimaxValue(depth - 1, playerIndex % m_players->size() + 1, alpha, beta).score;
        player.move(*m_board, moves[i][0] * -1, moves[i][1] * -1); // on le replace

        if (m_playerActual->getNumero() == playerIndex) { // joueur qui essaie de gagner : on maximise
            m_log << espaces << "MAX : " << score << std::endl;

            if (depth == m_depth && !m_bestActions.empty() && m_bestActions[0].score == score) {
                m_bestActions.push_back(IAResponse{score, IAResponse::Type::MOVE, moves[i][0], moves[i][1], IAResponse::WallOrientation::HORIZONTAL});
            }

            if (score > bestAction.score) {
                m_log << espaces << "new best score : " << score << std::endl;
                bestAction.score = score;
                bestAction.type = IAResponse::Type::MOVE;
                bestAction.bestI = moves[i][0];
                bestAction.bestJ = moves[i][1];

                if (depth == m_depth) {
                    m_bestActions.clear();
                    m_bestActions.push_back(bestAction);
                }
            }
            if (bestAction.score >= beta) {
                m_log << espaces << "-- cut beta --" << std::endl;
                return bestAction;
            }
            alpha = std::max(alpha, bestAction.score);

        } else { // adversaire : on minimise
            m_log << espaces << "MIN : " << score << std::endl;

            if (score < bestAction.score) {
                m_log << espaces << "new best score : " << score << std::endl;
                bestAction.score = score;
                bestAction.type = IAResponse::Type::MOVE;
                bestAction.bestI = moves[i][0];
                bestAction.bestJ = moves[i][1];
            }
            if (alpha >= bestAction.score) {
                m_log << espaces << "-- cut alpha --" << std::endl;
                return bestAction;
            }
            beta = std::min(beta, bestAction.score);

        }

    }

    // Pose de mur
    m_log << espaces << "-- put walls --" << std::endl;
    for (int i = 0; i < m_board->getSize() - 1; ++i) {
        for (int j = 0; j < m_board->getSize() - 1; ++j) {
            if (m_board->canPutWall(*m_players, player, i, j, Board::WALL_ORIENTATION::VERTICAL)) {

                m_log << espaces << "wall : " << i << ", " << j << " vertical" << std::endl;
                nodeCount++;
                m_nodeCount++;

                m_board->putWall(player, i, j, Board::WALL_ORIENTATION::VERTICAL);
                int score = minimaxValue(depth - 1, playerIndex % m_players->size() + 1, alpha, beta).score;
                m_board->destroyWall(player, i, j, Board::WALL_ORIENTATION::VERTICAL); // on enlève le mur

                if (m_playerActual->getNumero() == playerIndex) { // joueur qui essaie de gagner : on maximise
                    m_log << espaces << "MAX : " << score << std::endl;

                    if (depth == m_depth && !m_bestActions.empty() && m_bestActions[0].score == score) {
                        m_bestActions.push_back(IAResponse{score, IAResponse::Type::WALL, i, j, IAResponse::WallOrientation::VERTICAL});
                    }

                    if (score > bestAction.score) {
                        m_log << espaces << "new best score : " << score << std::endl;
                        bestAction.score = score;
                        bestAction.type = IAResponse::Type::WALL;
                        bestAction.orientation = IAResponse::WallOrientation::VERTICAL;
                        bestAction.bestI = i;
                        bestAction.bestJ = j;

                        if (depth == m_depth) {
                            m_bestActions.clear();
                            m_bestActions.push_back(bestAction);
                        }
                    }
                    if (bestAction.score >= beta) {
                        m_log << espaces << "-- cut beta --" << std::endl;
                        return bestAction;
                    }
                    alpha = std::max(alpha, bestAction.score);

                } else { // adversaire : on minimise
                    m_log << espaces << "MIN : " << score << std::endl;

                    if (score < bestAction.score) {
                        m_log << espaces << "new best score : " << score << std::endl;
                        bestAction.score = score;
                        bestAction.type = IAResponse::Type::WALL;
                        bestAction.orientation = IAResponse::WallOrientation::VERTICAL;
                        bestAction.bestI = i;
                        bestAction.bestJ = j;
                    }
                    if (alpha >= bestAction.score) {
                        m_log << espaces << "-- cut alpha --" << std::endl;
                        return bestAction;
                    }
                    beta = std::min(beta, bestAction.score);

                }

            }
            if (m_board->canPutWall(*m_players, player, i, j, Board::WALL_ORIENTATION::HORIZONTAL)) {

                m_log << espaces << "wall : " << i << ", " << j << " horizontal" << std::endl;
                nodeCount++;
                m_nodeCount++;

                m_board->putWall(player, i, j, Board::WALL_ORIENTATION::HORIZONTAL);
                int score = minimaxValue(depth - 1, playerIndex % m_players->size() + 1, alpha, beta).score;
                m_board->destroyWall(player, i, j, Board::WALL_ORIENTATION::HORIZONTAL); // on enlève le mur

                if (m_playerActual->getNumero() == playerIndex) { // joueur qui essaie de gagner : on maximise
                    m_log << espaces << "MAX : " << score << std::endl;

                    if (depth == m_depth && !m_bestActions.empty() && m_bestActions[0].score == score) {
                        m_bestActions.push_back(IAResponse{score, IAResponse::Type::WALL, i, j, IAResponse::WallOrientation::HORIZONTAL});
                    }

                    if (score > bestAction.score) {
                        m_log << espaces << "new best score : " << score << std::endl;
                        bestAction.score = score;
                        bestAction.type = IAResponse::Type::WALL;
                        bestAction.orientation = IAResponse::WallOrientation::HORIZONTAL;
                        bestAction.bestI = i;
                        bestAction.bestJ = j;

                        if (depth == m_depth) {
                            m_bestActions.clear();
                            m_bestActions.push_back(bestAction);
                        }
                    }
                    if (bestAction.score >= beta) {
                        m_log << espaces << "-- cut beta --" << std::endl;
                        return bestAction;
                    }
                    alpha = std::max(alpha, bestAction.score);

                } else { // adversaire : on minimise
                    m_log << espaces << "MIN : " << score << std::endl;

                    if (score < bestAction.score) {
                        m_log << espaces << "new best score : " << score << std::endl;
                        bestAction.score = score;
                        bestAction.type = IAResponse::Type::WALL;
                        bestAction.orientation = IAResponse::WallOrientation::HORIZONTAL;
                        bestAction.bestI = i;
                        bestAction.bestJ = j;
                    }
                    if (alpha >= bestAction.score) {
                        m_log << espaces << "-- cut alpha --" << std::endl;
                        return bestAction;
                    }
                    beta = std::min(beta, bestAction.score);

                }

            }
        }
    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    m_log << espaces << "Duration : " << time_span.count() << " seconds. " << nodeCount/time_span.count() << " nps" << std::endl;

    return bestAction;
}

int IAStrategyNegaMax::evaluation(int random) const
{
    int score = 0;

    m_board->syncShortestPathByPlayer(*m_playerActual);
    int shortestPathPlayerActual = m_playerActual->getLastShortestPath().size();
    assert(shortestPathPlayerActual != 0);

    const std::vector<int> weightWalls {
        0,
        8,
        7,
        6,
        5,
        4,
        3,
        2,
        1,
    };

    for (auto& player : *m_players) {
        if ((player.getNumero() == 1 && player.getJPos() == 0)
            || (player.getNumero() == 2 && player.getJPos() == m_board->getSize() - 1)
            || (player.getNumero() == 3 && player.getIPos() == 0)
            || (player.getNumero() == 4 && player.getIPos() == m_board->getSize() - 1)) {

            if (m_playerActual->getNumero() == player.getNumero()) {
                score += 1000;
            } else {
                score -= 1000;
            }
        }

        if (player.getNumero() != m_playerActual->getNumero()) {
            m_board->syncShortestPathByPlayer(player);
            assert(player.getLastShortestPath().size() != 0);
            score += -1 * (shortestPathPlayerActual - player.getLastShortestPath().size());
            //score += 1 * (weightWalls[m_playerActual->getNbWalls()] - weightWalls[player.getNbWalls()]);
            //score += 1 * (weightWalls[m_playerActual->getNbWalls()] - weightWalls[player.getNbWalls()]);
        }
    }

    //score += random;

    return score;
}

}
