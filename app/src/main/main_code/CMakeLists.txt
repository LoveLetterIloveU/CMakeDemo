cmake_minimum_required(VERSION 3.22.1)

project(c_main)

message("CMAKE_CURRENT_LIST_DIR = ${CMAKE_CURRENT_LIST_DIR}")

set(NATIVE_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/cpp/native-lib.cpp)
# set(BUILD_SOURCES ${BUILD_SOURCES} ${TRON_SDL_SOURCES}) # 合并多个源文件集合

# 更新git 版本号至库版本PLAYER_VERSION
execute_process(COMMAND sh version.sh . c_version.h WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

# add_library 将c文件编译成.a静态库、.so动态库
# 可以定义多个库
# 路径为CMakeList文件的相对路径
add_library(c_main SHARED ${NATIVE_SOURCES})
set(LIB_NAME c_main)


#  添加头文件至搜索路径 不建议使用
#include_directories(${CMAKE_CURRENT_LIST_DIR})

# INTERFACE：target对应的头文件使用
# PRIVATE：target对应的源文件使用
# PUBLIC：target对应的头文件、源文件都使用
target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/cpp/})
target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../depedency_code/cpp) # 添加依赖库文件至搜索路径（所有的依赖库都可加入）

# 减包体积
if (PKG_SIZE_OPT)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
    target_compile_options(c_main PUBLIC -Oz -flto -faddrsig -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions)
    target_link_options(c_main PUBLIC -Oz -flto -Wl,--icf=all -Wl,-mllvm,--enable-machine-outliner=always -Wl,--exclude-libs,ALL -Wl,--gc-sections)
endif ()


# 声明库之间的依赖关系，这里cmakedemo依赖log-lib 和 自研静态库c_depedency
target_link_libraries(c_main ${log-lib})
target_link_libraries(c_main c_depedency)
#target_link_libraries(c_main kyrenia::kyrenia) # 依赖prefab库