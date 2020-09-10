cmake_minimum_required(VERSION 3.16)
project(single C)

set(CMAKE_C_STANDARD 99)
file(GLOB_RECURSE mains RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
foreach (main IN LISTS mains)
    # Get file name without directory
    get_filename_component(name ${main} NAME_WE)
    add_executable(${name} ${main})
endforeach ()