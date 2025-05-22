cmake_minimum_required(VERSION 3.10)
project(DataCollection)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows特定设置
if(WIN32)
    # 设置输出目录
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    
    # 添加编译选项
    add_compile_options(/W4)
else()
    # Unix系统的编译选项
    add_compile_options(-Wall -Wextra)
endif()

# 添加源文件目录
add_subdirectory(source)
