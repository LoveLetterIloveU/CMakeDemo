cmake_minimum_required(VERSION 3.22.1)


message("CMAKE_CURRENT_LIST_DIR = ${CMAKE_CURRENT_LIST_DIR}")

#、指定头文件的路径，方便编译时能找到头文件
include_directories(${PROJECT_SOURCE_DIR}/cpp/)

set(NATIVE_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/cpp/native-lib.cpp)

# add_library 将c文件编译成.a静态库、.so动态库
# 可以定义多个库
# 路径为CMakeList文件的相对路径
add_library(c_main SHARED ${NATIVE_SOURCES})

# 声明库之间的依赖关系，这里capplication依赖log-lib 和 自研静态库
target_link_libraries(c_main ${log-lib} c_depedency)