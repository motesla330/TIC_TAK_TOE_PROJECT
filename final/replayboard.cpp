// Copyright 2025 MahmoudIsmail

#include <QThread>
#include <QTimer>

#include <vector>
#include <chrono>
#include <thread>

#include "final/replayboard.h"
#include "home.h"
#include "gamemanager.h"
#include "globals.h"

ReplayBoard::ReplayBoard(QWidget *parent) : QWidget(parent) {
    ui.setupUi(this);

    // Connect back button signal
    connect(ui.replayBackButton, &QPushButton::clicked,
            this, &ReplayBoard::onBackButtonClicked);
    connect(ui.pushButton, &QPushButton::clicked,
            this, &ReplayBoard::onstartButtonCliced);
}

ReplayBoard::~ReplayBoard() {}

void ReplayBoard::setButtonText(int row, int col, const QString& text) {
    QPushButton* button = nullptr;

    if (row == 0 && col == 0) button = ui.replayBtn_0_0;
    else if (row == 0 && col == 1) button = ui.replayBtn_0_1;
    else if (row == 0 && col == 2) button = ui.replayBtn_0_2;
    else if (row == 1 && col == 0) button = ui.replayBtn_1_0;
    else if (row == 1 && col == 1) button = ui.replayBtn_1_1;
    else if (row == 1 && col == 2) button = ui.replayBtn_1_2;
    else if (row == 2 && col == 0) button = ui.replayBtn_2_0;
    else if (row == 2 && col == 1) button = ui.replayBtn_2_1;
    else if (row == 2 && col == 2) button = ui.replayBtn_2_2;

    button->setText(text);

    // Only set red color for 'O' or 'o'
    if (text == 'O' || text == 'o') {
        button->setStyleSheet("color: red;");
    } else {
        button->setStyleSheet("color: blue;");
    }
}

void ReplayBoard::onBackButtonClicked() {
    Home* homeWindow = new Home();
    homeWindow->show();
    this->close();
}

void ReplayBoard::view() {
    // Get moves using global indexforgames
    std::vector<std::tuple<char, int, int>> moves =
        GAMEM->replayGameByIndex(indexforgames);

    // Clear the board first
    clearBoard();

    // Use QTimer::singleShot for each move with cumulative delays
    for (size_t i = 0; i < moves.size(); ++i) {
        const auto& [symbol, row, col] = moves[i];

        // Schedule each move with 2-second intervals
        QTimer::singleShot(1000 * (i + 1), [this, symbol, row, col]() {
            setButtonText(row, col, QString(QChar(symbol)));
        });
    }
}

void ReplayBoard::clearBoard() {
    // Clear all buttons
    setButtonText(0, 0, "");
    setButtonText(0, 1, "");
    setButtonText(0, 2, "");
    setButtonText(1, 0, "");
    setButtonText(1, 1, "");
    setButtonText(1, 2, "");
    setButtonText(2, 0, "");
    setButtonText(2, 1, "");
    setButtonText(2, 2, "");
}

void ReplayBoard::onstartButtonCliced() {
    view();
}
