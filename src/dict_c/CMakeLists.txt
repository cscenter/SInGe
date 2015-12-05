add_library(dictgen_c SHARED
    dictionary_c.h
    dictionary_c.cpp
)

target_link_libraries(dictgen_c
    dictgen
)
target_include_directories (dictgen_c PUBLIC
     ${CMAKE_CURRENT_SOURCE_DIR}
)

INSTALL( TARGETS dictgen_c
    DESTINATION lib
)

install(FILES
    dictionary_c.h
    DESTINATION include
)
add_executable(dict_c_tests
        dictionary_c_test.cpp
)

target_link_libraries(dict_c_tests
    gtest_main
    dictgen_c
)

add_test(NAME dict_c_tests COMMAND dict_c_tests)


