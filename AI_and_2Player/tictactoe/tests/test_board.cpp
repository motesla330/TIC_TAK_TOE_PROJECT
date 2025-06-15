#include <gtest/gtest.h>
#include "../Board.h"

TEST(BoardTest, InitialEmpty) {
    Board b;
    EXPECT_TRUE(b.isCellEmpty(0, 0));  // Assuming this function exists
}
