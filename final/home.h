#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QMessageBox>
#include "json.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class Home; }
QT_END_NAMESPACE



class Home : public QMainWindow
{
    Q_OBJECT

public:

    Home(QWidget *parent = nullptr);
    void addGameToHistory(const QString &winner, const QString &date, const QString &moves, const QString &opponent);
   // void scaleWidgets();
    //void scaleWidget(QWidget *widget, double scaleX, double scaleY);
    // In home.h - WRONG:

   // signals:
   // void gameSelectedForReplay(const QString& timestamp);
    // In home.h - CORRECT:

  // static void checkTimeLeft();

    ~Home();

private slots:
    //void on_logoutButton_clicked();
    void on_aiButton_clicked();
    void on_friendButton_clicked();
    void on_pushButton_clicked();// logout button
    void onGameHistoryDoubleClicked(const QModelIndex &index);
    //timer
    void onSessionExpired();
    void onUserActivity();
    //click on table
  void onGameHistoryTableClicked(int row, int column);
private:
    Ui::Home *ui;
    void setupGameHistoryTable();
    void loadGameHistoryFromDatabase();
    void addGameToHistoryTable(const nlohmann::json& gameData);
    void updatePlayerStats();
    void loadUserData();
    void calculateStatsFromGames();
    void saveUserData();
    void updateWelcomeLabel();
    void updateStatsLabel();
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};

#endif // HOME_H
