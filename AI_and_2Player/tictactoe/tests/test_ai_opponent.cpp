#include <gtest/gtest.h>
#include "ai_opponent.h"
#include "Board.h"

// Helper to set up a board with a specific layout
Board createBoard(const std::vector<std::string>& layout) {
    Board b;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            b.setCell(i, j, layout[i][j]);
    return b;
}
//Checks that the AI (in Easy mode) returns a move within board bounds (0–2 for both row and column).
TEST(AIOpponentTest, EasyReturnsValidMove) {
    Board board;
    auto move = getAIMove(board, EASY, 'x', 'o');
    ASSERT_GE(move.row, 0);
    ASSERT_GE(move.col, 0);
    ASSERT_LT(move.row, 3);
    ASSERT_LT(move.col, 3);
}

//Checks that the AI (in Medium mode) returns a move within valid board bounds.
TEST(AIOpponentTest, MediumReturnsValidMove) {
    Board board;
    auto move = getAIMove(board, MEDIUM, 'x', 'o');
    ASSERT_GE(move.row, 0);
    ASSERT_GE(move.col, 0);
    ASSERT_LT(move.row, 3);
    ASSERT_LT(move.col, 3);
}

//Ensures the AI (in Hard mode) detects a winning opportunity and picks the correct move to win the game.
TEST(AIOpponentTest, HardFindsWinningMove) {
    Board board = createBoard({
        "xx_",
        "oo_",
        "___"
    });
    auto move = getAIMove(board, HARD, 'x', 'o');
    // Winning move should be (0,2)
    EXPECT_EQ(move.row, 0);
    EXPECT_EQ(move.col, 2);
}

//Ensures the AI (in Hard mode) blocks the opponent’s immediate winning move.
TEST(AIOpponentTest, HardBlocksOpponentWin) {
    Board board = createBoard({
        "oo_",
        "xx_",
        "___"
    });
    auto move = getAIMove(board, HARD, 'x', 'o');
    // AI should block (0,2)
    EXPECT_EQ(move.row, 0);
    EXPECT_EQ(move.col, 2);
}
