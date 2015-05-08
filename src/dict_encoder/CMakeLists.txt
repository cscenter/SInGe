add_executable(encoder
  encoder.cpp
)
target_link_libraries(encoder LINK_PUBLIC
  vcdenc
  vcddec
  gflags
)