# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jakebeaton/CLionProjects/OSFileServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jakebeaton/CLionProjects/OSFileServer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/OSFileServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OSFileServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OSFileServer.dir/flags.make

CMakeFiles/OSFileServer.dir/main.c.o: CMakeFiles/OSFileServer.dir/flags.make
CMakeFiles/OSFileServer.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jakebeaton/CLionProjects/OSFileServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/OSFileServer.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OSFileServer.dir/main.c.o   -c /Users/jakebeaton/CLionProjects/OSFileServer/main.c

CMakeFiles/OSFileServer.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OSFileServer.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/jakebeaton/CLionProjects/OSFileServer/main.c > CMakeFiles/OSFileServer.dir/main.c.i

CMakeFiles/OSFileServer.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OSFileServer.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/jakebeaton/CLionProjects/OSFileServer/main.c -o CMakeFiles/OSFileServer.dir/main.c.s

# Object files for target OSFileServer
OSFileServer_OBJECTS = \
"CMakeFiles/OSFileServer.dir/main.c.o"

# External object files for target OSFileServer
OSFileServer_EXTERNAL_OBJECTS =

OSFileServer: CMakeFiles/OSFileServer.dir/main.c.o
OSFileServer: CMakeFiles/OSFileServer.dir/build.make
OSFileServer: CMakeFiles/OSFileServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jakebeaton/CLionProjects/OSFileServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable OSFileServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OSFileServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OSFileServer.dir/build: OSFileServer

.PHONY : CMakeFiles/OSFileServer.dir/build

CMakeFiles/OSFileServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OSFileServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OSFileServer.dir/clean

CMakeFiles/OSFileServer.dir/depend:
	cd /Users/jakebeaton/CLionProjects/OSFileServer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jakebeaton/CLionProjects/OSFileServer /Users/jakebeaton/CLionProjects/OSFileServer /Users/jakebeaton/CLionProjects/OSFileServer/cmake-build-debug /Users/jakebeaton/CLionProjects/OSFileServer/cmake-build-debug /Users/jakebeaton/CLionProjects/OSFileServer/cmake-build-debug/CMakeFiles/OSFileServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OSFileServer.dir/depend

