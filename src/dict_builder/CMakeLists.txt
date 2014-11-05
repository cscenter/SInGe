cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -std=c++11")

add_library( dictgen
	dictionary.cpp
	dictionary.hpp
	node.cpp
	node.hpp
	suffix_automaton.cpp
	suffix_automaton.hpp
	)

add_executable(pzip
	main.cpp
)

target_link_libraries(pzip dictgen)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(run_tests
	all_tests.cpp
	node_test.cpp
	node.cpp
	dictionary_test.cpp
	dictionary.cpp
	suffix_automaton_test.cpp
	suffix_automaton.cpp
	)

target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread)
