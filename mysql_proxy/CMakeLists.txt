CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(mysql_proxy C)

SET(CMAKE_C_STANDARD 99)

#SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

# HEADER 头文件
INCLUDE_DIRECTORIES(/usr/local/include)
# Link 库
LINK_DIRECTORIES(/usr/local/lib)
LINK_LIBRARIES(net)

FILE(GLOB mains RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
foreach (main IN LISTS mains)
    # Get file name without directory
    GET_FILENAME_COMPONENT(name ${main} NAME_WE)
    ADD_EXECUTABLE(${name} ${main})
endforeach ()
