#include "Board.h"

Board::Board() {
    resetBoard();
}

void Board::resetBoard() {
    for (auto& row : board) {
        row.fill(' ');
    }
}

bool Board::setCell(int row, int col, char symbol) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ') {
        board[row][col] = symbol;
        return true;
    }
    return false;
}

char Board::getCell(int row, int col) const {
    return board[row][col];
}

const std::array<std::array<char, 3>, 3>& Board::getBoard() const {
    return board;
}
