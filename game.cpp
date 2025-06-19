// Copyright 2025 <HudaEhab>

#include "Headers/game.h"
#include <queue>
#include <string>

Game::Game(std::string p1, std::string p2) : player1(p1), player2(p2) {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    timestamp = std::string(buf);
}

void Game::addMove(const Move& move) {
    moves.push(move);
}

void Game::setWinner(const std::string& win) {
    winner = win;
}

std::string Game::getPlayer1() const { return player1; }
std::string Game::getPlayer2() const { return player2; }
std::string Game::getWinner() const { return winner; }
std::string Game::getTimestamp() const { return timestamp; }
const std::queue<Move>& Game::getMoves() const { return moves; }
