cmake_minimum_required(VERSION 3.16)
project(tictactoe VERSION 0.1 LANGUAGES CXX)

# ========================
# Core Project Settings
# ========================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ========================
# Qt Configuration
# ========================
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# ========================
# Project Sources
# ========================
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Board.cpp
    Board.h
    gamelogic.cpp
    gamelogic.h
    historymanager.cpp
    historymanager.h
    ai_opponent.cpp
    ai_opponent.h
    AIAdapter.h
)

# ========================
# Main Executable (Qt)
# ========================
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tictactoe
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(tictactoe ${PROJECT_SOURCES})
endif()

target_link_libraries(tictactoe PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# ========================
# GoogleTest Setup
# ========================
# Add GoogleTest (assumes googletest/ is added to your repo root)
add_subdirectory(googletest)

# Add tests (you will create the tests folder)
enable_testing()

# Add test source files
set(TEST_SOURCES
    tests/test_board.cpp
    tests/test_dummy.cpp
)

add_executable(unit_tests ${TEST_SOURCES})

# Link GoogleTest and your project files
target_link_libraries(unit_tests
    gtest
    gtest_main
    Qt${QT_VERSION_MAJOR}::Widgets
)

# Include your project's headers if needed
target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Register test with CTest
add_test(NAME AllTests COMMAND unit_tests)
