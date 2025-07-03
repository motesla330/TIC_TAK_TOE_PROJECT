// Copyright 2025 MahmoudIsmail

#ifndef FINAL_PLAYERMANAGER_H_
#define FINAL_PLAYERMANAGER_H_

#include <unordered_map>
#include <string>
#include <vector>

#include "Game.h"
#include "json.hpp"

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
    explicit PlayerManager(const std::string& filename);
    void loadPlayers();
    void savePlayers();
    void updateStats(const Game& game);
    std::unordered_map<std::string, PlayerBD>& getPlayers();
    bool deletePlayerHistory(const std::string& name);
    bool deletePlayer(const std::string& name);
    PlayerBD* searchPlayer(const std::string& name);
    bool searchAndAssert(const std::string& name,
                         const std::string& password);
    bool findAndCheckEmail(const std::string& name,
                           const std::string& email);
    bool getStoredPasswordIfUserExists(const std::string& name,
                                       std::string& hashedPasswordOut);
    bool playerExists(const std::string& name) const;
    void saveStats(const std::string& filename) const;
};

#endif  // FINAL_PLAYERMANAGER_H_
