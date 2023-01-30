# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\pm-client-source-code_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\pm-client-source-code_autogen.dir\\ParseCache.txt"
  "pm-client-source-code_autogen"
  )
endif()
