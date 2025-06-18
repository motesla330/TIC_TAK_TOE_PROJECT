// Copyright 2025 MahmoudIsmail

#ifndef FINAL_PLAYBOARD_H_
#define FINAL_PLAYBOARD_H_

#include <QWidget>
#include "final/ai_opponent.h"
#include "final/Game.h"
#include "final/gamemanager.h"

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui {
class Form;
}
QT_END_NAMESPACE

class PlayBoard : public QWidget {
Q_OBJECT

 public:
  explicit PlayBoard(QWidget *parent = nullptr);
  ~PlayBoard();
  void setGameMode(int vsAI, Difficulty difficulty = MEDIUM);

 private slots:
  // Game board button slots
  void onButton1Clicked();
  void onButton2Clicked();
  void onButton3Clicked();
  void onButton4Clicked();
  void onButton5Clicked();
  void onButton6Clicked();
  void onButton7Clicked();
  void onButton8Clicked();
  void onButton9Clicked();

  // Control button slots
  void onNewGameButtonClicked();
  void onBackButtonClicked();
  void resetallbuttons();
  void enableallbuttons();
  void disableallbutton();
  void saveGameToDatabase();
  void makeAIMove();
  void onSessionExpired();
  void onUserActivity();

 protected:
  bool eventFilter(QObject *obj, QEvent *event) override;

 private:
  Ui::Form *ui;
  int VsIA;                 // 0 = 2-player mode, 1 = AI mode
  Difficulty aiDifficulty;  // AI difficulty level
  char humanPlayer;         // Human player symbol ('X' or 'O')
  char aiPlayer;            // AI player symbol ('X' or 'O')

  // Helper function to connect all signals
  void connectSignals();
  void makeMove(int row, int col, QPushButton *button);
  QPushButton *getButtonAt(int row, int col);
};

#endif  // FINAL_PLAYBOARD_H_
