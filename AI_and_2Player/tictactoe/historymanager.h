#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H
#include <vector>
#include <ctime>

enum class Player { None, X, O };

struct GameMove {
    int row;
    int col;
    Player player;
    time_t timestamp;
};

struct GameHistory {
    int id;
    time_t startTime;
    time_t endTime;
    Player startingPlayer;
    Player winner;
    std::vector<GameMove> moves;
};

class GameHistoryManager {
public:
    GameHistoryManager();

    void startNewGame(Player startingPlayer);
    void recordMove(int row, int col, Player player);
    void endCurrentGame(Player winner);
    const std::vector<GameHistory>& getHistory() const;
    bool replayGame(int gameId) const;

private:
    int nextId;
    GameHistory currentGame;
    std::vector<GameHistory> history;
};

#endif // GAMEHISTORYMANAGER_H