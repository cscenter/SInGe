cmake_minimum_required(VERSION 2.8.4)
project(SInGe)
#set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

#Add BOOST
Set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
#add boost packages here, if you need them
find_package(Boost REQUIRED COMPONENTS filesystem iostreams)
include_directories(${Boost_INCLUDE_DIRS}) #should we use target_include_directories instread???


#dictget
add_subdirectory (simple-SDCH-gen)
#open-vcdiff, incremental_generator
add_subdirectory(src/)









