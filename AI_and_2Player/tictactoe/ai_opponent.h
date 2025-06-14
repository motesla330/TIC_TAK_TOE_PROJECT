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

// Updated declaration using Board class
Move getAIMove(Board& board, Difficulty diff, char aiPlayer, char humanPlayer);

#endif // AI_OPPONENT_H
