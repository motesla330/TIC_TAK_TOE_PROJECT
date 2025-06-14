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
)

# Main executable (Qt)
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
# Google Test Configuration
# ========================
option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    # Test executable (DIFFERENT NAME)
    add_executable(tictactoe_tests
        Tests/test_gamelogic.cpp
        # Add other test files...
    )

    target_link_libraries(tictactoe_tests
        PRIVATE
        tictactoe  # Links with main executable
        GTest::GTest
        GTest::Main
    )

    target_include_directories(tictactoe_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    include(GoogleTest)
    gtest_discover_tests(tictactoe_tests)
endif()

# ========================
# Install/Platform Config
# ========================
# ... (Keep your existing install/packaging config)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(tictactoe)
endif()