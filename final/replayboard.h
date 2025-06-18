// Copyright 2025 MahmoudIsmail

#ifndef FINAL_REPLAYBOARD_H_
#define FINAL_REPLAYBOARD_H_

#include <QWidget>
#include <vector>  // For std::vector

#include "final/ui_replayboard.h"

class ReplayBoard : public QWidget {
    Q_OBJECT

 public:
    explicit ReplayBoard(QWidget *parent = nullptr);
    ~ReplayBoard();

    void setButtonText(int row, int col, const QString& text);

 private slots:
    void onBackButtonClicked();
    void onstartButtonCliced();

 signals:
    void backToHome();
    void pushButton();
    void playNextMove();

 private:
    Ui::ReplayBoardForm ui;
    QTimer* replayTimer;
    std::vector<std::tuple<char, int, int>> moves;
    size_t currentMoveIndex;

    // Methods
    void view();
    void clearBoard();
};

#endif  // FINAL_REPLAYBOARD_H_
