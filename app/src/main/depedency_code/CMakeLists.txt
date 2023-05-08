cmake_minimum_required(VERSION 3.22.1)

message("CMAKE_CURRENT_LIST_DIR = ${CMAKE_CURRENT_LIST_DIR}")

# 添加头文件至搜索路径
include_directories(${CMAKE_CURRENT_LIST_DIR}/cpp)

set(NATIVE_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/cpp/Depedency.cpp)

add_library(c_depedency STATIC ${NATIVE_SOURCES})
