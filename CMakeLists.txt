cmake_minimum_required(VERSION 3.10)
project(SessionManagementProject)

set(CMAKE_CXX_STANDARD 17)

# Add the source directory (current dir)
add_library(SessionManagement
    SessionManagement.cpp
)

# Enable testing
enable_testing()

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(test_runner test_session_manager.cpp)
target_link_libraries(test_runner SessionManagement gtest_main)

include(GoogleTest)
gtest_discover_tests(test_runner)
