// Copyright 2025 <MahmoudIsmail>

#include <QMessageBox>
#include <QHeaderView>
#include <QDateTime>
#include <QDebug>
#include <QRadioButton>
#include <QTableWidget>
#include <QAction>
#include <QMainWindow>

#include <fstream>
#include <string>
#include <chrono>
#include <json.hpp>

#include "final/home.h"
#include "final/ui_home.h"
#include "final/login.h"
#include "final/playboard.h"
#include "final/globals.h"
#include "final/sessiontimer.h"
#include "final/replayboard.h"

using json = nlohmann::json;

// Global variables for user data
QString username = "admin";  // Default fallback
qint16 no_games = 0;
qint16 no_wins = 0;
qint16 no_losses = 0;
qint16 no_draws = 0;

Difficulty level;

void Home::onGameHistoryDoubleClicked(const QModelIndex &index) {}

Home::Home(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Home) {
    ui->setupUi(this);

    // Load user data first
    loadUserData();

    // Update UI with loaded data
    updateWelcomeLabel();
    updateStatsLabel();

    // Timer setup
    connect(&SessionTimer::instance(), &SessionTimer::sessionExpired,
            this, &Home::onSessionExpired);

    SessionTimer::instance().updateTimeout(60000);  // 5 minutes
    SessionTimer::instance().start();

    this->installEventFilter(this);  // Install event filter

    loadGameHistoryFromDatabase();  // Load and display game history

    // Radial button default
    ui->radioButton->setChecked(true);  // Default selection

    connect(ui->radioButton, &QRadioButton::clicked,
        [this]() { level = EASY; });
    connect(ui->radioButton_2, &QRadioButton::clicked,
        [this]() { level = MEDIUM; });
    connect(ui->radioButton_3, &QRadioButton::clicked,
        [this]() { level = HARD; });

    connect(ui->actionFull_Screen, &QAction::triggered, this, [this]() {
        this->isFullScreen() ? this->showNormal() : this->showFullScreen();
    });

    connect(ui->gameHistoryTable, &QTableWidget::cellDoubleClicked,
            this, &Home::onGameHistoryTableClicked);
}

Home::~Home() {
    delete ui;
}

void Home::loadUserData() {
    try {
        std::ifstream userFile("user_data.json");
        if (userFile.is_open()) {
            json userData;
            userFile >> userData;
            userFile.close();

            if (userData.contains("username")) {
                username = QString::fromStdString(userData["username"]);
            }

            if (userData.contains("stats")) {
                const auto &stats = userData["stats"];
                if (stats.contains("games")) no_games = stats["games"];
                if (stats.contains("wins")) no_wins = stats["wins"];
                if (stats.contains("losses")) no_losses = stats["losses"];
                if (stats.contains("draws")) no_draws = stats["draws"];
            }

            qDebug() << "User data loaded successfully";
        } else {
            qDebug() << "No user_data.json file found - using defaults";
            calculateStatsFromGames();
        }
    } catch (const std::exception &e) {
        qDebug() << "Error loading user data:" << e.what();
        calculateStatsFromGames();
    }
}

void Home::calculateStatsFromGames() {
    try {
        std::ifstream inFile("games.json");
        if (!inFile.is_open()) return;

        json allGames;
        inFile >> allGames;
        inFile.close();

        no_games = no_wins = no_losses = no_draws = 0;

        for (const auto &game : allGames) {
            no_games++;

            std::string winner = game["winner"];
            std::string player1 = game["player1"];
            std::string player2 = game["player2"];

            if (winner == "tie") {
                no_draws++;
            } else if (winner == "Player" || winner == "Player X" ||
                       (winner == player1 &&
                        (player1 == "Player" || player1 == "Player X" ||
                         player1 == username.toStdString()))) {
                no_wins++;
            } else {
                no_losses++;
            }
        }

        qDebug() << "Stats calculated from games:" << no_games << "games,"
                 << no_wins << "wins," << no_losses << "losses,"
                 << no_draws << "draws";

        saveUserData();
    } catch (const std::exception &e) {
        qDebug() << "Error calculating stats from games:" << e.what();
    }
}

void Home::saveUserData() {
    try {
        json userData;
        userData["username"] = username.toStdString();
        userData["stats"]["games"] = no_games;
        userData["stats"]["wins"] = no_wins;
        userData["stats"]["losses"] = no_losses;
        userData["stats"]["draws"] = no_draws;
        userData["last_updated"] = QDateTime::currentDateTime()
                                       .toString(Qt::ISODate)
                                       .toStdString();

        std::ofstream userFile("user_data.json");
        if (userFile.is_open()) {
            userFile << userData.dump(4);
            userFile.close();
            qDebug() << "User data saved successfully";
        } else {
            qDebug() << "Failed to save user data";
        }
    } catch (const std::exception &e) {
        qDebug() << "Error saving user data:" << e.what();
    }
}

void Home::updateWelcomeLabel() {
    username = QString::fromStdString(AUTH->UserName);
    ui->userLabel->setText("👤 Welcome, " + username);
}

void Home::updateStatsLabel() {
    QString statsText = QString("📊 Quick Stats\nGames: %1 | Wins: %2 | "
                                 "Losses: %3 | Draws: %4")
                            .arg(no_games)
                            .arg(no_wins)
                            .arg(no_losses)
                            .arg(no_draws);
    ui->statsLabel->setText(statsText);
}

void Home::loadGameHistoryFromDatabase() {
    try {
        ui->gameHistoryTable->setRowCount(0);

        std::ifstream inFile("games.json");
        if (!inFile.is_open()) {
            qDebug() <<
            "No games.json file found - starting with empty history";
            return;
        }

        json allGames;
        inFile >> allGames;
        inFile.close();

        for (const auto &game : allGames) {
            addGameToHistoryTable(game);
        }

        calculateStatsFromGames();
        updateStatsLabel();
    } catch (const std::exception &e) {
        qDebug() << "Error loading game history:" << e.what();
        QMessageBox::warning(this, "Warning",
                             "Could not load game history from database.");
    }
}

void Home::addGameToHistoryTable(const json &gameData) {
    try {
        int rowCount = ui->gameHistoryTable->rowCount();
        ui->gameHistoryTable->insertRow(rowCount);

        std::string player1 = gameData["player1"];
        std::string player2 = gameData["player2"];
        std::string winner = gameData["winner"];
        std::string timestamp = gameData["timestamp"];

        int moveCount = 0;
        if (gameData.contains("moves") && gameData["moves"].is_array()) {
            moveCount = gameData["moves"].size();
            if (moveCount > 9) moveCount = 9;
        }

        QString winnerDisplay;
        if (winner == "tie") {
            winnerDisplay = "Draw";
        } else if (winner == player1) {
            winnerDisplay = QString::fromStdString(player1);
        } else if (winner == player2) {
            winnerDisplay = QString::fromStdString(player2);
        } else {
            winnerDisplay = QString::fromStdString(winner);
        }

        QString dateDisplay = QString::fromStdString(timestamp);

        QString opponentDisplay;
        if ((player1 == "Player" && player2 == "AI") ||
            (player1 == "AI" && player2 == "Player")) {
            opponentDisplay = "AI";
        } else if ((player1 == "Player X" && player2 == "Player O") ||
                   (player1 == "Player O" && player2 == "Player X")) {
            opponentDisplay = (player2 == "Player X") ? "Player X" : "Player O";
        } else {
            opponentDisplay = QString::fromStdString(player2);
        }

        ui->gameHistoryTable->setItem(rowCount, 0,
                                      new QTableWidgetItem(winnerDisplay));
        ui->gameHistoryTable->setItem(rowCount, 1,
                                      new QTableWidgetItem(dateDisplay));
        ui->gameHistoryTable->setItem(rowCount, 2,
                                      new QTableWidgetItem(
                                        QString::number(moveCount)));
        ui->gameHistoryTable->setItem(rowCount, 3,
                                      new QTableWidgetItem(opponentDisplay));

        QColor color;
        if (winner == "tie") {
            color = QColor(255, 255, 200);
        } else if (winnerDisplay.contains("Player")
         || winnerDisplay == username ||
                   winnerDisplay == "You") {
            color = QColor(200, 255, 200);
        } else {
            color = QColor(255, 200, 200);
        }

        for (int col = 0; col < ui->gameHistoryTable->columnCount(); ++col) {
            ui->gameHistoryTable->item(rowCount, col)->setBackground(color);
        }
    } catch (const std::exception &e) {
        qDebug() << "Error adding game to history table:" << e.what();
    }
}

void Home::updatePlayerStats() {
    calculateStatsFromGames();
    updateStatsLabel();
}

void Home::addGameToHistory(const QString &winner, const QString &date,
                             const QString &moves, const QString &opponent) {
    int rowCount = ui->gameHistoryTable->rowCount();
    ui->gameHistoryTable->insertRow(rowCount);

    ui->gameHistoryTable->setItem(rowCount, 0, new QTableWidgetItem(winner));
    ui->gameHistoryTable->setItem(rowCount, 1, new QTableWidgetItem(date));
    ui->gameHistoryTable->setItem(rowCount, 2, new QTableWidgetItem(moves));
    ui->gameHistoryTable->setItem(rowCount, 3, new QTableWidgetItem(opponent));
    ui->gameHistoryTable->setItem(rowCount, 4, new QTableWidgetItem("N/A"));
}

void Home::on_pushButton_clicked() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Logout",
                                  "Are you sure you want to logout?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        saveUserData();
        Login *loginWindow = new Login();
        loginWindow->show();
        this->close();
    }
}

void Home::on_aiButton_clicked() {
    VsAi = 1;
    PlayBoard *playboard = new PlayBoard();
    playboard->setGameMode(VsAi, level);
    playboard->show();
    this->close();
}

void Home::on_friendButton_clicked() {
    VsAi = 0;
    PlayBoard *playboard = new PlayBoard();
    playboard->setGameMode(VsAi, level);
    playboard->show();
    this->close();
}

void Home::onSessionExpired() {
    SessionTimer::instance().reset();
    QMessageBox::information(this, "Session Expired",
                             "Your session has expired due to inactivity. "
                             "Please login again.");
    saveUserData();
    Login *loginWindow = new Login();
    loginWindow->show();
    this->close();
}

void Home::onUserActivity() {
    SessionTimer::instance().reset();
}

bool Home::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress ||
        event->type() == QEvent::KeyPress ||
        event->type() == QEvent::MouseMove) {
        onUserActivity();
    }
    return QMainWindow::eventFilter(obj, event);
}

void Home::onGameHistoryTableClicked(int row, int column) {
    SessionTimer::instance().stop();
    indexforgames = row;

    ReplayBoard *repl = new ReplayBoard;
    repl->show();
    this->close();
}
