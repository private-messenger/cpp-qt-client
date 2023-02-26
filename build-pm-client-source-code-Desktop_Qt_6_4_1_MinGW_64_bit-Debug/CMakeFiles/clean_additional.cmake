# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\spik-source_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\spik-source_autogen.dir\\ParseCache.txt"
  "spik-source_autogen"
  )
endif()
