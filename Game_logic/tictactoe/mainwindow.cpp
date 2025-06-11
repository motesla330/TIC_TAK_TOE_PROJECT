#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    Board(),
    gamelogic(board) {
    ui->setupUi(this);
    setupBoardUI();

    historymanager.startNewGame(Player::X);
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
                    char symbol = gamegamelogic.getCurrentPlayer();
                    if (board.setCell(i, j, symbol)) {
                        updateButton(i, j, symbol);
                        historymanager.recordMove(i, j,
                                                  symbol == 'X' ? Player::X : Player::O);

                        if (gamegamelogic.checkWin(symbol)) {
                            showEndMessage(QString("Player %1 wins!").arg(symbol));
                            historymanager.endCurrentGame(symbol == 'X' ? Player::X : Player::O);
                            resetGame();
                        } else if (gamegamelogic.isDraw()) {
                            showEndMessage("It's a draw!");
                            historymanager.endCurrentGame(Player::None);
                            resetGame();
                        } else {
                            gamegamelogic.switchPlayer();
                        }
                    }
                }
            });
        }
    }

    setCentralWidget(central);
}


void MainWindow::handleButtonClick() {
    // placeholder – gamegamelogic handled directly in lambda in setupBoardUI
}

void MainWindow::updateButton(int row, int col, char symbol) {
    buttons[row][col]->setText(QString(symbol));
}

void MainWindow::showEndMessage(const QString &message) {
    QMessageBox::information(this, "Game Over", message);
}

void MainWindow::resetGame() {
    Board.resetBoard();
    gamegamelogic.reset();

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            buttons[i][j]->setText(" ");

    historymanager.startNewGame(Player::X);
}
