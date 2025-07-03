// Copyright 2025 <MahmoudIsmail>

#ifndef FINAL_LOGIN_H_
#define FINAL_LOGIN_H_

#include <QDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QDialog {
  Q_OBJECT

 public:
  explicit Login(QWidget *parent = nullptr);
  ~Login();

 private slots:
  void on_loginButton_clicked();
  void on_exitButton_clicked();
  void on_signupButton_clicked();

 private:
  Ui::Login *ui;
};

#endif  // FINAL_LOGIN_H_
