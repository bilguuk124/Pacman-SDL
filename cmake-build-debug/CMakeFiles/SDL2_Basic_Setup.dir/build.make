# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/bilguuk124/Documents/Pacman-SDL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/bilguuk124/Documents/Pacman-SDL/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SDL2_Basic_Setup.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/SDL2_Basic_Setup.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SDL2_Basic_Setup.dir/flags.make

CMakeFiles/SDL2_Basic_Setup.dir/src/main.c.o: CMakeFiles/SDL2_Basic_Setup.dir/flags.make
CMakeFiles/SDL2_Basic_Setup.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bilguuk124/Documents/Pacman-SDL/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/SDL2_Basic_Setup.dir/src/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/SDL2_Basic_Setup.dir/src/main.c.o -c /Users/bilguuk124/Documents/Pacman-SDL/src/main.c

CMakeFiles/SDL2_Basic_Setup.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SDL2_Basic_Setup.dir/src/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/bilguuk124/Documents/Pacman-SDL/src/main.c > CMakeFiles/SDL2_Basic_Setup.dir/src/main.c.i

CMakeFiles/SDL2_Basic_Setup.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SDL2_Basic_Setup.dir/src/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/bilguuk124/Documents/Pacman-SDL/src/main.c -o CMakeFiles/SDL2_Basic_Setup.dir/src/main.c.s

# Object files for target SDL2_Basic_Setup
SDL2_Basic_Setup_OBJECTS = \
"CMakeFiles/SDL2_Basic_Setup.dir/src/main.c.o"

# External object files for target SDL2_Basic_Setup
SDL2_Basic_Setup_EXTERNAL_OBJECTS =

bin/SDL2_Basic_Setup: CMakeFiles/SDL2_Basic_Setup.dir/src/main.c.o
bin/SDL2_Basic_Setup: CMakeFiles/SDL2_Basic_Setup.dir/build.make
bin/SDL2_Basic_Setup: /opt/homebrew/lib/libSDL2_ttf.dylib
bin/SDL2_Basic_Setup: /opt/homebrew/lib/libSDL2_ttf.dylib
bin/SDL2_Basic_Setup: /opt/homebrew/lib/libSDL2_image.dylib
bin/SDL2_Basic_Setup: /opt/homebrew/lib/libSDL2_mixer.dylib
bin/SDL2_Basic_Setup: CMakeFiles/SDL2_Basic_Setup.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/bilguuk124/Documents/Pacman-SDL/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/SDL2_Basic_Setup"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SDL2_Basic_Setup.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SDL2_Basic_Setup.dir/build: bin/SDL2_Basic_Setup
.PHONY : CMakeFiles/SDL2_Basic_Setup.dir/build

CMakeFiles/SDL2_Basic_Setup.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SDL2_Basic_Setup.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SDL2_Basic_Setup.dir/clean

CMakeFiles/SDL2_Basic_Setup.dir/depend:
	cd /Users/bilguuk124/Documents/Pacman-SDL/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/bilguuk124/Documents/Pacman-SDL /Users/bilguuk124/Documents/Pacman-SDL /Users/bilguuk124/Documents/Pacman-SDL/cmake-build-debug /Users/bilguuk124/Documents/Pacman-SDL/cmake-build-debug /Users/bilguuk124/Documents/Pacman-SDL/cmake-build-debug/CMakeFiles/SDL2_Basic_Setup.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SDL2_Basic_Setup.dir/depend
