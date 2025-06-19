// Copyright 2025 <MahmoudIsmail>

#ifndef FINAL_HOME_H_
#define FINAL_HOME_H_

#include <QMainWindow>
#include <QMessageBox>
#include <QModelIndex>
#include "json.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class Home;
}
QT_END_NAMESPACE

class Home : public QMainWindow {
  Q_OBJECT

 public:
  explicit Home(QWidget *parent = nullptr);
  void addGameToHistory(const QString &winner,
                        const QString &date,
                        const QString &moves,
                        const QString &opponent);
  ~Home();

 private slots:
  void on_aiButton_clicked();
  void on_friendButton_clicked();
  void on_pushButton_clicked();  // Logout button
  void onGameHistoryDoubleClicked(const QModelIndex &index);
  void onSessionExpired();       // Timer expired
  void onUserActivity();         // Any user activity resets timer
  void onGameHistoryTableClicked(int row, int column);  // Replay on click

 private:
  Ui::Home *ui;
  void setupGameHistoryTable();
  void loadGameHistoryFromDatabase();
  void addGameToHistoryTable(const nlohmann::json &gameData);
  void updatePlayerStats();
  void loadUserData();
  void calculateStatsFromGames();
  void saveUserData();
  void updateWelcomeLabel();
  void updateStatsLabel();

 protected:
  bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif  // FINAL_HOME_H_
