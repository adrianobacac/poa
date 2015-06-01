cmake_minimum_required(VERSION 2.8)
project(conpoa)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ".")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -pthread")


file(GLOB SOURCE_FILES
    "src/*.h"
    "src/*.cpp"
)

set(MAIN src/poa_1.cpp)
add_executable(conpoa ${MAIN} ${SOURCE_FILES})