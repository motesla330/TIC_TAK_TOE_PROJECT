#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    Board(),
    logic(board) {
    ui->setupUi(this);
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
                handleButtonClick();  // Optional call
                if (board.getCell(i, j) == ' ') {
                    char symbol = logic.getCurrentPlayer();
                    if (board.setCell(i, j, symbol)) {
                        updateButton(i, j, symbol);
                        historyManager.recordMove(i, j,
                                                  symbol == 'X' ? Player::X : Player::O);

                        if (logic.checkWin(symbol)) {
                            showEndMessage(QString("Player %1 wins!").arg(symbol));
                            historyManager.endCurrentGame(symbol == 'X' ? Player::X : Player::O);
                            resetGame();
                        } else if (logic.isDraw()) {
                            showEndMessage("It's a draw!");
                            historyManager.endCurrentGame(Player::None);
                            resetGame();
                        } else {
                            logic.switchPlayer();
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
    Board.resetBoard();
    logic.reset();

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            buttons[i][j]->setText(" ");

    historyManager.startNewGame(Player::X);
}
