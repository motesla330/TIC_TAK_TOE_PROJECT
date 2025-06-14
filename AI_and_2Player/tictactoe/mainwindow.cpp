// MainWindow.cpp (updated with AI and 2-player option)
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFont>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    board(),
    logic(board) {
    ui->setupUi(this);

    // Ask for game mode
    QStringList modes = {"Player vs Player", "Player vs AI"};
    bool ok;
    QString mode = QInputDialog::getItem(this, "Game Mode", "Select mode:", modes, 1, false, &ok);
    if (ok && mode == "Player vs AI") {
        vsAI = true;
        QStringList levels = {"Easy", "Medium", "Hard"};
        QString level = QInputDialog::getItem(this, "AI Difficulty", "Choose level:", levels, 2, false, &ok);
        if (ok) {
            if (level == "Easy") aiDifficulty = EASY;
            else if (level == "Medium") aiDifficulty = MEDIUM;
            else aiDifficulty = HARD;
        }
    } else {
        vsAI = false;
    }

    setupBoardUI();
    historyManager.startNewGame(Player::X);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupBoardUI() {
    central = new QWidget(this);
    gridLayout = new QGridLayout(central);
    QFont font("Arial", 24);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            buttons[i][j] = new QPushButton(" ");
            buttons[i][j]->setFixedSize(100, 100);
            buttons[i][j]->setFont(font);
            gridLayout->addWidget(buttons[i][j], i, j);

            connect(buttons[i][j], &QPushButton::clicked, [=]() {
                if (board.getCell(i, j) == ' ') {
                    char symbol = logic.getCurrentPlayer();
                    if (board.setCell(i, j, symbol)) {
                        updateButton(i, j, symbol);
                        historyManager.recordMove(i, j, symbol == 'X' ? Player::X : Player::O);

                        if (logic.checkWin(symbol)) {
                            showEndMessage(QString("Player %1 wins!").arg(symbol));
                            historyManager.endCurrentGame(symbol == 'X' ? Player::X : Player::O);
                            resetGame();
                            return;
                        } else if (logic.isDraw()) {
                            showEndMessage("It's a draw!");
                            historyManager.endCurrentGame(Player::None);
                            resetGame();
                            return;
                        }

                        logic.switchPlayer();

                        // AI Turn (only if enabled and it's O's turn)
                        if (vsAI && logic.getCurrentPlayer() == 'O') {
                            Move aiMove = getAIMove(board, aiDifficulty, 'O', 'X');
                            if (aiMove.row != -1 && aiMove.col != -1 &&
                                board.setCell(aiMove.row, aiMove.col, 'O')) {
                                updateButton(aiMove.row, aiMove.col, 'O');
                                historyManager.recordMove(aiMove.row, aiMove.col, Player::O);

                                if (logic.checkWin('O')) {
                                    showEndMessage("AI (O) wins!");
                                    historyManager.endCurrentGame(Player::O);
                                    resetGame();
                                    return;
                                } else if (logic.isDraw()) {
                                    showEndMessage("It's a draw!");
                                    historyManager.endCurrentGame(Player::None);
                                    resetGame();
                                    return;
                                }
                                logic.switchPlayer();
                            }
                        }
                    }
                }
            });
        }
    }

    setCentralWidget(central);
}

void MainWindow::handleButtonClick() {
    // placeholder – logic handled directly in lambda in setupBoardUI
}

void MainWindow::updateButton(int row, int col, char symbol) {
    buttons[row][col]->setText(QString(symbol));
}

void MainWindow::showEndMessage(const QString &message) {
    QMessageBox::information(this, "Game Over", message);
}

void MainWindow::resetGame() {
    board.resetBoard();
    logic.reset();

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            buttons[i][j]->setText(" ");

    historyManager.startNewGame(Player::X);
}
