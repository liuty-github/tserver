# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/hgfs/E/other/TServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/hgfs/E/other/TServer/build/linux

# Include any dependencies generated for this target.
include src/tEngine/CMakeFiles/tEngine.dir/depend.make

# Include the progress variables for this target.
include src/tEngine/CMakeFiles/tEngine.dir/progress.make

# Include the compile flags for this target's objects.
include src/tEngine/CMakeFiles/tEngine.dir/flags.make

src/tEngine/CMakeFiles/tEngine.dir/tConfig.cpp.o: src/tEngine/CMakeFiles/tEngine.dir/flags.make
src/tEngine/CMakeFiles/tEngine.dir/tConfig.cpp.o: ../../src/tEngine/tConfig.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/E/other/TServer/build/linux/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/tEngine/CMakeFiles/tEngine.dir/tConfig.cpp.o"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tEngine.dir/tConfig.cpp.o -c /mnt/hgfs/E/other/TServer/src/tEngine/tConfig.cpp

src/tEngine/CMakeFiles/tEngine.dir/tConfig.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tEngine.dir/tConfig.cpp.i"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/E/other/TServer/src/tEngine/tConfig.cpp > CMakeFiles/tEngine.dir/tConfig.cpp.i

src/tEngine/CMakeFiles/tEngine.dir/tConfig.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tEngine.dir/tConfig.cpp.s"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/E/other/TServer/src/tEngine/tConfig.cpp -o CMakeFiles/tEngine.dir/tConfig.cpp.s

src/tEngine/CMakeFiles/tEngine.dir/tConfig.cpp.o.requires:
.PHONY : src/tEngine/CMakeFiles/tEngine.dir/tConfig.cpp.o.requires

src/tEngine/CMakeFiles/tEngine.dir/tConfig.cpp.o.provides: src/tEngine/CMakeFiles/tEngine.dir/tConfig.cpp.o.requires
	$(MAKE) -f src/tEngine/CMakeFiles/tEngine.dir/build.make src/tEngine/CMakeFiles/tEngine.dir/tConfig.cpp.o.provides.build
.PHONY : src/tEngine/CMakeFiles/tEngine.dir/tConfig.cpp.o.provides

src/tEngine/CMakeFiles/tEngine.dir/tConfig.cpp.o.provides.build: src/tEngine/CMakeFiles/tEngine.dir/tConfig.cpp.o

src/tEngine/CMakeFiles/tEngine.dir/tEngine.cpp.o: src/tEngine/CMakeFiles/tEngine.dir/flags.make
src/tEngine/CMakeFiles/tEngine.dir/tEngine.cpp.o: ../../src/tEngine/tEngine.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/E/other/TServer/build/linux/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/tEngine/CMakeFiles/tEngine.dir/tEngine.cpp.o"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tEngine.dir/tEngine.cpp.o -c /mnt/hgfs/E/other/TServer/src/tEngine/tEngine.cpp

src/tEngine/CMakeFiles/tEngine.dir/tEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tEngine.dir/tEngine.cpp.i"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/E/other/TServer/src/tEngine/tEngine.cpp > CMakeFiles/tEngine.dir/tEngine.cpp.i

src/tEngine/CMakeFiles/tEngine.dir/tEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tEngine.dir/tEngine.cpp.s"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/E/other/TServer/src/tEngine/tEngine.cpp -o CMakeFiles/tEngine.dir/tEngine.cpp.s

src/tEngine/CMakeFiles/tEngine.dir/tEngine.cpp.o.requires:
.PHONY : src/tEngine/CMakeFiles/tEngine.dir/tEngine.cpp.o.requires

src/tEngine/CMakeFiles/tEngine.dir/tEngine.cpp.o.provides: src/tEngine/CMakeFiles/tEngine.dir/tEngine.cpp.o.requires
	$(MAKE) -f src/tEngine/CMakeFiles/tEngine.dir/build.make src/tEngine/CMakeFiles/tEngine.dir/tEngine.cpp.o.provides.build
.PHONY : src/tEngine/CMakeFiles/tEngine.dir/tEngine.cpp.o.provides

src/tEngine/CMakeFiles/tEngine.dir/tEngine.cpp.o.provides.build: src/tEngine/CMakeFiles/tEngine.dir/tEngine.cpp.o

src/tEngine/CMakeFiles/tEngine.dir/tLog.cxx.o: src/tEngine/CMakeFiles/tEngine.dir/flags.make
src/tEngine/CMakeFiles/tEngine.dir/tLog.cxx.o: ../../src/tEngine/tLog.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/E/other/TServer/build/linux/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/tEngine/CMakeFiles/tEngine.dir/tLog.cxx.o"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tEngine.dir/tLog.cxx.o -c /mnt/hgfs/E/other/TServer/src/tEngine/tLog.cxx

src/tEngine/CMakeFiles/tEngine.dir/tLog.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tEngine.dir/tLog.cxx.i"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/E/other/TServer/src/tEngine/tLog.cxx > CMakeFiles/tEngine.dir/tLog.cxx.i

src/tEngine/CMakeFiles/tEngine.dir/tLog.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tEngine.dir/tLog.cxx.s"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/E/other/TServer/src/tEngine/tLog.cxx -o CMakeFiles/tEngine.dir/tLog.cxx.s

src/tEngine/CMakeFiles/tEngine.dir/tLog.cxx.o.requires:
.PHONY : src/tEngine/CMakeFiles/tEngine.dir/tLog.cxx.o.requires

src/tEngine/CMakeFiles/tEngine.dir/tLog.cxx.o.provides: src/tEngine/CMakeFiles/tEngine.dir/tLog.cxx.o.requires
	$(MAKE) -f src/tEngine/CMakeFiles/tEngine.dir/build.make src/tEngine/CMakeFiles/tEngine.dir/tLog.cxx.o.provides.build
.PHONY : src/tEngine/CMakeFiles/tEngine.dir/tLog.cxx.o.provides

src/tEngine/CMakeFiles/tEngine.dir/tLog.cxx.o.provides.build: src/tEngine/CMakeFiles/tEngine.dir/tLog.cxx.o

src/tEngine/CMakeFiles/tEngine.dir/tMemoryPool.cpp.o: src/tEngine/CMakeFiles/tEngine.dir/flags.make
src/tEngine/CMakeFiles/tEngine.dir/tMemoryPool.cpp.o: ../../src/tEngine/tMemoryPool.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/E/other/TServer/build/linux/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/tEngine/CMakeFiles/tEngine.dir/tMemoryPool.cpp.o"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tEngine.dir/tMemoryPool.cpp.o -c /mnt/hgfs/E/other/TServer/src/tEngine/tMemoryPool.cpp

src/tEngine/CMakeFiles/tEngine.dir/tMemoryPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tEngine.dir/tMemoryPool.cpp.i"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/E/other/TServer/src/tEngine/tMemoryPool.cpp > CMakeFiles/tEngine.dir/tMemoryPool.cpp.i

src/tEngine/CMakeFiles/tEngine.dir/tMemoryPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tEngine.dir/tMemoryPool.cpp.s"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/E/other/TServer/src/tEngine/tMemoryPool.cpp -o CMakeFiles/tEngine.dir/tMemoryPool.cpp.s

src/tEngine/CMakeFiles/tEngine.dir/tMemoryPool.cpp.o.requires:
.PHONY : src/tEngine/CMakeFiles/tEngine.dir/tMemoryPool.cpp.o.requires

src/tEngine/CMakeFiles/tEngine.dir/tMemoryPool.cpp.o.provides: src/tEngine/CMakeFiles/tEngine.dir/tMemoryPool.cpp.o.requires
	$(MAKE) -f src/tEngine/CMakeFiles/tEngine.dir/build.make src/tEngine/CMakeFiles/tEngine.dir/tMemoryPool.cpp.o.provides.build
.PHONY : src/tEngine/CMakeFiles/tEngine.dir/tMemoryPool.cpp.o.provides

src/tEngine/CMakeFiles/tEngine.dir/tMemoryPool.cpp.o.provides.build: src/tEngine/CMakeFiles/tEngine.dir/tMemoryPool.cpp.o

src/tEngine/CMakeFiles/tEngine.dir/tProccess.cpp.o: src/tEngine/CMakeFiles/tEngine.dir/flags.make
src/tEngine/CMakeFiles/tEngine.dir/tProccess.cpp.o: ../../src/tEngine/tProccess.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/E/other/TServer/build/linux/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/tEngine/CMakeFiles/tEngine.dir/tProccess.cpp.o"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tEngine.dir/tProccess.cpp.o -c /mnt/hgfs/E/other/TServer/src/tEngine/tProccess.cpp

src/tEngine/CMakeFiles/tEngine.dir/tProccess.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tEngine.dir/tProccess.cpp.i"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/E/other/TServer/src/tEngine/tProccess.cpp > CMakeFiles/tEngine.dir/tProccess.cpp.i

src/tEngine/CMakeFiles/tEngine.dir/tProccess.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tEngine.dir/tProccess.cpp.s"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/E/other/TServer/src/tEngine/tProccess.cpp -o CMakeFiles/tEngine.dir/tProccess.cpp.s

src/tEngine/CMakeFiles/tEngine.dir/tProccess.cpp.o.requires:
.PHONY : src/tEngine/CMakeFiles/tEngine.dir/tProccess.cpp.o.requires

src/tEngine/CMakeFiles/tEngine.dir/tProccess.cpp.o.provides: src/tEngine/CMakeFiles/tEngine.dir/tProccess.cpp.o.requires
	$(MAKE) -f src/tEngine/CMakeFiles/tEngine.dir/build.make src/tEngine/CMakeFiles/tEngine.dir/tProccess.cpp.o.provides.build
.PHONY : src/tEngine/CMakeFiles/tEngine.dir/tProccess.cpp.o.provides

src/tEngine/CMakeFiles/tEngine.dir/tProccess.cpp.o.provides.build: src/tEngine/CMakeFiles/tEngine.dir/tProccess.cpp.o

src/tEngine/CMakeFiles/tEngine.dir/tThread.cpp.o: src/tEngine/CMakeFiles/tEngine.dir/flags.make
src/tEngine/CMakeFiles/tEngine.dir/tThread.cpp.o: ../../src/tEngine/tThread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/E/other/TServer/build/linux/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/tEngine/CMakeFiles/tEngine.dir/tThread.cpp.o"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tEngine.dir/tThread.cpp.o -c /mnt/hgfs/E/other/TServer/src/tEngine/tThread.cpp

src/tEngine/CMakeFiles/tEngine.dir/tThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tEngine.dir/tThread.cpp.i"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/E/other/TServer/src/tEngine/tThread.cpp > CMakeFiles/tEngine.dir/tThread.cpp.i

src/tEngine/CMakeFiles/tEngine.dir/tThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tEngine.dir/tThread.cpp.s"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/E/other/TServer/src/tEngine/tThread.cpp -o CMakeFiles/tEngine.dir/tThread.cpp.s

src/tEngine/CMakeFiles/tEngine.dir/tThread.cpp.o.requires:
.PHONY : src/tEngine/CMakeFiles/tEngine.dir/tThread.cpp.o.requires

src/tEngine/CMakeFiles/tEngine.dir/tThread.cpp.o.provides: src/tEngine/CMakeFiles/tEngine.dir/tThread.cpp.o.requires
	$(MAKE) -f src/tEngine/CMakeFiles/tEngine.dir/build.make src/tEngine/CMakeFiles/tEngine.dir/tThread.cpp.o.provides.build
.PHONY : src/tEngine/CMakeFiles/tEngine.dir/tThread.cpp.o.provides

src/tEngine/CMakeFiles/tEngine.dir/tThread.cpp.o.provides.build: src/tEngine/CMakeFiles/tEngine.dir/tThread.cpp.o

src/tEngine/CMakeFiles/tEngine.dir/tThreadTask.cpp.o: src/tEngine/CMakeFiles/tEngine.dir/flags.make
src/tEngine/CMakeFiles/tEngine.dir/tThreadTask.cpp.o: ../../src/tEngine/tThreadTask.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/E/other/TServer/build/linux/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/tEngine/CMakeFiles/tEngine.dir/tThreadTask.cpp.o"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tEngine.dir/tThreadTask.cpp.o -c /mnt/hgfs/E/other/TServer/src/tEngine/tThreadTask.cpp

src/tEngine/CMakeFiles/tEngine.dir/tThreadTask.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tEngine.dir/tThreadTask.cpp.i"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/E/other/TServer/src/tEngine/tThreadTask.cpp > CMakeFiles/tEngine.dir/tThreadTask.cpp.i

src/tEngine/CMakeFiles/tEngine.dir/tThreadTask.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tEngine.dir/tThreadTask.cpp.s"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/E/other/TServer/src/tEngine/tThreadTask.cpp -o CMakeFiles/tEngine.dir/tThreadTask.cpp.s

src/tEngine/CMakeFiles/tEngine.dir/tThreadTask.cpp.o.requires:
.PHONY : src/tEngine/CMakeFiles/tEngine.dir/tThreadTask.cpp.o.requires

src/tEngine/CMakeFiles/tEngine.dir/tThreadTask.cpp.o.provides: src/tEngine/CMakeFiles/tEngine.dir/tThreadTask.cpp.o.requires
	$(MAKE) -f src/tEngine/CMakeFiles/tEngine.dir/build.make src/tEngine/CMakeFiles/tEngine.dir/tThreadTask.cpp.o.provides.build
.PHONY : src/tEngine/CMakeFiles/tEngine.dir/tThreadTask.cpp.o.provides

src/tEngine/CMakeFiles/tEngine.dir/tThreadTask.cpp.o.provides.build: src/tEngine/CMakeFiles/tEngine.dir/tThreadTask.cpp.o

# Object files for target tEngine
tEngine_OBJECTS = \
"CMakeFiles/tEngine.dir/tConfig.cpp.o" \
"CMakeFiles/tEngine.dir/tEngine.cpp.o" \
"CMakeFiles/tEngine.dir/tLog.cxx.o" \
"CMakeFiles/tEngine.dir/tMemoryPool.cpp.o" \
"CMakeFiles/tEngine.dir/tProccess.cpp.o" \
"CMakeFiles/tEngine.dir/tThread.cpp.o" \
"CMakeFiles/tEngine.dir/tThreadTask.cpp.o"

# External object files for target tEngine
tEngine_EXTERNAL_OBJECTS =

../libtEngine.so: src/tEngine/CMakeFiles/tEngine.dir/tConfig.cpp.o
../libtEngine.so: src/tEngine/CMakeFiles/tEngine.dir/tEngine.cpp.o
../libtEngine.so: src/tEngine/CMakeFiles/tEngine.dir/tLog.cxx.o
../libtEngine.so: src/tEngine/CMakeFiles/tEngine.dir/tMemoryPool.cpp.o
../libtEngine.so: src/tEngine/CMakeFiles/tEngine.dir/tProccess.cpp.o
../libtEngine.so: src/tEngine/CMakeFiles/tEngine.dir/tThread.cpp.o
../libtEngine.so: src/tEngine/CMakeFiles/tEngine.dir/tThreadTask.cpp.o
../libtEngine.so: src/tEngine/CMakeFiles/tEngine.dir/build.make
../libtEngine.so: src/tEngine/CMakeFiles/tEngine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../../../libtEngine.so"
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tEngine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/tEngine/CMakeFiles/tEngine.dir/build: ../libtEngine.so
.PHONY : src/tEngine/CMakeFiles/tEngine.dir/build

src/tEngine/CMakeFiles/tEngine.dir/requires: src/tEngine/CMakeFiles/tEngine.dir/tConfig.cpp.o.requires
src/tEngine/CMakeFiles/tEngine.dir/requires: src/tEngine/CMakeFiles/tEngine.dir/tEngine.cpp.o.requires
src/tEngine/CMakeFiles/tEngine.dir/requires: src/tEngine/CMakeFiles/tEngine.dir/tLog.cxx.o.requires
src/tEngine/CMakeFiles/tEngine.dir/requires: src/tEngine/CMakeFiles/tEngine.dir/tMemoryPool.cpp.o.requires
src/tEngine/CMakeFiles/tEngine.dir/requires: src/tEngine/CMakeFiles/tEngine.dir/tProccess.cpp.o.requires
src/tEngine/CMakeFiles/tEngine.dir/requires: src/tEngine/CMakeFiles/tEngine.dir/tThread.cpp.o.requires
src/tEngine/CMakeFiles/tEngine.dir/requires: src/tEngine/CMakeFiles/tEngine.dir/tThreadTask.cpp.o.requires
.PHONY : src/tEngine/CMakeFiles/tEngine.dir/requires

src/tEngine/CMakeFiles/tEngine.dir/clean:
	cd /mnt/hgfs/E/other/TServer/build/linux/src/tEngine && $(CMAKE_COMMAND) -P CMakeFiles/tEngine.dir/cmake_clean.cmake
.PHONY : src/tEngine/CMakeFiles/tEngine.dir/clean

src/tEngine/CMakeFiles/tEngine.dir/depend:
	cd /mnt/hgfs/E/other/TServer/build/linux && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/hgfs/E/other/TServer /mnt/hgfs/E/other/TServer/src/tEngine /mnt/hgfs/E/other/TServer/build/linux /mnt/hgfs/E/other/TServer/build/linux/src/tEngine /mnt/hgfs/E/other/TServer/build/linux/src/tEngine/CMakeFiles/tEngine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/tEngine/CMakeFiles/tEngine.dir/depend

