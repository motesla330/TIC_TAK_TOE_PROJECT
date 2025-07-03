QT -= gui
CONFIG += console c++17
CONFIG -= app_bundle

TEMPLATE = app
TARGET = test_tests

INCLUDEPATH += googletest/googletest/include googletest/googletest
DEPENDPATH += googletest/googletest

SOURCES += \
    test_gamelogic.cpp \
    googletest/googletest/src/gtest-all.cc \
    gamelogic.cpp

HEADERS += \
    googletest/googletest/include/gtest/gtest.h \
    gamelogic.h

# QMAKE_CXXFLAGS += -pthread
