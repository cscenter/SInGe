cmake_minimum_required(VERSION 2.8.4)
project(SInGe)
#set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

#Add BOOST
Set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
#add boost packages here, if you need them
find_package(Boost REQUIRED COMPONENTS filesystem iostreams)
include_directories(${Boost_INCLUDE_DIRS}) #should we use target_include_directories instread???


#DictGet
add_subdirectory (simple-SDCH-gen)




#open-vcdiff
add_subdirectory(src/third_party/open-vcdiff/)

set(VCDIFF_SOURCE_PATH src/third_party/open-vcdiff/src)



set(SOURCE_FILES
    src/third_party/open-vcdiff/src/google/format_extension_flags.h
    src/third_party/open-vcdiff/src/google/output_string.h
    src/third_party/open-vcdiff/src/google/vcdecoder.h
    src/third_party/open-vcdiff/src/google/vcencoder.h
    src/third_party/open-vcdiff/src/zlib/adler32.c
    src/third_party/open-vcdiff/src/zlib/zconf.h
    src/third_party/open-vcdiff/src/zlib/zlib.h
    src/third_party/open-vcdiff/src/addrcache.cc
    src/third_party/open-vcdiff/src/addrcache.h
    src/third_party/open-vcdiff/src/addrcache_test.cc
    src/third_party/open-vcdiff/src/blockhash.cc
    src/third_party/open-vcdiff/src/blockhash.h
    src/third_party/open-vcdiff/src/blockhash_test.cc
    src/third_party/open-vcdiff/src/checksum.h
    src/third_party/open-vcdiff/src/codetable.cc
    src/third_party/open-vcdiff/src/codetable.h
    src/third_party/open-vcdiff/src/codetable_test.cc
    src/third_party/open-vcdiff/src/codetablewriter_interface.h
    src/third_party/open-vcdiff/src/compile_assert.h
    src/third_party/open-vcdiff/src/config.h
    src/third_party/open-vcdiff/src/decodetable.cc
    src/third_party/open-vcdiff/src/decodetable.h
    src/third_party/open-vcdiff/src/decodetable_test.cc
    src/third_party/open-vcdiff/src/encodetable.cc
    src/third_party/open-vcdiff/src/encodetable.h
    src/third_party/open-vcdiff/src/encodetable_test.cc
    src/third_party/open-vcdiff/src/headerparser.cc
    src/third_party/open-vcdiff/src/headerparser.h
    src/third_party/open-vcdiff/src/headerparser_test.cc
    src/third_party/open-vcdiff/src/instruction_map.cc
    src/third_party/open-vcdiff/src/instruction_map.h
    src/third_party/open-vcdiff/src/instruction_map_test.cc
    src/third_party/open-vcdiff/src/jsonwriter.cc
    src/third_party/open-vcdiff/src/jsonwriter.h
    src/third_party/open-vcdiff/src/jsonwriter_test.cc
    src/third_party/open-vcdiff/src/logging.cc
    src/third_party/open-vcdiff/src/logging.h
    src/third_party/open-vcdiff/src/output_string_crope.h
    src/third_party/open-vcdiff/src/output_string_test.cc
    src/third_party/open-vcdiff/src/rolling_hash.h
    src/third_party/open-vcdiff/src/rolling_hash_test.cc
    src/third_party/open-vcdiff/src/testing.h
    src/third_party/open-vcdiff/src/unique_ptr.h
    src/third_party/open-vcdiff/src/varint_bigendian.cc
    src/third_party/open-vcdiff/src/varint_bigendian.h
    src/third_party/open-vcdiff/src/varint_bigendian_test.cc
    src/third_party/open-vcdiff/src/vcdecoder.cc
    src/third_party/open-vcdiff/src/vcdecoder_test.cc
    src/third_party/open-vcdiff/src/vcdecoder_test.h
    src/third_party/open-vcdiff/src/vcdiff_defs.h
    src/third_party/open-vcdiff/src/vcdiff_main.cc
    src/third_party/open-vcdiff/src/vcdiffengine.cc
    src/third_party/open-vcdiff/src/vcdiffengine.h
    src/third_party/open-vcdiff/src/vcdiffengine_test.cc
    src/third_party/open-vcdiff/src/vcencoder.cc
    src/third_party/open-vcdiff/src/vcencoder_test.cc
    src/third_party/open-vcdiff/vsprojects/config.h
    src/third_party/open-vcdiff/vsprojects/stdint.h
    src/third_party/open-vcdiff/src/statistics_codetablewriter.h
    src/third_party/open-vcdiff/src/statistics_codetablewriter.cc
    src/third_party/open-vcdiff/src/statistics.h
    src/third_party/open-vcdiff/src/statistics.cc
    src/third_party/open-vcdiff/src/vcdecoder_test.cc
    )

add_executable(SInGe ${SOURCE_FILES})