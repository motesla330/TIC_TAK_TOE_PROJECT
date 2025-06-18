#include "home.h"
#include "ui_home.h"
#include "login.h"
#include <QMessageBox>
#include "playboard.h"
#include"globals.h"
#include <QHeaderView>
#include <fstream>
#include <json.hpp>
#include <QDebug>
#include <QDateTime>
#include <chrono>
#include <QDebug>
#include"sessiontimer.h"
#include<string>
#include"replayboard.h"

using json = nlohmann::json;

// Global variables for user data
QString username = "admin";  // Default fallback
qint16 no_games = 0;
qint16 no_wins = 0;
qint16 no_losses = 0;
qint16 no_draws = 0;

Difficulty level;

/*********************/
void Home::onGameHistoryDoubleClicked(const QModelIndex &index){}
Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);

    // Load user data first
    loadUserData();

    // Update UI with loaded data
    updateWelcomeLabel();
    updateStatsLabel();

    //timer setup
    connect(&SessionTimer::instance(), &SessionTimer::sessionExpired,
            this, &Home::onSessionExpired);

    // Set a longer timeout (5 minutes = 300000ms) and start
    SessionTimer::instance().updateTimeout(60000); // 5 minutes instead of 1
    SessionTimer::instance().start();

    // Install event filter
    this->installEventFilter(this);


    // Load and display game history from database
    loadGameHistoryFromDatabase();

    //radial button
    // Direct lambda connections
    ui->radioButton->setChecked(true);//default selection

    connect(ui->radioButton, &QRadioButton::clicked, [this]() { level = EASY; });
    connect(ui->radioButton_2, &QRadioButton::clicked, [this]() { level = MEDIUM; });
    connect(ui->radioButton_3, &QRadioButton::clicked, [this]() { level = HARD; });

    //full screen
    connect(ui->actionFull_Screen, &QAction::triggered, this, [this]() {
        this->isFullScreen() ? this->showNormal() : this->showFullScreen();
    });

    //click on table
    connect(ui->gameHistoryTable, &QTableWidget::cellDoubleClicked,
            this, &Home::onGameHistoryTableClicked);


};

Home::~Home()
{
    delete ui;
}

void Home::loadUserData()
{
    try {
        // Try to load user data from JSON file
        std::ifstream userFile("user_data.json");
        if (userFile.is_open()) {
            json userData;
            userFile >> userData;
            userFile.close();

            // Load username
            if (userData.contains("username")) {
                username = QString::fromStdString(userData["username"]);
            }

            // Load user stats if available
            if (userData.contains("stats")) {
                const auto& stats = userData["stats"];
                if (stats.contains("games")) no_games = stats["games"];
                if (stats.contains("wins")) no_wins = stats["wins"];
                if (stats.contains("losses")) no_losses = stats["losses"];
                if (stats.contains("draws")) no_draws = stats["draws"];
            }

            qDebug() << "User data loaded successfully";
        } else {
            qDebug() << "No user_data.json file found - using defaults";
            // Calculate stats from games.json if user_data.json doesn't exist
            calculateStatsFromGames();
        }
    } catch (const std::exception& e) {
        qDebug() << "Error loading user data:" << e.what();
        // Fallback to calculating from games
        calculateStatsFromGames();
    }
}

void Home::calculateStatsFromGames()
{
    try {
        std::ifstream inFile("games.json");
        if (!inFile.is_open()) {
            // No games file, keep default values
            return;
        }

        json allGames;
        inFile >> allGames;
        inFile.close();

        // Reset counters
        no_games = 0;
        no_wins = 0;
        no_losses = 0;
        no_draws = 0;

        // Count games and results
        for (const auto& game : allGames) {
            no_games++;

            std::string winner = game["winner"];
            std::string player1 = game["player1"];
            std::string player2 = game["player2"];

            if (winner == "tie") {
                no_draws++;
            } else if (winner == "Player" || winner == "Player X" ||
                       (winner == player1 && (player1 == "Player" || player1 == "Player X" || player1 == username.toStdString()))) {
                no_wins++;
            } else {
                no_losses++;
            }
        }

        qDebug() << "Stats calculated from games:" << no_games << "games," << no_wins << "wins," << no_losses << "losses," << no_draws << "draws";

        // Save calculated stats to user_data.json for future use
        saveUserData();

    } catch (const std::exception& e) {
        qDebug() << "Error calculating stats from games:" << e.what();
    }
}

void Home::saveUserData()
{
    try {
        json userData;
        userData["username"] = username.toStdString();
        userData["stats"]["games"] = no_games;
        userData["stats"]["wins"] = no_wins;
        userData["stats"]["losses"] = no_losses;
        userData["stats"]["draws"] = no_draws;
        userData["last_updated"] = QDateTime::currentDateTime().toString(Qt::ISODate).toStdString();

        std::ofstream userFile("user_data.json");
        if (userFile.is_open()) {
            userFile << userData.dump(4); // Pretty print with 4 spaces
            userFile.close();
            qDebug() << "User data saved successfully";
        } else {
            qDebug() << "Failed to save user data";
        }
    } catch (const std::exception& e) {
        qDebug() << "Error saving user data:" << e.what();
    }
}

void Home::updateWelcomeLabel()
{
    username=QString::fromStdString(AUTH->UserName);
    ui->userLabel->setText("👤 Welcome, " + username);
}

void Home::updateStatsLabel()
{
    QString statsText = QString("📊 Quick Stats\nGames: %1 | Wins: %2 | Losses: %3 | Draws: %4")
                            .arg(no_games)
                            .arg(no_wins)
                            .arg(no_losses)
                            .arg(no_draws);
    ui->statsLabel->setText(statsText);
}


void Home::loadGameHistoryFromDatabase()
{
    try {
        // Clear existing table content
        ui->gameHistoryTable->setRowCount(0);

        // Load games from JSON file
        std::ifstream inFile("games.json");
        if (!inFile.is_open()) {
            qDebug() << "No games.json file found - starting with empty history";
            return;
        }

        json allGames;
        inFile >> allGames;
        inFile.close();

        // Process each game and add to table
        for (const auto& game : allGames) {
            addGameToHistoryTable(game);
        }

        // Recalculate and update stats after loading games
        calculateStatsFromGames();
        updateStatsLabel();

    } catch (const std::exception& e) {
        qDebug() << "Error loading game history:" << e.what();
        QMessageBox::warning(this, "Warning", "Could not load game history from database.");
    }
}

void Home::addGameToHistoryTable(const json& gameData)
{
    try {
        int rowCount = ui->gameHistoryTable->rowCount();
        ui->gameHistoryTable->insertRow(rowCount);

        // Extract game information
        std::string player1 = gameData["player1"];
        std::string player2 = gameData["player2"];
        std::string winner = gameData["winner"];
        std::string timestamp = gameData["timestamp"];

        // Count moves
           int moveCount = 0;
            if (gameData.contains("moves") && gameData["moves"].is_array()) {
                moveCount = gameData["moves"].size();
                if (moveCount>9)moveCount=9;
            }

        // Format winner display
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

        // Format date (extract date part from timestamp)
        QString dateDisplay = QString::fromStdString(timestamp);
       // if (dateDisplay.contains(" ")) {
           // dateDisplay = dateDisplay.split(" ")[0]; // Take only date part
       // }

        // Determine opponent (for current user perspective)
        QString opponentDisplay;
        if (player1 == "Player" && player2 == "AI") {
            opponentDisplay = "AI";
        } else if (player1 == "AI" && player2 == "Player") {
            opponentDisplay = "AI";
        } else if (player1 == "Player X" && player2 == "Player O") {
            opponentDisplay = "Player O";
        } else if (player1 == "Player O" && player2 == "Player X") {
            opponentDisplay = "Player X";
        } else {
            opponentDisplay = QString::fromStdString(player2);
        }

        // Calculate approximate game duration (rough estimate: 30 seconds per move)
        //QString duration = QString::number(moveCount * 30) + "s";

        // Add data to table
        ui->gameHistoryTable->setItem(rowCount, 0, new QTableWidgetItem(winnerDisplay));
        ui->gameHistoryTable->setItem(rowCount, 1, new QTableWidgetItem(dateDisplay));
        ui->gameHistoryTable->setItem(rowCount, 2, new QTableWidgetItem(QString::number(moveCount)));
        ui->gameHistoryTable->setItem(rowCount, 3, new QTableWidgetItem(opponentDisplay));
        //ui->gameHistoryTable->setItem(rowCount, 4, new QTableWidgetItem(duration));

        // Set row color based on result (comparing with current username)
        if (winner == "tie") {
            // Yellow for draws
            for (int col = 0; col < ui->gameHistoryTable->columnCount(); ++col) {
                ui->gameHistoryTable->item(rowCount, col)->setBackground(QColor(255, 255, 200));
            }
        } else if (winnerDisplay.contains("Player") || winnerDisplay == username || winnerDisplay == "You") {
            // Light green for wins
            for (int col = 0; col < ui->gameHistoryTable->columnCount(); ++col) {
                ui->gameHistoryTable->item(rowCount, col)->setBackground(QColor(200, 255, 200));
            }
        } else {
            // Light red for losses
            for (int col = 0; col < ui->gameHistoryTable->columnCount(); ++col) {
                ui->gameHistoryTable->item(rowCount, col)->setBackground(QColor(255, 200, 200));
            }
        }

     } catch (const std::exception& e) {
        qDebug() << "Error adding game to history table:" << e.what();
    }
}

void Home::updatePlayerStats()
{
    // This method is now redundant as we handle stats in calculateStatsFromGames()
    // But keeping it for backward compatibility
    calculateStatsFromGames();
    updateStatsLabel();
}

void Home::addGameToHistory(const QString &winner, const QString &date, const QString &moves, const QString &opponent)
{
    int rowCount = ui->gameHistoryTable->rowCount();
    ui->gameHistoryTable->insertRow(rowCount);

    ui->gameHistoryTable->setItem(rowCount, 0, new QTableWidgetItem(winner));
    ui->gameHistoryTable->setItem(rowCount, 1, new QTableWidgetItem(date));
    ui->gameHistoryTable->setItem(rowCount, 2, new QTableWidgetItem(moves));
    ui->gameHistoryTable->setItem(rowCount, 3, new QTableWidgetItem(opponent));
    ui->gameHistoryTable->setItem(rowCount, 4, new QTableWidgetItem("N/A")); // Duration
}

void Home::on_pushButton_clicked()// pushButton is the logout button
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Logout", "Are you sure you want to logout?",
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes) {
        // Save user data before logout
        saveUserData();

        // Create login window
        Login *loginWindow = new Login();
        loginWindow->show();

        // Close current window and clean up
        this->close();
    }
}

void Home::on_aiButton_clicked()
{
    VsAi = 1;

    PlayBoard *playboard = new PlayBoard();
    playboard->setGameMode(VsAi, level);
    playboard->show();

    // Close current window and clean up
    this->close();
}

void Home::on_friendButton_clicked()
{
    VsAi = 0;
    PlayBoard *playboard = new PlayBoard();
    playboard->setGameMode(VsAi, level);
    playboard->show();

    // Close current window and clean up
    this->close();
}
// Add these methods at the end of home.cpp, before the last }

// Handle session expiry
void Home::onSessionExpired() {
    SessionTimer::instance().reset();
    QMessageBox::information(this, "Session Expired",
                             "Your session has expired due to inactivity. Please login again.");

    // Save user data before logout
    saveUserData();

    // Create login window
    Login *loginWindow = new Login();
    loginWindow->show();

    // Close current window
    this->close();

}

// Reset timer on user activity
void Home::onUserActivity() {
    SessionTimer::instance().reset();
}

// Event filter to detect mouse/keyboard activity
bool Home::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::MouseButtonPress ||
        event->type() == QEvent::KeyPress ||
        event->type() == QEvent::MouseMove) {
        onUserActivity();
    }
    return QMainWindow::eventFilter(obj, event);
}
void Home::onGameHistoryTableClicked(int row, int column)
{
    /*
    // Get the clicked row data
    QString winner = ui->gameHistoryTable->item(row, 0)->text();
    QString date = ui->gameHistoryTable->item(row, 1)->text();
    QString moves = ui->gameHistoryTable->item(row, 2)->text();
    QString opponent = ui->gameHistoryTable->item(row, 3)->text();

    // Do something with the clicked data
    // For example, show a message box with game details
    QMessageBox::information(this, "Game Details",
                             QString("Winner: %1\nDate: %2\nMoves: %3\nOpponent: %4")
                                 .arg(winner).arg(date).arg(moves).arg(opponent));*/
SessionTimer::instance().stop();
    indexforgames=row;

    ReplayBoard *repl=new ReplayBoard;
    repl->show();
    this->close();



    // Or you could open a detailed game view, replay the game, etc.
}
