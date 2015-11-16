cmake_minimum_required(VERSION 3.3)
project(Assembler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp parameters.h)
add_executable(Assembler ${SOURCE_FILES})