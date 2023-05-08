cmake_minimum_required(VERSION 3.22.1)

message("CMAKE_CURRENT_LIST_DIR = ${CMAKE_CURRENT_LIST_DIR}")

# 添加头文件至搜索路径(可以用<>引入头文件)
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}/cpp/)
# 添加依赖库文件至搜索路径（所有的依赖库都可加入）
include_directories(${CMAKE_CURRENT_LIST_DIR}/../depedency_code/cpp)

set(NATIVE_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/cpp/native-lib.cpp)

execute_process(COMMAND sh version.sh . c_version.h WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

# add_library 将c文件编译成.a静态库、.so动态库
# 可以定义多个库
# 路径为CMakeList文件的相对路径
add_library(c_main SHARED ${NATIVE_SOURCES})

# 声明库之间的依赖关系，这里capplication依赖log-lib 和 自研静态库c_depedency
target_link_libraries(c_main ${log-lib} c_depedency)