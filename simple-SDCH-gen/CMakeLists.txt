add_library( dictgen
  dictionary.cpp
  dictionary.hpp
  node.cpp
  node.hpp
  substring.cpp
  substring.hpp
  suffix_automaton.cpp
  suffix_automaton.hpp
  )

# Make sure the compiler can find include files for our dictgen library
# when other libraries or executables link to dictgen
target_include_directories (dictgen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(pzip
  main.cpp
)
target_link_libraries(pzip dictgen)




