aux_source_directory(. DIR_SRC)

# 添加子目录
add_subdirectory(hello)
add_subdirectory(world)

# 执行文件
add_executable(sample3 ${DIR_SRC})
target_link_libraries(sample3 hello_lib world_lib)
