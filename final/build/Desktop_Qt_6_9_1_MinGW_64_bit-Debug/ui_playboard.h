/********************************************************************************
** Form generated from reading UI file 'playboard.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYBOARD_H
#define UI_PLAYBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *mainVerticalLayout;
    QLabel *titleLabel;
    QLabel *statusLabel;
    QHBoxLayout *gameContainerLayout;
    QSpacerItem *leftGameSpacer;
    QGridLayout *gameGridLayout;
    QPushButton *pushButton_4;
    QPushButton *pushButton_8;
    QPushButton *pushButton_1;
    QPushButton *pushButton_5;
    QPushButton *pushButton_9;
    QPushButton *pushButton_3;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_2;
    QSpacerItem *bottomSpacer;
    QSpacerItem *rightGameSpacer;
    QHBoxLayout *controlButtonsLayout;
    QSpacerItem *leftSpacer;
    QPushButton *backButton;
    QPushButton *newGameButton;
    QSpacerItem *rightSpacer;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(900, 700);
        Form->setStyleSheet(QString::fromUtf8("QWidget#Form {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"                stop:0 #1e3c72, stop:0.5 #2a5298, stop:1 #1e3c72);\n"
"}\n"
"\n"
"QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                stop:0 #ffffff, stop:1 #e6e6e6);\n"
"    border: 3px solid #2c5aa0;\n"
"    border-radius: 15px;\n"
"    font-family: 'Arial Black', Arial, sans-serif;\n"
"    font-size: 48px;\n"
"    font-weight: bold;\n"
"    color: #2c5aa0;\n"
"    min-height: 80px;\n"
"    min-width: 80px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                stop:0 #f0f8ff, stop:1 #d0e8ff);\n"
"    border: 4px solid #1e4080;\n"
"    transform: scale(1.02);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                stop:0 #e0e0e0, stop:1 #c0c0c0);\n"
"    border: 3px solid #1a365d;\n"
"}\n"
"\n"
"QPushButton[text=\"X\"] {\n"
"    color: #dc2626;\n"
"    text-shadow: 2px 2"
                        "px 4px rgba(220, 38, 38, 0.3);\n"
"}\n"
"\n"
"QPushButton[text=\"O\"] {\n"
"    color: #2563eb;\n"
"    text-shadow: 2px 2px 4px rgba(37, 99, 235, 0.3);\n"
"}\n"
"\n"
"/* Control Buttons Styling */\n"
"QPushButton#resetButton, QPushButton#newGameButton, QPushButton#backButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                stop:0 #3b82f6, stop:1 #1d4ed8);\n"
"    border: 2px solid #1e40af;\n"
"    border-radius: 10px;\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    min-height: 40px;\n"
"    padding: 8px 16px;\n"
"}\n"
"\n"
"QPushButton#resetButton:hover, QPushButton#newGameButton:hover, QPushButton#backButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                stop:0 #2563eb, stop:1 #1e40af);\n"
"    border: 2px solid #1e3a8a;\n"
"}\n"
"\n"
"QPushButton#backButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                stop:0 #ef4444, stop:1 #dc2626);\n"
"    border: 2px solid #b91c"
                        "1c;\n"
"}\n"
"\n"
"QPushButton#backButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                stop:0 #dc2626, stop:1 #b91c1c);\n"
"    border: 2px solid #991b1b;\n"
"}\n"
"\n"
"QLabel#titleLabel {\n"
"    color: white;\n"
"    font-family: 'Arial Black', Arial, sans-serif;\n"
"    font-size: 32px;\n"
"    font-weight: bold;\n"
"    text-shadow: 3px 3px 6px rgba(0, 0, 0, 0.5);\n"
"    text-align: center;\n"
"}\n"
"\n"
"QLabel#statusLabel {\n"
"    color: #fbbf24;\n"
"    font-family: Arial, sans-serif;\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"    text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.5);\n"
"    text-align: center;\n"
"}"));
        mainVerticalLayout = new QVBoxLayout(Form);
        mainVerticalLayout->setSpacing(20);
        mainVerticalLayout->setObjectName("mainVerticalLayout");
        mainVerticalLayout->setContentsMargins(30, 20, 30, 20);
        titleLabel = new QLabel(Form);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        mainVerticalLayout->addWidget(titleLabel);

        statusLabel = new QLabel(Form);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        mainVerticalLayout->addWidget(statusLabel);

        gameContainerLayout = new QHBoxLayout();
        gameContainerLayout->setObjectName("gameContainerLayout");
        leftGameSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gameContainerLayout->addItem(leftGameSpacer);

        gameGridLayout = new QGridLayout();
        gameGridLayout->setSpacing(8);
        gameGridLayout->setObjectName("gameGridLayout");
        pushButton_4 = new QPushButton(Form);
        pushButton_4->setObjectName("pushButton_4");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);

        gameGridLayout->addWidget(pushButton_4, 1, 0, 1, 1);

        pushButton_8 = new QPushButton(Form);
        pushButton_8->setObjectName("pushButton_8");
        sizePolicy.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
        pushButton_8->setSizePolicy(sizePolicy);

        gameGridLayout->addWidget(pushButton_8, 2, 1, 1, 1);

        pushButton_1 = new QPushButton(Form);
        pushButton_1->setObjectName("pushButton_1");
        sizePolicy.setHeightForWidth(pushButton_1->sizePolicy().hasHeightForWidth());
        pushButton_1->setSizePolicy(sizePolicy);

        gameGridLayout->addWidget(pushButton_1, 0, 0, 1, 1);

        pushButton_5 = new QPushButton(Form);
        pushButton_5->setObjectName("pushButton_5");
        sizePolicy.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy);

        gameGridLayout->addWidget(pushButton_5, 1, 1, 1, 1);

        pushButton_9 = new QPushButton(Form);
        pushButton_9->setObjectName("pushButton_9");
        sizePolicy.setHeightForWidth(pushButton_9->sizePolicy().hasHeightForWidth());
        pushButton_9->setSizePolicy(sizePolicy);

        gameGridLayout->addWidget(pushButton_9, 2, 2, 1, 1);

        pushButton_3 = new QPushButton(Form);
        pushButton_3->setObjectName("pushButton_3");
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);

        gameGridLayout->addWidget(pushButton_3, 0, 2, 1, 1);

        pushButton_6 = new QPushButton(Form);
        pushButton_6->setObjectName("pushButton_6");
        sizePolicy.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy);

        gameGridLayout->addWidget(pushButton_6, 1, 2, 1, 1);

        pushButton_7 = new QPushButton(Form);
        pushButton_7->setObjectName("pushButton_7");
        sizePolicy.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy);

        gameGridLayout->addWidget(pushButton_7, 2, 0, 1, 1);

        pushButton_2 = new QPushButton(Form);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        gameGridLayout->addWidget(pushButton_2, 0, 1, 1, 1);

        bottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gameGridLayout->addItem(bottomSpacer, 3, 1, 1, 1);


        gameContainerLayout->addLayout(gameGridLayout);

        rightGameSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gameContainerLayout->addItem(rightGameSpacer);


        mainVerticalLayout->addLayout(gameContainerLayout);

        controlButtonsLayout = new QHBoxLayout();
        controlButtonsLayout->setSpacing(15);
        controlButtonsLayout->setObjectName("controlButtonsLayout");
        leftSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        controlButtonsLayout->addItem(leftSpacer);

        backButton = new QPushButton(Form);
        backButton->setObjectName("backButton");

        controlButtonsLayout->addWidget(backButton);

        newGameButton = new QPushButton(Form);
        newGameButton->setObjectName("newGameButton");

        controlButtonsLayout->addWidget(newGameButton);

        rightSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        controlButtonsLayout->addItem(rightSpacer);


        mainVerticalLayout->addLayout(controlButtonsLayout);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "TicTacToy - Game Board", nullptr));
        titleLabel->setText(QCoreApplication::translate("Form", "TicTacToy Game", nullptr));
        statusLabel->setText(QCoreApplication::translate("Form", "Player X's Turn", nullptr));
        pushButton_4->setText(QString());
        pushButton_8->setText(QString());
        pushButton_1->setText(QString());
        pushButton_5->setText(QString());
        pushButton_9->setText(QString());
        pushButton_3->setText(QString());
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
        pushButton_2->setText(QString());
#if QT_CONFIG(tooltip)
        backButton->setToolTip(QCoreApplication::translate("Form", "Return to the main menu", nullptr));
#endif // QT_CONFIG(tooltip)
        backButton->setText(QCoreApplication::translate("Form", "\360\237\217\240 Back to Home", nullptr));
#if QT_CONFIG(tooltip)
        newGameButton->setToolTip(QCoreApplication::translate("Form", "Start a fresh new game", nullptr));
#endif // QT_CONFIG(tooltip)
        newGameButton->setText(QCoreApplication::translate("Form", "\360\237\216\256 New Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYBOARD_H
