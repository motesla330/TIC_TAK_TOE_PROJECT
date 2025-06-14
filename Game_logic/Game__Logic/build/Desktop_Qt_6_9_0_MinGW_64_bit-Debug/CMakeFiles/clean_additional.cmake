# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Game__Logic_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Game__Logic_autogen.dir\\ParseCache.txt"
  "Game__Logic_autogen"
  )
endif()
