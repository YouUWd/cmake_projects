CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(leetcode C)

SET(CMAKE_C_STANDARD 99)
FILE(GLOB mains RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
foreach (main IN LISTS mains)
    # Get file name without directory
    GET_FILENAME_COMPONENT(name ${main} NAME_WE)
    ADD_EXECUTABLE(${name} ${main})
endforeach ()