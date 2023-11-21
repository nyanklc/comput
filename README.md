# This is abandoned.

# Requirements
- SDL2
- Eigen3

# Build
Set `COMPUT_DEBUG` environment variable to build in debug mode.

## Linux
- Run `build.sh` for clean build.
- Run `compile.sh` for compilation (make).
- Run `run.sh` to run the main program.

## Windows (can also simply use visual studio, it supports cmake)
- Create a directory `libs`. Put `SDL2` and `eigen` folders inside it.
- Run `visual-studio.bat` to generate Visual Studio 17 2022 project files (under directory `build`).
- Compile and run within VS.

## MacOS (can also be built with the same steps in Linux)
- Run `xcode.sh` to generate Xcode project files (under directory `build`).
- Compile and run within Xcode.

# Tests
Set `COMPUT_TESTS` environment variable to build the tests also. You can run test executables manually.
