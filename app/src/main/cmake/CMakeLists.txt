cmake_minimum_required(VERSION 3.22.1)

#设置project的名称，并将其存储在变量MAKE_PROJECT_NAME
project("capplication")

message("CMAKE_ANDROID_NDK = ${CMAKE_ANDROID_NDK}")
message("CMAKE_PROJECT_NAME = ${CMAKE_PROJECT_NAME}")
message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message("CMAKE_LIBRARY_OUTPUT_DIRECTORY = ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message("PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")

set(CMAKE_C_STANDARD 11) # c11
set(CMAKE_CXX_STANDARD 11) # cpp 11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2") # cpp flag

add_definitions(-DANDROID) # 类似#define ANDROID

message("CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}")
if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_definitions(-DNDEBUG) # 代码中#define NDEBUG
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_definitions(-DDEBUG) # 代码中#define DEBUG
endif ()

set(CMAKE_POSITION_INDEPENDENT_CODE ON) # 生成与位置无关的代码



#set(NATIVE_CODE_ROOT_PATH "${PROJECT_SOURCE_DIR}/../cpp")
#get_filename_component(NATIVE_CODE_ROOT_PATH ${NATIVE_CODE_ROOT_PATH} ABSOLUTE) # get_filename_component+ABSOLUTE 获取文件的绝对路径
#message("NATIVE_CODE_ROOT_PATH = ${NATIVE_CODE_ROOT_PATH}")
#
##===================依赖kyrenia====================#
##prefab库依赖方法：https://note.temu.team/doc/587527144526364672?root=587526906256117760
#find_package(kyrenia REQUIRED CONFIG)
##===================依赖kyrenia====================#


##===================依赖Audio_Engine====================#
#set(AUDIO_ENGINE_LIB_DIR ${NATIVE_CODE_ROOT_PATH}/tronmedia/audio_engine/libs/${ANDROID_ABI})
#set(AUDIO_ENGINE_INCLUDE_DIR ${NATIVE_CODE_ROOT_PATH}/tronmedia/audio_engine/include)
#message("AUDIO_ENGINE_LIB_DIR:${AUDIO_ENGINE_LIB_DIR}")
#
#add_library(audio_engine SHARED IMPORTED) # 引入依赖库audio_engine(此种方式需要将so库拷贝进仓库，可替换为prefab)
#set_target_properties(audio_engine PROPERTIES IMPORTED_LOCATION ${AUDIO_ENGINE_LIB_DIR}/libaudio_engine.so) # 设置audio_engine so位置
#set_target_properties(audio_engine PROPERTIES LINKER_LANGUAGE CXX)# 指定依赖库编译语言
##===================依赖Audio_Engine====================#


##=================== 依赖 libyuv + ======================#
#set(YUV_LIB_DIR ${NATIVE_CODE_ROOT_PATH}/tronmedia/libyuv/libs/${ANDROID_ABI})
#set(YUV_INCLUDE_DIR ${NATIVE_CODE_ROOT_PATH}/tronmedia/libyuv/include)
#message(STATUS "YUV_LIB_DIR:${YUV_LIB_DIR}")
#
#add_library(yuv SHARED IMPORTED)
#set_target_properties(yuv PROPERTIES IMPORTED_LOCATION ${YUV_LIB_DIR}/libyuv.so)
#set_target_properties(yuv PROPERTIES LINKER_LANGUAGE CXX)
##=================== 依赖 libyuv - ======================#


#add_subdirectory(${NATIVE_CODE_ROOT_PATH}/tronmedia tronmedia) # 设置子CMakeList文件路径


#、指定头文件的路径，方便编译时能找到头文件
include_directories(../cpp/)

# find_library查找ndk library并重命名
find_library(log-lib log)

# add_library 将c文件编译成静态库、动态库
# 可以定义多个库
# 路径为CMakeList文件的相对路径
add_library(capplication SHARED ../cpp/native-lib.cpp)
# 声明库之间的依赖关系，这里capplication依赖log-lib
target_link_libraries(capplication ${log-lib})


# -Oz可减小包体积，但部分函数可能被删除，使用 __attribute__ ((__used__))标识函数使其包含在目标文件中；