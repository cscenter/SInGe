# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gur/Projects/git/lastskipor/SInGe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gur/Projects/git/lastskipor/SInGe

# Include any dependencies generated for this target.
include src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/depend.make

# Include the progress variables for this target.
include src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/progress.make

# Include the compile flags for this target's objects.
include src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/flags.make

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/zlib/adler32.c.o: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/flags.make
src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/zlib/adler32.c.o: src/third_party/open-vcdiff/src/zlib/adler32.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gur/Projects/git/lastskipor/SInGe/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/zlib/adler32.c.o"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/vcdcom.dir/src/zlib/adler32.c.o   -c /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/src/zlib/adler32.c

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/zlib/adler32.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/vcdcom.dir/src/zlib/adler32.c.i"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/src/zlib/adler32.c > CMakeFiles/vcdcom.dir/src/zlib/adler32.c.i

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/zlib/adler32.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/vcdcom.dir/src/zlib/adler32.c.s"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/src/zlib/adler32.c -o CMakeFiles/vcdcom.dir/src/zlib/adler32.c.s

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/zlib/adler32.c.o.requires:
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/zlib/adler32.c.o.requires

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/zlib/adler32.c.o.provides: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/zlib/adler32.c.o.requires
	$(MAKE) -f src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/build.make src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/zlib/adler32.c.o.provides.build
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/zlib/adler32.c.o.provides

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/zlib/adler32.c.o.provides.build: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/zlib/adler32.c.o

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/addrcache.cc.o: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/flags.make
src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/addrcache.cc.o: src/third_party/open-vcdiff/src/addrcache.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gur/Projects/git/lastskipor/SInGe/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/addrcache.cc.o"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/vcdcom.dir/src/addrcache.cc.o -c /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/src/addrcache.cc

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/addrcache.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vcdcom.dir/src/addrcache.cc.i"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/src/addrcache.cc > CMakeFiles/vcdcom.dir/src/addrcache.cc.i

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/addrcache.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vcdcom.dir/src/addrcache.cc.s"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/src/addrcache.cc -o CMakeFiles/vcdcom.dir/src/addrcache.cc.s

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/addrcache.cc.o.requires:
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/addrcache.cc.o.requires

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/addrcache.cc.o.provides: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/addrcache.cc.o.requires
	$(MAKE) -f src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/build.make src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/addrcache.cc.o.provides.build
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/addrcache.cc.o.provides

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/addrcache.cc.o.provides.build: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/addrcache.cc.o

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/codetable.cc.o: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/flags.make
src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/codetable.cc.o: src/third_party/open-vcdiff/src/codetable.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gur/Projects/git/lastskipor/SInGe/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/codetable.cc.o"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/vcdcom.dir/src/codetable.cc.o -c /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/src/codetable.cc

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/codetable.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vcdcom.dir/src/codetable.cc.i"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/src/codetable.cc > CMakeFiles/vcdcom.dir/src/codetable.cc.i

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/codetable.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vcdcom.dir/src/codetable.cc.s"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/src/codetable.cc -o CMakeFiles/vcdcom.dir/src/codetable.cc.s

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/codetable.cc.o.requires:
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/codetable.cc.o.requires

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/codetable.cc.o.provides: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/codetable.cc.o.requires
	$(MAKE) -f src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/build.make src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/codetable.cc.o.provides.build
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/codetable.cc.o.provides

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/codetable.cc.o.provides.build: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/codetable.cc.o

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/logging.cc.o: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/flags.make
src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/logging.cc.o: src/third_party/open-vcdiff/src/logging.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gur/Projects/git/lastskipor/SInGe/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/logging.cc.o"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/vcdcom.dir/src/logging.cc.o -c /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/src/logging.cc

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/logging.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vcdcom.dir/src/logging.cc.i"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/src/logging.cc > CMakeFiles/vcdcom.dir/src/logging.cc.i

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/logging.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vcdcom.dir/src/logging.cc.s"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/src/logging.cc -o CMakeFiles/vcdcom.dir/src/logging.cc.s

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/logging.cc.o.requires:
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/logging.cc.o.requires

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/logging.cc.o.provides: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/logging.cc.o.requires
	$(MAKE) -f src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/build.make src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/logging.cc.o.provides.build
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/logging.cc.o.provides

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/logging.cc.o.provides.build: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/logging.cc.o

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.o: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/flags.make
src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.o: src/third_party/open-vcdiff/src/varint_bigendian.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gur/Projects/git/lastskipor/SInGe/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.o"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.o -c /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/src/varint_bigendian.cc

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.i"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/src/varint_bigendian.cc > CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.i

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.s"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/src/varint_bigendian.cc -o CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.s

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.o.requires:
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.o.requires

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.o.provides: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.o.requires
	$(MAKE) -f src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/build.make src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.o.provides.build
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.o.provides

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.o.provides.build: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.o

# Object files for target vcdcom
vcdcom_OBJECTS = \
"CMakeFiles/vcdcom.dir/src/zlib/adler32.c.o" \
"CMakeFiles/vcdcom.dir/src/addrcache.cc.o" \
"CMakeFiles/vcdcom.dir/src/codetable.cc.o" \
"CMakeFiles/vcdcom.dir/src/logging.cc.o" \
"CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.o"

# External object files for target vcdcom
vcdcom_EXTERNAL_OBJECTS =

lib/libvcdcom.a: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/zlib/adler32.c.o
lib/libvcdcom.a: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/addrcache.cc.o
lib/libvcdcom.a: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/codetable.cc.o
lib/libvcdcom.a: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/logging.cc.o
lib/libvcdcom.a: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.o
lib/libvcdcom.a: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/build.make
lib/libvcdcom.a: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../../lib/libvcdcom.a"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && $(CMAKE_COMMAND) -P CMakeFiles/vcdcom.dir/cmake_clean_target.cmake
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vcdcom.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/build: lib/libvcdcom.a
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/build

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/requires: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/zlib/adler32.c.o.requires
src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/requires: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/addrcache.cc.o.requires
src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/requires: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/codetable.cc.o.requires
src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/requires: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/logging.cc.o.requires
src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/requires: src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/src/varint_bigendian.cc.o.requires
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/requires

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/clean:
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && $(CMAKE_COMMAND) -P CMakeFiles/vcdcom.dir/cmake_clean.cmake
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/clean

src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/depend:
	cd /home/gur/Projects/git/lastskipor/SInGe && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gur/Projects/git/lastskipor/SInGe /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff /home/gur/Projects/git/lastskipor/SInGe /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdcom.dir/depend

