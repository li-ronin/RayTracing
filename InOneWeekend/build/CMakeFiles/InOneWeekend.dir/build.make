# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.28

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = E:\ENV\cmake\bin\cmake.exe

# The command to remove a file.
RM = E:\ENV\cmake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\Project\vsCode\RayTracing\InOneWeekend

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Project\vsCode\RayTracing\InOneWeekend\build

# Include any dependencies generated for this target.
include CMakeFiles/InOneWeekend.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/InOneWeekend.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/InOneWeekend.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/InOneWeekend.dir/flags.make

CMakeFiles/InOneWeekend.dir/src/inoneweekend.cpp.obj: CMakeFiles/InOneWeekend.dir/flags.make
CMakeFiles/InOneWeekend.dir/src/inoneweekend.cpp.obj: CMakeFiles/InOneWeekend.dir/includes_CXX.rsp
CMakeFiles/InOneWeekend.dir/src/inoneweekend.cpp.obj: E:/Project/vsCode/RayTracing/InOneWeekend/src/inoneweekend.cpp
CMakeFiles/InOneWeekend.dir/src/inoneweekend.cpp.obj: CMakeFiles/InOneWeekend.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=E:\Project\vsCode\RayTracing\InOneWeekend\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/InOneWeekend.dir/src/inoneweekend.cpp.obj"
	E:\ENV\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/InOneWeekend.dir/src/inoneweekend.cpp.obj -MF CMakeFiles\InOneWeekend.dir\src\inoneweekend.cpp.obj.d -o CMakeFiles\InOneWeekend.dir\src\inoneweekend.cpp.obj -c E:\Project\vsCode\RayTracing\InOneWeekend\src\inoneweekend.cpp

CMakeFiles/InOneWeekend.dir/src/inoneweekend.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/InOneWeekend.dir/src/inoneweekend.cpp.i"
	E:\ENV\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Project\vsCode\RayTracing\InOneWeekend\src\inoneweekend.cpp > CMakeFiles\InOneWeekend.dir\src\inoneweekend.cpp.i

CMakeFiles/InOneWeekend.dir/src/inoneweekend.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/InOneWeekend.dir/src/inoneweekend.cpp.s"
	E:\ENV\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Project\vsCode\RayTracing\InOneWeekend\src\inoneweekend.cpp -o CMakeFiles\InOneWeekend.dir\src\inoneweekend.cpp.s

# Object files for target InOneWeekend
InOneWeekend_OBJECTS = \
"CMakeFiles/InOneWeekend.dir/src/inoneweekend.cpp.obj"

# External object files for target InOneWeekend
InOneWeekend_EXTERNAL_OBJECTS =

E:/Project/vsCode/RayTracing/InOneWeekend/bin/InOneWeekend.exe: CMakeFiles/InOneWeekend.dir/src/inoneweekend.cpp.obj
E:/Project/vsCode/RayTracing/InOneWeekend/bin/InOneWeekend.exe: CMakeFiles/InOneWeekend.dir/build.make
E:/Project/vsCode/RayTracing/InOneWeekend/bin/InOneWeekend.exe: CMakeFiles/InOneWeekend.dir/linkLibs.rsp
E:/Project/vsCode/RayTracing/InOneWeekend/bin/InOneWeekend.exe: CMakeFiles/InOneWeekend.dir/objects1.rsp
E:/Project/vsCode/RayTracing/InOneWeekend/bin/InOneWeekend.exe: CMakeFiles/InOneWeekend.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=E:\Project\vsCode\RayTracing\InOneWeekend\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable E:\Project\vsCode\RayTracing\InOneWeekend\bin\InOneWeekend.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\InOneWeekend.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/InOneWeekend.dir/build: E:/Project/vsCode/RayTracing/InOneWeekend/bin/InOneWeekend.exe
.PHONY : CMakeFiles/InOneWeekend.dir/build

CMakeFiles/InOneWeekend.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\InOneWeekend.dir\cmake_clean.cmake
.PHONY : CMakeFiles/InOneWeekend.dir/clean

CMakeFiles/InOneWeekend.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Project\vsCode\RayTracing\InOneWeekend E:\Project\vsCode\RayTracing\InOneWeekend E:\Project\vsCode\RayTracing\InOneWeekend\build E:\Project\vsCode\RayTracing\InOneWeekend\build E:\Project\vsCode\RayTracing\InOneWeekend\build\CMakeFiles\InOneWeekend.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/InOneWeekend.dir/depend
