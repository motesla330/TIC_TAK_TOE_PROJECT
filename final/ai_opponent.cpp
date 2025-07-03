// Copyright 2025 <HebaEmad>

#include "ai_opponent.h"

#include <algorithm>  // std::max, std::min
#include <chrono>     // (if needed elsewhere)
#include <cstdlib>    // for EXIT_FAILURE etc.
#include <ctime>      // for time(), if still used
#include <iostream>
#include <random>
#include <vector>

static char player = 'x';
static char opponent = 'o';

// Check if any moves left on board
bool isMovesLeft(char board[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == EMPTY) {
        return true;
      }
    }
  }
  return false;
}

// Evaluate board: +10 if player wins, -10 if opponent wins, else 0
int evaluate(char b[3][3]) {
  // Rows
  for (int row = 0; row < 3; row++) {
    if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
      if (b[row][0] == player) {
        return +10;
      } else if (b[row][0] == opponent) {
        return -10;
      }
    }
  }
  // Columns
  for (int col = 0; col < 3; col++) {
    if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
      if (b[0][col] == player) {
        return +10;
      } else if (b[0][col] == opponent) {
        return -10;
      }
    }
  }
  // Diagonals
  if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
    if (b[0][0] == player) {
      return +10;
    } else if (b[0][0] == opponent) {
      return -10;
    }
  }
  if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
    if (b[0][2] == player) {
      return +10;
    } else if (b[0][2] == opponent) {
      return -10;
    }
  }
  return 0;
}

// Minimax with alpha-beta pruning
int minimax(char board[3][3], int depth, bool isMax, int alpha, int beta) {
  int score = evaluate(board);
  if (score == 10 || score == -10) {
    return score;
  }
  if (!isMovesLeft(board)) {
    return 0;  // tie
  }

  if (isMax) {
    int best = MIN;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == EMPTY) {
          board[i][j] = player;
          int val = minimax(board, depth + 1, false, alpha, beta);
          board[i][j] = EMPTY;
          best = std::max(best, val);
          alpha = std::max(alpha, best);
          if (beta <= alpha) {
            break;
          }
        }
      }
    }
    return best;
  } else {
    int best = MAX;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == EMPTY) {
          board[i][j] = opponent;
          int val = minimax(board, depth + 1, true, alpha, beta);
          board[i][j] = EMPTY;
          best = std::min(best, val);
          beta = std::min(beta, best);
          if (beta <= alpha) {
            break;
          }
        }
      }
    }
    return best;
  }
}

// Find best move for player
Move findBestMove(char board[3][3]) {
  int bestVal = -1000;
  Move bestMove = {-1, -1};

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == EMPTY) {
        board[i][j] = player;
        int moveVal = minimax(board, 0, false, MIN, MAX);
        board[i][j] = EMPTY;
        if (moveVal > bestVal) {
          bestMove = {i, j};
          bestVal = moveVal;
        }
      }
    }
  }
  return bestMove;
}

// Thread-safe random generator for moves
static int getRandomIndex(int n) {
  static thread_local std::mt19937 gen(std::random_device {}());
  std::uniform_int_distribution<> dist(0, n - 1);
  return dist(gen);
}

// Find a random available move
Move findRandomMove(char board[3][3]) {
  std::vector<Move> moves;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == EMPTY) {
        moves.push_back({i, j});
      }
    }
  }
  if (!moves.empty()) {
    int idx = getRandomIndex(static_cast<int>(moves.size()));
    return moves[idx];
  }
  return {-1, -1};
}

// Medium difficulty: randomly choose best or random
Move findMediumMove(char board[3][3]) {
  // 50-50 choice
  int coin = getRandomIndex(2);  // yields 0 or 1
  if (coin == 0) {
    return findBestMove(board);
  } else {
    return findRandomMove(board);
  }
}

// Determine AI move based on difficulty
Move getAIMove(Board& boardObj, Difficulty diff, char aiChar,
                char humanChar) {
  char tempBoard[3][3];
  const auto& grid = boardObj.getBoard();
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      // Assume EMPTY is '_' or another sentinel; adapt if needed
      tempBoard[i][j] =
          (grid[i][j] == ' ') ? EMPTY : grid[i][j];
    }
  }

  // Set symbols for minimax
  player = aiChar;
  opponent = humanChar;

  switch (diff) {
    case EASY:
      return findRandomMove(tempBoard);
    case MEDIUM:
      return findMediumMove(tempBoard);
    case HARD:
      return findBestMove(tempBoard);
    default:
      return findBestMove(tempBoard);
  }
}

// End of file (ensure newline follows)
