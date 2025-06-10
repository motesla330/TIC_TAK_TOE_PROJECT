#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GameLogic.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onBoardButtonClicked();
    void onGameOver(Player winner);
    void onNewGameTriggered();

private:
    Ui::MainWindow *ui;
    GameLogic m_gameLogic;
    QPushButton* m_boardButtons[3][3];

    void setupBoard();
    void updateBoard();
    void updateStatus();
    void showGameResult(Player winner);
};

#endif // MAINWINDOW_H
