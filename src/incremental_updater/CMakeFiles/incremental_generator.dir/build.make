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
include src/incremental_updater/CMakeFiles/incremental_generator.dir/depend.make

# Include the progress variables for this target.
include src/incremental_updater/CMakeFiles/incremental_generator.dir/progress.make

# Include the compile flags for this target's objects.
include src/incremental_updater/CMakeFiles/incremental_generator.dir/flags.make

src/incremental_updater/CMakeFiles/incremental_generator.dir/incremental_generator.cpp.o: src/incremental_updater/CMakeFiles/incremental_generator.dir/flags.make
src/incremental_updater/CMakeFiles/incremental_generator.dir/incremental_generator.cpp.o: src/incremental_updater/incremental_generator.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gur/Projects/git/lastskipor/SInGe/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/incremental_updater/CMakeFiles/incremental_generator.dir/incremental_generator.cpp.o"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/incremental_updater && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/incremental_generator.dir/incremental_generator.cpp.o -c /home/gur/Projects/git/lastskipor/SInGe/src/incremental_updater/incremental_generator.cpp

src/incremental_updater/CMakeFiles/incremental_generator.dir/incremental_generator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/incremental_generator.dir/incremental_generator.cpp.i"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/incremental_updater && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gur/Projects/git/lastskipor/SInGe/src/incremental_updater/incremental_generator.cpp > CMakeFiles/incremental_generator.dir/incremental_generator.cpp.i

src/incremental_updater/CMakeFiles/incremental_generator.dir/incremental_generator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/incremental_generator.dir/incremental_generator.cpp.s"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/incremental_updater && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gur/Projects/git/lastskipor/SInGe/src/incremental_updater/incremental_generator.cpp -o CMakeFiles/incremental_generator.dir/incremental_generator.cpp.s

src/incremental_updater/CMakeFiles/incremental_generator.dir/incremental_generator.cpp.o.requires:
.PHONY : src/incremental_updater/CMakeFiles/incremental_generator.dir/incremental_generator.cpp.o.requires

src/incremental_updater/CMakeFiles/incremental_generator.dir/incremental_generator.cpp.o.provides: src/incremental_updater/CMakeFiles/incremental_generator.dir/incremental_generator.cpp.o.requires
	$(MAKE) -f src/incremental_updater/CMakeFiles/incremental_generator.dir/build.make src/incremental_updater/CMakeFiles/incremental_generator.dir/incremental_generator.cpp.o.provides.build
.PHONY : src/incremental_updater/CMakeFiles/incremental_generator.dir/incremental_generator.cpp.o.provides

src/incremental_updater/CMakeFiles/incremental_generator.dir/incremental_generator.cpp.o.provides.build: src/incremental_updater/CMakeFiles/incremental_generator.dir/incremental_generator.cpp.o

# Object files for target incremental_generator
incremental_generator_OBJECTS = \
"CMakeFiles/incremental_generator.dir/incremental_generator.cpp.o"

# External object files for target incremental_generator
incremental_generator_EXTERNAL_OBJECTS =

bin/incremental_generator: src/incremental_updater/CMakeFiles/incremental_generator.dir/incremental_generator.cpp.o
bin/incremental_generator: src/incremental_updater/CMakeFiles/incremental_generator.dir/build.make
bin/incremental_generator: lib/libvcdenc.a
bin/incremental_generator: lib/libvcddec.a
bin/incremental_generator: lib/libdictgen.a
bin/incremental_generator: lib/libgflags.a
bin/incremental_generator: lib/libvcdcom.a
bin/incremental_generator: /usr/local/lib/libprotobuf.so
bin/incremental_generator: src/incremental_updater/CMakeFiles/incremental_generator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/incremental_generator"
	cd /home/gur/Projects/git/lastskipor/SInGe/src/incremental_updater && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/incremental_generator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/incremental_updater/CMakeFiles/incremental_generator.dir/build: bin/incremental_generator
.PHONY : src/incremental_updater/CMakeFiles/incremental_generator.dir/build

src/incremental_updater/CMakeFiles/incremental_generator.dir/requires: src/incremental_updater/CMakeFiles/incremental_generator.dir/incremental_generator.cpp.o.requires
.PHONY : src/incremental_updater/CMakeFiles/incremental_generator.dir/requires

src/incremental_updater/CMakeFiles/incremental_generator.dir/clean:
	cd /home/gur/Projects/git/lastskipor/SInGe/src/incremental_updater && $(CMAKE_COMMAND) -P CMakeFiles/incremental_generator.dir/cmake_clean.cmake
.PHONY : src/incremental_updater/CMakeFiles/incremental_generator.dir/clean

src/incremental_updater/CMakeFiles/incremental_generator.dir/depend:
	cd /home/gur/Projects/git/lastskipor/SInGe && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gur/Projects/git/lastskipor/SInGe /home/gur/Projects/git/lastskipor/SInGe/src/incremental_updater /home/gur/Projects/git/lastskipor/SInGe /home/gur/Projects/git/lastskipor/SInGe/src/incremental_updater /home/gur/Projects/git/lastskipor/SInGe/src/incremental_updater/CMakeFiles/incremental_generator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/incremental_updater/CMakeFiles/incremental_generator.dir/depend

