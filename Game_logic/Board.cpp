#include "Board.h"

Board::Board(int size) : size(size), board(size, std::vector<char>(size, ' ')) {}

void Board::resetBoard() {
    for (auto& row : board)
        std::fill(row.begin(), row.end(), ' ');
}

bool Board::setCell(int row, int col, char symbol) {
    if (row >= 0 && row < size && col >= 0 && col < size && board[row][col] == ' ') {
        board[row][col] = symbol;
        return true;
    }
    return false;
}

char Board::getCell(int row, int col) const {
    return board[row][col];
}

const std::vector<std::vector<char>>& Board::getBoard() const {
    return board;
}
