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

TEST(AIOpponentTest, EasyReturnsValidMove) {
    Board board;
    auto move = getAIMove(board, EASY, 'x', 'o');
    ASSERT_GE(move.row, 0);
    ASSERT_GE(move.col, 0);
    ASSERT_LT(move.row, 3);
    ASSERT_LT(move.col, 3);
}

TEST(AIOpponentTest, MediumReturnsValidMove) {
    Board board;
    auto move = getAIMove(board, MEDIUM, 'x', 'o');
    ASSERT_GE(move.row, 0);
    ASSERT_GE(move.col, 0);
    ASSERT_LT(move.row, 3);
    ASSERT_LT(move.col, 3);
}

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