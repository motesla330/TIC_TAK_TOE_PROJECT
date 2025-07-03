/********************************************************************************
** Form generated from reading UI file 'codeverification.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CODEVERIFICATION_H
#define UI_CODEVERIFICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CodeVerification
{
public:
    QFrame *containerFrame;
    QLabel *titleLabel;
    QLabel *instructionLabel;
    QLineEdit *codeLineEdit;
    QPushButton *verifyButton;
    QPushButton *resendButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *CodeVerification)
    {
        if (CodeVerification->objectName().isEmpty())
            CodeVerification->setObjectName("CodeVerification");
        CodeVerification->resize(450, 400);
        CodeVerification->setStyleSheet(QString::fromUtf8("\n"
"    /* Main Dialog Styling */\n"
"    QDialog {\n"
"        background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"                    stop:0 #1e3c72, stop:1 #2a5298);\n"
"        color: #ffffff;\n"
"    }\n"
"    \n"
"    /* Title Label */\n"
"    QLabel#titleLabel {\n"
"        color: #ffffff;\n"
"        font-family: 'Segoe UI', Arial, sans-serif;\n"
"        font-size: 24px;\n"
"        font-weight: 700;\n"
"        text-align: center;\n"
"        background: transparent;\n"
"        border: none;\n"
"        text-shadow: 2px 2px 4px rgba(0,0,0,0.3);\n"
"    }\n"
"    \n"
"    /* Instruction Label */\n"
"    QLabel#instructionLabel {\n"
"        color: rgba(255, 255, 255, 0.9);\n"
"        font-family: 'Segoe UI', Arial, sans-serif;\n"
"        font-size: 14px;\n"
"        font-weight: 400;\n"
"        text-align: center;\n"
"        background: transparent;\n"
"        border: none;\n"
"    }\n"
"    \n"
"    /* Container Frame */\n"
"    QFrame#containerFrame {\n"
"        background: rgba(255, 255"
                        ", 255, 0.05);\n"
"        border: 1px solid rgba(255, 255, 255, 0.1);\n"
"        border-radius: 20px;\n"
"    }\n"
"    \n"
"    /* Line Edit Fields */\n"
"    QLineEdit {\n"
"        background: rgba(255, 255, 255, 0.9);\n"
"        border: 2px solid rgba(255, 255, 255, 0.3);\n"
"        border-radius: 12px;\n"
"        color: #2c3e50;\n"
"        font-family: 'Segoe UI', Arial, sans-serif;\n"
"        font-size: 16px;\n"
"        font-weight: 500;\n"
"        padding: 15px 20px;\n"
"        selection-background-color: #4facfe;\n"
"        selection-color: white;\n"
"        text-align: center;\n"
"        letter-spacing: 3px;\n"
"    }\n"
"    \n"
"    QLineEdit:focus {\n"
"        border: 2px solid #4facfe;\n"
"        background: rgba(255, 255, 255, 0.95);\n"
"        box-shadow: 0 0 20px rgba(79, 172, 254, 0.4);\n"
"    }\n"
"    \n"
"    QLineEdit:hover {\n"
"        border: 2px solid rgba(79, 172, 254, 0.5);\n"
"        background: rgba(255, 255, 255, 0.95);\n"
"    }\n"
"    \n"
"    /* Placeholder te"
                        "xt color */\n"
"    QLineEdit::placeholder {\n"
"        color: #7f8c8d;\n"
"        font-style: italic;\n"
"        letter-spacing: 1px;\n"
"    }\n"
"    \n"
"    /* Professional Buttons */\n"
"    QPushButton {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #4facfe, stop:1 #00f2fe);\n"
"        border: none;\n"
"        border-radius: 12px;\n"
"        color: #ffffff;\n"
"        font-family: 'Segoe UI', Arial, sans-serif;\n"
"        font-size: 16px;\n"
"        font-weight: 600;\n"
"        padding: 12px 24px;\n"
"        text-shadow: 1px 1px 2px rgba(0,0,0,0.3);\n"
"        box-shadow: 0 4px 15px rgba(79, 172, 254, 0.3);\n"
"    }\n"
"    \n"
"    QPushButton:hover {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #5fbdff, stop:1 #1af3fe);\n"
"        transform: translateY(-2px);\n"
"        box-shadow: 0 6px 20px rgba(79, 172, 254, 0.4);\n"
"    }\n"
"    \n"
"    QPushButton:pressed {\n"
"        background: "
                        "qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #3a9bfd, stop:1 #00d9fe);\n"
"        transform: translateY(1px);\n"
"        box-shadow: 0 2px 10px rgba(79, 172, 254, 0.2);\n"
"    }\n"
"    \n"
"    /* Resend Button Special Styling */\n"
"    QPushButton#resendButton {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #667eea, stop:1 #764ba2);\n"
"        box-shadow: 0 4px 15px rgba(102, 126, 234, 0.3);\n"
"    }\n"
"    \n"
"    QPushButton#resendButton:hover {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #7b8beb, stop:1 #8659b3);\n"
"        box-shadow: 0 6px 20px rgba(102, 126, 234, 0.4);\n"
"    }\n"
"    \n"
"    QPushButton#resendButton:pressed {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #5a6fd8, stop:1 #6a4191);\n"
"        box-shadow: 0 2px 10px rgba(102, 126, 234, 0.2);\n"
"    }\n"
"    \n"
"    /* Cancel Button Special Styling */"
                        "\n"
"    QPushButton#cancelButton {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #ff6b6b, stop:1 #ee5a5a);\n"
"        box-shadow: 0 4px 15px rgba(255, 107, 107, 0.3);\n"
"    }\n"
"    \n"
"    QPushButton#cancelButton:hover {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #ff7979, stop:1 #f56565);\n"
"        box-shadow: 0 6px 20px rgba(255, 107, 107, 0.4);\n"
"    }\n"
"    \n"
"    QPushButton#cancelButton:pressed {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #ff5757, stop:1 #e74c3c);\n"
"        box-shadow: 0 2px 10px rgba(255, 107, 107, 0.2);\n"
"    }\n"
"   "));
        containerFrame = new QFrame(CodeVerification);
        containerFrame->setObjectName("containerFrame");
        containerFrame->setGeometry(QRect(30, 40, 390, 320));
        containerFrame->setFrameShape(QFrame::Shape::StyledPanel);
        containerFrame->setFrameShadow(QFrame::Shadow::Raised);
        titleLabel = new QLabel(containerFrame);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setGeometry(QRect(30, 30, 330, 40));
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        instructionLabel = new QLabel(containerFrame);
        instructionLabel->setObjectName("instructionLabel");
        instructionLabel->setGeometry(QRect(30, 75, 330, 50));
        instructionLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        instructionLabel->setWordWrap(true);
        codeLineEdit = new QLineEdit(containerFrame);
        codeLineEdit->setObjectName("codeLineEdit");
        codeLineEdit->setGeometry(QRect(70, 140, 250, 60));
        codeLineEdit->setMaxLength(6);
        verifyButton = new QPushButton(containerFrame);
        verifyButton->setObjectName("verifyButton");
        verifyButton->setGeometry(QRect(120, 210, 141, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setWeight(QFont::DemiBold);
        verifyButton->setFont(font);
        resendButton = new QPushButton(containerFrame);
        resendButton->setObjectName("resendButton");
        resendButton->setGeometry(QRect(50, 270, 141, 41));
        resendButton->setFont(font);
        cancelButton = new QPushButton(containerFrame);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setGeometry(QRect(219, 270, 131, 41));
        cancelButton->setFont(font);

        retranslateUi(CodeVerification);

        QMetaObject::connectSlotsByName(CodeVerification);
    } // setupUi

    void retranslateUi(QDialog *CodeVerification)
    {
        CodeVerification->setWindowTitle(QCoreApplication::translate("CodeVerification", "Email Verification", nullptr));
        titleLabel->setText(QCoreApplication::translate("CodeVerification", "Email Verification", nullptr));
        instructionLabel->setText(QCoreApplication::translate("CodeVerification", "We've sent a verification code to your email.\n"
"Please enter the code below to continue.", nullptr));
        codeLineEdit->setPlaceholderText(QCoreApplication::translate("CodeVerification", "Enter 6-digit code", nullptr));
#if QT_CONFIG(tooltip)
        verifyButton->setToolTip(QCoreApplication::translate("CodeVerification", "Click to verify the code", nullptr));
#endif // QT_CONFIG(tooltip)
        verifyButton->setText(QCoreApplication::translate("CodeVerification", "Verify Code", nullptr));
#if QT_CONFIG(tooltip)
        resendButton->setToolTip(QCoreApplication::translate("CodeVerification", "Resend verification code", nullptr));
#endif // QT_CONFIG(tooltip)
        resendButton->setText(QCoreApplication::translate("CodeVerification", "Resend Code", nullptr));
#if QT_CONFIG(tooltip)
        cancelButton->setToolTip(QCoreApplication::translate("CodeVerification", "Cancel verification", nullptr));
#endif // QT_CONFIG(tooltip)
        cancelButton->setText(QCoreApplication::translate("CodeVerification", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CodeVerification: public Ui_CodeVerification {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODEVERIFICATION_H
