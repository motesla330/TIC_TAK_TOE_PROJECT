#include <gtest/gtest.h>
#include "../Board.h"
#include "../gamelogic.h"

//Verifies the first player is 'X' when the game starts.
TEST(GameLogicTest, InitialPlayerIsX) {
    Board board;
    GameLogic logic(board);
    EXPECT_EQ(logic.getCurrentPlayer(), 'X');
}

//Checks that calling switchPlayer() alternates between 'X' and 'O'
TEST(GameLogicTest, PlayerSwitching) {
    Board board;
    GameLogic logic(board);
    logic.switchPlayer();
    EXPECT_EQ(logic.getCurrentPlayer(), 'O');
    logic.switchPlayer();
    EXPECT_EQ(logic.getCurrentPlayer(), 'X');
}

//Confirms a win is detected when a full row is filled with the same symbol.
TEST(GameLogicTest, DetectsWinInRow) {
    Board board;
    GameLogic logic(board);
    board.setCell(0, 0, 'X');
    board.setCell(0, 1, 'X');
    board.setCell(0, 2, 'X');
    EXPECT_TRUE(logic.checkWin('X'));
    EXPECT_FALSE(logic.checkWin('O'));
}

//Confirms a win is detected when a full column is filled with the same symbol.
TEST(GameLogicTest, DetectsWinInColumn) {
    Board board;
    GameLogic logic(board);
    board.setCell(0, 1, 'O');
    board.setCell(1, 1, 'O');
    board.setCell(2, 1, 'O');
    EXPECT_TRUE(logic.checkWin('O'));
    EXPECT_FALSE(logic.checkWin('X'));
}

//Verifies a win is detected along the main diagonal (top-left to bottom-right).
TEST(GameLogicTest, DetectsDiagonalWin) {
    Board board;
    GameLogic logic(board);
    board.setCell(0, 0, 'X');
    board.setCell(1, 1, 'X');
    board.setCell(2, 2, 'X');
    EXPECT_TRUE(logic.checkWin('X'));
}

// Verifies a win is detected along the anti-diagonal (top-right to bottom-left).
TEST(GameLogicTest, DetectsAntiDiagonalWin) {
    Board board;
    GameLogic logic(board);
    board.setCell(0, 2, 'O');
    board.setCell(1, 1, 'O');
    board.setCell(2, 0, 'O');
    EXPECT_TRUE(logic.checkWin('O'));
}

//Ensures the game recognizes a draw when all cells are filled with no winner.
TEST(GameLogicTest, DetectsDraw) {
    Board board;
    GameLogic logic(board);
    const char drawBoard[3][3] = {
        { 'X', 'O', 'X' },
        { 'X', 'O', 'O' },
        { 'O', 'X', 'X' }
    };

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board.setCell(i, j, drawBoard[i][j]);

    EXPECT_TRUE(logic.isDraw());
}


