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

add_executable(pzip
  main.cpp
)
target_link_libraries(pzip dictgen)




