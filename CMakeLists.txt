cmake_minimum_required(VERSION 3.16)
project(mystl)

set(CMAKE_CXX_STANDARD 17)

add_executable(mystl main.cpp)
add_executable(sstltest SSTL/test.cpp)