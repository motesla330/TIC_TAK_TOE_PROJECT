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
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# ========================
# Source Files
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
    ai_opponent.h
    ai_opponent.cpp
    AIAdapter.h
)

# ========================
# Main Executable
# ========================
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tictactoe
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(tictactoe ${PROJECT_SOURCES})
endif()

target_include_directories(tictactoe PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_CURRENT_BINARY_DIR}/tictactoe_autogen/include"
)

target_link_libraries(tictactoe PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# ========================
# Google Test Integration
# ========================
# Add GoogleTest as a subdirectory
add_subdirectory(${CMAKE_SOURCE_DIR}/external/googletest)

enable_testing()

# List test source files
set(TEST_SOURCES
    tests/test_gamelogic.cpp
    tests/test_board.cpp
    tests/test_ai_opponent.cpp
)

add_executable(UnitTests ${TEST_SOURCES}
               Board.cpp 
               gamelogic.cpp
               ai_opponent.cpp
)

# Include your project headers for testing
target_include_directories(UnitTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(UnitTests
    gtest
    gtest_main
)

# link with Qt if test Qt-based classes
# target_link_libraries(UnitTests Qt${QT_VERSION_MAJOR}::Widgets)

add_test(NAME AllTests COMMAND UnitTests)
