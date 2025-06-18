// GameManager.h
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector> // for std::vector
#include <tuple> // for std::tuple
#include <string>
#include "Game.h"
#include "PlayerManager.h"
#include<vector>

class GameManager {
private:
    std::string gameFile;
    PlayerManager& playerManager;


public:

    GameManager(const std::string& file, PlayerManager& manager);
    void saveGame(const Game& game);
    void loadGames();
    void replayGame(const Game& game);
    void playFullGame(const std::string& player1, const std::string& player2,
                      const std::vector<move>& moves, const std::string& winner);
    void  replayGameByTimestamp(const std::string& timestamp);


    std::vector<std::tuple<char, int, int>> replayGameByIndex(int index);

};

#endif
