cmake_minimum_required(VERSION 3.19)
project(database C)

set(CMAKE_C_STANDARD 99)

INCLUDE_DIRECTORIES(./include)
LINK_DIRECTORIES(./lib)

FILE(GLOB mains RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
foreach (main IN LISTS mains)
    # Get file name without directory
    GET_FILENAME_COMPONENT(name ${main} NAME_WE)
    ADD_EXECUTABLE(${name} ${main})
    TARGET_LINK_LIBRARIES(${name} libmysqlclient.dylib)
endforeach ()