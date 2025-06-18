cmake_minimum_required(VERSION 3.16)
project(tictactoe VERSION 0.1 LANGUAGES CXX)

# ========================
# Core Settings
# ========================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ========================
# Qt Setup
# ========================
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# ========================
# Source Files
# ========================
file(GLOB_RECURSE APP_SOURCES
    "*.cpp"
    "*.h"
    "*.ui"
)

# Filter out test files from app sources
list(FILTER APP_SOURCES EXCLUDE REGEX "tests/.*")

# ========================
# Add Executable for Main App
# ========================
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tictactoe
        MANUAL_FINALIZATION
        ${APP_SOURCES}
    )
else()
    add_executable(tictactoe ${APP_SOURCES})
endif()

target_link_libraries(tictactoe PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# ========================
# GoogleTest Setup
# ========================
# Add subdirectory only if GTest is local
add_subdirectory(external/googletest)
include_directories(external/googletest/googletest/include)

# ========================
# Test Sources
# ========================
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")

add_executable(runTests
    ${TEST_SOURCES}
    Board.cpp
    gamelogic.cpp
    historymanager.cpp
    ai_opponent.cpp
)

target_include_directories(runTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(runTests
    gtest
    gtest_main
    Qt${QT_VERSION_MAJOR}::Widgets  # If you test any Qt-based code
)

enable_testing()
add_test(NAME AllTests COMMAND runTests)
