// C++ program to find the next optimal move for 
// a player 
#include<bits/stdc++.h>   
using namespace std; 

char player = 'x', opponent = 'o',EMPTY = '_';
const int MAX = 1000;
const int MIN = -1000; 
struct Move 
{ 
    int row, col; 
}; 

enum Difficulty { EASY, MEDIUM, HARD };
   
// This function returns true if there are moves 
// remaining on the board. It returns false if 
// there are no moves left to play. 
bool isMovesLeft(char board[3][3]) 
{ 
    for (int i = 0; i<3; i++) 
        for (int j = 0; j<3; j++) 
            if (board[i][j]=='_') 
                return true; 
    return false; 
} 
// This function evaluates the board and returns
int evaluate(char b[3][3]) 
{ 
    // Checking for Rows for X or O victory. 
    for (int row = 0; row<3; row++) 
    { 
        if (b[row][0] == b[row][1] && 
            b[row][1] == b[row][2]) 
        { 
            if (b[row][0] == player) 
                return +10; 
            else if (b[row][0] == opponent) 
                return -10; 
        } 
    } 
  
    // Checking for Columns for X or O victory. 
    for (int col = 0; col<3; col++) 
    { 
        if (b[0][col] == b[1][col] && 
            b[1][col] == b[2][col]) 
        { 
            if (b[0][col] == player) 
                return +10; 
  
            else if (b[0][col] == opponent) 
                return -10; 
        } 
    } 
  
    // Checking for Diagonals for X or O victory. 
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) 
    { 
        if (b[0][0] == player) 
            return +10; 
        else if (b[0][0] == opponent) 
            return -10; 
    } 
  
    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) 
    { 
        if (b[0][2] == player) 
            return +10; 
        else if (b[0][2] == opponent) 
            return -10; 
    } 
  
    // Else if none of them have won then return 0 
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
                    best = max(best, minimax(board, depth + 1, false, alpha, beta));
                    board[i][j] = EMPTY;
                    alpha = max(alpha, best);
                    if (beta <= alpha) break;
                }
        return best;
    } else {
        int best = MAX;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == EMPTY) {
                    board[i][j] = opponent;
                    best = min(best, minimax(board, depth + 1, true, alpha, beta));
                    board[i][j] = EMPTY;
                    beta = min(beta, best);
                    if (beta <= alpha) break;
                }
        return best;
    }
}

Move findBestMove(char board[3][3]) 
{ 
    int bestVal = -1000; 
    Move bestMove; 
    bestMove.row = -1; 
    bestMove.col = -1; 
  
    // Traverse all cells, evaluate minimax function for 
    // all empty cells. And return the cell with optimal 
    // value. 
    for (int i = 0; i<3; i++) 
    { 
        for (int j = 0; j<3; j++) 
        { 
            // Check if cell is empty 
            if (board[i][j]=='_') 
            { 
                // Make the move 
                board[i][j] = player; 
  
                // compute evaluation function for this 
                // move. 
                int moveVal = minimax(board, 0, false, MIN, MAX); 
  
                // Undo the move 
                board[i][j] = '_'; 
  
                // If the value of the current move is 
                // more than the best value, then update 
                // best/ 
                if (moveVal > bestVal) 
                { 
                    bestMove.row = i; 
                    bestMove.col = j; 
                    bestVal = moveVal; 
                } 
            } 
        } 
    } 
    return bestMove; 
} 

// Random move for easy difficulty
Move findRandomMove(char board[3][3]) {
    vector<Move> moves;
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

// Medium: 50% best move, 50% random
Move findMediumMove(char board[3][3]) {
    if (rand() % 2 == 0)
        return findBestMove(board);
    else
        return findRandomMove(board);
}

// Select move based on difficulty
Move getAIMove(char board[3][3], Difficulty diff) {
    switch (diff) {
        case EASY: return findRandomMove(board);
        case MEDIUM: return findMediumMove(board);
        case HARD: return findBestMove(board);
        default: return findBestMove(board);
    }
}
Difficulty selectDifficulty() {
    int choice;
    cout << "Select AI Difficulty:\n1. Easy\n2. Medium\n3. Hard\nChoice: ";
    cin >> choice;
    switch (choice) {
        case 1: return EASY;
        case 2: return MEDIUM;
        case 3: return HARD;
        default: cout << "Invalid, defaulting to Hard.\n"; return HARD;
    }
}

int main() {
    char board[3][3] = {
        { '_', '_', '_' },
        { '_', '_', '_' },
        { '_', '_', '_' }
    };

    cout << "Welcome to Tic Tac Toe!" << endl;
    cout << "You are 'o' and AI is 'x'." << endl;

    Difficulty diff = selectDifficulty();

    int turn = 0; // 0 for player, 1 for AI
    while (true) {
        // Display the board
        cout << "Current board:" << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }

        // Check if the game is over
        int score = evaluate(board);
        if (score == 10) {
            cout << "AI wins!" << endl;
            break;
        } else if (score == -10) {
            cout << "You win!" << endl;
            break;
        } else if (!isMovesLeft(board)) {
            cout << "It's a draw!" << endl;
            break;
        }

        if (turn == 0) {
            // Player's turn
            int row, col;
            cout << "Enter your move (row and column): ";
            cin >> row >> col;
            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == '_') {
                board[row][col] = opponent;
                turn = 1;
            } else {
                cout << "Invalid move. Try again." << endl;
            }
        } else {
            // AI's turn
            cout << "AI is making its move..." << endl;
            Move aiMove = getAIMove(board, diff);
            if (aiMove.row != -1 && aiMove.col != -1)
                board[aiMove.row][aiMove.col] = player;
            turn = 0;
        }
    }

    return 0;
}