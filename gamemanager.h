// Copyright 2025 <Your Name>

#ifndef F__DATA_STRUCTURE_PROJECT_DATABASE_HEADERS_GAMEMANAGER_H_
#define F__DATA_STRUCTURE_PROJECT_DATABASE_HEADERS_GAMEMANAGER_H_

#include <string>
#include "Headers/game.h"
#include "Headers/playermanager.h"

class GameManager {
 private:
    std::string gameFile;
    PlayerManager& playerManager;

 public:
    GameManager(const std::string& file, PlayerManager& manager);
    void saveGame(const Game& game);
    void loadGames();
    void replayGame(const Game& game);
};

#endif  // F__DATA_STRUCTURE_PROJECT_DATABASE_HEADERS_GAMEMANAGER_H_
