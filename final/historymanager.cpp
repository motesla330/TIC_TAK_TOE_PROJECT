// Copyright 2025 <MahmoudIsmail>

#include <ctime>      // for std::time, std::ctime
#include <string>     // for std::string
#include <vector>     // for std::vector
#include <iostream>   // for std::cout, std::endl

#include "final/historymanager.h"

GameHistoryManager::GameHistoryManager()
    : nextId(1) {}

void GameHistoryManager::startNewGame(const std::string &startingPlayer) {
    currentGame = GameHistory();
    currentGame.id = nextId++;
    currentGame.startTime = std::time(nullptr);
    currentGame.startingPlayer = startingPlayer;
    currentGame.moves.clear();
}

void GameHistoryManager::recordMove(int row,
    int col, const std::string &player) {
    GameMove move;
    move.row = row;
    move.col = col;
    move.player = player;
    move.timestamp = std::time(nullptr);

    currentGame.moves.push_back(move);
}

void GameHistoryManager::endCurrentGame(const std::string &winner) {
    currentGame.endTime = std::time(nullptr);
    currentGame.winner = winner;
    history.push_back(currentGame);
}

const std::vector<GameHistory> &GameHistoryManager::getHistory() const {
    return history;
}

bool GameHistoryManager::replayGame(int gameId) const {
    for (const auto &game : history) {
        if (game.id == gameId) {
            std::cout << "Replaying Game ID: " << game.id << "\n";
            // std::ctime returns a newline-terminated string
            std::cout << "Started at: " << std::ctime(&game.startTime);
            std::cout << "Winner: "
                      << (game.winner.empty() ? "None" : game.winner)
                      << "\n";
            for (const auto &move : game.moves) {
                std::cout << "Player " << move.player
                          << " moved to (" << move.row << ", " << move.col
                          << ") at " << std::ctime(&move.timestamp);
            }
            return true;
        }
    }
    std::cout << "Game with ID " << gameId << " not found.\n";
    return false;
}
