#include "gamelogic.h"

// Winning patterns (8 possible ways to win in 3x3 Tic-Tac-Toe)
const int GameLogic::WIN_PATTERNS[8] = {
    0b111000000,  // First row (cells 0-2)
    0b000111000,  // Second row (cells 3-5)
    0b000000111,  // Third row (cells 6-8)
    0b100100100,  // First column (cells 0,3,6)
    0b010010010,  // Second column (cells 1,4,7)
    0b001001001,  // Third column (cells 2,5,8)
    0b100010001,  // Diagonal (cells 0,4,8)
    0b001010100   // Anti-diagonal (cells 2,4,6)
};

GameLogic::GameLogic(Board& boardRef) : board(boardRef) {
   reset();
}

void GameLogic::updateMasks() const {
    xMask = 0;
    oMask = 0;
    const auto& grid = board.getBoard();

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            int pos = 1 << (row * 3 + col);  // Calculate bit position
            if (grid[row][col] == 'X') xMask |= pos;
            else if (grid[row][col] == 'O') oMask |= pos;
        }
    }
}

bool GameLogic::checkWin(char symbol) const {
    updateMasks();  // Ensure masks are current
    int mask = (symbol == 'X') ? xMask : oMask;

    for (int pattern : WIN_PATTERNS) {
        if ((mask & pattern) == pattern) {
            return true;
        }
    }
    return false;
}

bool GameLogic::isDraw() const {
    updateMasks();
    return (xMask | oMask) == 0b111111111 && !checkWin('X') && !checkWin('O');
}

void GameLogic::switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

char GameLogic::getCurrentPlayer() const {
    return currentPlayer;
}

void GameLogic::reset() {
    currentPlayer = 'X';
    xMask = oMask = 0;
}
