#include "AI_Opponent.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>

char player = 'x';
char opponent = 'o';

bool isMovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return true;
    return false;
}

int evaluate(char b[3][3]) {
    for (int row = 0; row < 3; row++) {
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
            if (b[row][0] == player) return +10;
            else if (b[row][0] == opponent) return -10;
        }
    }

    for (int col = 0; col < 3; col++) {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
            if (b[0][col] == player) return +10;
            else if (b[0][col] == opponent) return -10;
        }
    }

    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == player) return +10;
        else if (b[0][0] == opponent) return -10;
    }

    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == player) return +10;
        else if (b[0][2] == opponent) return -10;
    }

    return 0;
}

int minimax(char board[3][3], int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(board);
    if (score == 10 || score == -10)
        return score;
    if (!isMovesLeft(board))
        return 0;

    if (isMax) {
        int best = MIN;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == EMPTY) {
                    board[i][j] = player;
                    best = std::max(best, minimax(board, depth + 1, false, alpha, beta));
                    board[i][j] = EMPTY;
                    alpha = std::max(alpha, best);
                    if (beta <= alpha) break;
                }
        return best;
    } else {
        int best = MAX;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == EMPTY) {
                    board[i][j] = opponent;
                    best = std::min(best, minimax(board, depth + 1, true, alpha, beta));
                    board[i][j] = EMPTY;
                    beta = std::min(beta, best);
                    if (beta <= alpha) break;
                }
        return best;
    }
}

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

Move findRandomMove(char board[3][3]) {
    std::vector<Move> moves;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                moves.push_back({i, j});

    if (!moves.empty()) {
        int idx = rand() % moves.size();
        return moves[idx];
    }
    return {-1, -1};
}

Move findMediumMove(char board[3][3]) {
    return (rand() % 2 == 0) ? findBestMove(board) : findRandomMove(board);
}

Move getAIMove(Board& boardObj, Difficulty diff, char aiChar, char humanChar) {
    char tempBoard[3][3];
    const auto& grid = boardObj.getBoard();

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            tempBoard[i][j] = (grid[i][j] == ' ') ? '_' : grid[i][j];

    // Set the symbols used by minimax
    player = aiChar;
    opponent = humanChar;

    switch (diff) {
    case EASY: return findRandomMove(tempBoard);
    case MEDIUM: return findMediumMove(tempBoard);
    case HARD: return findBestMove(tempBoard);
    default: return findBestMove(tempBoard);
    }
}
