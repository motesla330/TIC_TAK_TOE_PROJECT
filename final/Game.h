
// Game.h
#ifndef GAME_H
#define GAME_H

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
private:
    std::string player1;
    std::string player2;
    std::queue<move> moves;
    std::string winner;
    std::string timestamp;

public:
    Game(std::string p1, std::string p2);
    void addMove(const move& move);
    void setWinner(const std::string& win);
    std::string getPlayer1() const;
    std::string getPlayer2() const;
    std::string getWinner() const;
    std::string getTimestamp() const;
    const std::queue<move>& getMoves() const;
};

#endif
