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

const int WINNING_MASKS[8] = {
    0b000000111, // Row 0
    0b000111000, // Row 1
    0b111000000, // Row 2
    0b001001001, // Col 0
    0b010010010, // Col 1
    0b100100100, // Col 2
    0b100010001, // Diag
    0b001010100  // Diag
};
// Updated declaration using Board class
Move getAIMove(Board& board, Difficulty diff, char aiPlayer, char humanPlayer);

#endif // AI_OPPONENT_H
