cmake_minimum_required(VERSION 2.8.4)
project(SInGe)
#set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

#open-vcdiff, incremental_generator
add_subdirectory(src/)

