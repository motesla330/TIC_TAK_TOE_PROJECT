#include <gtest/gtest.h>
#include "gamelogic.h"  // Include your logic header

TEST(GameLogicTest, TestInitialState) {
    GameLogic logic;
    EXPECT_EQ(logic.getCurrentPlayer(), Player::X); // example
}

// Add more test cases...
