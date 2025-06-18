#ifndef AI_OPPONENT_H
#define AI_OPPONENT_H

#include <vector>
#include "Board.h"

#define EMPTY '_'
#define MIN -1000
#define MAX 1000

struct Move {
    int row, col;
};

enum Difficulty {
    EASY,
    MEDIUM,
    HARD
};

const int WIN_PATTERNS[8] = {
    0b111000000,  // First row (cells 0-2)
    0b000111000,  // Second row (cells 3-5)
    0b000000111,  // Third row (cells 6-8)
    0b100100100,  // First column (cells 0,3,6)
    0b010010010,  // Second column (cells 1,4,7)
    0b001001001,  // Third column (cells 2,5,8)
    0b100010001,  // Diagonal (cells 0,4,8)
    0b001010100   // Anti-diagonal (cells 2,4,6)
};

Move getAIMove(Board& board, Difficulty diff);

#endif // AI_OPPONENT_H
