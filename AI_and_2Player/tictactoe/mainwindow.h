#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include "Board.h"
#include "gamelogic.h"
#include "historymanager.h"
#include "AIAdapter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleButtonClick();

private:
    Ui::MainWindow *ui;

    QWidget* central;
    QGridLayout* gridLayout;
    QPushButton* buttons[3][3];

    Board board;
    GameLogic logic;
    GameHistoryManager historyManager;

    void setupboardUI();
    void resetGame();
    void updateButton(int row, int col, char symbol);
    void showEndMessage(const QString& message);

    bool vsAI = true;
    Difficulty aiDifficulty = HARD;
    char aiPlayer = 'O';
    bool gameInProgress = false;
    void setupGameMode();
    void makeAIMove();
    void handleAITurn();

};


#endif // MAINWINDOW_H
