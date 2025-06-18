/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QLineEdit *usernameLineEdit;
    QPushButton *loginButton;
    QLineEdit *passwordLineEdit;
    QPushButton *exitButton;
    QWidget *tab_2;
    QPushButton *signupButton;
    QLineEdit *nameLineEdit;
    QLineEdit *emailLineEdit;
    QLineEdit *newPasswordLineEdit;
    QLineEdit *confirmPasswordLineEdit;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(475, 489);
        Login->setStyleSheet(QString::fromUtf8("\n"
"    /* Main Dialog Styling */\n"
"    QDialog {\n"
"        background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"                    stop:0 #1e3c72, stop:1 #2a5298);\n"
"        color: #ffffff;\n"
"    }\n"
"    \n"
"    /* Tab Widget */\n"
"    QTabWidget {\n"
"        background: transparent;\n"
"        border: none;\n"
"    }\n"
"    \n"
"    QTabWidget::pane {\n"
"        background: rgba(255, 255, 255, 0.05);\n"
"        border: 1px solid rgba(255, 255, 255, 0.1);\n"
"        border-radius: 15px;\n"
"        margin-top: 10px;\n"
"    }\n"
"    \n"
"    QTabBar::tab {\n"
"        background: rgba(255, 255, 255, 0.1);\n"
"        color: #ffffff;\n"
"        font-family: 'Segoe UI', Arial, sans-serif;\n"
"        font-size: 14px;\n"
"        font-weight: 600;\n"
"        padding: 12px 24px;\n"
"        margin-right: 2px;\n"
"        border-top-left-radius: 10px;\n"
"        border-top-right-radius: 10px;\n"
"        border: 1px solid rgba(255, 255, 255, 0.2);\n"
"    }\n"
"    \n"
"    QTabBar::tab:"
                        "selected {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #4facfe, stop:1 #00f2fe);\n"
"        color: #ffffff;\n"
"        border-bottom: none;\n"
"    }\n"
"    \n"
"    QTabBar::tab:hover:!selected {\n"
"        background: rgba(255, 255, 255, 0.2);\n"
"    }\n"
"    \n"
"    /* Line Edit Fields */\n"
"    QLineEdit {\n"
"        background: rgba(255, 255, 255, 0.9);\n"
"        border: 2px solid rgba(255, 255, 255, 0.3);\n"
"        border-radius: 12px;\n"
"        color: #2c3e50;\n"
"        font-family: 'Segoe UI', Arial, sans-serif;\n"
"        font-size: 14px;\n"
"        padding: 12px 16px;\n"
"        selection-background-color: #4facfe;\n"
"        selection-color: white;\n"
"    }\n"
"    \n"
"    QLineEdit:focus {\n"
"        border: 2px solid #4facfe;\n"
"        background: rgba(255, 255, 255, 0.95);\n"
"        box-shadow: 0 0 15px rgba(79, 172, 254, 0.3);\n"
"    }\n"
"    \n"
"    QLineEdit:hover {\n"
"        border: 2px solid rgba(79, 172, 254"
                        ", 0.5);\n"
"        background: rgba(255, 255, 255, 0.95);\n"
"    }\n"
"    \n"
"    /* Placeholder text color */\n"
"    QLineEdit::placeholder {\n"
"        color: #7f8c8d;\n"
"        font-style: italic;\n"
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
""
                        "    }\n"
"    \n"
"    QPushButton:pressed {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #3a9bfd, stop:1 #00d9fe);\n"
"        transform: translateY(1px);\n"
"        box-shadow: 0 2px 10px rgba(79, 172, 254, 0.2);\n"
"    }\n"
"    \n"
"    /* Exit Button Special Styling */\n"
"    QPushButton#exitButton {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #ff6b6b, stop:1 #ee5a5a);\n"
"        box-shadow: 0 4px 15px rgba(255, 107, 107, 0.3);\n"
"    }\n"
"    \n"
"    QPushButton#exitButton:hover {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #ff7979, stop:1 #f56565);\n"
"        box-shadow: 0 6px 20px rgba(255, 107, 107, 0.4);\n"
"    }\n"
"    \n"
"    QPushButton#exitButton:pressed {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #ff5757, stop:1 #e74c3c);\n"
"        box-shadow: 0 2px 10px rgba(255, 107, 107, 0.2);\n"
""
                        "    }\n"
"    \n"
"    /* Sign Up Button Special Styling */\n"
"    QPushButton#signupButton {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #667eea, stop:1 #764ba2);\n"
"        box-shadow: 0 4px 15px rgba(102, 126, 234, 0.3);\n"
"    }\n"
"    \n"
"    QPushButton#signupButton:hover {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #7b8beb, stop:1 #8659b3);\n"
"        box-shadow: 0 6px 20px rgba(102, 126, 234, 0.4);\n"
"    }\n"
"    \n"
"    QPushButton#signupButton:pressed {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #5a6fd8, stop:1 #6a4191);\n"
"        box-shadow: 0 2px 10px rgba(102, 126, 234, 0.2);\n"
"    }\n"
"   "));
        tabWidget = new QTabWidget(Login);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(-4, -1, 481, 491));
        tabWidget->setTabPosition(QTabWidget::TabPosition::North);
        tabWidget->setTabShape(QTabWidget::TabShape::Rounded);
        tabWidget->setElideMode(Qt::TextElideMode::ElideMiddle);
        tab = new QWidget();
        tab->setObjectName("tab");
        usernameLineEdit = new QLineEdit(tab);
        usernameLineEdit->setObjectName("usernameLineEdit");
        usernameLineEdit->setGeometry(QRect(120, 100, 261, 51));
        loginButton = new QPushButton(tab);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(190, 240, 111, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setWeight(QFont::DemiBold);
        loginButton->setFont(font);
        passwordLineEdit = new QLineEdit(tab);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setGeometry(QRect(120, 160, 261, 51));
        passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
        exitButton = new QPushButton(tab);
        exitButton->setObjectName("exitButton");
        exitButton->setGeometry(QRect(190, 310, 111, 41));
        exitButton->setFont(font);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        signupButton = new QPushButton(tab_2);
        signupButton->setObjectName("signupButton");
        signupButton->setGeometry(QRect(180, 350, 111, 51));
        signupButton->setFont(font);
        nameLineEdit = new QLineEdit(tab_2);
        nameLineEdit->setObjectName("nameLineEdit");
        nameLineEdit->setGeometry(QRect(70, 50, 351, 51));
        emailLineEdit = new QLineEdit(tab_2);
        emailLineEdit->setObjectName("emailLineEdit");
        emailLineEdit->setGeometry(QRect(70, 110, 351, 51));
        newPasswordLineEdit = new QLineEdit(tab_2);
        newPasswordLineEdit->setObjectName("newPasswordLineEdit");
        newPasswordLineEdit->setGeometry(QRect(70, 170, 351, 51));
        newPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
        confirmPasswordLineEdit = new QLineEdit(tab_2);
        confirmPasswordLineEdit->setObjectName("confirmPasswordLineEdit");
        confirmPasswordLineEdit->setGeometry(QRect(70, 230, 351, 51));
        confirmPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
        tabWidget->addTab(tab_2, QString());

        retranslateUi(Login);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Login", nullptr));
        usernameLineEdit->setPlaceholderText(QCoreApplication::translate("Login", "Enter User Name ", nullptr));
#if QT_CONFIG(tooltip)
        loginButton->setToolTip(QCoreApplication::translate("Login", "press to login ", nullptr));
#endif // QT_CONFIG(tooltip)
        loginButton->setText(QCoreApplication::translate("Login", "Login ", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("Login", "Enter Password ", nullptr));
#if QT_CONFIG(tooltip)
        exitButton->setToolTip(QCoreApplication::translate("Login", "press to exit ", nullptr));
#endif // QT_CONFIG(tooltip)
        exitButton->setText(QCoreApplication::translate("Login", "Exit", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Login", "login", nullptr));
#if QT_CONFIG(tooltip)
        signupButton->setToolTip(QCoreApplication::translate("Login", "press to sign up", nullptr));
#endif // QT_CONFIG(tooltip)
        signupButton->setText(QCoreApplication::translate("Login", "Sign Up", nullptr));
        nameLineEdit->setPlaceholderText(QCoreApplication::translate("Login", "Enter Your Name ", nullptr));
        emailLineEdit->setPlaceholderText(QCoreApplication::translate("Login", "Enter Your Email ", nullptr));
        newPasswordLineEdit->setPlaceholderText(QCoreApplication::translate("Login", "Password ", nullptr));
        confirmPasswordLineEdit->setPlaceholderText(QCoreApplication::translate("Login", "Confirm Password ", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Login", "Sign up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
