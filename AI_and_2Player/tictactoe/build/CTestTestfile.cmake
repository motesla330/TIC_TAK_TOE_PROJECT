# CMake generated Testfile for 
# Source directory: C:/Users/PC/OneDrive/Documents/GitHub/TIC_TAK_TOE_PROJECT/AI_and_2Player/tictactoe
# Build directory: C:/Users/PC/OneDrive/Documents/GitHub/TIC_TAK_TOE_PROJECT/AI_and_2Player/tictactoe/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(AllTests "C:/Users/PC/OneDrive/Documents/GitHub/TIC_TAK_TOE_PROJECT/AI_and_2Player/tictactoe/build/Debug/UnitTests.exe")
  set_tests_properties(AllTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/PC/OneDrive/Documents/GitHub/TIC_TAK_TOE_PROJECT/AI_and_2Player/tictactoe/CMakeLists.txt;93;add_test;C:/Users/PC/OneDrive/Documents/GitHub/TIC_TAK_TOE_PROJECT/AI_and_2Player/tictactoe/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(AllTests "C:/Users/PC/OneDrive/Documents/GitHub/TIC_TAK_TOE_PROJECT/AI_and_2Player/tictactoe/build/Release/UnitTests.exe")
  set_tests_properties(AllTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/PC/OneDrive/Documents/GitHub/TIC_TAK_TOE_PROJECT/AI_and_2Player/tictactoe/CMakeLists.txt;93;add_test;C:/Users/PC/OneDrive/Documents/GitHub/TIC_TAK_TOE_PROJECT/AI_and_2Player/tictactoe/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(AllTests "C:/Users/PC/OneDrive/Documents/GitHub/TIC_TAK_TOE_PROJECT/AI_and_2Player/tictactoe/build/MinSizeRel/UnitTests.exe")
  set_tests_properties(AllTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/PC/OneDrive/Documents/GitHub/TIC_TAK_TOE_PROJECT/AI_and_2Player/tictactoe/CMakeLists.txt;93;add_test;C:/Users/PC/OneDrive/Documents/GitHub/TIC_TAK_TOE_PROJECT/AI_and_2Player/tictactoe/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(AllTests "C:/Users/PC/OneDrive/Documents/GitHub/TIC_TAK_TOE_PROJECT/AI_and_2Player/tictactoe/build/RelWithDebInfo/UnitTests.exe")
  set_tests_properties(AllTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/PC/OneDrive/Documents/GitHub/TIC_TAK_TOE_PROJECT/AI_and_2Player/tictactoe/CMakeLists.txt;93;add_test;C:/Users/PC/OneDrive/Documents/GitHub/TIC_TAK_TOE_PROJECT/AI_and_2Player/tictactoe/CMakeLists.txt;0;")
else()
  add_test(AllTests NOT_AVAILABLE)
endif()
subdirs("external/googletest")
