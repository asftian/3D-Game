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
CMAKE_SOURCE_DIR = /home/felix/Downloads/glbase/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/felix/Downloads/glbase/src/cmakebuild

# Include any dependencies generated for this target.
include glbase/CMakeFiles/glbase.dir/depend.make

# Include the progress variables for this target.
include glbase/CMakeFiles/glbase.dir/progress.make

# Include the compile flags for this target's objects.
include glbase/CMakeFiles/glbase.dir/flags.make

glbase/CMakeFiles/glbase.dir/tp1.cpp.o: glbase/CMakeFiles/glbase.dir/flags.make
glbase/CMakeFiles/glbase.dir/tp1.cpp.o: ../glbase/tp1.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/felix/Downloads/glbase/src/cmakebuild/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object glbase/CMakeFiles/glbase.dir/tp1.cpp.o"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/glbase.dir/tp1.cpp.o -c /home/felix/Downloads/glbase/src/glbase/tp1.cpp

glbase/CMakeFiles/glbase.dir/tp1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glbase.dir/tp1.cpp.i"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/felix/Downloads/glbase/src/glbase/tp1.cpp > CMakeFiles/glbase.dir/tp1.cpp.i

glbase/CMakeFiles/glbase.dir/tp1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glbase.dir/tp1.cpp.s"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/felix/Downloads/glbase/src/glbase/tp1.cpp -o CMakeFiles/glbase.dir/tp1.cpp.s

glbase/CMakeFiles/glbase.dir/tp1.cpp.o.requires:
.PHONY : glbase/CMakeFiles/glbase.dir/tp1.cpp.o.requires

glbase/CMakeFiles/glbase.dir/tp1.cpp.o.provides: glbase/CMakeFiles/glbase.dir/tp1.cpp.o.requires
	$(MAKE) -f glbase/CMakeFiles/glbase.dir/build.make glbase/CMakeFiles/glbase.dir/tp1.cpp.o.provides.build
.PHONY : glbase/CMakeFiles/glbase.dir/tp1.cpp.o.provides

glbase/CMakeFiles/glbase.dir/tp1.cpp.o.provides.build: glbase/CMakeFiles/glbase.dir/tp1.cpp.o

glbase/CMakeFiles/glbase.dir/log.cpp.o: glbase/CMakeFiles/glbase.dir/flags.make
glbase/CMakeFiles/glbase.dir/log.cpp.o: ../glbase/log.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/felix/Downloads/glbase/src/cmakebuild/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object glbase/CMakeFiles/glbase.dir/log.cpp.o"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/glbase.dir/log.cpp.o -c /home/felix/Downloads/glbase/src/glbase/log.cpp

glbase/CMakeFiles/glbase.dir/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glbase.dir/log.cpp.i"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/felix/Downloads/glbase/src/glbase/log.cpp > CMakeFiles/glbase.dir/log.cpp.i

glbase/CMakeFiles/glbase.dir/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glbase.dir/log.cpp.s"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/felix/Downloads/glbase/src/glbase/log.cpp -o CMakeFiles/glbase.dir/log.cpp.s

glbase/CMakeFiles/glbase.dir/log.cpp.o.requires:
.PHONY : glbase/CMakeFiles/glbase.dir/log.cpp.o.requires

glbase/CMakeFiles/glbase.dir/log.cpp.o.provides: glbase/CMakeFiles/glbase.dir/log.cpp.o.requires
	$(MAKE) -f glbase/CMakeFiles/glbase.dir/build.make glbase/CMakeFiles/glbase.dir/log.cpp.o.provides.build
.PHONY : glbase/CMakeFiles/glbase.dir/log.cpp.o.provides

glbase/CMakeFiles/glbase.dir/log.cpp.o.provides.build: glbase/CMakeFiles/glbase.dir/log.cpp.o

glbase/CMakeFiles/glbase.dir/main.cpp.o: glbase/CMakeFiles/glbase.dir/flags.make
glbase/CMakeFiles/glbase.dir/main.cpp.o: ../glbase/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/felix/Downloads/glbase/src/cmakebuild/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object glbase/CMakeFiles/glbase.dir/main.cpp.o"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/glbase.dir/main.cpp.o -c /home/felix/Downloads/glbase/src/glbase/main.cpp

glbase/CMakeFiles/glbase.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glbase.dir/main.cpp.i"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/felix/Downloads/glbase/src/glbase/main.cpp > CMakeFiles/glbase.dir/main.cpp.i

glbase/CMakeFiles/glbase.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glbase.dir/main.cpp.s"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/felix/Downloads/glbase/src/glbase/main.cpp -o CMakeFiles/glbase.dir/main.cpp.s

glbase/CMakeFiles/glbase.dir/main.cpp.o.requires:
.PHONY : glbase/CMakeFiles/glbase.dir/main.cpp.o.requires

glbase/CMakeFiles/glbase.dir/main.cpp.o.provides: glbase/CMakeFiles/glbase.dir/main.cpp.o.requires
	$(MAKE) -f glbase/CMakeFiles/glbase.dir/build.make glbase/CMakeFiles/glbase.dir/main.cpp.o.provides.build
.PHONY : glbase/CMakeFiles/glbase.dir/main.cpp.o.provides

glbase/CMakeFiles/glbase.dir/main.cpp.o.provides.build: glbase/CMakeFiles/glbase.dir/main.cpp.o

glbase/CMakeFiles/glbase.dir/scene.cpp.o: glbase/CMakeFiles/glbase.dir/flags.make
glbase/CMakeFiles/glbase.dir/scene.cpp.o: ../glbase/scene.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/felix/Downloads/glbase/src/cmakebuild/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object glbase/CMakeFiles/glbase.dir/scene.cpp.o"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/glbase.dir/scene.cpp.o -c /home/felix/Downloads/glbase/src/glbase/scene.cpp

glbase/CMakeFiles/glbase.dir/scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glbase.dir/scene.cpp.i"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/felix/Downloads/glbase/src/glbase/scene.cpp > CMakeFiles/glbase.dir/scene.cpp.i

glbase/CMakeFiles/glbase.dir/scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glbase.dir/scene.cpp.s"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/felix/Downloads/glbase/src/glbase/scene.cpp -o CMakeFiles/glbase.dir/scene.cpp.s

glbase/CMakeFiles/glbase.dir/scene.cpp.o.requires:
.PHONY : glbase/CMakeFiles/glbase.dir/scene.cpp.o.requires

glbase/CMakeFiles/glbase.dir/scene.cpp.o.provides: glbase/CMakeFiles/glbase.dir/scene.cpp.o.requires
	$(MAKE) -f glbase/CMakeFiles/glbase.dir/build.make glbase/CMakeFiles/glbase.dir/scene.cpp.o.provides.build
.PHONY : glbase/CMakeFiles/glbase.dir/scene.cpp.o.provides

glbase/CMakeFiles/glbase.dir/scene.cpp.o.provides.build: glbase/CMakeFiles/glbase.dir/scene.cpp.o

glbase/CMakeFiles/glbase.dir/misc.cpp.o: glbase/CMakeFiles/glbase.dir/flags.make
glbase/CMakeFiles/glbase.dir/misc.cpp.o: ../glbase/misc.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/felix/Downloads/glbase/src/cmakebuild/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object glbase/CMakeFiles/glbase.dir/misc.cpp.o"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/glbase.dir/misc.cpp.o -c /home/felix/Downloads/glbase/src/glbase/misc.cpp

glbase/CMakeFiles/glbase.dir/misc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glbase.dir/misc.cpp.i"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/felix/Downloads/glbase/src/glbase/misc.cpp > CMakeFiles/glbase.dir/misc.cpp.i

glbase/CMakeFiles/glbase.dir/misc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glbase.dir/misc.cpp.s"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/felix/Downloads/glbase/src/glbase/misc.cpp -o CMakeFiles/glbase.dir/misc.cpp.s

glbase/CMakeFiles/glbase.dir/misc.cpp.o.requires:
.PHONY : glbase/CMakeFiles/glbase.dir/misc.cpp.o.requires

glbase/CMakeFiles/glbase.dir/misc.cpp.o.provides: glbase/CMakeFiles/glbase.dir/misc.cpp.o.requires
	$(MAKE) -f glbase/CMakeFiles/glbase.dir/build.make glbase/CMakeFiles/glbase.dir/misc.cpp.o.provides.build
.PHONY : glbase/CMakeFiles/glbase.dir/misc.cpp.o.provides

glbase/CMakeFiles/glbase.dir/misc.cpp.o.provides.build: glbase/CMakeFiles/glbase.dir/misc.cpp.o

glbase/CMakeFiles/glbase.dir/core.cpp.o: glbase/CMakeFiles/glbase.dir/flags.make
glbase/CMakeFiles/glbase.dir/core.cpp.o: ../glbase/core.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/felix/Downloads/glbase/src/cmakebuild/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object glbase/CMakeFiles/glbase.dir/core.cpp.o"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/glbase.dir/core.cpp.o -c /home/felix/Downloads/glbase/src/glbase/core.cpp

glbase/CMakeFiles/glbase.dir/core.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glbase.dir/core.cpp.i"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/felix/Downloads/glbase/src/glbase/core.cpp > CMakeFiles/glbase.dir/core.cpp.i

glbase/CMakeFiles/glbase.dir/core.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glbase.dir/core.cpp.s"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/felix/Downloads/glbase/src/glbase/core.cpp -o CMakeFiles/glbase.dir/core.cpp.s

glbase/CMakeFiles/glbase.dir/core.cpp.o.requires:
.PHONY : glbase/CMakeFiles/glbase.dir/core.cpp.o.requires

glbase/CMakeFiles/glbase.dir/core.cpp.o.provides: glbase/CMakeFiles/glbase.dir/core.cpp.o.requires
	$(MAKE) -f glbase/CMakeFiles/glbase.dir/build.make glbase/CMakeFiles/glbase.dir/core.cpp.o.provides.build
.PHONY : glbase/CMakeFiles/glbase.dir/core.cpp.o.provides

glbase/CMakeFiles/glbase.dir/core.cpp.o.provides.build: glbase/CMakeFiles/glbase.dir/core.cpp.o

# Object files for target glbase
glbase_OBJECTS = \
"CMakeFiles/glbase.dir/tp1.cpp.o" \
"CMakeFiles/glbase.dir/log.cpp.o" \
"CMakeFiles/glbase.dir/main.cpp.o" \
"CMakeFiles/glbase.dir/scene.cpp.o" \
"CMakeFiles/glbase.dir/misc.cpp.o" \
"CMakeFiles/glbase.dir/core.cpp.o"

# External object files for target glbase
glbase_EXTERNAL_OBJECTS =

/home/felix/Downloads/glbase/build/Debug/glbase: glbase/CMakeFiles/glbase.dir/tp1.cpp.o
/home/felix/Downloads/glbase/build/Debug/glbase: glbase/CMakeFiles/glbase.dir/log.cpp.o
/home/felix/Downloads/glbase/build/Debug/glbase: glbase/CMakeFiles/glbase.dir/main.cpp.o
/home/felix/Downloads/glbase/build/Debug/glbase: glbase/CMakeFiles/glbase.dir/scene.cpp.o
/home/felix/Downloads/glbase/build/Debug/glbase: glbase/CMakeFiles/glbase.dir/misc.cpp.o
/home/felix/Downloads/glbase/build/Debug/glbase: glbase/CMakeFiles/glbase.dir/core.cpp.o
/home/felix/Downloads/glbase/build/Debug/glbase: glbase/CMakeFiles/glbase.dir/build.make
/home/felix/Downloads/glbase/build/Debug/glbase: glfw/lib.a
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libGLU.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libX11.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libXrandr.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libXi.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/librt.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libm.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libGL.so
/home/felix/Downloads/glbase/build/Debug/glbase: glfw/lib.a
/home/felix/Downloads/glbase/build/Debug/glbase: glew/libglew.a
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libGLU.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libGL.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libSM.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libICE.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libX11.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libXext.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libGLU.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libXrandr.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libXi.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/librt.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libm.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libGL.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libSM.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libICE.so
/home/felix/Downloads/glbase/build/Debug/glbase: /usr/lib/x86_64-linux-gnu/libXext.so
/home/felix/Downloads/glbase/build/Debug/glbase: glbase/CMakeFiles/glbase.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /home/felix/Downloads/glbase/build/Debug/glbase"
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glbase.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
glbase/CMakeFiles/glbase.dir/build: /home/felix/Downloads/glbase/build/Debug/glbase
.PHONY : glbase/CMakeFiles/glbase.dir/build

glbase/CMakeFiles/glbase.dir/requires: glbase/CMakeFiles/glbase.dir/tp1.cpp.o.requires
glbase/CMakeFiles/glbase.dir/requires: glbase/CMakeFiles/glbase.dir/log.cpp.o.requires
glbase/CMakeFiles/glbase.dir/requires: glbase/CMakeFiles/glbase.dir/main.cpp.o.requires
glbase/CMakeFiles/glbase.dir/requires: glbase/CMakeFiles/glbase.dir/scene.cpp.o.requires
glbase/CMakeFiles/glbase.dir/requires: glbase/CMakeFiles/glbase.dir/misc.cpp.o.requires
glbase/CMakeFiles/glbase.dir/requires: glbase/CMakeFiles/glbase.dir/core.cpp.o.requires
.PHONY : glbase/CMakeFiles/glbase.dir/requires

glbase/CMakeFiles/glbase.dir/clean:
	cd /home/felix/Downloads/glbase/src/cmakebuild/glbase && $(CMAKE_COMMAND) -P CMakeFiles/glbase.dir/cmake_clean.cmake
.PHONY : glbase/CMakeFiles/glbase.dir/clean

glbase/CMakeFiles/glbase.dir/depend:
	cd /home/felix/Downloads/glbase/src/cmakebuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/felix/Downloads/glbase/src /home/felix/Downloads/glbase/src/glbase /home/felix/Downloads/glbase/src/cmakebuild /home/felix/Downloads/glbase/src/cmakebuild/glbase /home/felix/Downloads/glbase/src/cmakebuild/glbase/CMakeFiles/glbase.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : glbase/CMakeFiles/glbase.dir/depend

