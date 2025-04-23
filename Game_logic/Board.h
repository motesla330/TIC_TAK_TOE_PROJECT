#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
public:
    Board(int size = 3); // default to 3x3

    void resetBoard();
    bool setCell(int row, int col, char symbol);
    char getCell(int row, int col) const;
    const std::vector<std::vector<char>>& getBoard() const;

private:
    int size;
    std::vector<std::vector<char>> board;
};

#endif // BOARD_H
