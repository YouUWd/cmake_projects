cmake_minimum_required(VERSION 3.15)
project(tinyhttpd C)

set(CMAKE_C_STANDARD 99)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/htdocs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(httpd httpd.c)
add_executable(client client.c)