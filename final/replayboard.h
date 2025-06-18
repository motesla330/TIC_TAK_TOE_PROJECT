#ifndef REPLAYBOARD_H
#define REPLAYBOARD_H

#include <QWidget>
#include "ui_replayboard.h"

class ReplayBoard : public QWidget
{
    Q_OBJECT

public:
    ReplayBoard(QWidget *parent = nullptr);
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

#endif // REPLAYBOARD_H
