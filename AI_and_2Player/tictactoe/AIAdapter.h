// AIAdapter.h
#ifndef AI_ADAPTER_H
#define AI_ADAPTER_H

#include "Board.h"
#include "ai_opponent.h"

inline void convertBoard(const Board& boardObj, char aiBoard[3][3]) {
    const auto& b = boardObj.getBoard();
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            aiBoard[i][j] = (b[i][j] == ' ') ? '_' : b[i][j];
}

#endif // AI_ADAPTER_H
