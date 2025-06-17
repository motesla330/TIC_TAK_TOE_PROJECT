cmake_minimum_required(VERSION 3.14)
project(AuthenticationSystem)

set(CMAKE_CXX_STANDARD 17)

# GoogleTest Setup
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Main library
add_library(authentication
    Authentication.cpp
    Authentication.h
)

# Test executable
add_executable(auth_tests
    Authentication_test.cpp
)

# Link everything
target_link_libraries(auth_tests
    PRIVATE authentication
    GTest::gtest_main
)

# Enable test discovery
include(GoogleTest)
enable_testing()
gtest_discover_tests(auth_tests)
