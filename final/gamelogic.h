// Copyright 2025 <MennaAssem>

#ifndef FINAL_GAMELOGIC_H_
#define FINAL_GAMELOGIC_H_

#include "final/Board.h"

class GameLogic {
 public:
    explicit GameLogic(Board &boardRef);

    bool checkWin(char symbol) const;
    bool isDraw() const;
    void switchPlayer();
    char getCurrentPlayer() const;
    void reset();

 private:
    Board &board;
    char currentPlayer;

    // Bitmask representations
    mutable int xMask = 0;
    mutable int oMask = 0;
    char convertToCharArray;
    void updateMasks() const;
    static const int WIN_PATTERNS[8];
};

#endif  // FINAL_GAMELOGIC_H_
