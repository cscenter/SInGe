add_executable(two_dicts_tester
  tester.cpp
)
target_link_libraries(two_dicts_tester LINK_PUBLIC
  vcdenc
  vcddec
  dictgen
)
