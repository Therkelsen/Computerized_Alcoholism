# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/therkelsen/Computerized_Alcoholism/Kinematics/RobotControl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/therkelsen/Computerized_Alcoholism/Kinematics/build-RobotControl-Desktop-Debug

# Include any dependencies generated for this target.
include CMakeFiles/RobotControl.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RobotControl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RobotControl.dir/flags.make

CMakeFiles/RobotControl.dir/main.cpp.o: CMakeFiles/RobotControl.dir/flags.make
CMakeFiles/RobotControl.dir/main.cpp.o: /home/therkelsen/Computerized_Alcoholism/Kinematics/RobotControl/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/therkelsen/Computerized_Alcoholism/Kinematics/build-RobotControl-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RobotControl.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RobotControl.dir/main.cpp.o -c /home/therkelsen/Computerized_Alcoholism/Kinematics/RobotControl/main.cpp

CMakeFiles/RobotControl.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RobotControl.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/therkelsen/Computerized_Alcoholism/Kinematics/RobotControl/main.cpp > CMakeFiles/RobotControl.dir/main.cpp.i

CMakeFiles/RobotControl.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RobotControl.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/therkelsen/Computerized_Alcoholism/Kinematics/RobotControl/main.cpp -o CMakeFiles/RobotControl.dir/main.cpp.s

# Object files for target RobotControl
RobotControl_OBJECTS = \
"CMakeFiles/RobotControl.dir/main.cpp.o"

# External object files for target RobotControl
RobotControl_EXTERNAL_OBJECTS =

RobotControl: CMakeFiles/RobotControl.dir/main.cpp.o
RobotControl: CMakeFiles/RobotControl.dir/build.make
RobotControl: /usr/lib/x86_64-linux-gnu/librtde.so.1.4.5
RobotControl: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
RobotControl: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
RobotControl: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.71.0
RobotControl: CMakeFiles/RobotControl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/therkelsen/Computerized_Alcoholism/Kinematics/build-RobotControl-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable RobotControl"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RobotControl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RobotControl.dir/build: RobotControl

.PHONY : CMakeFiles/RobotControl.dir/build

CMakeFiles/RobotControl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RobotControl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RobotControl.dir/clean

CMakeFiles/RobotControl.dir/depend:
	cd /home/therkelsen/Computerized_Alcoholism/Kinematics/build-RobotControl-Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/therkelsen/Computerized_Alcoholism/Kinematics/RobotControl /home/therkelsen/Computerized_Alcoholism/Kinematics/RobotControl /home/therkelsen/Computerized_Alcoholism/Kinematics/build-RobotControl-Desktop-Debug /home/therkelsen/Computerized_Alcoholism/Kinematics/build-RobotControl-Desktop-Debug /home/therkelsen/Computerized_Alcoholism/Kinematics/build-RobotControl-Desktop-Debug/CMakeFiles/RobotControl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RobotControl.dir/depend
