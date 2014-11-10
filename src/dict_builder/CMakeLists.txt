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

add_executable(run_tests
	node_test.cpp
)

target_link_libraries(run_tests
  gtest_main
  dictgen
)
