# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/enrico/Documenti/Programmazione/OpenGlC++/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/enrico/Documenti/Programmazione/OpenGlC++/build

# Include any dependencies generated for this target.
include 18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include 18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/compiler_depend.make

# Include the progress variables for this target.
include 18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/progress.make

# Include the compile flags for this target's objects.
include 18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/flags.make

18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/main.cpp.o: 18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/flags.make
18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/main.cpp.o: /home/enrico/Documenti/Programmazione/OpenGlC++/src/18_RotazioneCamera/main.cpp
18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/main.cpp.o: 18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/enrico/Documenti/Programmazione/OpenGlC++/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object 18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/main.cpp.o"
	cd /home/enrico/Documenti/Programmazione/OpenGlC++/build/18_RotazioneCamera && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT 18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/main.cpp.o -MF CMakeFiles/18_RotazioneCamera.dir/main.cpp.o.d -o CMakeFiles/18_RotazioneCamera.dir/main.cpp.o -c /home/enrico/Documenti/Programmazione/OpenGlC++/src/18_RotazioneCamera/main.cpp

18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/18_RotazioneCamera.dir/main.cpp.i"
	cd /home/enrico/Documenti/Programmazione/OpenGlC++/build/18_RotazioneCamera && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/enrico/Documenti/Programmazione/OpenGlC++/src/18_RotazioneCamera/main.cpp > CMakeFiles/18_RotazioneCamera.dir/main.cpp.i

18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/18_RotazioneCamera.dir/main.cpp.s"
	cd /home/enrico/Documenti/Programmazione/OpenGlC++/build/18_RotazioneCamera && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/enrico/Documenti/Programmazione/OpenGlC++/src/18_RotazioneCamera/main.cpp -o CMakeFiles/18_RotazioneCamera.dir/main.cpp.s

# Object files for target 18_RotazioneCamera
18_RotazioneCamera_OBJECTS = \
"CMakeFiles/18_RotazioneCamera.dir/main.cpp.o"

# External object files for target 18_RotazioneCamera
18_RotazioneCamera_EXTERNAL_OBJECTS =

Executables/18_RotazioneCamera/18_RotazioneCamera: 18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/main.cpp.o
Executables/18_RotazioneCamera/18_RotazioneCamera: 18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/build.make
Executables/18_RotazioneCamera/18_RotazioneCamera: /usr/lib/libglfw.so.3.3
Executables/18_RotazioneCamera/18_RotazioneCamera: /usr/lib/libGLEW.so.2.2
Executables/18_RotazioneCamera/18_RotazioneCamera: /usr/lib/libGL.so
Executables/18_RotazioneCamera/18_RotazioneCamera: 18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/enrico/Documenti/Programmazione/OpenGlC++/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../Executables/18_RotazioneCamera/18_RotazioneCamera"
	cd /home/enrico/Documenti/Programmazione/OpenGlC++/build/18_RotazioneCamera && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/18_RotazioneCamera.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/build: Executables/18_RotazioneCamera/18_RotazioneCamera
.PHONY : 18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/build

18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/clean:
	cd /home/enrico/Documenti/Programmazione/OpenGlC++/build/18_RotazioneCamera && $(CMAKE_COMMAND) -P CMakeFiles/18_RotazioneCamera.dir/cmake_clean.cmake
.PHONY : 18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/clean

18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/depend:
	cd /home/enrico/Documenti/Programmazione/OpenGlC++/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/enrico/Documenti/Programmazione/OpenGlC++/src /home/enrico/Documenti/Programmazione/OpenGlC++/src/18_RotazioneCamera /home/enrico/Documenti/Programmazione/OpenGlC++/build /home/enrico/Documenti/Programmazione/OpenGlC++/build/18_RotazioneCamera /home/enrico/Documenti/Programmazione/OpenGlC++/build/18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : 18_RotazioneCamera/CMakeFiles/18_RotazioneCamera.dir/depend

