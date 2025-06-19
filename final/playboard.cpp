// Copyright 2025 MahmoudIsmail

#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>

#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#include "final/playboard.h"
#include "final/home.h"
#include "final/Board.h"
#include "final/gamelogic.h"
#include "final/historymanager.h"
#include "final/ai_opponent.h"
#include "final/globals.h"
#include "final/gamemanager.h"
#include "final/sessiontimer.h"
#include "final/login.h"

Board board;
GameLogic gamelogic(board);
GameHistoryManager historyManager;

PlayBoard::PlayBoard(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Form),
      humanPlayer('X'),
      aiPlayer('O') {
  ui->setupUi(this);

  connect(&SessionTimer::instance(), &SessionTimer::sessionExpired,
          this, &PlayBoard::onSessionExpired);

  SessionTimer::instance().start();
  this->installEventFilter(this);
  connectSignals();

  GameHistoryManager historyManager;
  historyManager.startNewGame("Player X");

  enableallbuttons();

  srand(time(nullptr));
  ui->statusLabel->setText("Player X's Turn");
}

PlayBoard::~PlayBoard() {
  delete ui;
}

void PlayBoard::setGameMode(int vsAI, Difficulty difficulty) {
  VsIA = vsAI;
  aiDifficulty = difficulty;
}

void PlayBoard::connectSignals() {
  connect(ui->pushButton_1,
     &QPushButton::clicked, this, &PlayBoard::onButton1Clicked);
  connect(ui->pushButton_2,
     &QPushButton::clicked, this, &PlayBoard::onButton2Clicked);
  connect(ui->pushButton_3,
     &QPushButton::clicked, this, &PlayBoard::onButton3Clicked);
  connect(ui->pushButton_4,
     &QPushButton::clicked, this, &PlayBoard::onButton4Clicked);
  connect(ui->pushButton_5,
     &QPushButton::clicked, this, &PlayBoard::onButton5Clicked);
  connect(ui->pushButton_6,
     &QPushButton::clicked, this, &PlayBoard::onButton6Clicked);
  connect(ui->pushButton_7,
     &QPushButton::clicked, this, &PlayBoard::onButton7Clicked);
  connect(ui->pushButton_8,
     &QPushButton::clicked, this, &PlayBoard::onButton8Clicked);
  connect(ui->pushButton_9,
     &QPushButton::clicked, this, &PlayBoard::onButton9Clicked);

  connect(ui->newGameButton,
     &QPushButton::clicked, this, &PlayBoard::onNewGameButtonClicked);
  connect(ui->backButton,
     &QPushButton::clicked, this, &PlayBoard::onBackButtonClicked);
}

void PlayBoard::makeMove(int row, int col, QPushButton *button) {
  const char player = gamelogic.getCurrentPlayer();

  button->setText(QString(player));
  button->setEnabled(false);
  if (player == 'O') {
    button->setStyleSheet("color: red;");
  }

  board.setCell(row, col, player);

  std::string playerName;
  if (VsIA == 1) {
    playerName = (player == humanPlayer) ? "Player" : "AI";
  } else {
    playerName = std::string("Player ") + player;
  }
  historyManager.recordMove(row, col, playerName);

  gamelogic.switchPlayer();

  if (VsIA == 1) {
    ui->statusLabel->setText(gamelogic.getCurrentPlayer() == aiPlayer
                             ? "AI's Turn"
                             : "Your Turn");
  } else {
    ui->statusLabel->setText(QString("Player %1's Turn")
                             .arg(gamelogic.getCurrentPlayer()));
  }

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
    saveGameToDatabase();
    disableallbutton();
    return;
  }

  if (gamelogic.isDraw()) {
    QMessageBox::information(this, "Game Over", "It's a Draw!");
    historyManager.endCurrentGame("tie");
    saveGameToDatabase();
    disableallbutton();
    return;
  }

  if (VsIA == 1 && gamelogic.getCurrentPlayer() == aiPlayer) {
    QTimer::singleShot(500, this, &PlayBoard::makeAIMove);
  }
}

void PlayBoard::saveGameToDatabase() {
  const std::vector<GameHistory> &history = historyManager.getHistory();
  if (history.empty()) return;

  const GameHistory &currentGame = history.back();
  std::vector<struct move> gameMoves;
  for (const GameMove &historyMove : currentGame.moves) {
    struct move gameMove;
    gameMove.player = historyMove.player;
    gameMove.row = historyMove.row;
    gameMove.col = historyMove.col;
    gameMoves.push_back(gameMove);
  }

  std::string player1, player2, winner;
  if (VsIA == 1) {
    player1 = AUTH->UserName;
    player2 = "AI";
    winner = currentGame.winner;
    if (winner == "Player") {
      winner = AUTH->UserName;
    }
  } else {
    player1 = AUTH->UserName;
    player2 = "Player O";
    winner = currentGame.winner ==
     "Player X" ? AUTH->UserName
      : (currentGame.winner == "Player O" ? "player2" : "tie");
  }

  GAMEM->playFullGame(AUTH->UserName, player2, gameMoves, winner);
}

void PlayBoard::makeAIMove() {
  if (gamelogic.getCurrentPlayer() != aiPlayer) return;

  Move aiMove = getAIMove(board, aiDifficulty, aiPlayer, humanPlayer);
  if (aiMove.row == -1 || aiMove.col == -1) return;

  QPushButton *button = getButtonAt(aiMove.row, aiMove.col);
  if (button && button->isEnabled()) {
    makeMove(aiMove.row, aiMove.col, button);
  }
}

QPushButton *PlayBoard::getButtonAt(int row, int col) {
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

#define DEF_CLICK_HANDLER(BUTTON_NUM, ROW, COL)                \
  void PlayBoard::onButton##BUTTON_NUM##Clicked() {            \
    if (VsIA == 1 && gamelogic.getCurrentPlayer() != humanPlayer) return; \
    makeMove(ROW, COL, ui->pushButton_##BUTTON_NUM);           \
  }

DEF_CLICK_HANDLER(1, 0, 0)
DEF_CLICK_HANDLER(2, 0, 1)
DEF_CLICK_HANDLER(3, 0, 2)
DEF_CLICK_HANDLER(4, 1, 0)
DEF_CLICK_HANDLER(5, 1, 1)
DEF_CLICK_HANDLER(6, 1, 2)
DEF_CLICK_HANDLER(7, 2, 0)
DEF_CLICK_HANDLER(8, 2, 1)
DEF_CLICK_HANDLER(9, 2, 2)

void PlayBoard::onNewGameButtonClicked() {
  resetallbuttons();
  enableallbuttons();
  gamelogic.reset();
  board.resetBoard();

  std::string startingPlayer = VsIA == 1
                              ? (humanPlayer == 'X' ? "Player" : "AI")
                              : "Player X";
  historyManager.startNewGame(startingPlayer);

  if (VsIA == 1) {
    ui->statusLabel->setText(humanPlayer == 'X' ? "Your Turn" : "AI's Turn");
    if (gamelogic.getCurrentPlayer() == aiPlayer) {
      QTimer::singleShot(500, this, &PlayBoard::makeAIMove);
    }
  } else {
    ui->statusLabel->setText("Player X's Turn");
  }
}

void PlayBoard::onBackButtonClicked() {
  gamelogic.reset();
  board.resetBoard();
  Home *homeWindow = new Home();
  homeWindow->show();
  this->close();
}

void PlayBoard::resetallbuttons() {
  for (int i = 1; i <= 9; ++i) {
    getButtonAt((i - 1) / 3, (i - 1) % 3)->setText("");
  }
}

void PlayBoard::enableallbuttons() {
  for (int i = 1; i <= 9; ++i) {
    getButtonAt((i - 1) / 3, (i - 1) % 3)->setEnabled(true);
  }
}

void PlayBoard::disableallbutton() {
  for (int i = 1; i <= 9; ++i) {
    getButtonAt((i - 1) / 3, (i - 1) % 3)->setEnabled(false);
  }
}

void PlayBoard::onSessionExpired() {
  QMessageBox::information(this, "Session Expired",
   "Your session has expired due to inactivity. Please login again.");
  Login *loginWindow = new Login();
  loginWindow->show();
  this->close();
}

void PlayBoard::onUserActivity() {
  SessionTimer::instance().reset();
}

bool PlayBoard::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() == QEvent::MouseButtonPress ||
      event->type() == QEvent::KeyPress ||
      event->type() == QEvent::MouseMove) {
    onUserActivity();
  }
  return QWidget::eventFilter(obj, event);
}



