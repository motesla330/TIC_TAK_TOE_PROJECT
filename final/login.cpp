// Copyright 2025 <MahmoudIsmail>



#include <memory>
#include <string>

#include "login.h"
#include "home.h"
#include "final/Authentication.h"
#include "final/playermanager.h"
#include "final/codeverification.h"
#include "final/globals.h"
#include "final/sessiontimer.h"

using std::string;
using std::nullptr_t;
using TimePoint = std::chrono::system_clock::time_point;

Login::Login(QWidget *parent)
    : QDialog(parent), ui(new Ui::Login) {
  ui->setupUi(this);
  setWindowTitle("Login");
}

Login::~Login() {
  delete ui;
}

void Login::on_loginButton_clicked() {
  GAMEM->loadGames();
  PLAYM->loadPlayers();

  QString username = ui->usernameLineEdit->text();
  QString password = ui->passwordLineEdit->text();

  string *name = nullptr;
  string hashedpasswordfromdb;
  bool ishere = false;

  AUTH->SignIn(username.toStdString(), password.toStdString());
  AUTH->PushSignedInData(name);  // NAME POINT UN

  ishere = PLAYM->getStoredPasswordIfUserExists(*name, hashedpasswordfromdb);

  if (!ishere) {
    QMessageBox::information(this, "Warning",
         "No existing account with this username!");
    return;
  }

  AUTH->IsHereConnect(hashedpasswordfromdb, ishere);

  if (AUTH->IsHereInterface()) {
    QMessageBox::information(this, "Success", "Login successful!");
    SessionTimer::instance().updateTimeout(6000);

    Home *homeWindow = new Home();
    homeWindow->show();
    this->close();
  } else {
    QMessageBox::warning(this, "Error", "Invalid password!");
    ui->passwordLineEdit->clear();
  }
}

void Login::on_exitButton_clicked() {
  this->close();
}

void Login::on_signupButton_clicked() {
  PLAYM->loadPlayers();

  QString name = ui->nameLineEdit->text();
  QString email = ui->emailLineEdit->text();
  QString password = ui->newPasswordLineEdit->text();
  QString confirmPassword = ui->confirmPasswordLineEdit->text();

  AUTH->SignUp(name.toStdString(), password.toStdString(), email.toStdString());

  if (!AUTH->FieldsIsValidNew()) {
    QMessageBox::information(this, "Warning",
         "Some fields are empty, please check!");
    return;
  }

  if (!AUTH->UsernameIsValid()) {
    QMessageBox::information(this, "Warning",
         "Username is too short, try a longer one!");
    return;
  }

  if (PLAYM->playerExists(name.toStdString())) {
    QMessageBox::information(this, "Warning",
         "Username is already taken.");
    return;
  }

  if (!AUTH->PasswordLongIsValid()) {
    QMessageBox::information(this, "Warning",
         "Password is too short!");
    ui->passwordLineEdit->clear();
    ui->newPasswordLineEdit->clear();
    return;
  }

  if (password != confirmPassword) {
    QMessageBox::information(this, "Warning", "Passwords do not match!");
    return;
  }

  if (!AUTH->PasswordComplexityIsValid()) {
    QMessageBox::information(this,
        "Warning",
        "Password must contain an uppercase letter, "
        "lowercase letter, special character, and numbers.");
    return;
  }

  if (!AUTH->EmailIsValid()) {
    QMessageBox::information(this, "Warning", "Invalid email!");
    return;
  }

  AUTH->VerificationMailSMTP();

  CodeVerification *codepage = new CodeVerification;
  codepage->show();
}
