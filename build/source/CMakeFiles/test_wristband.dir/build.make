# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/chenhaiwei/miniconda3/envs/py3.9/lib/python3.9/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/chenhaiwei/miniconda3/envs/py3.9/lib/python3.9/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chenhaiwei/code/Data-Collection

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chenhaiwei/code/Data-Collection/build

# Include any dependencies generated for this target.
include source/CMakeFiles/test_wristband.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include source/CMakeFiles/test_wristband.dir/compiler_depend.make

# Include the progress variables for this target.
include source/CMakeFiles/test_wristband.dir/progress.make

# Include the compile flags for this target's objects.
include source/CMakeFiles/test_wristband.dir/flags.make

source/CMakeFiles/test_wristband.dir/testCase/testWristband.cpp.o: source/CMakeFiles/test_wristband.dir/flags.make
source/CMakeFiles/test_wristband.dir/testCase/testWristband.cpp.o: /home/chenhaiwei/code/Data-Collection/source/testCase/testWristband.cpp
source/CMakeFiles/test_wristband.dir/testCase/testWristband.cpp.o: source/CMakeFiles/test_wristband.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chenhaiwei/code/Data-Collection/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object source/CMakeFiles/test_wristband.dir/testCase/testWristband.cpp.o"
	cd /home/chenhaiwei/code/Data-Collection/build/source && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT source/CMakeFiles/test_wristband.dir/testCase/testWristband.cpp.o -MF CMakeFiles/test_wristband.dir/testCase/testWristband.cpp.o.d -o CMakeFiles/test_wristband.dir/testCase/testWristband.cpp.o -c /home/chenhaiwei/code/Data-Collection/source/testCase/testWristband.cpp

source/CMakeFiles/test_wristband.dir/testCase/testWristband.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_wristband.dir/testCase/testWristband.cpp.i"
	cd /home/chenhaiwei/code/Data-Collection/build/source && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chenhaiwei/code/Data-Collection/source/testCase/testWristband.cpp > CMakeFiles/test_wristband.dir/testCase/testWristband.cpp.i

source/CMakeFiles/test_wristband.dir/testCase/testWristband.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_wristband.dir/testCase/testWristband.cpp.s"
	cd /home/chenhaiwei/code/Data-Collection/build/source && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chenhaiwei/code/Data-Collection/source/testCase/testWristband.cpp -o CMakeFiles/test_wristband.dir/testCase/testWristband.cpp.s

# Object files for target test_wristband
test_wristband_OBJECTS = \
"CMakeFiles/test_wristband.dir/testCase/testWristband.cpp.o"

# External object files for target test_wristband
test_wristband_EXTERNAL_OBJECTS =

source/test_wristband: source/CMakeFiles/test_wristband.dir/testCase/testWristband.cpp.o
source/test_wristband: source/CMakeFiles/test_wristband.dir/build.make
source/test_wristband: source/libsensors.a
source/test_wristband: source/CMakeFiles/test_wristband.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chenhaiwei/code/Data-Collection/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_wristband"
	cd /home/chenhaiwei/code/Data-Collection/build/source && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_wristband.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/CMakeFiles/test_wristband.dir/build: source/test_wristband
.PHONY : source/CMakeFiles/test_wristband.dir/build

source/CMakeFiles/test_wristband.dir/clean:
	cd /home/chenhaiwei/code/Data-Collection/build/source && $(CMAKE_COMMAND) -P CMakeFiles/test_wristband.dir/cmake_clean.cmake
.PHONY : source/CMakeFiles/test_wristband.dir/clean

source/CMakeFiles/test_wristband.dir/depend:
	cd /home/chenhaiwei/code/Data-Collection/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chenhaiwei/code/Data-Collection /home/chenhaiwei/code/Data-Collection/source /home/chenhaiwei/code/Data-Collection/build /home/chenhaiwei/code/Data-Collection/build/source /home/chenhaiwei/code/Data-Collection/build/source/CMakeFiles/test_wristband.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/CMakeFiles/test_wristband.dir/depend

