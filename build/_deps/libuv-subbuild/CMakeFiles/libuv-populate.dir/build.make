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
CMAKE_SOURCE_DIR = /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild

# Utility rule file for libuv-populate.

# Include any custom commands dependencies for this target.
include CMakeFiles/libuv-populate.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/libuv-populate.dir/progress.make

CMakeFiles/libuv-populate: CMakeFiles/libuv-populate-complete

CMakeFiles/libuv-populate-complete: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-install
CMakeFiles/libuv-populate-complete: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-mkdir
CMakeFiles/libuv-populate-complete: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-download
CMakeFiles/libuv-populate-complete: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-update
CMakeFiles/libuv-populate-complete: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-patch
CMakeFiles/libuv-populate-complete: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-configure
CMakeFiles/libuv-populate-complete: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-build
CMakeFiles/libuv-populate-complete: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-install
CMakeFiles/libuv-populate-complete: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-test
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'libuv-populate'"
	/usr/bin/cmake -E make_directory /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/CMakeFiles
	/usr/bin/cmake -E touch /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/CMakeFiles/libuv-populate-complete
	/usr/bin/cmake -E touch /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-done

libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-update:
.PHONY : libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-update

libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-build: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No build step for 'libuv-populate'"
	cd /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-build && /usr/bin/cmake -E echo_append
	cd /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-build && /usr/bin/cmake -E touch /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-build

libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-configure: libuv-populate-prefix/tmp/libuv-populate-cfgcmd.txt
libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-configure: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "No configure step for 'libuv-populate'"
	cd /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-build && /usr/bin/cmake -E echo_append
	cd /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-build && /usr/bin/cmake -E touch /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-configure

libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-download: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-gitinfo.txt
libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-download: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'libuv-populate'"
	cd /media/shanfl/KINGSTON/Server4Poker/build/_deps && /usr/bin/cmake -P /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/libuv-populate-prefix/tmp/libuv-populate-gitclone.cmake
	cd /media/shanfl/KINGSTON/Server4Poker/build/_deps && /usr/bin/cmake -E touch /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-download

libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-install: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No install step for 'libuv-populate'"
	cd /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-build && /usr/bin/cmake -E echo_append
	cd /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-build && /usr/bin/cmake -E touch /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-install

libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'libuv-populate'"
	/usr/bin/cmake -E make_directory /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-src
	/usr/bin/cmake -E make_directory /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-build
	/usr/bin/cmake -E make_directory /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/libuv-populate-prefix
	/usr/bin/cmake -E make_directory /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/libuv-populate-prefix/tmp
	/usr/bin/cmake -E make_directory /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/libuv-populate-prefix/src/libuv-populate-stamp
	/usr/bin/cmake -E make_directory /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/libuv-populate-prefix/src
	/usr/bin/cmake -E make_directory /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/libuv-populate-prefix/src/libuv-populate-stamp
	/usr/bin/cmake -E touch /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-mkdir

libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-patch: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-update
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'libuv-populate'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-patch

libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-update:
.PHONY : libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-update

libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-test: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No test step for 'libuv-populate'"
	cd /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-build && /usr/bin/cmake -E echo_append
	cd /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-build && /usr/bin/cmake -E touch /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-test

libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-update: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Performing update step for 'libuv-populate'"
	cd /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-src && /usr/bin/cmake -P /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/libuv-populate-prefix/tmp/libuv-populate-gitupdate.cmake

libuv-populate: CMakeFiles/libuv-populate
libuv-populate: CMakeFiles/libuv-populate-complete
libuv-populate: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-build
libuv-populate: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-configure
libuv-populate: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-download
libuv-populate: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-install
libuv-populate: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-mkdir
libuv-populate: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-patch
libuv-populate: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-test
libuv-populate: libuv-populate-prefix/src/libuv-populate-stamp/libuv-populate-update
libuv-populate: CMakeFiles/libuv-populate.dir/build.make
.PHONY : libuv-populate

# Rule to build all files generated by this target.
CMakeFiles/libuv-populate.dir/build: libuv-populate
.PHONY : CMakeFiles/libuv-populate.dir/build

CMakeFiles/libuv-populate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libuv-populate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libuv-populate.dir/clean

CMakeFiles/libuv-populate.dir/depend:
	cd /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild /media/shanfl/KINGSTON/Server4Poker/build/_deps/libuv-subbuild/CMakeFiles/libuv-populate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libuv-populate.dir/depend

