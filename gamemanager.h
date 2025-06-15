// GameManager.h
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <string>
#include "Game.h"
#include "PlayerManager.h"

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

#endif
