// PlayerManager.h
#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include <unordered_map>
#include <string>
#include <vector>
#include "json.hpp"
#include "Game.h"

using json = nlohmann::json;

struct PlayerBD {
    std::string password;
    std::string email;
    int wins = 0;
    int losses = 0;
    int ties = 0;
    std::vector<Game> gameHistory;
};

class PlayerManager {
private:
    std::string playerFile;
    std::unordered_map<std::string, PlayerBD> players;

public:

    PlayerManager(const std::string& filename);
    void loadPlayers();
    void savePlayers();
    void updateStats(const Game& game);
    std::unordered_map<std::string, PlayerBD>& getPlayers();
    bool deletePlayerHistory(const std::string& name);
    bool deletePlayer(const std::string& name);
    PlayerBD* searchPlayer(const std::string& name);
    bool searchAndAssert(const std::string& name, const std::string& password);
    bool findAndCheckEmail(const std::string& name, const std::string& email);
    bool getStoredPasswordIfUserExists(const std::string& name, std::string& hashedPasswordOut);
    bool playerExists(const std::string& name) const;
    void saveStats(const std::string& filename) const;
};

#endif
