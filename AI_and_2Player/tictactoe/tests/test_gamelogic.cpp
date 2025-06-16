#include <gtest/gtest.h>
#include "../Board.h"

// Test that a new board is empty
TEST(BoardTest, BoardStartsEmpty) {
    Board b;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            EXPECT_EQ(b.getCell(row, col), ' ');
        }
    }
}