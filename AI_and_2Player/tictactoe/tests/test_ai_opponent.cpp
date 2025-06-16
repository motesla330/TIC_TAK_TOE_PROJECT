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

// Simulates an empty board
Board EmptyBoard() {
    return CreateBoard({
        "___",
        "___",
        "___"
    });
}

TEST(AITest, EvaluateDetectsXWin) {
    char board[3][3] = {
        {'X', 'X', 'X'},
        {'O', '_', 'O'},
        {'_', '_', '_'}
    };
    player = 'X';
    opponent = 'O';
    EXPECT_EQ(evaluate(board), 10);
}

TEST(AITest, EvaluateDetectsOWin) {
    char board[3][3] = {
        {'O', 'O', 'O'},
        {'X', '_', '_'},
        {'_', 'X', '_'}
    };
    player = 'X';
    opponent = 'O';
    EXPECT_EQ(evaluate(board), -10);
}

TEST(AITest, EvaluateDetectsDraw) {
    char board[3][3] = {
        {'X', 'O', 'X'},
        {'X', 'X', 'O'},
        {'O', 'X', 'O'}
    };
    player = 'X';
    opponent = 'O';
    EXPECT_EQ(evaluate(board), 0);
}

TEST(AITest, EasyMoveIsValid) {
    Board board = EmptyBoard();
    move m = getAIMove(board, EASY, 'X', 'O');
    EXPECT_GE(m.row, 0);
    EXPECT_GE(m.col, 0);
    EXPECT_LT(m.row, 3);
    EXPECT_LT(m.col, 3);
}

TEST(AITest, BlocksOpponentWin) {
    Board board = CreateBoard({
        "OO_",
        "X__",
        "_X_"
    });
    move m = getAIMove(board, HARD, 'X', 'O');
    EXPECT_EQ(m.row, 0);
    EXPECT_EQ(m.col, 2); // Block O's win
}

TEST(AITest, MediumPreventsImmediateLossButMayMissFork) {
    Board board = CreateBoard({
        "O__",
        "_X_",
        "__O"
    });
    move m = getAIMove(board, MEDIUM, 'X', 'O');
    EXPECT_TRUE((m.row == 0 && m.col == 1) || (m.row == 2 && m.col == 1));
}

TEST(AITest, EasyModeMovesCanVary) {
    Board board = EmptyBoard();
    move m1 = getAIMove(board, EASY, 'X', 'O');
    move m2 = getAIMove(board, EASY, 'X', 'O');
    // Could be same due to luck, but often not
    EXPECT_FALSE(m1.row == m2.row && m1.col == m2.col);
}

TEST(AITest, MediumModeSometimesBestOrRandom) {
    Board board = CreateBoard({
        "OX_",
        "XO_",
        "___"
    });

    bool sawBest = false, sawRandom = false;
    for (int i = 0; i < 10; ++i) {
        move m = getAIMove(board, MEDIUM, 'X', 'O');
        if (m.row == 0 && m.col == 2) sawBest = true;
        if (!(m.row == 0 && m.col == 2)) sawRandom = true;
    }
    EXPECT_TRUE(sawBest && sawRandom);
}

TEST(AITest, FullBoardReturnsInvalidMove) {
    Board board = CreateBoard({
        "XOX",
        "OXO",
        "OXO"
    });
    move m = getAIMove(board, HARD, 'X', 'O');
    EXPECT_EQ(m.row, -1);
    EXPECT_EQ(m.col, -1);
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
}
