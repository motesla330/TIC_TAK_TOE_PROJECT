#include "codeverification.h"
#include "ui_codeverification.h"
#include <QApplication>
#include <QClipboard>
#include <QKeyEvent>
#include"Authentication.h"
#include"globals.h"
#include<string>
#include<iostream>
#include"sessiontimer.h"
using namespace std ;
CodeVerification::CodeVerification(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CodeVerification)
    , m_isVerified(false)
    , m_resendCountdown(60)
{
    // Setup UI from .ui file
    ui->setupUi(this);

    // Initialize components
    setupUI();
    setupConnections();
    setupValidators();

    // Initialize timer
    m_resendTimer = new QTimer(this);
    connect(m_resendTimer, &QTimer::timeout, this, &CodeVerification::onResendTimerTimeout);

    // Set window properties
    setModal(true);
    setFixedSize(450, 400);

    // Focus on code input
    ui->codeLineEdit->setFocus();
}

CodeVerification::~CodeVerification()
{
    if (m_resendTimer) {
        m_resendTimer->stop();
    }
    delete ui;
}

void CodeVerification::setupUI()
{
    // Set initial button states
    ui->verifyButton->setEnabled(false);

    // Configure code input
    ui->codeLineEdit->setMaxLength(6);
    ui->codeLineEdit->setAlignment(Qt::AlignCenter);

    // Set initial instruction text
    if (ui->instructionLabel) {
        ui->instructionLabel->setText("We've sent a verification code to your email.\nPlease enter the code below to continue.");
    }
}

void CodeVerification::setupConnections()
{
    // Connect button signals
    connect(ui->verifyButton, &QPushButton::clicked, this, &CodeVerification::onVerifyButtonClicked);
    connect(ui->resendButton, &QPushButton::clicked, this, &CodeVerification::onResendButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &CodeVerification::onCancelButtonClicked);

    // Connect line edit signals
    connect(ui->codeLineEdit, &QLineEdit::textChanged, this, &CodeVerification::onCodeTextChanged);
    connect(ui->codeLineEdit, &QLineEdit::returnPressed, this, &CodeVerification::onVerifyButtonClicked);
}

void CodeVerification::setupValidators()
{
    // Create validator for numeric input only
    QRegularExpression regExp("[0-9]{0,6}");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regExp, this);
    ui->codeLineEdit->setValidator(validator);
}

void CodeVerification::setEmailAddress(const QString &email)
{
    m_emailAddress = email;

    // Update instruction text with email
    if (ui->instructionLabel && !email.isEmpty()) {
        QString maskedEmail = email;
        int atIndex = email.indexOf('@');
        if (atIndex > 2) {
            for (int i = 2; i < atIndex - 1; ++i) {
                maskedEmail[i] = '*';
            }
        }

        ui->instructionLabel->setText(QString("We've sent a verification code to:\n%1\n\nPlease enter the code below to continue.").arg(maskedEmail));
    }
}

QString CodeVerification::getVerificationCode() const
{
    return ui->codeLineEdit->text();
}

bool CodeVerification::isCodeVerified() const
{
    return m_isVerified;
}

void CodeVerification::onVerifyButtonClicked()
{
    QString code = ui->codeLineEdit->text().trimmed();

    if (code.length() != 6) {
        showErrorMessage("Please enter a 6-digit verification code.");
        return;
    }

    if (!validateCode(code)) {
        showErrorMessage("Please enter only numeric characters.");
        return;
    }

    // Disable UI during verification
    ui->verifyButton->setEnabled(false);
    ui->verifyButton->setText("Verifying...");
    ui->codeLineEdit->setEnabled(false);

    // Simulate verification process (replace with actual verification logic)
   accountiscreated= AUTH->IsVerificationCodeValid(code.toInt());
    if(accountiscreated){

        string *username =NULL ;
        string *hashedpass =NULL;
        string *mail=NULL;
std::cout << "Loaded before " << PLAYM->getPlayers().size() << " players.\n";
        AUTH->PushNewAccount(username,hashedpass,mail);

        PLAYM->loadPlayers();
        PlayerBD player1 = {*hashedpass, *mail};
        PLAYM->getPlayers()[*username] = player1;
        PLAYM->savePlayers();
std::cout << "Loaded after " <<PLAYM->getPlayers().size() << " players.\n";
        emit codeVerified(code);
        accept();

    }
   /*
    QTimer::singleShot(1000, this, [this, code]() {
        // For demo purposes - in real app, verify with server
        bool isValid = true; // Replace with actual verification result

        if (isValid) {
            m_isVerified = true;
            showSuccessMessage();
            emit codeVerified(code);
            accept();
        } else {
            showErrorMessage("Invalid verification code. Please try again.");
            // Re-enable UI
            ui->verifyButton->setEnabled(true);
            ui->verifyButton->setText("Verify Code");
            ui->codeLineEdit->setEnabled(true);
            ui->codeLineEdit->clear();
            ui->codeLineEdit->setFocus();
        }
    });*/
}

void CodeVerification::onResendButtonClicked()
{
    if (m_emailAddress.isEmpty()) {
        showErrorMessage("Email address not set. Cannot resend code.");
        return;
    }

    // Disable resend button and start countdown
    disableResendButton();

    // Clear current code
    ui->codeLineEdit->clear();
    ui->codeLineEdit->setFocus();

    // Emit signal to request new code
    emit resendCodeRequested(m_emailAddress);

    // Show confirmation
    QMessageBox::information(this, "Code Sent",
                             QString("A new verification code has been sent to your email address.\n%1").arg(m_emailAddress));
}

void CodeVerification::onCancelButtonClicked()
{
    emit verificationCancelled();
    reject();
}

void CodeVerification::onCodeTextChanged(const QString &text)
{
    // Enable/disable verify button based on input length
    ui->verifyButton->setEnabled(text.length() == 6);

    // Auto-verify when 6 digits are entered (optional)
    if (text.length() == 6 && validateCode(text)) {
        // Optional: Auto-verify after a short delay
        QTimer::singleShot(500, this, &CodeVerification::onVerifyButtonClicked);
    }
}

void CodeVerification::onResendTimerTimeout()
{
    m_resendCountdown--;

    if (m_resendCountdown <= 0) {
        enableResendButton();
    } else {
        ui->resendButton->setText(QString("Resend (%1s)").arg(m_resendCountdown));
    }
}

void CodeVerification::enableResendButton()
{
    m_resendTimer->stop();
    m_resendCountdown = 60;
    ui->resendButton->setEnabled(true);
    ui->resendButton->setText("Resend Code");
}

void CodeVerification::disableResendButton()
{
    m_resendCountdown = 60;
    ui->resendButton->setEnabled(false);
    ui->resendButton->setText(QString("Resend (%1s)").arg(m_resendCountdown));
    m_resendTimer->start(1000); // Update every second
}

bool CodeVerification::validateCode(const QString &code)
{
    // Check if code contains only digits
    QRegularExpression regExp("^[0-9]{6}$");
    return regExp.match(code).hasMatch();
}

void CodeVerification::showSuccessMessage()
{
    QMessageBox msgBox(this);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("Verification Successful");
    msgBox.setText("Email verification completed successfully!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
    SessionTimer::instance().updateTimeout(60000);

}

void CodeVerification::showErrorMessage(const QString &message)
{
    QMessageBox msgBox(this);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Verification Error");
    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void CodeVerification::resetForm()
{
    ui->codeLineEdit->clear();
    m_isVerified = false;
    ui->verifyButton->setEnabled(false);
    ui->verifyButton->setText("Verify Code");
    ui->codeLineEdit->setEnabled(true);
    enableResendButton();
}
