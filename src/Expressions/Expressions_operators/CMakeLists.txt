cmake_minimum_required(VERSION 3.13)
project(prog1Project)

set(CMAKE_CXX_STANDARD 14)

set (SOURCE_FILES Div.h Mul.h Minus.h Plus.h Pow.h)
add_executable(prog1Project ${SOURCE_FILES})