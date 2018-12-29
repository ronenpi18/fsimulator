cmake_minimum_required(VERSION 3.13)
project(prog1Project)

set(CMAKE_CXX_STANDARD 14)

set (SOURCE_FILES Bigger.h Equals.h NotEquals.h Smaller.h)
add_executable(prog1Project ${SOURCE_FILES})