#include "playboard.h"
#include "ui_playboard.h"
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include "home.h"
#include "Board.h"
#include "gamelogic.h"
#include "historymanager.h"
#include "ai_opponent.h"
#include"globals.h"
#include"gamemanager.h"
#include"sessiontimer.h"
#include"login.h"


Board board;
GameLogic gamelogic(board);
GameHistoryManager historyManager;

PlayBoard::PlayBoard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
    //, VsIA(VsAi)// Default to 2-player mode, set to 1 for AI mode
    //  , aiDifficulty(MEDIUM) // Default AI difficulty
    , humanPlayer('X') // Human plays as X
    , aiPlayer('O') // AI plays as O
{
    ui->setupUi(this);
    //timer
    connect(&SessionTimer::instance(), &SessionTimer::sessionExpired,
            this, &PlayBoard::onSessionExpired);

    // Start session timer
    SessionTimer::instance().start();

    // Install event filter to detect user activity
    this->installEventFilter(this);
    connectSignals();
    GameHistoryManager historyManager;
    historyManager.startNewGame("Player X");  // Changed to more descriptive name
    enableallbuttons();

    // Initialize random seed for AI
    srand(time(nullptr));

    // Set initial status
    ui->statusLabel->setText("Player X's Turn");
}

PlayBoard::~PlayBoard()
{
    delete ui;
}

void PlayBoard::setGameMode(int vsAI, Difficulty difficulty)
{
    VsIA = vsAI;
    aiDifficulty = difficulty;
}

void PlayBoard::connectSignals()
{
    // Connect game board buttons
    connect(ui->pushButton_1, &QPushButton::clicked, this, &PlayBoard::onButton1Clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &PlayBoard::onButton2Clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &PlayBoard::onButton3Clicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &PlayBoard::onButton4Clicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &PlayBoard::onButton5Clicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &PlayBoard::onButton6Clicked);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &PlayBoard::onButton7Clicked);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &PlayBoard::onButton8Clicked);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &PlayBoard::onButton9Clicked);

    // Connect control buttons
    connect(ui->newGameButton, &QPushButton::clicked, this, &PlayBoard::onNewGameButtonClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &PlayBoard::onBackButtonClicked);
}

void PlayBoard::makeMove(int row, int col, QPushButton* button)
{
    const char player = gamelogic.getCurrentPlayer();

    // Update UI
    if (player=='X'){
        button->setText(QString(player));
        button->setEnabled(false);
    }
    else {
        button->setText(QString(player));
        button->setStyleSheet("color: red;");
        button->setEnabled(false);
    }

    // Update game state
    board.setCell(row, col, player);

    // Record move in history manager with proper player name
    std::string playerName;
    if (VsIA == 1) {
        playerName = (player == humanPlayer) ? "Player" : "AI";
    } else {
        playerName = std::string("Player ") + player;
    }
    historyManager.recordMove(row, col, playerName);

    gamelogic.switchPlayer();

    // Update status label for next player
    if (VsIA == 1) {
        // In AI mode, show appropriate status
        if (gamelogic.getCurrentPlayer() == aiPlayer) {
            ui->statusLabel->setText("AI's Turn");
        } else {
            ui->statusLabel->setText("Your Turn");
        }
    } else {
        // In 2-player mode
        if (gamelogic.getCurrentPlayer() == 'X') {
            ui->statusLabel->setText("Player X's Turn");
        } else {
            ui->statusLabel->setText("Player O's Turn");
        }
    }

    // Check for win or draw
    if (gamelogic.checkWin(player)) {
        QString winMessage;
        std::string winner;

        if (VsIA == 1) {
            winMessage = (player == humanPlayer) ? "You Win!" : "AI Wins!";
            winner = (player == humanPlayer) ? "Player" : "AI";
        } else {
            winMessage = QString("Player %1 Wins!").arg(player);
            winner = std::string("Player ") + player;
        }

        QMessageBox::information(this, "Game Over", winMessage);
        historyManager.endCurrentGame(winner);

        // Save game to database using the new function
        saveGameToDatabase();

        disableallbutton();
        return;
    }

    // Check for draw
    if (gamelogic.isDraw()) {
        QMessageBox::information(this, "Game Over", "It's a Draw!");
        historyManager.endCurrentGame("tie");

        // Save game to database using the new function
        saveGameToDatabase();

        disableallbutton();
        return;
    }

    // If it's AI mode and now it's AI's turn, make AI move
    if (VsIA == 1 && gamelogic.getCurrentPlayer() == aiPlayer) {
        // Use QTimer to add a small delay for better UX
        QTimer::singleShot(500, this, &PlayBoard::makeAIMove);
    }
}

// New function to save game data to database
void PlayBoard::saveGameToDatabase()
{
    // Get the current game history
    const std::vector<GameHistory>& history = historyManager.getHistory();
    if (history.empty()) return;

    const GameHistory& currentGame = history.back();

    // Convert HistoryManager moves to GameManager move format
    std::vector<struct move> gameMoves;
    for (const GameMove& historyMove : currentGame.moves) {
        struct move gameMove;
        gameMove.player = historyMove.player;
        gameMove.row = historyMove.row;
        gameMove.col = historyMove.col;
        gameMoves.push_back(gameMove);
    }

    // Determine player names and winner
    std::string player1, player2, winner;

    if (VsIA == 1) {
        // AI vs Player mode
        player1 = AUTH->UserName;
        player2 = "AI";
        winner = currentGame.winner;
        if (winner=="Player")
        {winner= AUTH->UserName;}
    } else {
        // Player vs Player mode
        player1 = AUTH->UserName;
        player2 = "Player O";
        if (currentGame.winner == "Player X") {
            winner = AUTH->UserName;
        } else if (currentGame.winner == "Player O") {
            winner = "player2";
        } else {
            winner = "tie";
        }
    }

    // Save to database using GameManager
    GAMEM->playFullGame(AUTH->UserName, player2, gameMoves, winner);
}

void PlayBoard::makeAIMove()
{
    if (gamelogic.getCurrentPlayer() != aiPlayer) {
        return; // Safety check
    }

    // Get AI move
    Move aiMove = getAIMove(board, aiDifficulty, aiPlayer, humanPlayer);

    if (aiMove.row == -1 || aiMove.col == -1) {
        return; // No valid move found
    }

    // Find the corresponding button and make the move
    QPushButton* button = getButtonAt(aiMove.row, aiMove.col);
    if (button && button->isEnabled()) {
        makeMove(aiMove.row, aiMove.col, button);
    }
}

QPushButton* PlayBoard::getButtonAt(int row, int col)
{
    int buttonIndex = row * 3 + col + 1;

    switch (buttonIndex) {
    case 1: return ui->pushButton_1;
    case 2: return ui->pushButton_2;
    case 3: return ui->pushButton_3;
    case 4: return ui->pushButton_4;
    case 5: return ui->pushButton_5;
    case 6: return ui->pushButton_6;
    case 7: return ui->pushButton_7;
    case 8: return ui->pushButton_8;
    case 9: return ui->pushButton_9;
    default: return nullptr;
    }
}

// Modified button click handlers - now much simpler
void PlayBoard::onButton1Clicked()
{
    if (VsIA == 1 && gamelogic.getCurrentPlayer() != humanPlayer) {
        return; // Ignore clicks when it's AI's turn
    }
    makeMove(0, 0, ui->pushButton_1);
}

void PlayBoard::onButton2Clicked()
{
    if (VsIA == 1 && gamelogic.getCurrentPlayer() != humanPlayer) {
        return;
    }
    makeMove(0, 1, ui->pushButton_2);
}

void PlayBoard::onButton3Clicked()
{
    if (VsIA == 1 && gamelogic.getCurrentPlayer() != humanPlayer) {
        return;
    }
    makeMove(0, 2, ui->pushButton_3);
}

void PlayBoard::onButton4Clicked()
{
    if (VsIA == 1 && gamelogic.getCurrentPlayer() != humanPlayer) {
        return;
    }
    makeMove(1, 0, ui->pushButton_4);
}

void PlayBoard::onButton5Clicked()
{
    if (VsIA == 1 && gamelogic.getCurrentPlayer() != humanPlayer) {
        return;
    }
    makeMove(1, 1, ui->pushButton_5);
}

void PlayBoard::onButton6Clicked()
{
    if (VsIA == 1 && gamelogic.getCurrentPlayer() != humanPlayer) {
        return;
    }
    makeMove(1, 2, ui->pushButton_6);
}

void PlayBoard::onButton7Clicked()
{
    if (VsIA == 1 && gamelogic.getCurrentPlayer() != humanPlayer) {
        return;
    }
    makeMove(2, 0, ui->pushButton_7);
}

void PlayBoard::onButton8Clicked()
{
    if (VsIA == 1 && gamelogic.getCurrentPlayer() != humanPlayer) {
        return;
    }
    makeMove(2, 1, ui->pushButton_8);
}

void PlayBoard::onButton9Clicked()
{
    if (VsIA == 1 && gamelogic.getCurrentPlayer() != humanPlayer) {
        return;
    }
    makeMove(2, 2, ui->pushButton_9);
}

void PlayBoard::onNewGameButtonClicked()
{
    resetallbuttons();
    enableallbuttons();
    gamelogic.reset();
    board.resetBoard();

    // Start new game in history manager with proper starting player name
    std::string startingPlayer;
    if (VsIA == 1) {
        startingPlayer = (humanPlayer == 'X') ? "Player" : "AI";
    } else {
        startingPlayer = "Player X";
    }
    historyManager.startNewGame(startingPlayer);

    // Reset status label
    if (VsIA == 1) {
        ui->statusLabel->setText(humanPlayer == 'X' ? "Your Turn" : "AI's Turn");
        // If AI goes first, make AI move
        if (gamelogic.getCurrentPlayer() == aiPlayer) {
            QTimer::singleShot(500, this, &PlayBoard::makeAIMove);
        }
    } else {
        ui->statusLabel->setText("Player X's Turn");
    }
}

void PlayBoard::onBackButtonClicked()
{
    gamelogic.reset();
    board.resetBoard();
    Home *homeWindow = new Home();
    homeWindow->show();
    this->close();
}

void PlayBoard::resetallbuttons()
{
    ui->pushButton_1->setText("");
    ui->pushButton_2->setText("");
    ui->pushButton_3->setText("");
    ui->pushButton_4->setText("");
    ui->pushButton_5->setText("");
    ui->pushButton_6->setText("");
    ui->pushButton_7->setText("");
    ui->pushButton_8->setText("");
    ui->pushButton_9->setText("");
}

void PlayBoard::enableallbuttons()
{
    ui->pushButton_1->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
    ui->pushButton_6->setEnabled(true);
    ui->pushButton_7->setEnabled(true);
    ui->pushButton_8->setEnabled(true);
    ui->pushButton_9->setEnabled(true);
}

void PlayBoard::disableallbutton()
{
    ui->pushButton_1->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_8->setEnabled(false);
    ui->pushButton_9->setEnabled(false);
}
// in playboard.h/.cpp

//timer fun
// Add these methods at the end of home.cpp, before the last }

// Handle session expiry
void PlayBoard::onSessionExpired() {
    QMessageBox::information(this, "Session Expired",
                             "Your session has expired due to inactivity. Please login again.");

    // Save user data before logout
//    saveUserData();

    // Create login window
    Login *loginWindow = new Login();
    loginWindow->show();

    // Close current window
    this->close();
}

// Reset timer on user activity
void PlayBoard::onUserActivity() {
    SessionTimer::instance().reset();
}

// Event filter to detect mouse/keyboard activity
bool PlayBoard::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::MouseButtonPress ||
        event->type() == QEvent::KeyPress ||
        event->type() == QEvent::MouseMove) {
        onUserActivity();
    }
    return QWidget::eventFilter(obj, event);
}
