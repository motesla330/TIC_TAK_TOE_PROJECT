
// PlayerManager.cpp
#include "PlayerManager.h"
#include <fstream>
#include <iostream>

PlayerManager::PlayerManager(const std::string& filename) : playerFile(filename) {}

void PlayerManager::loadPlayers() {
    std::ifstream in(playerFile);
    if (in.is_open()) {
        json j;
        in >> j;
        for (auto& [username, data] : j.items()) {
            Player p;
            p.password = data["password"];
            p.email = data.value("email", "");
            p.wins = data["wins"];
            p.losses = data["losses"];
            p.ties = data["ties"];
            players[username] = p;
        }
    }
}

void PlayerManager::savePlayers() {
    json j;
    for (const auto& [username, p] : players) {
        j[username] = {
            {"password", p.password},
            {"email", p.email},
            {"wins", p.wins},
            {"losses", p.losses},
            {"ties", p.ties}
        };
    }
    std::ofstream out(playerFile);
    out << j.dump(4);
}

void PlayerManager::updateStats(const Game& game) {
    if (players.find(game.getPlayer1()) == players.end())
        players[game.getPlayer1()] = Player{};
    if (players.find(game.getPlayer2()) == players.end())
        players[game.getPlayer2()] = Player{};

    players[game.getPlayer1()].gameHistory.push_back(game);
    players[game.getPlayer2()].gameHistory.push_back(game);

    if (game.getWinner() == "tie") {
        players[game.getPlayer1()].ties++;
        players[game.getPlayer2()].ties++;
    } else if (game.getWinner() == game.getPlayer1()) {
        players[game.getPlayer1()].wins++;
        players[game.getPlayer2()].losses++;
    } else {
        players[game.getPlayer2()].wins++;
        players[game.getPlayer1()].losses++;
    }
}

std::unordered_map<std::string, Player>& PlayerManager::getPlayers() {
    return players;
}

bool PlayerManager::deletePlayerHistory(const std::string& name) {
    auto it = players.find(name);
    if (it != players.end()) {
        it->second.gameHistory.clear();
        it->second.wins = 0;
        it->second.losses = 0;
        it->second.ties = 0;
        return true;
    }
    return false;
}

bool PlayerManager::deletePlayer(const std::string& name) {
    return players.erase(name) > 0;
}

Player* PlayerManager::searchPlayer(const std::string& name) {
    auto it = players.find(name);
    if (it != players.end()) {
        return &it->second;
    }
    return nullptr;
}

bool PlayerManager::searchAndAssert(const std::string& name, const std::string& password) {
    auto it = players.find(name);
    if (it != players.end()) {
        return it->second.password == password;
    }
    return false;
}

bool PlayerManager::findAndCheckEmail(const std::string& name, const std::string& email) {
    auto it = players.find(name);
    if (it != players.end()) {
        return it->second.email == email;
    }
    return false;
}
