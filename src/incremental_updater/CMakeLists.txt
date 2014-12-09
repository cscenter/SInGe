add_executable(incremental_generator
  incremental_generator.cpp
)
target_link_libraries(incremental_generator LINK_PUBLIC
  vcdenc
  vcddec
  dictgen
  gflags
)