#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Board.h"

class GameLogic {
public:
    GameLogic(Board& boardRef);

    bool checkWin(char symbol) const;
    bool isDraw() const;
    void switchPlayer();
    char getCurrentPlayer() const;
    void reset();

private:
    Board& board;
    char currentPlayer;

    // Bitmask representations
    mutable int xMask = 0;
    mutable int oMask = 0;

    void updateMasks() const;
    static const int WIN_PATTERNS[8];
};

#endif // GAMELOGIC_H
