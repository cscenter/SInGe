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
include src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/depend.make

# Include the progress variables for this target.
include src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/progress.make

# Include the compile flags for this target's objects.
include src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/flags.make

src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.o: src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/flags.make
src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.o: src/third_party/open-vcdiff/src/vcdiff_main.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gur/Projects/git/lastskipor/SInGe/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.o"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.o -c /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/src/vcdiff_main.cc

src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.i"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/src/vcdiff_main.cc > CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.i

src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.s"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/src/vcdiff_main.cc -o CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.s

src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.o.requires:
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.o.requires

src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.o.provides: src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.o.requires
	$(MAKE) -f src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/build.make src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.o.provides.build
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.o.provides

src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.o.provides.build: src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.o

# Object files for target vcdiff
vcdiff_OBJECTS = \
"CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.o"

# External object files for target vcdiff
vcdiff_EXTERNAL_OBJECTS =

bin/vcdiff: src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.o
bin/vcdiff: src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/build.make
bin/vcdiff: lib/libvcdenc.a
bin/vcdiff: lib/libvcddec.a
bin/vcdiff: lib/libgflags.a
bin/vcdiff: lib/libvcdcom.a
bin/vcdiff: src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/vcdiff"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vcdiff.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/build: bin/vcdiff
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/build

src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/requires: src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/src/vcdiff_main.cc.o.requires
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/requires

src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/clean:
	cd /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff && $(CMAKE_COMMAND) -P CMakeFiles/vcdiff.dir/cmake_clean.cmake
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/clean

src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/depend:
	cd /home/gur/Projects/git/lastskipor/SInGe && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gur/Projects/git/lastskipor/SInGe /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff /home/gur/Projects/git/lastskipor/SInGe /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff /home/gur/Projects/git/lastskipor/SInGe/src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/third_party/open-vcdiff/CMakeFiles/vcdiff.dir/depend

