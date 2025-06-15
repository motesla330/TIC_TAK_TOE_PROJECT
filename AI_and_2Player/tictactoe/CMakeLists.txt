cmake_minimum_required(VERSION 3.10)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

# Add Qt components
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR})

# Add source files
set(SOURCES
    main.cpp
    mainwindow.cpp
    Board.cpp
    gamelogic.cpp
    historymanager.cpp
    ai_opponent.cpp
)

set(HEADERS
    mainwindow.h
    Board.h
    gamelogic.h
    historymanager.h
    ai_opponent.h
    AIAdapter.h
)

qt6_wrap_ui(UI_HEADERS mainwindow.ui)

add_executable(TicTacToe ${SOURCES} ${HEADERS} ${UI_HEADERS})
target_link_libraries(TicTacToe Qt6::Core Qt6::Gui Qt6::Widgets)

# GoogleTest
add_subdirectory(../googletest googletest-build)

enable_testing()

add_executable(runTests
    test/test_main.cpp
    test/test_logic.cpp
    test/test_board.cpp
)

target_link_libraries(runTests gtest gtest_main)
add_test(NAME runTests COMMAND runTests)
