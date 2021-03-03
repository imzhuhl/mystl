cmake_minimum_required(VERSION 3.16)
project(mystl)

set(CMAKE_CXX_STANDARD 17)

add_executable(sstltest SSTL/test.cpp)
add_executable(exp0 explore/exp0.cpp)
add_executable(exp1 explore/exp1.cpp)
add_executable(exp2 explore/exp2.cpp)
