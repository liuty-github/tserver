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
CMAKE_SOURCE_DIR = /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux

# Include any dependencies generated for this target.
include src/tserver/CMakeFiles/tserver.dir/depend.make

# Include the progress variables for this target.
include src/tserver/CMakeFiles/tserver.dir/progress.make

# Include the compile flags for this target's objects.
include src/tserver/CMakeFiles/tserver.dir/flags.make

src/tserver/CMakeFiles/tserver.dir/tConfig.cpp.o: src/tserver/CMakeFiles/tserver.dir/flags.make
src/tserver/CMakeFiles/tserver.dir/tConfig.cpp.o: ../../src/tserver/tConfig.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/tserver/CMakeFiles/tserver.dir/tConfig.cpp.o"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tserver.dir/tConfig.cpp.o -c /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tConfig.cpp

src/tserver/CMakeFiles/tserver.dir/tConfig.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tserver.dir/tConfig.cpp.i"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tConfig.cpp > CMakeFiles/tserver.dir/tConfig.cpp.i

src/tserver/CMakeFiles/tserver.dir/tConfig.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tserver.dir/tConfig.cpp.s"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tConfig.cpp -o CMakeFiles/tserver.dir/tConfig.cpp.s

src/tserver/CMakeFiles/tserver.dir/tConfig.cpp.o.requires:
.PHONY : src/tserver/CMakeFiles/tserver.dir/tConfig.cpp.o.requires

src/tserver/CMakeFiles/tserver.dir/tConfig.cpp.o.provides: src/tserver/CMakeFiles/tserver.dir/tConfig.cpp.o.requires
	$(MAKE) -f src/tserver/CMakeFiles/tserver.dir/build.make src/tserver/CMakeFiles/tserver.dir/tConfig.cpp.o.provides.build
.PHONY : src/tserver/CMakeFiles/tserver.dir/tConfig.cpp.o.provides

src/tserver/CMakeFiles/tserver.dir/tConfig.cpp.o.provides.build: src/tserver/CMakeFiles/tserver.dir/tConfig.cpp.o

src/tserver/CMakeFiles/tserver.dir/tEngine.cpp.o: src/tserver/CMakeFiles/tserver.dir/flags.make
src/tserver/CMakeFiles/tserver.dir/tEngine.cpp.o: ../../src/tserver/tEngine.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/tserver/CMakeFiles/tserver.dir/tEngine.cpp.o"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tserver.dir/tEngine.cpp.o -c /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tEngine.cpp

src/tserver/CMakeFiles/tserver.dir/tEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tserver.dir/tEngine.cpp.i"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tEngine.cpp > CMakeFiles/tserver.dir/tEngine.cpp.i

src/tserver/CMakeFiles/tserver.dir/tEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tserver.dir/tEngine.cpp.s"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tEngine.cpp -o CMakeFiles/tserver.dir/tEngine.cpp.s

src/tserver/CMakeFiles/tserver.dir/tEngine.cpp.o.requires:
.PHONY : src/tserver/CMakeFiles/tserver.dir/tEngine.cpp.o.requires

src/tserver/CMakeFiles/tserver.dir/tEngine.cpp.o.provides: src/tserver/CMakeFiles/tserver.dir/tEngine.cpp.o.requires
	$(MAKE) -f src/tserver/CMakeFiles/tserver.dir/build.make src/tserver/CMakeFiles/tserver.dir/tEngine.cpp.o.provides.build
.PHONY : src/tserver/CMakeFiles/tserver.dir/tEngine.cpp.o.provides

src/tserver/CMakeFiles/tserver.dir/tEngine.cpp.o.provides.build: src/tserver/CMakeFiles/tserver.dir/tEngine.cpp.o

src/tserver/CMakeFiles/tserver.dir/tLog.cxx.o: src/tserver/CMakeFiles/tserver.dir/flags.make
src/tserver/CMakeFiles/tserver.dir/tLog.cxx.o: ../../src/tserver/tLog.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/tserver/CMakeFiles/tserver.dir/tLog.cxx.o"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tserver.dir/tLog.cxx.o -c /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tLog.cxx

src/tserver/CMakeFiles/tserver.dir/tLog.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tserver.dir/tLog.cxx.i"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tLog.cxx > CMakeFiles/tserver.dir/tLog.cxx.i

src/tserver/CMakeFiles/tserver.dir/tLog.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tserver.dir/tLog.cxx.s"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tLog.cxx -o CMakeFiles/tserver.dir/tLog.cxx.s

src/tserver/CMakeFiles/tserver.dir/tLog.cxx.o.requires:
.PHONY : src/tserver/CMakeFiles/tserver.dir/tLog.cxx.o.requires

src/tserver/CMakeFiles/tserver.dir/tLog.cxx.o.provides: src/tserver/CMakeFiles/tserver.dir/tLog.cxx.o.requires
	$(MAKE) -f src/tserver/CMakeFiles/tserver.dir/build.make src/tserver/CMakeFiles/tserver.dir/tLog.cxx.o.provides.build
.PHONY : src/tserver/CMakeFiles/tserver.dir/tLog.cxx.o.provides

src/tserver/CMakeFiles/tserver.dir/tLog.cxx.o.provides.build: src/tserver/CMakeFiles/tserver.dir/tLog.cxx.o

src/tserver/CMakeFiles/tserver.dir/tProccess.cpp.o: src/tserver/CMakeFiles/tserver.dir/flags.make
src/tserver/CMakeFiles/tserver.dir/tProccess.cpp.o: ../../src/tserver/tProccess.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/tserver/CMakeFiles/tserver.dir/tProccess.cpp.o"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tserver.dir/tProccess.cpp.o -c /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tProccess.cpp

src/tserver/CMakeFiles/tserver.dir/tProccess.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tserver.dir/tProccess.cpp.i"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tProccess.cpp > CMakeFiles/tserver.dir/tProccess.cpp.i

src/tserver/CMakeFiles/tserver.dir/tProccess.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tserver.dir/tProccess.cpp.s"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tProccess.cpp -o CMakeFiles/tserver.dir/tProccess.cpp.s

src/tserver/CMakeFiles/tserver.dir/tProccess.cpp.o.requires:
.PHONY : src/tserver/CMakeFiles/tserver.dir/tProccess.cpp.o.requires

src/tserver/CMakeFiles/tserver.dir/tProccess.cpp.o.provides: src/tserver/CMakeFiles/tserver.dir/tProccess.cpp.o.requires
	$(MAKE) -f src/tserver/CMakeFiles/tserver.dir/build.make src/tserver/CMakeFiles/tserver.dir/tProccess.cpp.o.provides.build
.PHONY : src/tserver/CMakeFiles/tserver.dir/tProccess.cpp.o.provides

src/tserver/CMakeFiles/tserver.dir/tProccess.cpp.o.provides.build: src/tserver/CMakeFiles/tserver.dir/tProccess.cpp.o

src/tserver/CMakeFiles/tserver.dir/tserver.cpp.o: src/tserver/CMakeFiles/tserver.dir/flags.make
src/tserver/CMakeFiles/tserver.dir/tserver.cpp.o: ../../src/tserver/tserver.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/tserver/CMakeFiles/tserver.dir/tserver.cpp.o"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tserver.dir/tserver.cpp.o -c /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tserver.cpp

src/tserver/CMakeFiles/tserver.dir/tserver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tserver.dir/tserver.cpp.i"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tserver.cpp > CMakeFiles/tserver.dir/tserver.cpp.i

src/tserver/CMakeFiles/tserver.dir/tserver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tserver.dir/tserver.cpp.s"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tserver.cpp -o CMakeFiles/tserver.dir/tserver.cpp.s

src/tserver/CMakeFiles/tserver.dir/tserver.cpp.o.requires:
.PHONY : src/tserver/CMakeFiles/tserver.dir/tserver.cpp.o.requires

src/tserver/CMakeFiles/tserver.dir/tserver.cpp.o.provides: src/tserver/CMakeFiles/tserver.dir/tserver.cpp.o.requires
	$(MAKE) -f src/tserver/CMakeFiles/tserver.dir/build.make src/tserver/CMakeFiles/tserver.dir/tserver.cpp.o.provides.build
.PHONY : src/tserver/CMakeFiles/tserver.dir/tserver.cpp.o.provides

src/tserver/CMakeFiles/tserver.dir/tserver.cpp.o.provides.build: src/tserver/CMakeFiles/tserver.dir/tserver.cpp.o

src/tserver/CMakeFiles/tserver.dir/tThread.cpp.o: src/tserver/CMakeFiles/tserver.dir/flags.make
src/tserver/CMakeFiles/tserver.dir/tThread.cpp.o: ../../src/tserver/tThread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/tserver/CMakeFiles/tserver.dir/tThread.cpp.o"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tserver.dir/tThread.cpp.o -c /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tThread.cpp

src/tserver/CMakeFiles/tserver.dir/tThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tserver.dir/tThread.cpp.i"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tThread.cpp > CMakeFiles/tserver.dir/tThread.cpp.i

src/tserver/CMakeFiles/tserver.dir/tThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tserver.dir/tThread.cpp.s"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tThread.cpp -o CMakeFiles/tserver.dir/tThread.cpp.s

src/tserver/CMakeFiles/tserver.dir/tThread.cpp.o.requires:
.PHONY : src/tserver/CMakeFiles/tserver.dir/tThread.cpp.o.requires

src/tserver/CMakeFiles/tserver.dir/tThread.cpp.o.provides: src/tserver/CMakeFiles/tserver.dir/tThread.cpp.o.requires
	$(MAKE) -f src/tserver/CMakeFiles/tserver.dir/build.make src/tserver/CMakeFiles/tserver.dir/tThread.cpp.o.provides.build
.PHONY : src/tserver/CMakeFiles/tserver.dir/tThread.cpp.o.provides

src/tserver/CMakeFiles/tserver.dir/tThread.cpp.o.provides.build: src/tserver/CMakeFiles/tserver.dir/tThread.cpp.o

src/tserver/CMakeFiles/tserver.dir/tThreadTask.cpp.o: src/tserver/CMakeFiles/tserver.dir/flags.make
src/tserver/CMakeFiles/tserver.dir/tThreadTask.cpp.o: ../../src/tserver/tThreadTask.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/tserver/CMakeFiles/tserver.dir/tThreadTask.cpp.o"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tserver.dir/tThreadTask.cpp.o -c /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tThreadTask.cpp

src/tserver/CMakeFiles/tserver.dir/tThreadTask.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tserver.dir/tThreadTask.cpp.i"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tThreadTask.cpp > CMakeFiles/tserver.dir/tThreadTask.cpp.i

src/tserver/CMakeFiles/tserver.dir/tThreadTask.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tserver.dir/tThreadTask.cpp.s"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/tThreadTask.cpp -o CMakeFiles/tserver.dir/tThreadTask.cpp.s

src/tserver/CMakeFiles/tserver.dir/tThreadTask.cpp.o.requires:
.PHONY : src/tserver/CMakeFiles/tserver.dir/tThreadTask.cpp.o.requires

src/tserver/CMakeFiles/tserver.dir/tThreadTask.cpp.o.provides: src/tserver/CMakeFiles/tserver.dir/tThreadTask.cpp.o.requires
	$(MAKE) -f src/tserver/CMakeFiles/tserver.dir/build.make src/tserver/CMakeFiles/tserver.dir/tThreadTask.cpp.o.provides.build
.PHONY : src/tserver/CMakeFiles/tserver.dir/tThreadTask.cpp.o.provides

src/tserver/CMakeFiles/tserver.dir/tThreadTask.cpp.o.provides.build: src/tserver/CMakeFiles/tserver.dir/tThreadTask.cpp.o

src/tserver/CMakeFiles/tserver.dir/v2vhttp_conn.cpp.o: src/tserver/CMakeFiles/tserver.dir/flags.make
src/tserver/CMakeFiles/tserver.dir/v2vhttp_conn.cpp.o: ../../src/tserver/v2vhttp_conn.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/tserver/CMakeFiles/tserver.dir/v2vhttp_conn.cpp.o"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tserver.dir/v2vhttp_conn.cpp.o -c /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/v2vhttp_conn.cpp

src/tserver/CMakeFiles/tserver.dir/v2vhttp_conn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tserver.dir/v2vhttp_conn.cpp.i"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/v2vhttp_conn.cpp > CMakeFiles/tserver.dir/v2vhttp_conn.cpp.i

src/tserver/CMakeFiles/tserver.dir/v2vhttp_conn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tserver.dir/v2vhttp_conn.cpp.s"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver/v2vhttp_conn.cpp -o CMakeFiles/tserver.dir/v2vhttp_conn.cpp.s

src/tserver/CMakeFiles/tserver.dir/v2vhttp_conn.cpp.o.requires:
.PHONY : src/tserver/CMakeFiles/tserver.dir/v2vhttp_conn.cpp.o.requires

src/tserver/CMakeFiles/tserver.dir/v2vhttp_conn.cpp.o.provides: src/tserver/CMakeFiles/tserver.dir/v2vhttp_conn.cpp.o.requires
	$(MAKE) -f src/tserver/CMakeFiles/tserver.dir/build.make src/tserver/CMakeFiles/tserver.dir/v2vhttp_conn.cpp.o.provides.build
.PHONY : src/tserver/CMakeFiles/tserver.dir/v2vhttp_conn.cpp.o.provides

src/tserver/CMakeFiles/tserver.dir/v2vhttp_conn.cpp.o.provides.build: src/tserver/CMakeFiles/tserver.dir/v2vhttp_conn.cpp.o

# Object files for target tserver
tserver_OBJECTS = \
"CMakeFiles/tserver.dir/tConfig.cpp.o" \
"CMakeFiles/tserver.dir/tEngine.cpp.o" \
"CMakeFiles/tserver.dir/tLog.cxx.o" \
"CMakeFiles/tserver.dir/tProccess.cpp.o" \
"CMakeFiles/tserver.dir/tserver.cpp.o" \
"CMakeFiles/tserver.dir/tThread.cpp.o" \
"CMakeFiles/tserver.dir/tThreadTask.cpp.o" \
"CMakeFiles/tserver.dir/v2vhttp_conn.cpp.o"

# External object files for target tserver
tserver_EXTERNAL_OBJECTS =

../tserver: src/tserver/CMakeFiles/tserver.dir/tConfig.cpp.o
../tserver: src/tserver/CMakeFiles/tserver.dir/tEngine.cpp.o
../tserver: src/tserver/CMakeFiles/tserver.dir/tLog.cxx.o
../tserver: src/tserver/CMakeFiles/tserver.dir/tProccess.cpp.o
../tserver: src/tserver/CMakeFiles/tserver.dir/tserver.cpp.o
../tserver: src/tserver/CMakeFiles/tserver.dir/tThread.cpp.o
../tserver: src/tserver/CMakeFiles/tserver.dir/tThreadTask.cpp.o
../tserver: src/tserver/CMakeFiles/tserver.dir/v2vhttp_conn.cpp.o
../tserver: src/tserver/CMakeFiles/tserver.dir/build.make
../tserver: src/tserver/CMakeFiles/tserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../tserver"
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/tserver/CMakeFiles/tserver.dir/build: ../tserver
.PHONY : src/tserver/CMakeFiles/tserver.dir/build

src/tserver/CMakeFiles/tserver.dir/requires: src/tserver/CMakeFiles/tserver.dir/tConfig.cpp.o.requires
src/tserver/CMakeFiles/tserver.dir/requires: src/tserver/CMakeFiles/tserver.dir/tEngine.cpp.o.requires
src/tserver/CMakeFiles/tserver.dir/requires: src/tserver/CMakeFiles/tserver.dir/tLog.cxx.o.requires
src/tserver/CMakeFiles/tserver.dir/requires: src/tserver/CMakeFiles/tserver.dir/tProccess.cpp.o.requires
src/tserver/CMakeFiles/tserver.dir/requires: src/tserver/CMakeFiles/tserver.dir/tserver.cpp.o.requires
src/tserver/CMakeFiles/tserver.dir/requires: src/tserver/CMakeFiles/tserver.dir/tThread.cpp.o.requires
src/tserver/CMakeFiles/tserver.dir/requires: src/tserver/CMakeFiles/tserver.dir/tThreadTask.cpp.o.requires
src/tserver/CMakeFiles/tserver.dir/requires: src/tserver/CMakeFiles/tserver.dir/v2vhttp_conn.cpp.o.requires
.PHONY : src/tserver/CMakeFiles/tserver.dir/requires

src/tserver/CMakeFiles/tserver.dir/clean:
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver && $(CMAKE_COMMAND) -P CMakeFiles/tserver.dir/cmake_clean.cmake
.PHONY : src/tserver/CMakeFiles/tserver.dir/clean

src/tserver/CMakeFiles/tserver.dir/depend:
	cd /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/src/tserver /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver /mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build/linux/src/tserver/CMakeFiles/tserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/tserver/CMakeFiles/tserver.dir/depend

