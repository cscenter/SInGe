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
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(FILES
    dictionary_c.h
    DESTINATION include
)


