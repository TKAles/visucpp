# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/tka/source/visucpp/visucpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tka/source/visucpp/visucpp/build/Desktop-Debug

# Include any dependencies generated for this target.
include CMakeFiles/visucpp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/visucpp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/visucpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/visucpp.dir/flags.make

visucpp_autogen/timestamp: /usr/lib64/qt6/libexec/moc
visucpp_autogen/timestamp: /usr/lib64/qt6/libexec/uic
visucpp_autogen/timestamp: CMakeFiles/visucpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/tka/source/visucpp/visucpp/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target visucpp"
	/usr/bin/cmake -E cmake_autogen /home/tka/source/visucpp/visucpp/build/Desktop-Debug/CMakeFiles/visucpp_autogen.dir/AutogenInfo.json Debug
	/usr/bin/cmake -E touch /home/tka/source/visucpp/visucpp/build/Desktop-Debug/visucpp_autogen/timestamp

CMakeFiles/visucpp.dir/visucpp_autogen/mocs_compilation.cpp.o: CMakeFiles/visucpp.dir/flags.make
CMakeFiles/visucpp.dir/visucpp_autogen/mocs_compilation.cpp.o: visucpp_autogen/mocs_compilation.cpp
CMakeFiles/visucpp.dir/visucpp_autogen/mocs_compilation.cpp.o: CMakeFiles/visucpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tka/source/visucpp/visucpp/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/visucpp.dir/visucpp_autogen/mocs_compilation.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/visucpp.dir/visucpp_autogen/mocs_compilation.cpp.o -MF CMakeFiles/visucpp.dir/visucpp_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/visucpp.dir/visucpp_autogen/mocs_compilation.cpp.o -c /home/tka/source/visucpp/visucpp/build/Desktop-Debug/visucpp_autogen/mocs_compilation.cpp

CMakeFiles/visucpp.dir/visucpp_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/visucpp.dir/visucpp_autogen/mocs_compilation.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tka/source/visucpp/visucpp/build/Desktop-Debug/visucpp_autogen/mocs_compilation.cpp > CMakeFiles/visucpp.dir/visucpp_autogen/mocs_compilation.cpp.i

CMakeFiles/visucpp.dir/visucpp_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/visucpp.dir/visucpp_autogen/mocs_compilation.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tka/source/visucpp/visucpp/build/Desktop-Debug/visucpp_autogen/mocs_compilation.cpp -o CMakeFiles/visucpp.dir/visucpp_autogen/mocs_compilation.cpp.s

CMakeFiles/visucpp.dir/main.cpp.o: CMakeFiles/visucpp.dir/flags.make
CMakeFiles/visucpp.dir/main.cpp.o: /home/tka/source/visucpp/visucpp/main.cpp
CMakeFiles/visucpp.dir/main.cpp.o: CMakeFiles/visucpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tka/source/visucpp/visucpp/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/visucpp.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/visucpp.dir/main.cpp.o -MF CMakeFiles/visucpp.dir/main.cpp.o.d -o CMakeFiles/visucpp.dir/main.cpp.o -c /home/tka/source/visucpp/visucpp/main.cpp

CMakeFiles/visucpp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/visucpp.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tka/source/visucpp/visucpp/main.cpp > CMakeFiles/visucpp.dir/main.cpp.i

CMakeFiles/visucpp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/visucpp.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tka/source/visucpp/visucpp/main.cpp -o CMakeFiles/visucpp.dir/main.cpp.s

CMakeFiles/visucpp.dir/mainwindow.cpp.o: CMakeFiles/visucpp.dir/flags.make
CMakeFiles/visucpp.dir/mainwindow.cpp.o: /home/tka/source/visucpp/visucpp/mainwindow.cpp
CMakeFiles/visucpp.dir/mainwindow.cpp.o: CMakeFiles/visucpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tka/source/visucpp/visucpp/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/visucpp.dir/mainwindow.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/visucpp.dir/mainwindow.cpp.o -MF CMakeFiles/visucpp.dir/mainwindow.cpp.o.d -o CMakeFiles/visucpp.dir/mainwindow.cpp.o -c /home/tka/source/visucpp/visucpp/mainwindow.cpp

CMakeFiles/visucpp.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/visucpp.dir/mainwindow.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tka/source/visucpp/visucpp/mainwindow.cpp > CMakeFiles/visucpp.dir/mainwindow.cpp.i

CMakeFiles/visucpp.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/visucpp.dir/mainwindow.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tka/source/visucpp/visucpp/mainwindow.cpp -o CMakeFiles/visucpp.dir/mainwindow.cpp.s

CMakeFiles/visucpp.dir/wfmcollection.cpp.o: CMakeFiles/visucpp.dir/flags.make
CMakeFiles/visucpp.dir/wfmcollection.cpp.o: /home/tka/source/visucpp/visucpp/wfmcollection.cpp
CMakeFiles/visucpp.dir/wfmcollection.cpp.o: CMakeFiles/visucpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tka/source/visucpp/visucpp/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/visucpp.dir/wfmcollection.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/visucpp.dir/wfmcollection.cpp.o -MF CMakeFiles/visucpp.dir/wfmcollection.cpp.o.d -o CMakeFiles/visucpp.dir/wfmcollection.cpp.o -c /home/tka/source/visucpp/visucpp/wfmcollection.cpp

CMakeFiles/visucpp.dir/wfmcollection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/visucpp.dir/wfmcollection.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tka/source/visucpp/visucpp/wfmcollection.cpp > CMakeFiles/visucpp.dir/wfmcollection.cpp.i

CMakeFiles/visucpp.dir/wfmcollection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/visucpp.dir/wfmcollection.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tka/source/visucpp/visucpp/wfmcollection.cpp -o CMakeFiles/visucpp.dir/wfmcollection.cpp.s

CMakeFiles/visucpp.dir/wfmcpp.cpp.o: CMakeFiles/visucpp.dir/flags.make
CMakeFiles/visucpp.dir/wfmcpp.cpp.o: /home/tka/source/visucpp/visucpp/wfmcpp.cpp
CMakeFiles/visucpp.dir/wfmcpp.cpp.o: CMakeFiles/visucpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tka/source/visucpp/visucpp/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/visucpp.dir/wfmcpp.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/visucpp.dir/wfmcpp.cpp.o -MF CMakeFiles/visucpp.dir/wfmcpp.cpp.o.d -o CMakeFiles/visucpp.dir/wfmcpp.cpp.o -c /home/tka/source/visucpp/visucpp/wfmcpp.cpp

CMakeFiles/visucpp.dir/wfmcpp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/visucpp.dir/wfmcpp.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tka/source/visucpp/visucpp/wfmcpp.cpp > CMakeFiles/visucpp.dir/wfmcpp.cpp.i

CMakeFiles/visucpp.dir/wfmcpp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/visucpp.dir/wfmcpp.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tka/source/visucpp/visucpp/wfmcpp.cpp -o CMakeFiles/visucpp.dir/wfmcpp.cpp.s

CMakeFiles/visucpp.dir/qcustomplot.cpp.o: CMakeFiles/visucpp.dir/flags.make
CMakeFiles/visucpp.dir/qcustomplot.cpp.o: /home/tka/source/visucpp/visucpp/qcustomplot.cpp
CMakeFiles/visucpp.dir/qcustomplot.cpp.o: CMakeFiles/visucpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tka/source/visucpp/visucpp/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/visucpp.dir/qcustomplot.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/visucpp.dir/qcustomplot.cpp.o -MF CMakeFiles/visucpp.dir/qcustomplot.cpp.o.d -o CMakeFiles/visucpp.dir/qcustomplot.cpp.o -c /home/tka/source/visucpp/visucpp/qcustomplot.cpp

CMakeFiles/visucpp.dir/qcustomplot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/visucpp.dir/qcustomplot.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tka/source/visucpp/visucpp/qcustomplot.cpp > CMakeFiles/visucpp.dir/qcustomplot.cpp.i

CMakeFiles/visucpp.dir/qcustomplot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/visucpp.dir/qcustomplot.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tka/source/visucpp/visucpp/qcustomplot.cpp -o CMakeFiles/visucpp.dir/qcustomplot.cpp.s

# Object files for target visucpp
visucpp_OBJECTS = \
"CMakeFiles/visucpp.dir/visucpp_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/visucpp.dir/main.cpp.o" \
"CMakeFiles/visucpp.dir/mainwindow.cpp.o" \
"CMakeFiles/visucpp.dir/wfmcollection.cpp.o" \
"CMakeFiles/visucpp.dir/wfmcpp.cpp.o" \
"CMakeFiles/visucpp.dir/qcustomplot.cpp.o"

# External object files for target visucpp
visucpp_EXTERNAL_OBJECTS =

visucpp: CMakeFiles/visucpp.dir/visucpp_autogen/mocs_compilation.cpp.o
visucpp: CMakeFiles/visucpp.dir/main.cpp.o
visucpp: CMakeFiles/visucpp.dir/mainwindow.cpp.o
visucpp: CMakeFiles/visucpp.dir/wfmcollection.cpp.o
visucpp: CMakeFiles/visucpp.dir/wfmcpp.cpp.o
visucpp: CMakeFiles/visucpp.dir/qcustomplot.cpp.o
visucpp: CMakeFiles/visucpp.dir/build.make
visucpp: /usr/lib64/libQt6PrintSupport.so.6.7.1
visucpp: /usr/lib64/libQt6Widgets.so.6.7.1
visucpp: /usr/lib64/libQt6Gui.so.6.7.1
visucpp: /usr/lib64/libQt6Core.so.6.7.1
visucpp: /usr/lib64/libGLX.so
visucpp: /usr/lib64/libOpenGL.so
visucpp: CMakeFiles/visucpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/tka/source/visucpp/visucpp/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable visucpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/visucpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/visucpp.dir/build: visucpp
.PHONY : CMakeFiles/visucpp.dir/build

CMakeFiles/visucpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/visucpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/visucpp.dir/clean

CMakeFiles/visucpp.dir/depend: visucpp_autogen/timestamp
	cd /home/tka/source/visucpp/visucpp/build/Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tka/source/visucpp/visucpp /home/tka/source/visucpp/visucpp /home/tka/source/visucpp/visucpp/build/Desktop-Debug /home/tka/source/visucpp/visucpp/build/Desktop-Debug /home/tka/source/visucpp/visucpp/build/Desktop-Debug/CMakeFiles/visucpp.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/visucpp.dir/depend

