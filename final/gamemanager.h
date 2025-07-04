// Copyright 2025 <MennaAssem>

#ifndef FINAL_GAMEMANAGER_H_
#define FINAL_GAMEMANAGER_H_

#include <vector>  // for std::vector
#include <tuple>   // for std::tuple
#include <string>  // for std::string
#include "Game.h"
#include "PlayerManager.h"

class GameManager {
 public:
    GameManager(const std::string &file, PlayerManager &manager);
    void saveGame(const Game &game);
    void loadGames();
    void replayGame(const Game &game);
    void playFullGame(
        const std::string &player1,
        const std::string &player2,
        const std::vector<move> &moves,
        const std::string &winner);
    void replayGameByTimestamp(const std::string &timestamp);
    std::vector<std::tuple<char, int, int>> replayGameByIndex(int index);

 private:
    std::string gameFile;
    PlayerManager &playerManager;
};

#endif  // FINAL_GAMEMANAGER_H_
