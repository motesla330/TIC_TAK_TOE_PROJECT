#include <gtest/gtest.h>
#include "../Board.h"

TEST(BoardTest, StartsEmpty) {
    Board board;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_EQ(board.getCell(i, j), ' ');
}

TEST(BoardTest, SetCellValid) {
    Board board;
    EXPECT_TRUE(board.setCell(1, 1, 'X'));
    EXPECT_EQ(board.getCell(1, 1), 'X');
}

TEST(BoardTest, SetCellInvalidOutOfBounds) {
    Board board;
    EXPECT_FALSE(board.setCell(-1, 0, 'O'));
    EXPECT_FALSE(board.setCell(3, 3, 'O'));
}

TEST(BoardTest, SetCellOccupied) {
    Board board;
    board.setCell(0, 0, 'X');
    EXPECT_FALSE(board.setCell(0, 0, 'O'));
    EXPECT_EQ(board.getCell(0, 0), 'X');
}

TEST(BoardTest, ResetBoardWorks) {
    Board board;
    board.setCell(0, 0, 'X');
    board.resetBoard();
    EXPECT_EQ(board.getCell(0, 0), ' ');
}

