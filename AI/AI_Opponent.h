// AI_Opponent.h

#ifndef AI_OPPONENT_H
#define AI_OPPONENT_H

#include <vector>
using namespace std;

#define EMPTY '_'
#define MIN -1000
#define MAX 1000

// Structure to represent a move
struct Move {
    int row, col;
};

// Enum to represent AI difficulty levels
enum Difficulty {
    EASY,
    MEDIUM,
    HARD
};

// Global characters representing the AI and human player
extern char player;
extern char opponent;

// Function declarations
bool isMovesLeft(char board[3][3]);
int evaluate(char board[3][3]);
int minimax(char board[3][3], int depth, bool isMax, int alpha, int beta);
Move findBestMove(char board[3][3]);
Move findRandomMove(char board[3][3]);
Move findMediumMove(char board[3][3]);
Move getAIMove(char board[3][3], Difficulty diff);
Difficulty selectDifficulty();

#endif // AI_OPPONENT_H
