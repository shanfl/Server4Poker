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
CMAKE_SOURCE_DIR = /media/shanfl/KINGSTON/Server4Poker

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/shanfl/KINGSTON/Server4Poker/build

# Include any dependencies generated for this target.
include CMakeFiles/BaseServer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/BaseServer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/BaseServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BaseServer.dir/flags.make

CMakeFiles/BaseServer.dir/Msg.def.o: CMakeFiles/BaseServer.dir/flags.make
CMakeFiles/BaseServer.dir/Msg.def.o: ../Msg.def.cpp
CMakeFiles/BaseServer.dir/Msg.def.o: CMakeFiles/BaseServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/shanfl/KINGSTON/Server4Poker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BaseServer.dir/Msg.def.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BaseServer.dir/Msg.def.o -MF CMakeFiles/BaseServer.dir/Msg.def.o.d -o CMakeFiles/BaseServer.dir/Msg.def.o -c /media/shanfl/KINGSTON/Server4Poker/Msg.def.cpp

CMakeFiles/BaseServer.dir/Msg.def.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BaseServer.dir/Msg.def.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/shanfl/KINGSTON/Server4Poker/Msg.def.cpp > CMakeFiles/BaseServer.dir/Msg.def.i

CMakeFiles/BaseServer.dir/Msg.def.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BaseServer.dir/Msg.def.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/shanfl/KINGSTON/Server4Poker/Msg.def.cpp -o CMakeFiles/BaseServer.dir/Msg.def.s

CMakeFiles/BaseServer.dir/ServerBase.o: CMakeFiles/BaseServer.dir/flags.make
CMakeFiles/BaseServer.dir/ServerBase.o: ../ServerBase.cpp
CMakeFiles/BaseServer.dir/ServerBase.o: CMakeFiles/BaseServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/shanfl/KINGSTON/Server4Poker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/BaseServer.dir/ServerBase.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BaseServer.dir/ServerBase.o -MF CMakeFiles/BaseServer.dir/ServerBase.o.d -o CMakeFiles/BaseServer.dir/ServerBase.o -c /media/shanfl/KINGSTON/Server4Poker/ServerBase.cpp

CMakeFiles/BaseServer.dir/ServerBase.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BaseServer.dir/ServerBase.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/shanfl/KINGSTON/Server4Poker/ServerBase.cpp > CMakeFiles/BaseServer.dir/ServerBase.i

CMakeFiles/BaseServer.dir/ServerBase.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BaseServer.dir/ServerBase.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/shanfl/KINGSTON/Server4Poker/ServerBase.cpp -o CMakeFiles/BaseServer.dir/ServerBase.s

CMakeFiles/BaseServer.dir/Thread.o: CMakeFiles/BaseServer.dir/flags.make
CMakeFiles/BaseServer.dir/Thread.o: ../Thread.cpp
CMakeFiles/BaseServer.dir/Thread.o: CMakeFiles/BaseServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/shanfl/KINGSTON/Server4Poker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/BaseServer.dir/Thread.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BaseServer.dir/Thread.o -MF CMakeFiles/BaseServer.dir/Thread.o.d -o CMakeFiles/BaseServer.dir/Thread.o -c /media/shanfl/KINGSTON/Server4Poker/Thread.cpp

CMakeFiles/BaseServer.dir/Thread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BaseServer.dir/Thread.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/shanfl/KINGSTON/Server4Poker/Thread.cpp > CMakeFiles/BaseServer.dir/Thread.i

CMakeFiles/BaseServer.dir/Thread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BaseServer.dir/Thread.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/shanfl/KINGSTON/Server4Poker/Thread.cpp -o CMakeFiles/BaseServer.dir/Thread.s

CMakeFiles/BaseServer.dir/TimerListener.o: CMakeFiles/BaseServer.dir/flags.make
CMakeFiles/BaseServer.dir/TimerListener.o: ../TimerListener.cpp
CMakeFiles/BaseServer.dir/TimerListener.o: CMakeFiles/BaseServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/shanfl/KINGSTON/Server4Poker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/BaseServer.dir/TimerListener.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BaseServer.dir/TimerListener.o -MF CMakeFiles/BaseServer.dir/TimerListener.o.d -o CMakeFiles/BaseServer.dir/TimerListener.o -c /media/shanfl/KINGSTON/Server4Poker/TimerListener.cpp

CMakeFiles/BaseServer.dir/TimerListener.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BaseServer.dir/TimerListener.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/shanfl/KINGSTON/Server4Poker/TimerListener.cpp > CMakeFiles/BaseServer.dir/TimerListener.i

CMakeFiles/BaseServer.dir/TimerListener.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BaseServer.dir/TimerListener.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/shanfl/KINGSTON/Server4Poker/TimerListener.cpp -o CMakeFiles/BaseServer.dir/TimerListener.s

CMakeFiles/BaseServer.dir/AsyncUvw.o: CMakeFiles/BaseServer.dir/flags.make
CMakeFiles/BaseServer.dir/AsyncUvw.o: ../AsyncUvw.cpp
CMakeFiles/BaseServer.dir/AsyncUvw.o: CMakeFiles/BaseServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/shanfl/KINGSTON/Server4Poker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/BaseServer.dir/AsyncUvw.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BaseServer.dir/AsyncUvw.o -MF CMakeFiles/BaseServer.dir/AsyncUvw.o.d -o CMakeFiles/BaseServer.dir/AsyncUvw.o -c /media/shanfl/KINGSTON/Server4Poker/AsyncUvw.cpp

CMakeFiles/BaseServer.dir/AsyncUvw.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BaseServer.dir/AsyncUvw.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/shanfl/KINGSTON/Server4Poker/AsyncUvw.cpp > CMakeFiles/BaseServer.dir/AsyncUvw.i

CMakeFiles/BaseServer.dir/AsyncUvw.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BaseServer.dir/AsyncUvw.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/shanfl/KINGSTON/Server4Poker/AsyncUvw.cpp -o CMakeFiles/BaseServer.dir/AsyncUvw.s

CMakeFiles/BaseServer.dir/gen_proto/BaseMsg.pb.o: CMakeFiles/BaseServer.dir/flags.make
CMakeFiles/BaseServer.dir/gen_proto/BaseMsg.pb.o: ../gen_proto/BaseMsg.pb.cc
CMakeFiles/BaseServer.dir/gen_proto/BaseMsg.pb.o: CMakeFiles/BaseServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/shanfl/KINGSTON/Server4Poker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/BaseServer.dir/gen_proto/BaseMsg.pb.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BaseServer.dir/gen_proto/BaseMsg.pb.o -MF CMakeFiles/BaseServer.dir/gen_proto/BaseMsg.pb.o.d -o CMakeFiles/BaseServer.dir/gen_proto/BaseMsg.pb.o -c /media/shanfl/KINGSTON/Server4Poker/gen_proto/BaseMsg.pb.cc

CMakeFiles/BaseServer.dir/gen_proto/BaseMsg.pb.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BaseServer.dir/gen_proto/BaseMsg.pb.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/shanfl/KINGSTON/Server4Poker/gen_proto/BaseMsg.pb.cc > CMakeFiles/BaseServer.dir/gen_proto/BaseMsg.pb.i

CMakeFiles/BaseServer.dir/gen_proto/BaseMsg.pb.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BaseServer.dir/gen_proto/BaseMsg.pb.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/shanfl/KINGSTON/Server4Poker/gen_proto/BaseMsg.pb.cc -o CMakeFiles/BaseServer.dir/gen_proto/BaseMsg.pb.s

# Object files for target BaseServer
BaseServer_OBJECTS = \
"CMakeFiles/BaseServer.dir/Msg.def.o" \
"CMakeFiles/BaseServer.dir/ServerBase.o" \
"CMakeFiles/BaseServer.dir/Thread.o" \
"CMakeFiles/BaseServer.dir/TimerListener.o" \
"CMakeFiles/BaseServer.dir/AsyncUvw.o" \
"CMakeFiles/BaseServer.dir/gen_proto/BaseMsg.pb.o"

# External object files for target BaseServer
BaseServer_EXTERNAL_OBJECTS =

libBaseServer.a: CMakeFiles/BaseServer.dir/Msg.def.o
libBaseServer.a: CMakeFiles/BaseServer.dir/ServerBase.o
libBaseServer.a: CMakeFiles/BaseServer.dir/Thread.o
libBaseServer.a: CMakeFiles/BaseServer.dir/TimerListener.o
libBaseServer.a: CMakeFiles/BaseServer.dir/AsyncUvw.o
libBaseServer.a: CMakeFiles/BaseServer.dir/gen_proto/BaseMsg.pb.o
libBaseServer.a: CMakeFiles/BaseServer.dir/build.make
libBaseServer.a: CMakeFiles/BaseServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/shanfl/KINGSTON/Server4Poker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library libBaseServer.a"
	$(CMAKE_COMMAND) -P CMakeFiles/BaseServer.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BaseServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BaseServer.dir/build: libBaseServer.a
.PHONY : CMakeFiles/BaseServer.dir/build

CMakeFiles/BaseServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BaseServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BaseServer.dir/clean

CMakeFiles/BaseServer.dir/depend:
	cd /media/shanfl/KINGSTON/Server4Poker/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/shanfl/KINGSTON/Server4Poker /media/shanfl/KINGSTON/Server4Poker /media/shanfl/KINGSTON/Server4Poker/build /media/shanfl/KINGSTON/Server4Poker/build /media/shanfl/KINGSTON/Server4Poker/build/CMakeFiles/BaseServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BaseServer.dir/depend

