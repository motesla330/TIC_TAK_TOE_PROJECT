// Copyright 2025 <Your Name>

#include "Headers/gamemanager.h"
#include <fstream>
#include <iostream>
#include <string>

GameManager::GameManager(const std::string& file, PlayerManager& manager)
    : gameFile(file), playerManager(manager) {}

void GameManager::saveGame(const Game& game) {
    json gameJson;
    gameJson["player1"] = game.getPlayer1();
    gameJson["player2"] = game.getPlayer2();
    gameJson["winner"] = game.getWinner();
    gameJson["timestamp"] = game.getTimestamp();

    json movesJson = json::array();
    auto moveQueue = game.getMoves();
    while (!moveQueue.empty()) {
        Move m = moveQueue.front();
        moveQueue.pop();
        movesJson.push_back({
            {"player", m.player},
            {"row", m.row},
            {"col", m.col}
        });
    }
    gameJson["moves"] = movesJson;

    std::ifstream inFile(gameFile);
    json allGames = json::array();
    if (inFile.is_open()) {
        inFile >> allGames;
        inFile.close();
    }
    allGames.push_back(gameJson);

    std::ofstream outFile(gameFile);
    outFile << allGames.dump(4);
}

void GameManager::loadGames() {
    std::ifstream inFile(gameFile);
    if (!inFile.is_open()) return;

    json allGames;
    inFile >> allGames;
    auto& players = playerManager.getPlayers();

    for (const auto& g : allGames) {
        Game game(g["player1"], g["player2"]);
        for (const auto& move : g["moves"]) {
            game.addMove({
                move["player"],
                move["row"],
                move["col"]
            });
        }
        game.setWinner(g["winner"]);
        players[game.getPlayer1()].gameHistory.push_back(game);
        players[game.getPlayer2()].gameHistory.push_back(game);
    }
}

void GameManager::replayGame(const Game& game) {
    std::cout << "Replaying game between "
              << game.getPlayer1() << " and "
              << game.getPlayer2() << "\n";
    std::cout << "Winner: " << game.getWinner() << "\n";
    std::cout << "Timestamp: " << game.getTimestamp() << "\n";
    auto moves = game.getMoves();
    while (!moves.empty()) {
        auto m = moves.front();
        std::cout << m.player << " moved to ("
                  << m.row << ", " << m.col << ")\n";
        moves.pop();
    }
}
