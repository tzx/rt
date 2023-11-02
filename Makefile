# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_COMMAND = /nix/store/wjbqjwmnbi24qsvfh589my84fjr8wa3l-cmake-3.26.4/bin/cmake

# The command to remove a file.
RM = /nix/store/wjbqjwmnbi24qsvfh589my84fjr8wa3l-cmake-3.26.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/timmy/code/rt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/timmy/code/rt

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/nix/store/wjbqjwmnbi24qsvfh589my84fjr8wa3l-cmake-3.26.4/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/nix/store/wjbqjwmnbi24qsvfh589my84fjr8wa3l-cmake-3.26.4/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/timmy/code/rt/CMakeFiles /home/timmy/code/rt//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/timmy/code/rt/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -P /home/timmy/code/rt/CMakeFiles/VerifyGlobs.cmake
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Rt

# Build rule for target.
Rt: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Rt
.PHONY : Rt

# fast build rule for target.
Rt/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/build
.PHONY : Rt/fast

#=============================================================================
# Target rules for targets named tester

# Build rule for target.
tester: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 tester
.PHONY : tester

# fast build rule for target.
tester/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/build
.PHONY : tester/fast

src/canvas/camera.o: src/canvas/camera.cpp.o
.PHONY : src/canvas/camera.o

# target to build an object file
src/canvas/camera.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/canvas/camera.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/canvas/camera.cpp.o
.PHONY : src/canvas/camera.cpp.o

src/canvas/camera.i: src/canvas/camera.cpp.i
.PHONY : src/canvas/camera.i

# target to preprocess a source file
src/canvas/camera.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/canvas/camera.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/canvas/camera.cpp.i
.PHONY : src/canvas/camera.cpp.i

src/canvas/camera.s: src/canvas/camera.cpp.s
.PHONY : src/canvas/camera.s

# target to generate assembly for a file
src/canvas/camera.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/canvas/camera.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/canvas/camera.cpp.s
.PHONY : src/canvas/camera.cpp.s

src/canvas/canvas.o: src/canvas/canvas.cpp.o
.PHONY : src/canvas/canvas.o

# target to build an object file
src/canvas/canvas.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/canvas/canvas.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/canvas/canvas.cpp.o
.PHONY : src/canvas/canvas.cpp.o

src/canvas/canvas.i: src/canvas/canvas.cpp.i
.PHONY : src/canvas/canvas.i

# target to preprocess a source file
src/canvas/canvas.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/canvas/canvas.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/canvas/canvas.cpp.i
.PHONY : src/canvas/canvas.cpp.i

src/canvas/canvas.s: src/canvas/canvas.cpp.s
.PHONY : src/canvas/canvas.s

# target to generate assembly for a file
src/canvas/canvas.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/canvas/canvas.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/canvas/canvas.cpp.s
.PHONY : src/canvas/canvas.cpp.s

src/canvas/color.o: src/canvas/color.cpp.o
.PHONY : src/canvas/color.o

# target to build an object file
src/canvas/color.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/canvas/color.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/canvas/color.cpp.o
.PHONY : src/canvas/color.cpp.o

src/canvas/color.i: src/canvas/color.cpp.i
.PHONY : src/canvas/color.i

# target to preprocess a source file
src/canvas/color.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/canvas/color.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/canvas/color.cpp.i
.PHONY : src/canvas/color.cpp.i

src/canvas/color.s: src/canvas/color.cpp.s
.PHONY : src/canvas/color.s

# target to generate assembly for a file
src/canvas/color.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/canvas/color.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/canvas/color.cpp.s
.PHONY : src/canvas/color.cpp.s

src/canvas/world.o: src/canvas/world.cpp.o
.PHONY : src/canvas/world.o

# target to build an object file
src/canvas/world.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/canvas/world.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/canvas/world.cpp.o
.PHONY : src/canvas/world.cpp.o

src/canvas/world.i: src/canvas/world.cpp.i
.PHONY : src/canvas/world.i

# target to preprocess a source file
src/canvas/world.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/canvas/world.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/canvas/world.cpp.i
.PHONY : src/canvas/world.cpp.i

src/canvas/world.s: src/canvas/world.cpp.s
.PHONY : src/canvas/world.s

# target to generate assembly for a file
src/canvas/world.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/canvas/world.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/canvas/world.cpp.s
.PHONY : src/canvas/world.cpp.s

src/intersection.o: src/intersection.cpp.o
.PHONY : src/intersection.o

# target to build an object file
src/intersection.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/intersection.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/intersection.cpp.o
.PHONY : src/intersection.cpp.o

src/intersection.i: src/intersection.cpp.i
.PHONY : src/intersection.i

# target to preprocess a source file
src/intersection.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/intersection.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/intersection.cpp.i
.PHONY : src/intersection.cpp.i

src/intersection.s: src/intersection.cpp.s
.PHONY : src/intersection.s

# target to generate assembly for a file
src/intersection.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/intersection.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/intersection.cpp.s
.PHONY : src/intersection.cpp.s

src/lights/material.o: src/lights/material.cpp.o
.PHONY : src/lights/material.o

# target to build an object file
src/lights/material.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/lights/material.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/lights/material.cpp.o
.PHONY : src/lights/material.cpp.o

src/lights/material.i: src/lights/material.cpp.i
.PHONY : src/lights/material.i

# target to preprocess a source file
src/lights/material.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/lights/material.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/lights/material.cpp.i
.PHONY : src/lights/material.cpp.i

src/lights/material.s: src/lights/material.cpp.s
.PHONY : src/lights/material.s

# target to generate assembly for a file
src/lights/material.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/lights/material.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/lights/material.cpp.s
.PHONY : src/lights/material.cpp.s

src/lights/point_light.o: src/lights/point_light.cpp.o
.PHONY : src/lights/point_light.o

# target to build an object file
src/lights/point_light.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/lights/point_light.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/lights/point_light.cpp.o
.PHONY : src/lights/point_light.cpp.o

src/lights/point_light.i: src/lights/point_light.cpp.i
.PHONY : src/lights/point_light.i

# target to preprocess a source file
src/lights/point_light.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/lights/point_light.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/lights/point_light.cpp.i
.PHONY : src/lights/point_light.cpp.i

src/lights/point_light.s: src/lights/point_light.cpp.s
.PHONY : src/lights/point_light.s

# target to generate assembly for a file
src/lights/point_light.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/lights/point_light.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/lights/point_light.cpp.s
.PHONY : src/lights/point_light.cpp.s

src/primitives/matrix.o: src/primitives/matrix.cpp.o
.PHONY : src/primitives/matrix.o

# target to build an object file
src/primitives/matrix.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/primitives/matrix.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/primitives/matrix.cpp.o
.PHONY : src/primitives/matrix.cpp.o

src/primitives/matrix.i: src/primitives/matrix.cpp.i
.PHONY : src/primitives/matrix.i

# target to preprocess a source file
src/primitives/matrix.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/primitives/matrix.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/primitives/matrix.cpp.i
.PHONY : src/primitives/matrix.cpp.i

src/primitives/matrix.s: src/primitives/matrix.cpp.s
.PHONY : src/primitives/matrix.s

# target to generate assembly for a file
src/primitives/matrix.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/primitives/matrix.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/primitives/matrix.cpp.s
.PHONY : src/primitives/matrix.cpp.s

src/primitives/transformations.o: src/primitives/transformations.cpp.o
.PHONY : src/primitives/transformations.o

# target to build an object file
src/primitives/transformations.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/primitives/transformations.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/primitives/transformations.cpp.o
.PHONY : src/primitives/transformations.cpp.o

src/primitives/transformations.i: src/primitives/transformations.cpp.i
.PHONY : src/primitives/transformations.i

# target to preprocess a source file
src/primitives/transformations.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/primitives/transformations.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/primitives/transformations.cpp.i
.PHONY : src/primitives/transformations.cpp.i

src/primitives/transformations.s: src/primitives/transformations.cpp.s
.PHONY : src/primitives/transformations.s

# target to generate assembly for a file
src/primitives/transformations.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/primitives/transformations.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/primitives/transformations.cpp.s
.PHONY : src/primitives/transformations.cpp.s

src/primitives/tuple.o: src/primitives/tuple.cpp.o
.PHONY : src/primitives/tuple.o

# target to build an object file
src/primitives/tuple.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/primitives/tuple.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/primitives/tuple.cpp.o
.PHONY : src/primitives/tuple.cpp.o

src/primitives/tuple.i: src/primitives/tuple.cpp.i
.PHONY : src/primitives/tuple.i

# target to preprocess a source file
src/primitives/tuple.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/primitives/tuple.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/primitives/tuple.cpp.i
.PHONY : src/primitives/tuple.cpp.i

src/primitives/tuple.s: src/primitives/tuple.cpp.s
.PHONY : src/primitives/tuple.s

# target to generate assembly for a file
src/primitives/tuple.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/primitives/tuple.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/primitives/tuple.cpp.s
.PHONY : src/primitives/tuple.cpp.s

src/ray.o: src/ray.cpp.o
.PHONY : src/ray.o

# target to build an object file
src/ray.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/ray.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/ray.cpp.o
.PHONY : src/ray.cpp.o

src/ray.i: src/ray.cpp.i
.PHONY : src/ray.i

# target to preprocess a source file
src/ray.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/ray.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/ray.cpp.i
.PHONY : src/ray.cpp.i

src/ray.s: src/ray.cpp.s
.PHONY : src/ray.s

# target to generate assembly for a file
src/ray.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/ray.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/ray.cpp.s
.PHONY : src/ray.cpp.s

src/rt.o: src/rt.cpp.o
.PHONY : src/rt.o

# target to build an object file
src/rt.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/rt.cpp.o
.PHONY : src/rt.cpp.o

src/rt.i: src/rt.cpp.i
.PHONY : src/rt.i

# target to preprocess a source file
src/rt.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/rt.cpp.i
.PHONY : src/rt.cpp.i

src/rt.s: src/rt.cpp.s
.PHONY : src/rt.s

# target to generate assembly for a file
src/rt.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/rt.cpp.s
.PHONY : src/rt.cpp.s

src/sphere.o: src/sphere.cpp.o
.PHONY : src/sphere.o

# target to build an object file
src/sphere.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/sphere.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/sphere.cpp.o
.PHONY : src/sphere.cpp.o

src/sphere.i: src/sphere.cpp.i
.PHONY : src/sphere.i

# target to preprocess a source file
src/sphere.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/sphere.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/sphere.cpp.i
.PHONY : src/sphere.cpp.i

src/sphere.s: src/sphere.cpp.s
.PHONY : src/sphere.s

# target to generate assembly for a file
src/sphere.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/sphere.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/sphere.cpp.s
.PHONY : src/sphere.cpp.s

src/util/approx.o: src/util/approx.cpp.o
.PHONY : src/util/approx.o

# target to build an object file
src/util/approx.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/util/approx.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/util/approx.cpp.o
.PHONY : src/util/approx.cpp.o

src/util/approx.i: src/util/approx.cpp.i
.PHONY : src/util/approx.i

# target to preprocess a source file
src/util/approx.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/util/approx.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/util/approx.cpp.i
.PHONY : src/util/approx.cpp.i

src/util/approx.s: src/util/approx.cpp.s
.PHONY : src/util/approx.s

# target to generate assembly for a file
src/util/approx.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/util/approx.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/util/approx.cpp.s
.PHONY : src/util/approx.cpp.s

src/util/rangen.o: src/util/rangen.cpp.o
.PHONY : src/util/rangen.o

# target to build an object file
src/util/rangen.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/util/rangen.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/util/rangen.cpp.o
.PHONY : src/util/rangen.cpp.o

src/util/rangen.i: src/util/rangen.cpp.i
.PHONY : src/util/rangen.i

# target to preprocess a source file
src/util/rangen.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/util/rangen.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/util/rangen.cpp.i
.PHONY : src/util/rangen.cpp.i

src/util/rangen.s: src/util/rangen.cpp.s
.PHONY : src/util/rangen.s

# target to generate assembly for a file
src/util/rangen.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/util/rangen.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/util/rangen.cpp.s
.PHONY : src/util/rangen.cpp.s

tests/canvas.o: tests/canvas.cpp.o
.PHONY : tests/canvas.o

# target to build an object file
tests/canvas.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/canvas.cpp.o
.PHONY : tests/canvas.cpp.o

tests/canvas.i: tests/canvas.cpp.i
.PHONY : tests/canvas.i

# target to preprocess a source file
tests/canvas.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/canvas.cpp.i
.PHONY : tests/canvas.cpp.i

tests/canvas.s: tests/canvas.cpp.s
.PHONY : tests/canvas.s

# target to generate assembly for a file
tests/canvas.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/canvas.cpp.s
.PHONY : tests/canvas.cpp.s

tests/color.o: tests/color.cpp.o
.PHONY : tests/color.o

# target to build an object file
tests/color.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/color.cpp.o
.PHONY : tests/color.cpp.o

tests/color.i: tests/color.cpp.i
.PHONY : tests/color.i

# target to preprocess a source file
tests/color.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/color.cpp.i
.PHONY : tests/color.cpp.i

tests/color.s: tests/color.cpp.s
.PHONY : tests/color.s

# target to generate assembly for a file
tests/color.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/color.cpp.s
.PHONY : tests/color.cpp.s

tests/lighting.o: tests/lighting.cpp.o
.PHONY : tests/lighting.o

# target to build an object file
tests/lighting.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/lighting.cpp.o
.PHONY : tests/lighting.cpp.o

tests/lighting.i: tests/lighting.cpp.i
.PHONY : tests/lighting.i

# target to preprocess a source file
tests/lighting.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/lighting.cpp.i
.PHONY : tests/lighting.cpp.i

tests/lighting.s: tests/lighting.cpp.s
.PHONY : tests/lighting.s

# target to generate assembly for a file
tests/lighting.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/lighting.cpp.s
.PHONY : tests/lighting.cpp.s

tests/matrix.o: tests/matrix.cpp.o
.PHONY : tests/matrix.o

# target to build an object file
tests/matrix.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/matrix.cpp.o
.PHONY : tests/matrix.cpp.o

tests/matrix.i: tests/matrix.cpp.i
.PHONY : tests/matrix.i

# target to preprocess a source file
tests/matrix.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/matrix.cpp.i
.PHONY : tests/matrix.cpp.i

tests/matrix.s: tests/matrix.cpp.s
.PHONY : tests/matrix.s

# target to generate assembly for a file
tests/matrix.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/matrix.cpp.s
.PHONY : tests/matrix.cpp.s

tests/ray.o: tests/ray.cpp.o
.PHONY : tests/ray.o

# target to build an object file
tests/ray.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/ray.cpp.o
.PHONY : tests/ray.cpp.o

tests/ray.i: tests/ray.cpp.i
.PHONY : tests/ray.i

# target to preprocess a source file
tests/ray.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/ray.cpp.i
.PHONY : tests/ray.cpp.i

tests/ray.s: tests/ray.cpp.s
.PHONY : tests/ray.s

# target to generate assembly for a file
tests/ray.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/ray.cpp.s
.PHONY : tests/ray.cpp.s

tests/scene.o: tests/scene.cpp.o
.PHONY : tests/scene.o

# target to build an object file
tests/scene.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/scene.cpp.o
.PHONY : tests/scene.cpp.o

tests/scene.i: tests/scene.cpp.i
.PHONY : tests/scene.i

# target to preprocess a source file
tests/scene.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/scene.cpp.i
.PHONY : tests/scene.cpp.i

tests/scene.s: tests/scene.cpp.s
.PHONY : tests/scene.s

# target to generate assembly for a file
tests/scene.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/scene.cpp.s
.PHONY : tests/scene.cpp.s

tests/transformations.o: tests/transformations.cpp.o
.PHONY : tests/transformations.o

# target to build an object file
tests/transformations.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/transformations.cpp.o
.PHONY : tests/transformations.cpp.o

tests/transformations.i: tests/transformations.cpp.i
.PHONY : tests/transformations.i

# target to preprocess a source file
tests/transformations.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/transformations.cpp.i
.PHONY : tests/transformations.cpp.i

tests/transformations.s: tests/transformations.cpp.s
.PHONY : tests/transformations.s

# target to generate assembly for a file
tests/transformations.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/transformations.cpp.s
.PHONY : tests/transformations.cpp.s

tests/tuple.o: tests/tuple.cpp.o
.PHONY : tests/tuple.o

# target to build an object file
tests/tuple.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/tuple.cpp.o
.PHONY : tests/tuple.cpp.o

tests/tuple.i: tests/tuple.cpp.i
.PHONY : tests/tuple.i

# target to preprocess a source file
tests/tuple.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/tuple.cpp.i
.PHONY : tests/tuple.cpp.i

tests/tuple.s: tests/tuple.cpp.s
.PHONY : tests/tuple.s

# target to generate assembly for a file
tests/tuple.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/tests/tuple.cpp.s
.PHONY : tests/tuple.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... Rt"
	@echo "... tester"
	@echo "... src/canvas/camera.o"
	@echo "... src/canvas/camera.i"
	@echo "... src/canvas/camera.s"
	@echo "... src/canvas/canvas.o"
	@echo "... src/canvas/canvas.i"
	@echo "... src/canvas/canvas.s"
	@echo "... src/canvas/color.o"
	@echo "... src/canvas/color.i"
	@echo "... src/canvas/color.s"
	@echo "... src/canvas/world.o"
	@echo "... src/canvas/world.i"
	@echo "... src/canvas/world.s"
	@echo "... src/intersection.o"
	@echo "... src/intersection.i"
	@echo "... src/intersection.s"
	@echo "... src/lights/material.o"
	@echo "... src/lights/material.i"
	@echo "... src/lights/material.s"
	@echo "... src/lights/point_light.o"
	@echo "... src/lights/point_light.i"
	@echo "... src/lights/point_light.s"
	@echo "... src/primitives/matrix.o"
	@echo "... src/primitives/matrix.i"
	@echo "... src/primitives/matrix.s"
	@echo "... src/primitives/transformations.o"
	@echo "... src/primitives/transformations.i"
	@echo "... src/primitives/transformations.s"
	@echo "... src/primitives/tuple.o"
	@echo "... src/primitives/tuple.i"
	@echo "... src/primitives/tuple.s"
	@echo "... src/ray.o"
	@echo "... src/ray.i"
	@echo "... src/ray.s"
	@echo "... src/rt.o"
	@echo "... src/rt.i"
	@echo "... src/rt.s"
	@echo "... src/sphere.o"
	@echo "... src/sphere.i"
	@echo "... src/sphere.s"
	@echo "... src/util/approx.o"
	@echo "... src/util/approx.i"
	@echo "... src/util/approx.s"
	@echo "... src/util/rangen.o"
	@echo "... src/util/rangen.i"
	@echo "... src/util/rangen.s"
	@echo "... tests/canvas.o"
	@echo "... tests/canvas.i"
	@echo "... tests/canvas.s"
	@echo "... tests/color.o"
	@echo "... tests/color.i"
	@echo "... tests/color.s"
	@echo "... tests/lighting.o"
	@echo "... tests/lighting.i"
	@echo "... tests/lighting.s"
	@echo "... tests/matrix.o"
	@echo "... tests/matrix.i"
	@echo "... tests/matrix.s"
	@echo "... tests/ray.o"
	@echo "... tests/ray.i"
	@echo "... tests/ray.s"
	@echo "... tests/scene.o"
	@echo "... tests/scene.i"
	@echo "... tests/scene.s"
	@echo "... tests/transformations.o"
	@echo "... tests/transformations.i"
	@echo "... tests/transformations.s"
	@echo "... tests/tuple.o"
	@echo "... tests/tuple.i"
	@echo "... tests/tuple.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -P /home/timmy/code/rt/CMakeFiles/VerifyGlobs.cmake
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

