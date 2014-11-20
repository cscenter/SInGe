add_executable(incremental_tester
  tester.cpp
  incremental_tester.cpp
)
target_link_libraries(incremental_tester LINK_PUBLIC
  vcdenc
  vcddec
  dictgen
)
