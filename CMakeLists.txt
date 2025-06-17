cmake_minimum_required(VERSION 3.10)
project(SessionManagementTest)

set(CMAKE_CXX_STANDARD 17)

# Add main library
add_library(SessionManagement
    SessionManagement.cpp
)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test runner
add_executable(test_runner test_session_manager.cpp)
# Just use gtest without gtest_main
target_link_libraries(test_runner
    SessionManagement
    gtest
)
add_test(NAME SessionTests COMMAND test_runner)