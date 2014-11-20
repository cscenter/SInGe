<<<<<<< HEAD
add_library( dictgen
=======
find_package(Protobuf REQUIRED)

set (PROTO_SOURCES
    proto/automaton.proto
)

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${PROTO_SOURCES})

add_library(dictgen
>>>>>>> upstream/master
	dictionary.cpp
	dictionary.hpp
	node.cpp
	node.hpp
	suffix_automaton.cpp
	suffix_automaton.hpp
<<<<<<< HEAD
=======
	${PROTO_SRCS}
	${PROTO_HDRS}
)

target_link_libraries(dictgen
 ${PROTOBUF_LIBRARIES}
)
target_include_directories (dictgen PUBLIC
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${PROTOBUF_INCLUDE_DIRS}
 ${CMAKE_CURRENT_BINARY_DIR}
>>>>>>> upstream/master
)

add_executable(pzip
	main.cpp
)
target_link_libraries(pzip dictgen)

add_executable(dict_builder_tests
	node_test.cpp
	dictionary_test.cpp
	suffix_automaton_test.cpp
<<<<<<< HEAD
=======
	serialization_tests.cpp
>>>>>>> upstream/master
)

target_link_libraries(dict_builder_tests
  gtest_main
  dictgen
)
target_include_directories (dictgen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME dict_builder_tests COMMAND dict_builder_tests)
