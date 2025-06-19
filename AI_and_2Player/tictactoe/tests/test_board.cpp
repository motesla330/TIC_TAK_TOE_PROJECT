#include <gtest/gtest.h>
#include "../Board.h"

//Checks that all cells in a new board are empty (' ').
TEST(BoardTest, StartsEmpty) {
    Board board;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_EQ(board.getCell(i, j), ' ');
}

//Tests setting a valid cell (inside bounds and empty), expecting it to succeed and store the value 'X'.
TEST(BoardTest, SetCellValid) {
    Board board;
    EXPECT_TRUE(board.setCell(1, 1, 'X'));
    EXPECT_EQ(board.getCell(1, 1), 'X');
}

//Ensures setting a cell outside the 3×3 board (e.g., (-1, 0) or (3, 3)) fails and returns false.
TEST(BoardTest, SetCellInvalidOutOfBounds) {
    Board board;
    EXPECT_FALSE(board.setCell(-1, 0, 'O'));
    EXPECT_FALSE(board.setCell(3, 3, 'O'));
}

// Verifies that trying to set a cell that’s already occupied doesn't overwrite the original value and returns false.
TEST(BoardTest, SetCellOccupied) {
    Board board;
    board.setCell(0, 0, 'X');
    EXPECT_FALSE(board.setCell(0, 0, 'O'));
    EXPECT_EQ(board.getCell(0, 0), 'X');
}

// Confirms that resetBoard() clears all cells (sets them back to ' '), resetting the board to its initial state.
TEST(BoardTest, ResetBoardWorks) {
    Board board;
    board.setCell(0, 0, 'X');
    board.resetBoard();
    EXPECT_EQ(board.getCell(0, 0), ' ');
}
