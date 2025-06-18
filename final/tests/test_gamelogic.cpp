#include <gtest/gtest.h>
#include "../Board.h"
#include "../gamelogic.h"

TEST(GameLogicTest, InitialPlayerIsX) {
    Board board;
    GameLogic logic(board);
    EXPECT_EQ(logic.getCurrentPlayer(), 'X');
}

TEST(GameLogicTest, PlayerSwitching) {
    Board board;
    GameLogic logic(board);
    logic.switchPlayer();
    EXPECT_EQ(logic.getCurrentPlayer(), 'O');
    logic.switchPlayer();
    EXPECT_EQ(logic.getCurrentPlayer(), 'X');
}

TEST(GameLogicTest, DetectsWinInRow) {
    Board board;
    GameLogic logic(board);
    board.setCell(0, 0, 'X');
    board.setCell(0, 1, 'X');
    board.setCell(0, 2, 'X');
    EXPECT_TRUE(logic.checkWin('X'));
    EXPECT_FALSE(logic.checkWin('O'));
}

TEST(GameLogicTest, DetectsWinInColumn) {
    Board board;
    GameLogic logic(board);
    board.setCell(0, 1, 'O');
    board.setCell(1, 1, 'O');
    board.setCell(2, 1, 'O');
    EXPECT_TRUE(logic.checkWin('O'));
    EXPECT_FALSE(logic.checkWin('X'));
}

TEST(GameLogicTest, DetectsDiagonalWin) {
    Board board;
    GameLogic logic(board);
    board.setCell(0, 0, 'X');
    board.setCell(1, 1, 'X');
    board.setCell(2, 2, 'X');
    EXPECT_TRUE(logic.checkWin('X'));
}

TEST(GameLogicTest, DetectsAntiDiagonalWin) {
    Board board;
    GameLogic logic(board);
    board.setCell(0, 2, 'O');
    board.setCell(1, 1, 'O');
    board.setCell(2, 0, 'O');
    EXPECT_TRUE(logic.checkWin('O'));
}

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

TEST(GameLogicTest, NotDrawIfWinExists) {
    Board board;
    GameLogic logic(board);
    board.setCell(0, 0, 'X');
    board.setCell(0, 1, 'X');
    board.setCell(0, 2, 'X');
    board.setCell(1, 0, 'O');
    board.setCell(1, 1, 'O');
    board.setCell(1, 2, 'X');
    board.setCell(2, 0, 'X');
    board.setCell(2, 1, 'O');
    board.setCell(2, 2, 'O');
    EXPECT_FALSE(logic.isDraw());
}
