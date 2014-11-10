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
	dictionary_test.cpp
	suffix_automaton_test.cpp
)

target_link_libraries(run_tests
  gtest_main
  dictgen
)

add_test(NAME dict_build_tests COMMAND run_tests)
