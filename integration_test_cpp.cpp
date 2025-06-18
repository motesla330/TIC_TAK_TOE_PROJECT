// integration_test.cpp
// Integration tests for Tic-Tac-Toe application

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "final/ai_opponent.h"
#include "Board.h"
#include "gamelogic.h"
#include "final/game.h"
#include "final/gamemanager.h"
#include "final/playermanager.h"
#include "Authentication.h"

#include <fstream>
#include <cstdio>

// Helper to create a temporary game file
static const std::string TEMP_GAME_FILE = "temp_games.json";

TEST_CASE("Board set and get cell operations") {
    Board board;
    REQUIRE(board.setCell(0, 0, 'X', false));
    REQUIRE(board.getCell(0, 0) == 'X');
    // Cannot overwrite unless temporary
    REQUIRE_FALSE(board.setCell(0, 0, 'O', false));
    REQUIRE(board.setCell(0, 0, 'O', true));
    REQUIRE(board.getCell(0, 0) == 'O');
}

TEST_CASE("GameLogic win detection and draw") {
    Board board;
    GameLogic logic(board);
    // Horizontal win X
    board.resetBoard();
    board.setCell(1, 0, 'X', false);
    board.setCell(1, 1, 'X', false);
    board.setCell(1, 2, 'X', false);
    REQUIRE(logic.checkWin('X'));
    REQUIRE_FALSE(logic.checkWin('O'));
    // Draw board
    board.resetBoard();
    char seq[9] = {'X','O','X','X','O','O','O','X','X'};
    for (int i=0;i<9;++i) board.setCell(i/3,i%3, seq[i], false);
    REQUIRE(logic.isDraw());
}

TEST_CASE("AI opponent returns valid moves") {
    char boardArr[3][3] = {{'X','O','X'},{' ','O',' '},{' ',' ','X'}};
    Move mvRandom = findRandomMove(boardArr);
    REQUIRE(mvRandom.row >= 0);
    REQUIRE(mvRandom.col >= 0);
    // Best move should block opponent if necessary
    // Setup simple block scenario
    char boardArr2[3][3] = {{'X','X',' '},{'O','O',' '},{' ',' ',' '}};
    player = 'O'; opponent = 'X';
    Move mvBest = findBestMove(boardArr2);
    // Best block is at (0,2) or (1,2)
    REQUIRE((mvBest.row == 0 && mvBest.col == 2) || (mvBest.row == 1 && mvBest.col == 2));
}

TEST_CASE("Authentication password hashing and validation") {
    Authentication auth;
    std::string pwd = "Abc!2345";
    std::string hash1 = auth.HashingPassword(pwd);
    std::string hash2 = auth.HashingPassword(pwd);
    REQUIRE(hash1 == hash2);
    auth.SignUp("user1", pwd, "user1@example.com");
    REQUIRE(auth.FieldsIsValidNew());
    auth.IsHereConnect(hash1, true);
    REQUIRE(auth.IsHereInterface());
}

TEST_CASE("GameManager save and load games integration") {
    // Remove existing temp file
    std::remove(TEMP_GAME_FILE.c_str());
    PlayerManager pm;
    GameManager gm(TEMP_GAME_FILE, pm);
    // Create and save game
    Game game("Alice", "Bob");
    game.setWinner("Alice");
    gm.saveGame(game);
    // Load back
    pm.loadPlayers(); // no players
    gm.loadGames();
    // After load, pm.getPlayers() should contain Alice and Bob histories
    auto &players = pm.getPlayers();
    REQUIRE(players.find("Alice") != players.end());
    REQUIRE(players.find("Bob") != players.end());
    REQUIRE(players["Alice"].wins + players["Bob"].losses >= 1);
}

TEST_CASE("PlayerManager stats updates") {
    PlayerManager pm;
    Game game("P1", "P2");
    game.setWinner("tie");
    pm.updateStats(game);
    auto *p1 = pm.searchPlayer("P1");
    auto *p2 = pm.searchPlayer("P2");
    REQUIRE(p1 != nullptr);
    REQUIRE(p2 != nullptr);
    REQUIRE(p1->ties == 1);
    REQUIRE(p2->ties == 1);
}
