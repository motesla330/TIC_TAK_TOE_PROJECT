// Copyright 2025 <HebaEmad>

#ifndef FINAL_AI_OPPONENT_H_
#define FINAL_AI_OPPONENT_H_

#include <vector>
#include "Board.h"

#define EMPTY '_'
#define MIN -1000
#define MAX 1000

struct Move {
  int row;
  int col;
};

enum Difficulty {
  EASY,
  MEDIUM,
  HARD
};

// Get the AI move based on board state and difficulty
Move getAIMove(Board& board, Difficulty diff, char aiPlayer, char humanPlayer);

#endif  // FINAL_AI_OPPONENT_H_
