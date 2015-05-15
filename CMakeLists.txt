cmake_minimum_required(VERSION 3.0)
project(poa)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")


file(GLOB SOURCE_FILES
    "src/*.h"
    "src/*.cpp"
)

set(MAIN src/poa_1.cpp)
add_executable(poa ${MAIN} ${SOURCE_FILES})