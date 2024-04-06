cmake_minimum_required(VERSION 3.15) 
PROJECT ( SlidingWindow )

set(CMAKE_C_COMPILER "/usr/bin/gcc-13")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")

find_package(OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "-Wall -std=c++23 -O3")

include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB all_SRCS ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(  ${PROJECT_NAME} ${all_SRCS})
         
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )