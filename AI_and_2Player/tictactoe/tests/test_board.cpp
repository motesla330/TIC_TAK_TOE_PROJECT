#include <gtest/gtest.h>
#include "../Board.h"

TEST(BoardTest, BoardIsEmptyAfterReset) {
    Board board;

    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
            EXPECT_EQ(board.getCell(row, col), ' ');
}

TEST(BoardTest, SetCellSuccess) {
    Board board;
    bool success = board.setCell(1, 1, 'X');
    EXPECT_TRUE(success);
    EXPECT_EQ(board.getCell(1, 1), 'X');
}

TEST(BoardTest, SetCellFailsIfOccupied) {
    Board board;
    board.setCell(0, 0, 'O');
    bool success = board.setCell(0, 0, 'X');
    EXPECT_FALSE(success);
    EXPECT_EQ(board.getCell(0, 0), 'O');
}

TEST(BoardTest, SetCellFailsIfOutOfBounds) {
    Board board;
    EXPECT_FALSE(board.setCell(-1, 0, 'X'));
    EXPECT_FALSE(board.setCell(0, -1, 'X'));
    EXPECT_FALSE(board.setCell(3, 0, 'X'));
    EXPECT_FALSE(board.setCell(0, 3, 'X'));
}

TEST(BoardTest, GetBoardReturnsCorrectGrid) {
    Board board;
    board.setCell(2, 2, 'O');

    const auto& grid = board.getBoard();
    EXPECT_EQ(grid[2][2], 'O');
}

TEST(BoardTest, ResetClearsTheBoard) {
    Board board;
    board.setCell(1, 1, 'X');
    board.setCell(0, 2, 'O');
    board.resetBoard();

    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
            EXPECT_EQ(board.getCell(row, col), ' ');
}
