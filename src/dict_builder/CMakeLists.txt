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

add_executable(dict_builder_tests
	node_test.cpp
	dictionary_test.cpp
	suffix_automaton_test.cpp
)

target_link_libraries(dict_builder_tests
  gtest_main
  dictgen
)
target_include_directories (dictgen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME dict_builder_tests COMMAND dict_builder_tests)
