add_library(vcdcom
  src/google/format_extension_flags.h
  src/google/output_string.h
  src/addrcache.h
  src/checksum.h
  src/codetable.h
  src/logging.h
  src/unique_ptr.h
  src/varint_bigendian.h
  src/vcdiff_defs.h
  src/zlib/zlib.h
  src/zlib/zconf.h
  src/zlib/adler32.c
  src/addrcache.cc
  src/codetable.cc
  src/logging.cc
  src/varint_bigendian.cc
)

add_library(vcddec
  src/google/vcdecoder.h
  src/decodetable.h
  src/headerparser.h
  src/decodetable.cc
  src/headerparser.cc
  src/vcdecoder.cc
)

target_link_libraries(vcddec
  vcdcom
)

add_library(vcdenc
  src/google/vcencoder.h
  src/blockhash.h
  src/codetablewriter_interface.h
  src/compile_assert.h
  src/encodetable.h
  src/instruction_map.h
  src/jsonwriter.h
  src/rolling_hash.h
  src/vcdiffengine.h
  src/blockhash.cc
  src/encodetable.cc
  src/instruction_map.cc
  src/jsonwriter.cc
  src/vcdiffengine.cc
  src/statistics_codetablewriter.h
  src/statistics_codetablewriter.cc
  src/statistics.h
  src/statistics.cc
  src/vcencoder.cc
)

target_link_libraries(vcdenc
  vcdcom
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/
  ${CMAKE_CURRENT_SOURCE_DIR}/src/zlib
  ${CMAKE_CURRENT_SOURCE_DIR}/gflags/src
)
set(VCDIFF_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories (vcdcom PUBLIC ${VCDIFF_INCLUDE_DIR})
target_include_directories (vcddec PUBLIC ${VCDIFF_INCLUDE_DIR})
target_include_directories (vcdenc PUBLIC ${VCDIFF_INCLUDE_DIR})



add_library(gflags
  gflags/src/gflags/gflags.h
  gflags/src/gflags/gflags_completions.h
  gflags/src/mutex.h
  gflags/src/gflags.cc
  gflags/src/gflags_completions.cc
  gflags/src/gflags_reporting.cc
)
add_executable(vcdiff
  src/vcdiff_main.cc
)
target_link_libraries(vcdiff
  vcdenc
  vcddec
  gflags
)

