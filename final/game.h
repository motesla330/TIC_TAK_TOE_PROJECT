// Copyright 2025 <MahmoudIsmail>

#ifndef FINAL_GAME_H_
#define FINAL_GAME_H_

#include <queue>
#include <string>
#include <ctime>
#include "json.hpp"

struct move {
    std::string player;
    int row;
    int col;
};

class Game {
 public:
    Game(const std::string &p1, const std::string &p2);
    void addMove(const move &mv);
    void setWinner(const std::string &win);
    std::string getPlayer1() const;
    std::string getPlayer2() const;
    std::string getWinner() const;
    std::string getTimestamp() const;
    const std::queue<move> &getMoves() const;

 private:
    std::string player1;
    std::string player2;
    std::queue<move> moves;
    std::string winner;
    std::string timestamp;
};

#endif  // FINAL_GAME_H_
