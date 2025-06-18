#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <vector>
#include <string>
#include <ctime>

struct GameMove {
    int row;
    int col;
    std::string player;  // Changed from Player to string
    time_t timestamp;
};

struct GameHistory {
    int id;
    time_t startTime;
    time_t endTime;
    std::string startingPlayer;  // Changed from Player to string
    std::string winner;          // Changed from Player to string
    std::vector<GameMove> moves;
};

class GameHistoryManager {
public:
    GameHistoryManager();

    void startNewGame(const std::string& startingPlayer);
    void recordMove(int row, int col, const std::string& player);
    void endCurrentGame(const std::string& winner);
    const std::vector<GameHistory>& getHistory() const;
    bool replayGame(int gameId) const;

private:
    int nextId;
    GameHistory currentGame;
    std::vector<GameHistory> history;
};

#endif // GAMEHISTORYMANAGER_H
