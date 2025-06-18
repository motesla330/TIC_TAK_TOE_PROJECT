QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Authentication.cpp \
    Board.cpp \
    ai_opponent.cpp \
    codeverification.cpp \
    game.cpp \
    gamelogic.cpp \
    gamemanager.cpp \
    globals.cpp \
    historymanager.cpp \
    home.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    playboard.cpp \
    playermanager.cpp \
    replayboard.cpp \
    sessiontimer.cpp

HEADERS += \
    Authentication.h \
    Board.h \
    ai_opponent.h \
    codeverification.h \
    game.h \
    gamelogic.h \
    gamemanager.h \
    globals.h \
    historymanager.h \
    home.h \
    json.hpp \
    login.h \
    mainwindow.h \
    playboard.h \
    playermanager.h \
    replayboard.h \
    sessiontimer.h

FORMS += \
    codeverification.ui \
    home.ui \
    login.ui \
    mainwindow.ui \
    playboard.ui \
    replayboard.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Adjust paths based on your installation directory
INCLUDEPATH += "C:/Program Files/OpenSSL-Win64/include"
LIBS += -L"C:/Program Files/OpenSSL-Win64/lib/VC/x64/MD" -lcrypto -lssl

# For runtime, ensure DLLs are accessible
# Either copy DLLs to your output directory or add to PATH

DISTFILES += \
    payload.json
