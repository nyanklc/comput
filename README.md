# Requirements
- SDL2
- Eigen3

# Build
Set `COMPUT_DEBUG` environment variable to build in debug mode.

## Linux
- Run `build.sh` for clean build.
- Run `compile.sh` for compilation (make).
- Run `run.sh` to run the main program.

## Windows
- Create a directory `libs`. Put `SDL2` and `eigen` folders inside it.
- Run `visual-studio.bat` to generate Visual Studio 17 2022 project files (under directory `build`).
- Compile and run within VS.

## MacOS
- Run `xcode.sh` to generate Xcode project files (under directory `build`).
- Compile and run within Xcode.

# Tests
Set `COMPUT_TESTS` environment variable to build the tests also. You can run test executables manually.