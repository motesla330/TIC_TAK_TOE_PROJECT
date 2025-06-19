// Copyright 2025 <Your Name>

#ifndef F__DATA_STRUCTURE_PROJECT_DATABASE_HEADERS_PLAYERMANAGER_H_
#define F__DATA_STRUCTURE_PROJECT_DATABASE_HEADERS_PLAYERMANAGER_H_

#include <unordered_map>
#include <string>
#include <vector>
#include "Headers/json.hpp"
#include "Headers/Game.h"

using json = nlohmann::json;

struct Player {
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
    std::unordered_map<std::string, Player> players;

 public:
    explicit PlayerManager(const std::string& filename);
    void loadPlayers();
    void savePlayers();
    void updateStats(const Game& game);
    std::unordered_map<std::string, Player>& getPlayers();
    bool deletePlayerHistory(const std::string& name);
    bool deletePlayer(const std::string& name);
    Player* searchPlayer(const std::string& name);
    bool searchAndAssert(const std::string& name,
                         const std::string& password);
    bool findAndCheckEmail(const std::string& name,
                           const std::string& email);
};

#endif  // F__DATA_STRUCTURE_PROJECT_DATABASE_HEADERS_PLAYERMANAGER_H_
