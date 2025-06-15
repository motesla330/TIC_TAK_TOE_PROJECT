cmake_minimum_required(VERSION 3.14)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

# Qt setup
find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Your source files
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

# UI file
set(UIS
    mainwindow.ui
)

# Add your app
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UIS})
target_link_libraries(${PROJECT_NAME} Qt6::Widgets)

# -------------- GTest Section --------------

# Add GoogleTest
add_subdirectory(googletest)

# Create test executable
add_executable(tests
    tests/test_board.cpp
    tests/test_dummy.cpp
)

# Link GoogleTest + your source code
target_link_libraries(tests gtest gtest_main)

# Link your source files to tests (optional if functions/classes are reused)
target_link_libraries(tests PRIVATE Qt6::Widgets)

# Enable testing
enable_testing()
add_test(NAME AllTests COMMAND tests)
