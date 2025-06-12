#include <gtest/gtest.h>
#include "../tictactoe/gamelogic.h"
#include "../tictactoe/Board.h"

TEST(GameLogicTest, PlayerSwitching) {
    Board board;
    GameLogic logic(board);
    Player current = logic.getCurrentPlayer();
    logic.switchPlayer();
    EXPECT_NE(current, logic.getCurrentPlayer());
}
