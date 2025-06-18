
// GameManager.cpp
#include "GameManager.h"
#include <fstream>
#include <iostream>


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
        move m = moveQueue.front();
        moveQueue.pop();
        movesJson.push_back({ {"player", m.player}, {"row", m.row}, {"col", m.col} });
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
            game.addMove({ move["player"], move["row"], move["col"] });
        }
        game.setWinner(g["winner"]);
        players[game.getPlayer1()].gameHistory.push_back(game);
        players[game.getPlayer2()].gameHistory.push_back(game);
    }
}

void GameManager::replayGame(const Game& game) {
    std::cout << "Replaying game between " << game.getPlayer1() << " and " << game.getPlayer2() << "\n";
    std::cout << "Winner: " << game.getWinner() << "\n";
    std::cout << "Timestamp: " << game.getTimestamp() << "\n";
    auto moves = game.getMoves();
    while (!moves.empty()) {
        auto m = moves.front();
        std::cout << m.player << " moved to (" << m.row << ", " << m.col << ")\n";
        moves.pop();
    }
}
void GameManager::replayGameByTimestamp(const std::string& timestamp) {
    std::ifstream inFile(gameFile);
    if (!inFile.is_open()) return;

    json allGames;
    inFile >> allGames;

    for (const auto& g : allGames) {
        if (g["timestamp"] == timestamp) {
            std::cout << "Replaying game between " << g["player1"] << " and " << g["player2"] << "\n";
            std::cout << "Winner: " << g["winner"] << "\n";

            char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

            for (const auto& move : g["moves"]) {
                std::string player = move["player"];
                int row = move["row"];
                int col = move["col"];
                char symbol = (player == g["player1"]) ? 'X' : 'O';
                board[row][col] = symbol;

                // Print board
                std::cout << "Move by " << player << ":\n";
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j)
                        std::cout << "[" << board[i][j] << "]";
                    std::cout << "\n";
                }
                std::cout << "-------------------\n";
            }
            return;
        }
    }

    std::cout << "Game with timestamp " << timestamp << " not found.\n";
}

void GameManager::playFullGame(const std::string& player1, const std::string& player2,
                               const std::vector<move>& moves, const std::string& winner) {
    Game game(player1, player2);

    for (const auto& move : moves) {
        game.addMove(move);
    }

    // Ensure tie is set correctly
    if (winner == "tie" || winner == "Tie" || winner == "TIE") {
        game.setWinner("tie");
    } else {
        game.setWinner(winner);  // "player1" or "player2"
    }

    playerManager.updateStats(game);
    saveGame(game);
    playerManager.savePlayers();
}




std::vector<std::tuple<char, int, int>> GameManager::replayGameByIndex(int index) {
    std::vector<std::tuple<char, int, int>> movesList;

    std::ifstream inFile(gameFile);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open game file.\n";

        return movesList;
    }

    json allGames;
    inFile >> allGames;

   if (!allGames.is_array() || index < 0 || index >= allGames.size()) {
        std::cerr << "Invalid index.\n";
        return movesList;
    }
    const auto& g = allGames[index];
    std::string player1 = g["player1"];
    std::string player2 = g["player2"];

    char symbol;
    for (const auto& move : g["moves"]) {
        std::string player = move["player"];
        int row = move["row"];
        int col = move["col"];
        if((player == player1) || (player == "Player X") || (player == "player")||(player=="Player"))
        {
            symbol = 'X';
        }
        else
        {
            symbol = 'O';
        }
        movesList.emplace_back(symbol, row, col);

    }

    return movesList;
}
