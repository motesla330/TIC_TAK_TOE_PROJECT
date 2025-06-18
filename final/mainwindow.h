// Copyright 2025 <MahmoudIsmail>

#ifndef FINAL_MAINWINDOW_H_
#define FINAL_MAINWINDOW_H_

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
};

#endif  // FINAL_MAINWINDOW_H_
