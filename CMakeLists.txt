cmake_minimum_required(VERSION 3.14)
project(TIC_TAC_TOE_PROJECT)
set(CMAKE_CXX_STANDARD 17)

# Use MSYS2 MinGW OpenSSL headers + libraries
include_directories("C:/msys64/mingw64/include")
link_directories("C:/msys64/mingw64/lib")

add_library(authentication Authentication.cpp Authentication.h)

include(FetchContent)
FetchContent_Declare(
  googletest URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(auth_tests Authentication_test.cpp)
target_link_libraries(auth_tests
  authentication
  gtest
  gtest_main
  ssl
  crypto
)
include(GoogleTest)
gtest_discover_tests(auth_tests)
