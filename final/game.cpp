// Copyright 2025 <MennaAssem>

#include <ctime>    // For time_t, std::time, std::localtime, std::strftime
#include <string>   // For std::string
#include <queue>    // For std::queue

#include "game.h"
#include "globals.h"

Game::Game(const std::string &p1, const std::string &p2)
    : player1(p1), player2(p2) {
    std::time_t now = std::time(nullptr);
    char buf[80];
    std::tm *lt = std::localtime(&now);
    if (lt) {
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", lt);
        timestamp = std::string(buf);
    } else {
        timestamp.clear();
    }
}

void Game::addMove(const move &mv) {
    moves.push(mv);
}

void Game::setWinner(const std::string &win) {
    winner = win;
}

std::string Game::getPlayer1() const {
    // Assuming AUTH->UserName holds the correct player1 name
    return AUTH->UserName;
}

std::string Game::getPlayer2() const {
    if (VsAi) {
        return "AI";
    } else {
        return "Player";
    }
}

std::string Game::getWinner() const {
    return winner;
}

std::string Game::getTimestamp() const {
    return timestamp;
}

const std::queue<move> &Game::getMoves() const {
    return moves;
}
