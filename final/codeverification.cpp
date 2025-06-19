// Copyright 2025 <Tesla>

#include <QApplication>
#include <QClipboard>
#include <QKeyEvent>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QTimer>

#include <string>
#include <iostream>

#include "final/codeverification.h"
#include "final/ui_codeverification.h"
#include "final/Authentication.h"
#include "final/globals.h"
#include "final/sessiontimer.h"

CodeVerification::CodeVerification(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::CodeVerification),
      m_isVerified(false),
      m_resendCountdown(60) {
  ui->setupUi(this);
  setupUI();
  setupConnections();
  setupValidators();

  m_resendTimer = new QTimer(this);
  connect(m_resendTimer, &QTimer::timeout, this,
          &CodeVerification::onResendTimerTimeout);

  setModal(true);
  setFixedSize(450, 400);
  ui->codeLineEdit->setFocus();
}

CodeVerification::~CodeVerification() {
  if (m_resendTimer) {
    m_resendTimer->stop();
  }
  delete ui;
}

void CodeVerification::setupUI() {
  ui->verifyButton->setEnabled(false);
  ui->codeLineEdit->setMaxLength(6);
  ui->codeLineEdit->setAlignment(Qt::AlignCenter);

  if (ui->instructionLabel) {
    ui->instructionLabel->setText(
        QStringLiteral("We've sent a verification code to your email.\n"
                       "Please enter the code below to continue."));
  }
}

void CodeVerification::setupConnections() {
  connect(ui->verifyButton, &QPushButton::clicked, this,
          &CodeVerification::onVerifyButtonClicked);
  connect(ui->resendButton, &QPushButton::clicked, this,
          &CodeVerification::onResendButtonClicked);
  connect(ui->cancelButton, &QPushButton::clicked, this,
          &CodeVerification::onCancelButtonClicked);
  connect(ui->codeLineEdit, &QLineEdit::textChanged, this,
          &CodeVerification::onCodeTextChanged);
  connect(ui->codeLineEdit, &QLineEdit::returnPressed, this,
          &CodeVerification::onVerifyButtonClicked);
}

void CodeVerification::setupValidators() {
  QRegularExpression regExp("[0-9]{0,6}");
  auto *validator = new QRegularExpressionValidator(regExp, this);
  ui->codeLineEdit->setValidator(validator);
}

void CodeVerification::setEmailAddress(const QString &email) {
  m_emailAddress = email;

  if (ui->instructionLabel && !email.isEmpty()) {
    QString maskedEmail = email;
    int atIndex = email.indexOf('@');
    if (atIndex > 2) {
      for (int i = 2; i < atIndex - 1; ++i) {
        maskedEmail[i] = '*';
      }
    }
    ui->instructionLabel->setText(
        QStringLiteral("We've sent a verification code to:\n%1\n\n"
                       "Please enter the code below to continue.")
            .arg(maskedEmail));
  }
}

QString CodeVerification::getVerificationCode() const {
  return ui->codeLineEdit->text();
}

bool CodeVerification::isCodeVerified() const {
  return m_isVerified;
}

void CodeVerification::onVerifyButtonClicked() {
  QString code = ui->codeLineEdit->text().trimmed();
  if (code.length() != 6) {
    showErrorMessage(QStringLiteral(
        "Please enter a 6-digit verification code."));
    return;
  }
  if (!validateCode(code)) {
    showErrorMessage(QStringLiteral("Please enter only numeric characters."));
    return;
  }

  ui->verifyButton->setEnabled(false);
  ui->verifyButton->setText(QStringLiteral("Verifying..."));
  ui->codeLineEdit->setEnabled(false);

  accountiscreated = AUTH->IsVerificationCodeValid(code.toInt());
  if (accountiscreated) {
    std::string *username = nullptr;
    std::string *hashedpass = nullptr;
    std::string *mail = nullptr;

    std::cout << "Loaded before " << PLAYM->getPlayers().size()
              << " players.\n";
    AUTH->PushNewAccount(username, hashedpass, mail);
    PLAYM->loadPlayers();
    PlayerBD player1 = {*hashedpass, *mail};
    PLAYM->getPlayers()[*username] = player1;
    PLAYM->savePlayers();
    std::cout << "Loaded after " << PLAYM->getPlayers().size()
              << " players.\n";

    emit codeVerified(code);
    accept();
  }
}

void CodeVerification::onResendButtonClicked() {
  if (m_emailAddress.isEmpty()) {
    showErrorMessage(QStringLiteral(
        "Email address not set. Cannot resend code."));
    return;
  }

  disableResendButton();
  ui->codeLineEdit->clear();
  ui->codeLineEdit->setFocus();
  emit resendCodeRequested(m_emailAddress);

  QMessageBox::information(
      this, QStringLiteral("Code Sent"),
      QStringLiteral(
        "A new verification code has been sent to your email address.\n%1")
          .arg(m_emailAddress));
}

void CodeVerification::onCancelButtonClicked() {
  emit verificationCancelled();
  reject();
}

void CodeVerification::onCodeTextChanged(const QString &text) {
  ui->verifyButton->setEnabled(text.length() == 6);
  if (text.length() == 6 && validateCode(text)) {
    QTimer::singleShot(500, this, &CodeVerification::onVerifyButtonClicked);
  }
}

void CodeVerification::onResendTimerTimeout() {
  m_resendCountdown--;
  if (m_resendCountdown <= 0) {
    enableResendButton();
  } else {
    ui->resendButton->setText(
        QStringLiteral("Resend (%1s)").arg(m_resendCountdown));
  }
}

void CodeVerification::enableResendButton() {
  m_resendTimer->stop();
  m_resendCountdown = 60;
  ui->resendButton->setEnabled(true);
  ui->resendButton->setText(QStringLiteral("Resend Code"));
}

void CodeVerification::disableResendButton() {
  m_resendCountdown = 60;
  ui->resendButton->setEnabled(false);
  ui->resendButton->setText(
      QStringLiteral("Resend (%1s)").arg(m_resendCountdown));
  m_resendTimer->start(1000);
}

bool CodeVerification::validateCode(const QString &code) {
  QRegularExpression regExp("^[0-9]{6}$");
  return regExp.match(code).hasMatch();
}

void CodeVerification::showSuccessMessage() {
  QMessageBox msgBox(this);
  msgBox.setIcon(QMessageBox::Information);
  msgBox.setWindowTitle(QStringLiteral("Verification Successful"));
  msgBox.setText(QStringLiteral("Email verification completed successfully!"));
  msgBox.setStandardButtons(QMessageBox::Ok);
  msgBox.exec();
  SessionTimer::instance().updateTimeout(60000);
}

void CodeVerification::showErrorMessage(const QString &message) {
  QMessageBox msgBox(this);
  msgBox.setIcon(QMessageBox::Warning);
  msgBox.setWindowTitle(QStringLiteral("Verification Error"));
  msgBox.setText(message);
  msgBox.setStandardButtons(QMessageBox::Ok);
  msgBox.exec();
}

void CodeVerification::resetForm() {
  ui->codeLineEdit->clear();
  m_isVerified = false;
  ui->verifyButton->setEnabled(false);
  ui->verifyButton->setText(QStringLiteral("Verify Code"));
  ui->codeLineEdit->setEnabled(true);
  enableResendButton();
}
