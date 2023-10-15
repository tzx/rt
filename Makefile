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

src/canvas.o: src/canvas.cpp.o
.PHONY : src/canvas.o

# target to build an object file
src/canvas.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/canvas.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/canvas.cpp.o
.PHONY : src/canvas.cpp.o

src/canvas.i: src/canvas.cpp.i
.PHONY : src/canvas.i

# target to preprocess a source file
src/canvas.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/canvas.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/canvas.cpp.i
.PHONY : src/canvas.cpp.i

src/canvas.s: src/canvas.cpp.s
.PHONY : src/canvas.s

# target to generate assembly for a file
src/canvas.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/canvas.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/canvas.cpp.s
.PHONY : src/canvas.cpp.s

src/color.o: src/color.cpp.o
.PHONY : src/color.o

# target to build an object file
src/color.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/color.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/color.cpp.o
.PHONY : src/color.cpp.o

src/color.i: src/color.cpp.i
.PHONY : src/color.i

# target to preprocess a source file
src/color.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/color.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/color.cpp.i
.PHONY : src/color.cpp.i

src/color.s: src/color.cpp.s
.PHONY : src/color.s

# target to generate assembly for a file
src/color.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/color.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/color.cpp.s
.PHONY : src/color.cpp.s

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

src/tuple.o: src/tuple.cpp.o
.PHONY : src/tuple.o

# target to build an object file
src/tuple.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/tuple.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/tuple.cpp.o
.PHONY : src/tuple.cpp.o

src/tuple.i: src/tuple.cpp.i
.PHONY : src/tuple.i

# target to preprocess a source file
src/tuple.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/tuple.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/tuple.cpp.i
.PHONY : src/tuple.cpp.i

src/tuple.s: src/tuple.cpp.s
.PHONY : src/tuple.s

# target to generate assembly for a file
src/tuple.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Rt.dir/build.make CMakeFiles/Rt.dir/src/tuple.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/tester.dir/build.make CMakeFiles/tester.dir/src/tuple.cpp.s
.PHONY : src/tuple.cpp.s

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
	@echo "... src/canvas.o"
	@echo "... src/canvas.i"
	@echo "... src/canvas.s"
	@echo "... src/color.o"
	@echo "... src/color.i"
	@echo "... src/color.s"
	@echo "... src/rt.o"
	@echo "... src/rt.i"
	@echo "... src/rt.s"
	@echo "... src/tuple.o"
	@echo "... src/tuple.i"
	@echo "... src/tuple.s"
	@echo "... tests/canvas.o"
	@echo "... tests/canvas.i"
	@echo "... tests/canvas.s"
	@echo "... tests/color.o"
	@echo "... tests/color.i"
	@echo "... tests/color.s"
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

