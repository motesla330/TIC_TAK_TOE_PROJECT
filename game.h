// Copyright 2025 <Your Name>

#ifndef F__DATA_STRUCTURE_PROJECT_DATABASE_HEADERS_GAME_H_
#define F__DATA_STRUCTURE_PROJECT_DATABASE_HEADERS_GAME_H_

#include <queue>
#include <string>
#include <ctime>
#include "Headers/json.hpp"

struct Move {
    std::string player;
    int row;
    int col;
};

class Game {
 private:
    std::string player1;
    std::string player2;
    std::queue<Move> moves;
    std::string winner;
    std::string timestamp;

 public:
    Game(std::string p1, std::string p2);
    void addMove(const Move& move);
    void setWinner(const std::string& win);
    std::string getPlayer1() const;
    std::string getPlayer2() const;
    std::string getWinner() const;
    std::string getTimestamp() const;
    const std::queue<Move>& getMoves() const;
};

#endif  // F__DATA_STRUCTURE_PROJECT_DATABASE_HEADERS_GAME_H_
