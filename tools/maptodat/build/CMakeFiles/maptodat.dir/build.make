# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/linus/ws/justdontdie/tools/maptodat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/linus/ws/justdontdie/tools/maptodat/build

# Include any dependencies generated for this target.
include CMakeFiles/maptodat.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/maptodat.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/maptodat.dir/flags.make

CMakeFiles/maptodat.dir/src/maptodat.cpp.o: CMakeFiles/maptodat.dir/flags.make
CMakeFiles/maptodat.dir/src/maptodat.cpp.o: ../src/maptodat.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linus/ws/justdontdie/tools/maptodat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/maptodat.dir/src/maptodat.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/maptodat.dir/src/maptodat.cpp.o -c /home/linus/ws/justdontdie/tools/maptodat/src/maptodat.cpp

CMakeFiles/maptodat.dir/src/maptodat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maptodat.dir/src/maptodat.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linus/ws/justdontdie/tools/maptodat/src/maptodat.cpp > CMakeFiles/maptodat.dir/src/maptodat.cpp.i

CMakeFiles/maptodat.dir/src/maptodat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maptodat.dir/src/maptodat.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linus/ws/justdontdie/tools/maptodat/src/maptodat.cpp -o CMakeFiles/maptodat.dir/src/maptodat.cpp.s

CMakeFiles/maptodat.dir/src/maptodat.cpp.o.requires:

.PHONY : CMakeFiles/maptodat.dir/src/maptodat.cpp.o.requires

CMakeFiles/maptodat.dir/src/maptodat.cpp.o.provides: CMakeFiles/maptodat.dir/src/maptodat.cpp.o.requires
	$(MAKE) -f CMakeFiles/maptodat.dir/build.make CMakeFiles/maptodat.dir/src/maptodat.cpp.o.provides.build
.PHONY : CMakeFiles/maptodat.dir/src/maptodat.cpp.o.provides

CMakeFiles/maptodat.dir/src/maptodat.cpp.o.provides.build: CMakeFiles/maptodat.dir/src/maptodat.cpp.o


# Object files for target maptodat
maptodat_OBJECTS = \
"CMakeFiles/maptodat.dir/src/maptodat.cpp.o"

# External object files for target maptodat
maptodat_EXTERNAL_OBJECTS =

maptodat: CMakeFiles/maptodat.dir/src/maptodat.cpp.o
maptodat: CMakeFiles/maptodat.dir/build.make
maptodat: CMakeFiles/maptodat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/linus/ws/justdontdie/tools/maptodat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable maptodat"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/maptodat.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/maptodat.dir/build: maptodat

.PHONY : CMakeFiles/maptodat.dir/build

CMakeFiles/maptodat.dir/requires: CMakeFiles/maptodat.dir/src/maptodat.cpp.o.requires

.PHONY : CMakeFiles/maptodat.dir/requires

CMakeFiles/maptodat.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/maptodat.dir/cmake_clean.cmake
.PHONY : CMakeFiles/maptodat.dir/clean

CMakeFiles/maptodat.dir/depend:
	cd /home/linus/ws/justdontdie/tools/maptodat/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/linus/ws/justdontdie/tools/maptodat /home/linus/ws/justdontdie/tools/maptodat /home/linus/ws/justdontdie/tools/maptodat/build /home/linus/ws/justdontdie/tools/maptodat/build /home/linus/ws/justdontdie/tools/maptodat/build/CMakeFiles/maptodat.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/maptodat.dir/depend

