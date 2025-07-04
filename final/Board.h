// Copyright 2025 <MennaAssem>

#ifndef FINAL_BOARD_H_
#define FINAL_BOARD_H_

#include <array>

class Board {
 public:
  Board();
  bool setCell(int row, int col, char symbol, bool temporary = false);
  void resetBoard();
  char getCell(int row, int col) const;
  const std::array<std::array<char, 3>, 3>& getBoard() const;

 private:
  static const int SIZE = 3;
  std::array<std::array<char, 3>, 3> board;  // Fixed 3x3 array
};

#endif  // FINAL_BOARD_H_
