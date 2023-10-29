# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/dag/src/BezierCurve/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dag/src/BezierCurve/src/build

# Include any dependencies generated for this target.
include CMakeFiles/BezierCurve.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/BezierCurve.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/BezierCurve.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BezierCurve.dir/flags.make

CMakeFiles/BezierCurve.dir/main.cpp.o: CMakeFiles/BezierCurve.dir/flags.make
CMakeFiles/BezierCurve.dir/main.cpp.o: ../main.cpp
CMakeFiles/BezierCurve.dir/main.cpp.o: CMakeFiles/BezierCurve.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dag/src/BezierCurve/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BezierCurve.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BezierCurve.dir/main.cpp.o -MF CMakeFiles/BezierCurve.dir/main.cpp.o.d -o CMakeFiles/BezierCurve.dir/main.cpp.o -c /home/dag/src/BezierCurve/src/main.cpp

CMakeFiles/BezierCurve.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BezierCurve.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dag/src/BezierCurve/src/main.cpp > CMakeFiles/BezierCurve.dir/main.cpp.i

CMakeFiles/BezierCurve.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BezierCurve.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dag/src/BezierCurve/src/main.cpp -o CMakeFiles/BezierCurve.dir/main.cpp.s

CMakeFiles/BezierCurve.dir/Grid3D.cpp.o: CMakeFiles/BezierCurve.dir/flags.make
CMakeFiles/BezierCurve.dir/Grid3D.cpp.o: ../Grid3D.cpp
CMakeFiles/BezierCurve.dir/Grid3D.cpp.o: CMakeFiles/BezierCurve.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dag/src/BezierCurve/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/BezierCurve.dir/Grid3D.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BezierCurve.dir/Grid3D.cpp.o -MF CMakeFiles/BezierCurve.dir/Grid3D.cpp.o.d -o CMakeFiles/BezierCurve.dir/Grid3D.cpp.o -c /home/dag/src/BezierCurve/src/Grid3D.cpp

CMakeFiles/BezierCurve.dir/Grid3D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BezierCurve.dir/Grid3D.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dag/src/BezierCurve/src/Grid3D.cpp > CMakeFiles/BezierCurve.dir/Grid3D.cpp.i

CMakeFiles/BezierCurve.dir/Grid3D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BezierCurve.dir/Grid3D.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dag/src/BezierCurve/src/Grid3D.cpp -o CMakeFiles/BezierCurve.dir/Grid3D.cpp.s

CMakeFiles/BezierCurve.dir/CubicBezier.cpp.o: CMakeFiles/BezierCurve.dir/flags.make
CMakeFiles/BezierCurve.dir/CubicBezier.cpp.o: ../CubicBezier.cpp
CMakeFiles/BezierCurve.dir/CubicBezier.cpp.o: CMakeFiles/BezierCurve.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dag/src/BezierCurve/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/BezierCurve.dir/CubicBezier.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BezierCurve.dir/CubicBezier.cpp.o -MF CMakeFiles/BezierCurve.dir/CubicBezier.cpp.o.d -o CMakeFiles/BezierCurve.dir/CubicBezier.cpp.o -c /home/dag/src/BezierCurve/src/CubicBezier.cpp

CMakeFiles/BezierCurve.dir/CubicBezier.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BezierCurve.dir/CubicBezier.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dag/src/BezierCurve/src/CubicBezier.cpp > CMakeFiles/BezierCurve.dir/CubicBezier.cpp.i

CMakeFiles/BezierCurve.dir/CubicBezier.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BezierCurve.dir/CubicBezier.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dag/src/BezierCurve/src/CubicBezier.cpp -o CMakeFiles/BezierCurve.dir/CubicBezier.cpp.s

CMakeFiles/BezierCurve.dir/CubicBezierPatch.cpp.o: CMakeFiles/BezierCurve.dir/flags.make
CMakeFiles/BezierCurve.dir/CubicBezierPatch.cpp.o: ../CubicBezierPatch.cpp
CMakeFiles/BezierCurve.dir/CubicBezierPatch.cpp.o: CMakeFiles/BezierCurve.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dag/src/BezierCurve/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/BezierCurve.dir/CubicBezierPatch.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BezierCurve.dir/CubicBezierPatch.cpp.o -MF CMakeFiles/BezierCurve.dir/CubicBezierPatch.cpp.o.d -o CMakeFiles/BezierCurve.dir/CubicBezierPatch.cpp.o -c /home/dag/src/BezierCurve/src/CubicBezierPatch.cpp

CMakeFiles/BezierCurve.dir/CubicBezierPatch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BezierCurve.dir/CubicBezierPatch.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dag/src/BezierCurve/src/CubicBezierPatch.cpp > CMakeFiles/BezierCurve.dir/CubicBezierPatch.cpp.i

CMakeFiles/BezierCurve.dir/CubicBezierPatch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BezierCurve.dir/CubicBezierPatch.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dag/src/BezierCurve/src/CubicBezierPatch.cpp -o CMakeFiles/BezierCurve.dir/CubicBezierPatch.cpp.s

CMakeFiles/BezierCurve.dir/QuadraticBezier.cpp.o: CMakeFiles/BezierCurve.dir/flags.make
CMakeFiles/BezierCurve.dir/QuadraticBezier.cpp.o: ../QuadraticBezier.cpp
CMakeFiles/BezierCurve.dir/QuadraticBezier.cpp.o: CMakeFiles/BezierCurve.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dag/src/BezierCurve/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/BezierCurve.dir/QuadraticBezier.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BezierCurve.dir/QuadraticBezier.cpp.o -MF CMakeFiles/BezierCurve.dir/QuadraticBezier.cpp.o.d -o CMakeFiles/BezierCurve.dir/QuadraticBezier.cpp.o -c /home/dag/src/BezierCurve/src/QuadraticBezier.cpp

CMakeFiles/BezierCurve.dir/QuadraticBezier.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BezierCurve.dir/QuadraticBezier.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dag/src/BezierCurve/src/QuadraticBezier.cpp > CMakeFiles/BezierCurve.dir/QuadraticBezier.cpp.i

CMakeFiles/BezierCurve.dir/QuadraticBezier.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BezierCurve.dir/QuadraticBezier.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dag/src/BezierCurve/src/QuadraticBezier.cpp -o CMakeFiles/BezierCurve.dir/QuadraticBezier.cpp.s

CMakeFiles/BezierCurve.dir/QuadraticBezierPatch.cpp.o: CMakeFiles/BezierCurve.dir/flags.make
CMakeFiles/BezierCurve.dir/QuadraticBezierPatch.cpp.o: ../QuadraticBezierPatch.cpp
CMakeFiles/BezierCurve.dir/QuadraticBezierPatch.cpp.o: CMakeFiles/BezierCurve.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dag/src/BezierCurve/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/BezierCurve.dir/QuadraticBezierPatch.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BezierCurve.dir/QuadraticBezierPatch.cpp.o -MF CMakeFiles/BezierCurve.dir/QuadraticBezierPatch.cpp.o.d -o CMakeFiles/BezierCurve.dir/QuadraticBezierPatch.cpp.o -c /home/dag/src/BezierCurve/src/QuadraticBezierPatch.cpp

CMakeFiles/BezierCurve.dir/QuadraticBezierPatch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BezierCurve.dir/QuadraticBezierPatch.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dag/src/BezierCurve/src/QuadraticBezierPatch.cpp > CMakeFiles/BezierCurve.dir/QuadraticBezierPatch.cpp.i

CMakeFiles/BezierCurve.dir/QuadraticBezierPatch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BezierCurve.dir/QuadraticBezierPatch.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dag/src/BezierCurve/src/QuadraticBezierPatch.cpp -o CMakeFiles/BezierCurve.dir/QuadraticBezierPatch.cpp.s

# Object files for target BezierCurve
BezierCurve_OBJECTS = \
"CMakeFiles/BezierCurve.dir/main.cpp.o" \
"CMakeFiles/BezierCurve.dir/Grid3D.cpp.o" \
"CMakeFiles/BezierCurve.dir/CubicBezier.cpp.o" \
"CMakeFiles/BezierCurve.dir/CubicBezierPatch.cpp.o" \
"CMakeFiles/BezierCurve.dir/QuadraticBezier.cpp.o" \
"CMakeFiles/BezierCurve.dir/QuadraticBezierPatch.cpp.o"

# External object files for target BezierCurve
BezierCurve_EXTERNAL_OBJECTS =

BezierCurve: CMakeFiles/BezierCurve.dir/main.cpp.o
BezierCurve: CMakeFiles/BezierCurve.dir/Grid3D.cpp.o
BezierCurve: CMakeFiles/BezierCurve.dir/CubicBezier.cpp.o
BezierCurve: CMakeFiles/BezierCurve.dir/CubicBezierPatch.cpp.o
BezierCurve: CMakeFiles/BezierCurve.dir/QuadraticBezier.cpp.o
BezierCurve: CMakeFiles/BezierCurve.dir/QuadraticBezierPatch.cpp.o
BezierCurve: CMakeFiles/BezierCurve.dir/build.make
BezierCurve: glfw-3.3.8/src/libglfw3.a
BezierCurve: glad/libglad.a
BezierCurve: /usr/lib/x86_64-linux-gnu/librt.a
BezierCurve: /usr/lib/x86_64-linux-gnu/libm.so
BezierCurve: /usr/lib/x86_64-linux-gnu/libX11.so
BezierCurve: CMakeFiles/BezierCurve.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dag/src/BezierCurve/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable BezierCurve"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BezierCurve.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BezierCurve.dir/build: BezierCurve
.PHONY : CMakeFiles/BezierCurve.dir/build

CMakeFiles/BezierCurve.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BezierCurve.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BezierCurve.dir/clean

CMakeFiles/BezierCurve.dir/depend:
	cd /home/dag/src/BezierCurve/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dag/src/BezierCurve/src /home/dag/src/BezierCurve/src /home/dag/src/BezierCurve/src/build /home/dag/src/BezierCurve/src/build /home/dag/src/BezierCurve/src/build/CMakeFiles/BezierCurve.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BezierCurve.dir/depend
