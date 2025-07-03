/********************************************************************************
** Form generated from reading UI file 'replayboard.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPLAYBOARD_H
#define UI_REPLAYBOARD_H

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

class Ui_ReplayBoardForm
{
public:
    QVBoxLayout *replayMainLayout;
    QLabel *replayTitleLabel;
    QHBoxLayout *replayGameLayout;
    QSpacerItem *replayLeftSpacer;
    QGridLayout *replayBoardGrid;
    QPushButton *replayBtn_1_1;
    QPushButton *replayBtn_2_0;
    QSpacerItem *replayBottomSpacer;
    QPushButton *replayBtn_0_0;
    QPushButton *replayBtn_2_2;
    QPushButton *replayBtn_0_2;
    QPushButton *replayBtn_0_1;
    QPushButton *replayBtn_1_2;
    QPushButton *replayBtn_1_0;
    QPushButton *replayBtn_2_1;
    QPushButton *pushButton;
    QSpacerItem *replayRightSpacer;
    QHBoxLayout *replayControlLayout;
    QSpacerItem *replayControlLeftSpacer;
    QPushButton *replayBackButton;
    QSpacerItem *replayControlRightSpacer;

    void setupUi(QWidget *ReplayBoardForm)
    {
        if (ReplayBoardForm->objectName().isEmpty())
            ReplayBoardForm->setObjectName("ReplayBoardForm");
        ReplayBoardForm->resize(900, 700);
        ReplayBoardForm->setStyleSheet(QString::fromUtf8("QWidget#ReplayBoardForm {\n"
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
"    text-sh"
                        "adow: 2px 2px 4px rgba(220, 38, 38, 0.3);\n"
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
"    border: 2px "
                        "solid #b91c1c;\n"
"}\n"
"\n"
"QPushButton#backButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                stop:0 #dc2626, stop:1 #b91c1c);\n"
"    border: 2px solid #991b1b;\n"
"}\n"
"\n"
"QPushButton#replayBackButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                stop:0 #ef4444, stop:1 #dc2626);\n"
"    border: 2px solid #b91c1c;\n"
"    border-radius: 8px;\n"
"    color: white;\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    min-height: 30px;\n"
"    padding: 6px 12px;\n"
"}\n"
"\n"
"QPushButton#replayBackButton:hover {\n"
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
"QLabel#"
                        "statusLabel {\n"
"    color: #fbbf24;\n"
"    font-family: Arial, sans-serif;\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"    text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.5);\n"
"    text-align: center;\n"
"}"));
        replayMainLayout = new QVBoxLayout(ReplayBoardForm);
        replayMainLayout->setSpacing(20);
        replayMainLayout->setObjectName("replayMainLayout");
        replayMainLayout->setContentsMargins(30, 20, 30, 20);
        replayTitleLabel = new QLabel(ReplayBoardForm);
        replayTitleLabel->setObjectName("replayTitleLabel");
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(20);
        font.setBold(true);
        replayTitleLabel->setFont(font);
        replayTitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        replayMainLayout->addWidget(replayTitleLabel);

        replayGameLayout = new QHBoxLayout();
        replayGameLayout->setObjectName("replayGameLayout");
        replayLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        replayGameLayout->addItem(replayLeftSpacer);

        replayBoardGrid = new QGridLayout();
        replayBoardGrid->setSpacing(8);
        replayBoardGrid->setObjectName("replayBoardGrid");
        replayBtn_1_1 = new QPushButton(ReplayBoardForm);
        replayBtn_1_1->setObjectName("replayBtn_1_1");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(replayBtn_1_1->sizePolicy().hasHeightForWidth());
        replayBtn_1_1->setSizePolicy(sizePolicy);

        replayBoardGrid->addWidget(replayBtn_1_1, 1, 1, 1, 1);

        replayBtn_2_0 = new QPushButton(ReplayBoardForm);
        replayBtn_2_0->setObjectName("replayBtn_2_0");
        sizePolicy.setHeightForWidth(replayBtn_2_0->sizePolicy().hasHeightForWidth());
        replayBtn_2_0->setSizePolicy(sizePolicy);

        replayBoardGrid->addWidget(replayBtn_2_0, 2, 0, 1, 1);

        replayBottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        replayBoardGrid->addItem(replayBottomSpacer, 3, 1, 1, 1);

        replayBtn_0_0 = new QPushButton(ReplayBoardForm);
        replayBtn_0_0->setObjectName("replayBtn_0_0");
        sizePolicy.setHeightForWidth(replayBtn_0_0->sizePolicy().hasHeightForWidth());
        replayBtn_0_0->setSizePolicy(sizePolicy);

        replayBoardGrid->addWidget(replayBtn_0_0, 0, 0, 1, 1);

        replayBtn_2_2 = new QPushButton(ReplayBoardForm);
        replayBtn_2_2->setObjectName("replayBtn_2_2");
        sizePolicy.setHeightForWidth(replayBtn_2_2->sizePolicy().hasHeightForWidth());
        replayBtn_2_2->setSizePolicy(sizePolicy);

        replayBoardGrid->addWidget(replayBtn_2_2, 2, 2, 1, 1);

        replayBtn_0_2 = new QPushButton(ReplayBoardForm);
        replayBtn_0_2->setObjectName("replayBtn_0_2");
        sizePolicy.setHeightForWidth(replayBtn_0_2->sizePolicy().hasHeightForWidth());
        replayBtn_0_2->setSizePolicy(sizePolicy);

        replayBoardGrid->addWidget(replayBtn_0_2, 0, 2, 1, 1);

        replayBtn_0_1 = new QPushButton(ReplayBoardForm);
        replayBtn_0_1->setObjectName("replayBtn_0_1");
        sizePolicy.setHeightForWidth(replayBtn_0_1->sizePolicy().hasHeightForWidth());
        replayBtn_0_1->setSizePolicy(sizePolicy);

        replayBoardGrid->addWidget(replayBtn_0_1, 0, 1, 1, 1);

        replayBtn_1_2 = new QPushButton(ReplayBoardForm);
        replayBtn_1_2->setObjectName("replayBtn_1_2");
        sizePolicy.setHeightForWidth(replayBtn_1_2->sizePolicy().hasHeightForWidth());
        replayBtn_1_2->setSizePolicy(sizePolicy);

        replayBoardGrid->addWidget(replayBtn_1_2, 1, 2, 1, 1);

        replayBtn_1_0 = new QPushButton(ReplayBoardForm);
        replayBtn_1_0->setObjectName("replayBtn_1_0");
        sizePolicy.setHeightForWidth(replayBtn_1_0->sizePolicy().hasHeightForWidth());
        replayBtn_1_0->setSizePolicy(sizePolicy);

        replayBoardGrid->addWidget(replayBtn_1_0, 1, 0, 1, 1);

        replayBtn_2_1 = new QPushButton(ReplayBoardForm);
        replayBtn_2_1->setObjectName("replayBtn_2_1");
        sizePolicy.setHeightForWidth(replayBtn_2_1->sizePolicy().hasHeightForWidth());
        replayBtn_2_1->setSizePolicy(sizePolicy);

        replayBoardGrid->addWidget(replayBtn_2_1, 2, 1, 1, 1);

        pushButton = new QPushButton(ReplayBoardForm);
        pushButton->setObjectName("pushButton");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial Black")});
        font1.setBold(true);
        font1.setItalic(true);
        pushButton->setFont(font1);

        replayBoardGrid->addWidget(pushButton, 4, 1, 1, 1);


        replayGameLayout->addLayout(replayBoardGrid);

        replayRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        replayGameLayout->addItem(replayRightSpacer);


        replayMainLayout->addLayout(replayGameLayout);

        replayControlLayout = new QHBoxLayout();
        replayControlLayout->setSpacing(15);
        replayControlLayout->setObjectName("replayControlLayout");
        replayControlLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        replayControlLayout->addItem(replayControlLeftSpacer);

        replayBackButton = new QPushButton(ReplayBoardForm);
        replayBackButton->setObjectName("replayBackButton");

        replayControlLayout->addWidget(replayBackButton);

        replayControlRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        replayControlLayout->addItem(replayControlRightSpacer);


        replayMainLayout->addLayout(replayControlLayout);


        retranslateUi(ReplayBoardForm);

        QMetaObject::connectSlotsByName(ReplayBoardForm);
    } // setupUi

    void retranslateUi(QWidget *ReplayBoardForm)
    {
        ReplayBoardForm->setWindowTitle(QCoreApplication::translate("ReplayBoardForm", "TicTacToy - Game Board", nullptr));
        replayTitleLabel->setText(QCoreApplication::translate("ReplayBoardForm", "Review Game", nullptr));
        replayBtn_1_1->setText(QString());
        replayBtn_2_0->setText(QString());
        replayBtn_0_0->setText(QString());
        replayBtn_2_2->setText(QString());
        replayBtn_0_2->setText(QString());
        replayBtn_0_1->setText(QString());
        replayBtn_1_2->setText(QString());
        replayBtn_1_0->setText(QString());
        replayBtn_2_1->setText(QString());
        pushButton->setText(QCoreApplication::translate("ReplayBoardForm", "Start", nullptr));
#if QT_CONFIG(tooltip)
        replayBackButton->setToolTip(QCoreApplication::translate("ReplayBoardForm", "Return to the main menu", nullptr));
#endif // QT_CONFIG(tooltip)
        replayBackButton->setText(QCoreApplication::translate("ReplayBoardForm", "\360\237\217\240 Back to Home", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReplayBoardForm: public Ui_ReplayBoardForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPLAYBOARD_H
