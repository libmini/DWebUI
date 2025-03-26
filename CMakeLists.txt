cmake_minimum_required(VERSION 3.10)
project(DWebUI CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置3rdparty路径
set(THIRDPARTY_DIR ${CMAKE_SOURCE_DIR}/3rdparty)
set(THIRDPARTY_INCLUDE_DIR ${THIRDPARTY_DIR}/include)
set(THIRDPARTY_LIB_DIR ${THIRDPARTY_DIR}/lib)

# 添加头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${THIRDPARTY_INCLUDE_DIR}/)

# 查找依赖库
find_library(WEBUI_LIBRARY NAMES libwebui-2-secure-static PATHS ${THIRDPARTY_LIB_DIR} NO_DEFAULT_PATH)

if(NOT WEBUI_LIBRARY)
    message(FATAL_ERROR "Required libraries (webui) not found in 3rdparty/lib")
endif()

# 添加源文件
set(SOURCES
    src/main.cpp
)

# 创建示例可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out
)