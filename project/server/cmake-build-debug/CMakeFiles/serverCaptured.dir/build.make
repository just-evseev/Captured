# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ilya/Desktop/Captured/project/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ilya/Desktop/Captured/project/server/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/serverCaptured.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/serverCaptured.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/serverCaptured.dir/flags.make

CMakeFiles/serverCaptured.dir/src/main.cpp.o: CMakeFiles/serverCaptured.dir/flags.make
CMakeFiles/serverCaptured.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ilya/Desktop/Captured/project/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/serverCaptured.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/serverCaptured.dir/src/main.cpp.o -c /Users/ilya/Desktop/Captured/project/server/src/main.cpp

CMakeFiles/serverCaptured.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serverCaptured.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ilya/Desktop/Captured/project/server/src/main.cpp > CMakeFiles/serverCaptured.dir/src/main.cpp.i

CMakeFiles/serverCaptured.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serverCaptured.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ilya/Desktop/Captured/project/server/src/main.cpp -o CMakeFiles/serverCaptured.dir/src/main.cpp.s

CMakeFiles/serverCaptured.dir/src/MapRender.cpp.o: CMakeFiles/serverCaptured.dir/flags.make
CMakeFiles/serverCaptured.dir/src/MapRender.cpp.o: ../src/MapRender.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ilya/Desktop/Captured/project/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/serverCaptured.dir/src/MapRender.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/serverCaptured.dir/src/MapRender.cpp.o -c /Users/ilya/Desktop/Captured/project/server/src/MapRender.cpp

CMakeFiles/serverCaptured.dir/src/MapRender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serverCaptured.dir/src/MapRender.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ilya/Desktop/Captured/project/server/src/MapRender.cpp > CMakeFiles/serverCaptured.dir/src/MapRender.cpp.i

CMakeFiles/serverCaptured.dir/src/MapRender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serverCaptured.dir/src/MapRender.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ilya/Desktop/Captured/project/server/src/MapRender.cpp -o CMakeFiles/serverCaptured.dir/src/MapRender.cpp.s

# Object files for target serverCaptured
serverCaptured_OBJECTS = \
"CMakeFiles/serverCaptured.dir/src/main.cpp.o" \
"CMakeFiles/serverCaptured.dir/src/MapRender.cpp.o"

# External object files for target serverCaptured
serverCaptured_EXTERNAL_OBJECTS =

serverCaptured: CMakeFiles/serverCaptured.dir/src/main.cpp.o
serverCaptured: CMakeFiles/serverCaptured.dir/src/MapRender.cpp.o
serverCaptured: CMakeFiles/serverCaptured.dir/build.make
serverCaptured: CMakeFiles/serverCaptured.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ilya/Desktop/Captured/project/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable serverCaptured"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serverCaptured.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/serverCaptured.dir/build: serverCaptured

.PHONY : CMakeFiles/serverCaptured.dir/build

CMakeFiles/serverCaptured.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/serverCaptured.dir/cmake_clean.cmake
.PHONY : CMakeFiles/serverCaptured.dir/clean

CMakeFiles/serverCaptured.dir/depend:
	cd /Users/ilya/Desktop/Captured/project/server/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ilya/Desktop/Captured/project/server /Users/ilya/Desktop/Captured/project/server /Users/ilya/Desktop/Captured/project/server/cmake-build-debug /Users/ilya/Desktop/Captured/project/server/cmake-build-debug /Users/ilya/Desktop/Captured/project/server/cmake-build-debug/CMakeFiles/serverCaptured.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/serverCaptured.dir/depend

