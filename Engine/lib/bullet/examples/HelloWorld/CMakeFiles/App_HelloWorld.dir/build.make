# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ragora/Documents/Projects/Torque3D

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ragora/Documents/Projects/Torque3D

# Include any dependencies generated for this target.
include Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/compiler_depend.make

# Include the progress variables for this target.
include Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/progress.make

# Include the compile flags for this target's objects.
include Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/flags.make

Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/HelloWorld.o: Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/flags.make
Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/HelloWorld.o: Engine/lib/bullet/examples/HelloWorld/HelloWorld.cpp
Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/HelloWorld.o: Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ragora/Documents/Projects/Torque3D/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/HelloWorld.o"
	cd /Users/ragora/Documents/Projects/Torque3D/Engine/lib/bullet/examples/HelloWorld && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/HelloWorld.o -MF CMakeFiles/App_HelloWorld.dir/HelloWorld.o.d -o CMakeFiles/App_HelloWorld.dir/HelloWorld.o -c /Users/ragora/Documents/Projects/Torque3D/Engine/lib/bullet/examples/HelloWorld/HelloWorld.cpp

Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/HelloWorld.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/App_HelloWorld.dir/HelloWorld.i"
	cd /Users/ragora/Documents/Projects/Torque3D/Engine/lib/bullet/examples/HelloWorld && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ragora/Documents/Projects/Torque3D/Engine/lib/bullet/examples/HelloWorld/HelloWorld.cpp > CMakeFiles/App_HelloWorld.dir/HelloWorld.i

Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/HelloWorld.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/App_HelloWorld.dir/HelloWorld.s"
	cd /Users/ragora/Documents/Projects/Torque3D/Engine/lib/bullet/examples/HelloWorld && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ragora/Documents/Projects/Torque3D/Engine/lib/bullet/examples/HelloWorld/HelloWorld.cpp -o CMakeFiles/App_HelloWorld.dir/HelloWorld.s

# Object files for target App_HelloWorld
App_HelloWorld_OBJECTS = \
"CMakeFiles/App_HelloWorld.dir/HelloWorld.o"

# External object files for target App_HelloWorld
App_HelloWorld_EXTERNAL_OBJECTS =

Engine/lib/bullet/examples/HelloWorld/App_HelloWorld: Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/HelloWorld.o
Engine/lib/bullet/examples/HelloWorld/App_HelloWorld: Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/build.make
Engine/lib/bullet/examples/HelloWorld/App_HelloWorld: Engine/lib/bullet/src/BulletDynamics/libBulletDynamics.2.85.dylib
Engine/lib/bullet/examples/HelloWorld/App_HelloWorld: Engine/lib/bullet/src/BulletCollision/libBulletCollision.2.85.dylib
Engine/lib/bullet/examples/HelloWorld/App_HelloWorld: Engine/lib/bullet/src/LinearMath/libLinearMath.2.85.dylib
Engine/lib/bullet/examples/HelloWorld/App_HelloWorld: Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ragora/Documents/Projects/Torque3D/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable App_HelloWorld"
	cd /Users/ragora/Documents/Projects/Torque3D/Engine/lib/bullet/examples/HelloWorld && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/App_HelloWorld.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/build: Engine/lib/bullet/examples/HelloWorld/App_HelloWorld
.PHONY : Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/build

Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/clean:
	cd /Users/ragora/Documents/Projects/Torque3D/Engine/lib/bullet/examples/HelloWorld && $(CMAKE_COMMAND) -P CMakeFiles/App_HelloWorld.dir/cmake_clean.cmake
.PHONY : Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/clean

Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/depend:
	cd /Users/ragora/Documents/Projects/Torque3D && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ragora/Documents/Projects/Torque3D /Users/ragora/Documents/Projects/Torque3D/Engine/lib/bullet/examples/HelloWorld /Users/ragora/Documents/Projects/Torque3D /Users/ragora/Documents/Projects/Torque3D/Engine/lib/bullet/examples/HelloWorld /Users/ragora/Documents/Projects/Torque3D/Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Engine/lib/bullet/examples/HelloWorld/CMakeFiles/App_HelloWorld.dir/depend
