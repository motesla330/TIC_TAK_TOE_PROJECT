/********************************************************************************
** Form generated from reading UI file 'home.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_H
#define UI_HOME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Home
{
public:
    QAction *actionNew_Game;
    QAction *actionSettings;
    QAction *actionExit;
    QAction *actionFull_Screen;
    QAction *actionTheme;
    QAction *actionHow_to_Play;
    QAction *actionAbout;
    QWidget *centralwidget;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QLabel *userLabel;
    QTableWidget *gameHistoryTable;
    QPushButton *aiButton;
    QPushButton *friendButton;
    QFrame *statsFrame;
    QVBoxLayout *verticalLayout;
    QLabel *statsLabel;
    QPushButton *pushButton;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_3;
    QMenuBar *menubar;
    QMenu *menuGame;
    QMenu *menuView;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Home)
    {
        if (Home->objectName().isEmpty())
            Home->setObjectName("Home");
        Home->resize(900, 700);
        Home->setMinimumSize(QSize(900, 700));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        QLinearGradient gradient(0, 0, 1, 1);
        gradient.setSpread(QGradient::Spread::PadSpread);
        gradient.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient.setColorAt(0, QColor(30, 60, 114, 255));
        gradient.setColorAt(1, QColor(42, 82, 152, 255));
        QBrush brush1(gradient);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Light, brush2);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Midlight, brush2);
        QBrush brush3(QColor(127, 127, 127, 255));
        brush3.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Dark, brush3);
        QBrush brush4(QColor(170, 170, 170, 255));
        brush4.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Mid, brush4);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::BrightText, brush2);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush);
        QLinearGradient gradient1(0, 0, 1, 1);
        gradient1.setSpread(QGradient::Spread::PadSpread);
        gradient1.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient1.setColorAt(0, QColor(30, 60, 114, 255));
        gradient1.setColorAt(1, QColor(42, 82, 152, 255));
        QBrush brush5(gradient1);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush5);
        QLinearGradient gradient2(0, 0, 1, 1);
        gradient2.setSpread(QGradient::Spread::PadSpread);
        gradient2.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient2.setColorAt(0, QColor(30, 60, 114, 255));
        gradient2.setColorAt(1, QColor(42, 82, 152, 255));
        QBrush brush6(gradient2);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush6);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Shadow, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::AlternateBase, brush2);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipBase, brush7);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipText, brush);
        QBrush brush8(QColor(0, 0, 0, 127));
        brush8.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush8);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Accent, brush2);
#endif
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        QLinearGradient gradient3(0, 0, 1, 1);
        gradient3.setSpread(QGradient::Spread::PadSpread);
        gradient3.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient3.setColorAt(0, QColor(30, 60, 114, 255));
        gradient3.setColorAt(1, QColor(42, 82, 152, 255));
        QBrush brush9(gradient3);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush9);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Light, brush2);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Midlight, brush2);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Dark, brush3);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Mid, brush4);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::BrightText, brush2);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush);
        QLinearGradient gradient4(0, 0, 1, 1);
        gradient4.setSpread(QGradient::Spread::PadSpread);
        gradient4.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient4.setColorAt(0, QColor(30, 60, 114, 255));
        gradient4.setColorAt(1, QColor(42, 82, 152, 255));
        QBrush brush10(gradient4);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush10);
        QLinearGradient gradient5(0, 0, 1, 1);
        gradient5.setSpread(QGradient::Spread::PadSpread);
        gradient5.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient5.setColorAt(0, QColor(30, 60, 114, 255));
        gradient5.setColorAt(1, QColor(42, 82, 152, 255));
        QBrush brush11(gradient5);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush11);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Shadow, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::AlternateBase, brush2);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipBase, brush7);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush8);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Accent, brush2);
#endif
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush3);
        QLinearGradient gradient6(0, 0, 1, 1);
        gradient6.setSpread(QGradient::Spread::PadSpread);
        gradient6.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient6.setColorAt(0, QColor(30, 60, 114, 255));
        gradient6.setColorAt(1, QColor(42, 82, 152, 255));
        QBrush brush12(gradient6);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush12);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Light, brush2);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Midlight, brush2);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Dark, brush3);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Mid, brush4);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush3);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::BrightText, brush2);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush3);
        QLinearGradient gradient7(0, 0, 1, 1);
        gradient7.setSpread(QGradient::Spread::PadSpread);
        gradient7.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient7.setColorAt(0, QColor(30, 60, 114, 255));
        gradient7.setColorAt(1, QColor(42, 82, 152, 255));
        QBrush brush13(gradient7);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush13);
        QLinearGradient gradient8(0, 0, 1, 1);
        gradient8.setSpread(QGradient::Spread::PadSpread);
        gradient8.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient8.setColorAt(0, QColor(30, 60, 114, 255));
        gradient8.setColorAt(1, QColor(42, 82, 152, 255));
        QBrush brush14(gradient8);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush14);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Shadow, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::AlternateBase, brush2);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipBase, brush7);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipText, brush);
        QBrush brush15(QColor(127, 127, 127, 127));
        brush15.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush15);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Accent, brush2);
#endif
        Home->setPalette(palette);
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("applications-games")));
        Home->setWindowIcon(icon);
        Home->setStyleSheet(QString::fromUtf8("\n"
"    /* Main Window Styling */\n"
"    QMainWindow {\n"
"        background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"                    stop:0 #1e3c72, stop:1 #2a5298);\n"
"        color: #ffffff;\n"
"    }\n"
"    \n"
"    /* Central Widget */\n"
"    QWidget#centralwidget {\n"
"        background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"                    stop:0 #1e3c72, stop:1 #2a5298);\n"
"    }\n"
"    \n"
"    /* Header Labels */\n"
"    QLabel#titleLabel {\n"
"        color: #ffffff;\n"
"        font-family: 'Segoe UI', Arial, sans-serif;\n"
"        font-size: 28px;\n"
"        font-weight: bold;\n"
"        text-shadow: 2px 2px 4px rgba(0,0,0,0.5);\n"
"        background: transparent;\n"
"    }\n"
"    \n"
"    QLabel#subtitleLabel {\n"
"        color: #e8f4fd;\n"
"        font-family: 'Segoe UI', Arial, sans-serif;\n"
"        font-size: 16px;\n"
"        font-weight: 500;\n"
"        text-shadow: 1px 1px 2px rgba(0,0,0,0.3);\n"
"        background: transparent;\n"
"    }\n"
"    \n"
" "
                        "   QLabel#userLabel {\n"
"        color: #ffffff;\n"
"        font-family: 'Segoe UI', Arial, sans-serif;\n"
"        font-size: 14px;\n"
"        font-weight: 600;\n"
"        background: rgba(255,255,255,0.1);\n"
"        border-radius: 8px;\n"
"        padding: 8px 12px;\n"
"        border: 1px solid rgba(255,255,255,0.2);\n"
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
"                    stop:0 #5fbdff, s"
                        "top:1 #1af3fe);\n"
"        transform: translateY(-2px);\n"
"        box-shadow: 0 6px 20px rgba(79, 172, 254, 0.4);\n"
"    }\n"
"    \n"
"    QPushButton:pressed {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #3a9bfd, stop:1 #00d9fe);\n"
"        transform: translateY(1px);\n"
"        box-shadow: 0 2px 10px rgba(79, 172, 254, 0.2);\n"
"    }\n"
"    \n"
"    QPushButton#aiButton {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #667eea, stop:1 #764ba2);\n"
"        box-shadow: 0 4px 15px rgba(102, 126, 234, 0.3);\n"
"    }\n"
"    \n"
"    QPushButton#aiButton:hover {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #7b8beb, stop:1 #8659b3);\n"
"        box-shadow: 0 6px 20px rgba(102, 126, 234, 0.4);\n"
"    }\n"
"    \n"
"    /* Game History Table */\n"
"    QTableWidget {\n"
"        background: rgba(255, 255, 255, 0.95);\n"
"        border: none;\n"
"        bord"
                        "er-radius: 15px;\n"
"        gridline-color: #e0e0e0;\n"
"        font-family: 'Segoe UI', Arial, sans-serif;\n"
"        font-size: 13px;\n"
"        selection-background-color: #4facfe;\n"
"        selection-color: white;\n"
"        box-shadow: 0 8px 30px rgba(0,0,0,0.1);\n"
"    }\n"
"    \n"
"    QTableWidget::item {\n"
"        padding: 12px;\n"
"        border-bottom: 1px solid #f0f0f0;\n"
"    }\n"
"    \n"
"    QTableWidget::item:selected {\n"
"        background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                    stop:0 #4facfe, stop:1 #00f2fe);\n"
"        color: white;\n"
"    }\n"
"    \n"
"    QHeaderView::section {\n"
"        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                    stop:0 #2c3e50, stop:1 #34495e);\n"
"        color: white;\n"
"        font-weight: bold;\n"
"        font-size: 14px;\n"
"        padding: 15px;\n"
"        border: none;\n"
"        border-right: 1px solid #34495e;\n"
"    }\n"
"    \n"
"    QHeaderView::section:first {\n"
"        b"
                        "order-top-left-radius: 15px;\n"
"    }\n"
"    \n"
"    QHeaderView::section:last {\n"
"        border-top-right-radius: 15px;\n"
"        border-right: none;\n"
"    }\n"
"    \n"
"    /* Scrollbars */\n"
"    QScrollBar:vertical {\n"
"        background: rgba(255,255,255,0.1);\n"
"        width: 12px;\n"
"        border-radius: 6px;\n"
"    }\n"
"    \n"
"    QScrollBar::handle:vertical {\n"
"        background: rgba(255,255,255,0.3);\n"
"        border-radius: 6px;\n"
"        min-height: 20px;\n"
"    }\n"
"    \n"
"    QScrollBar::handle:vertical:hover {\n"
"        background: rgba(255,255,255,0.5);\n"
"    }\n"
"    \n"
"    /* Menu Bar */\n"
"    QMenuBar {\n"
"        background: rgba(0,0,0,0.2);\n"
"        color: white;\n"
"        font-family: 'Segoe UI', Arial, sans-serif;\n"
"        font-size: 13px;\n"
"        border: none;\n"
"    }\n"
"    \n"
"    QMenuBar::item {\n"
"        padding: 8px 16px;\n"
"        background: transparent;\n"
"    }\n"
"    \n"
"    QMenuBar::item:selected {\n"
"    "
                        "    background: rgba(255,255,255,0.1);\n"
"        border-radius: 4px;\n"
"    }\n"
"    \n"
"    /* Status Bar */\n"
"    QStatusBar {\n"
"        background: rgba(0,0,0,0.2);\n"
"        color: white;\n"
"        font-family: 'Segoe UI', Arial, sans-serif;\n"
"        border: none;\n"
"    }\n"
"   "));
        actionNew_Game = new QAction(Home);
        actionNew_Game->setObjectName("actionNew_Game");
        actionSettings = new QAction(Home);
        actionSettings->setObjectName("actionSettings");
        actionExit = new QAction(Home);
        actionExit->setObjectName("actionExit");
        actionFull_Screen = new QAction(Home);
        actionFull_Screen->setObjectName("actionFull_Screen");
        actionTheme = new QAction(Home);
        actionTheme->setObjectName("actionTheme");
        actionHow_to_Play = new QAction(Home);
        actionHow_to_Play->setObjectName("actionHow_to_Play");
        actionAbout = new QAction(Home);
        actionAbout->setObjectName("actionAbout");
        centralwidget = new QWidget(Home);
        centralwidget->setObjectName("centralwidget");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setGeometry(QRect(0, 30, 900, 50));
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        subtitleLabel = new QLabel(centralwidget);
        subtitleLabel->setObjectName("subtitleLabel");
        subtitleLabel->setGeometry(QRect(0, 80, 900, 30));
        subtitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        userLabel = new QLabel(centralwidget);
        userLabel->setObjectName("userLabel");
        userLabel->setGeometry(QRect(20, 10, 200, 40));
        userLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        gameHistoryTable = new QTableWidget(centralwidget);
        if (gameHistoryTable->columnCount() < 4)
            gameHistoryTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        gameHistoryTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        gameHistoryTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        gameHistoryTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        gameHistoryTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        gameHistoryTable->setObjectName("gameHistoryTable");
        gameHistoryTable->setGeometry(QRect(50, 140, 800, 380));
        gameHistoryTable->setAlternatingRowColors(true);
        gameHistoryTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        gameHistoryTable->setShowGrid(false);
        gameHistoryTable->setSortingEnabled(true);
        gameHistoryTable->horizontalHeader()->setDefaultSectionSize(200);
        gameHistoryTable->verticalHeader()->setVisible(false);
        aiButton = new QPushButton(centralwidget);
        aiButton->setObjectName("aiButton");
        aiButton->setGeometry(QRect(510, 550, 200, 60));
        aiButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        friendButton = new QPushButton(centralwidget);
        friendButton->setObjectName("friendButton");
        friendButton->setGeometry(QRect(150, 550, 200, 60));
        friendButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        statsFrame = new QFrame(centralwidget);
        statsFrame->setObjectName("statsFrame");
        statsFrame->setGeometry(QRect(630, 10, 251, 81));
        statsFrame->setStyleSheet(QString::fromUtf8("\n"
"      QFrame {\n"
"          background: rgba(255,255,255,0.1);\n"
"          border-radius: 12px;\n"
"          border: 1px solid rgba(255,255,255,0.2);\n"
"      }\n"
"     "));
        verticalLayout = new QVBoxLayout(statsFrame);
        verticalLayout->setObjectName("verticalLayout");
        statsLabel = new QLabel(statsFrame);
        statsLabel->setObjectName("statsLabel");
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setBold(true);
        statsLabel->setFont(font);
        statsLabel->setStyleSheet(QString::fromUtf8("\n"
"       QLabel {\n"
"           color: white;\n"
"           font-family: 'Segoe UI', Arial, sans-serif;\n"
"           font-size: 12px;\n"
"           background: transparent;\n"
"           border: none;\n"
"       }\n"
"      "));
        statsLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(statsLabel);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(60, 60, 111, 51));
        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(730, 550, 112, 26));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(radioButton->sizePolicy().hasHeightForWidth());
        radioButton->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        radioButton->setFont(font1);
        radioButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        radioButton_2 = new QRadioButton(centralwidget);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(730, 570, 112, 26));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(radioButton_2->sizePolicy().hasHeightForWidth());
        radioButton_2->setSizePolicy(sizePolicy1);
        radioButton_2->setFont(font1);
        radioButton_2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        radioButton_3 = new QRadioButton(centralwidget);
        radioButton_3->setObjectName("radioButton_3");
        radioButton_3->setGeometry(QRect(730, 590, 112, 26));
        sizePolicy1.setHeightForWidth(radioButton_3->sizePolicy().hasHeightForWidth());
        radioButton_3->setSizePolicy(sizePolicy1);
        radioButton_3->setFont(font1);
        radioButton_3->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(50, 159, 791, 361));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        Home->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Home);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 900, 33));
        menuGame = new QMenu(menubar);
        menuGame->setObjectName("menuGame");
        menuView = new QMenu(menubar);
        menuView->setObjectName("menuView");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        Home->setMenuBar(menubar);
        statusbar = new QStatusBar(Home);
        statusbar->setObjectName("statusbar");
        statusbar->setSizeGripEnabled(true);
        Home->setStatusBar(statusbar);

        menubar->addAction(menuGame->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuGame->addAction(actionNew_Game);
        menuGame->addAction(actionSettings);
        menuGame->addSeparator();
        menuGame->addAction(actionExit);
        menuView->addAction(actionFull_Screen);
        menuView->addAction(actionTheme);
        menuHelp->addAction(actionHow_to_Play);
        menuHelp->addAction(actionAbout);

        retranslateUi(Home);

        QMetaObject::connectSlotsByName(Home);
    } // setupUi

    void retranslateUi(QMainWindow *Home)
    {
        Home->setWindowTitle(QCoreApplication::translate("Home", "Tic Tac Toe Pro", nullptr));
        actionNew_Game->setText(QCoreApplication::translate("Home", "New Game", nullptr));
#if QT_CONFIG(shortcut)
        actionNew_Game->setShortcut(QCoreApplication::translate("Home", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSettings->setText(QCoreApplication::translate("Home", "Settings", nullptr));
#if QT_CONFIG(shortcut)
        actionSettings->setShortcut(QCoreApplication::translate("Home", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionExit->setText(QCoreApplication::translate("Home", "Exit", nullptr));
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QCoreApplication::translate("Home", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFull_Screen->setText(QCoreApplication::translate("Home", "Full Screen", nullptr));
#if QT_CONFIG(shortcut)
        actionFull_Screen->setShortcut(QCoreApplication::translate("Home", "F11", nullptr));
#endif // QT_CONFIG(shortcut)
        actionTheme->setText(QCoreApplication::translate("Home", "Change Theme", nullptr));
        actionHow_to_Play->setText(QCoreApplication::translate("Home", "How to Play", nullptr));
#if QT_CONFIG(shortcut)
        actionHow_to_Play->setShortcut(QCoreApplication::translate("Home", "F1", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAbout->setText(QCoreApplication::translate("Home", "About", nullptr));
        titleLabel->setText(QCoreApplication::translate("Home", "TIC TAC TOE PRO", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("Home", "Choose your game mode and start playing!", nullptr));
        userLabel->setText(QCoreApplication::translate("Home", "\360\237\221\244 Welcome, Player!", nullptr));
        QTableWidgetItem *___qtablewidgetitem = gameHistoryTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Home", "\360\237\217\206 Winner", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = gameHistoryTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Home", "\360\237\223\205 Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = gameHistoryTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Home", "\360\237\216\257 Moves", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = gameHistoryTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Home", "\360\237\244\226 Opponent", nullptr));
        aiButton->setText(QCoreApplication::translate("Home", "\360\237\244\226 Play vs AI", nullptr));
        friendButton->setText(QCoreApplication::translate("Home", "\360\237\221\245 Play with Friend", nullptr));
        statsLabel->setText(QCoreApplication::translate("Home", "\360\237\223\212 Quick Stats\n"
"Games: 12 | Wins: 8", nullptr));
        pushButton->setText(QCoreApplication::translate("Home", "Logout", nullptr));
        radioButton->setText(QCoreApplication::translate("Home", "Easy", nullptr));
        radioButton_2->setText(QCoreApplication::translate("Home", "Normal", nullptr));
        radioButton_3->setText(QCoreApplication::translate("Home", "Hard", nullptr));
        menuGame->setTitle(QCoreApplication::translate("Home", "Game", nullptr));
        menuView->setTitle(QCoreApplication::translate("Home", "View", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("Home", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Home: public Ui_Home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_H
