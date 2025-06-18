#ifndef CODEVERIFICATION_H
#define CODEVERIFICATION_H

#include <QDialog>
#include <QTimer>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class CodeVerification; }
QT_END_NAMESPACE

class CodeVerification : public QDialog
{
    Q_OBJECT

public:
    CodeVerification(QWidget *parent = nullptr);
    ~CodeVerification();

    // Public methods
    void setEmailAddress(const QString &email);
    QString getVerificationCode() const;
    bool isCodeVerified() const;

signals:
    void codeVerified(const QString &code);
    void verificationCancelled();
    void resendCodeRequested(const QString &email);

private slots:
    void onVerifyButtonClicked();
    void onResendButtonClicked();
    void onCancelButtonClicked();
    void onCodeTextChanged(const QString &text);
    void onResendTimerTimeout();

private:
    Ui::CodeVerification *ui;

    // Member variables
    QString m_emailAddress;
    QString m_expectedCode;
    bool m_isVerified;
    QTimer *m_resendTimer;
    int m_resendCountdown;

    // Private methods
    void setupUI();
    void setupConnections();
    void setupValidators();
    void enableResendButton();
    void disableResendButton();
    bool validateCode(const QString &code);
    void showSuccessMessage();
    void showErrorMessage(const QString &message);
    void resetForm();
};

#endif // CODEVERIFICATION_H
