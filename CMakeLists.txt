cmake_minimum_required(VERSION 3.21)
project(comput)

# export compile commands for clangd database
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# compiler
# set(CMAKE_CXX_COMPILER clang)
set(CMAKE_CXX_COMPILER g++)

# libs
# windows can't find sdl automatically
# use environment variables holding the path to sdl installation for now
# TODO: still can't get it to compile on windows without manually copying header files from sdl
if (WIN32 OR MSVC)
  set(SDL2_INCLUDE_DIRS "include/SDL/") # TODO: remove this
  # set(SDL2_INCLUDE_DIRS $ENV{COMPUT_SDL2_INCLUDE_DIRS}) # TODO: uncomment this
  set(SDL2_LIBRARIES $ENV{COMPUT_SDL2_LIBRARIES})
  message("comput - Building for Windows.")
  # message("SDL2 INCLUDE DIRECTORIES: ${SDL2_INCLUDE_DIRS}")
  # message("SDL2 LIBRARIES: ${SDL2_LIBRARIES}")
  # TODO: does eigen3 work?
else()
message("comput - Building for *nix.")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
endif()

if (NOT $ENV{COMPUT_DEBUG})
  # release
  message("comput - Building in release mode.")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCMAKE_BUILD_TYPE=RelWithDebInfo -std=c++20 -Wall") # just use cmake release + debinfo for now
else()
  # debug
  message("comput - Building in debug mode.")
  add_definitions(-DCOMPUT_DEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCMAKE_BUILD_TYPE=Debug -std=c++20 -Wall") # just use cmake debug for now
endif()

# links to all targets defined after this call
link_libraries(${SDL2_LIBRARIES})

add_executable(comput_main src/main.cpp)

add_library(comput_object src/object.cpp)

# tests
if (DEFINED $ENV{COMPUT_TEST})
  message("comput - Building tests.")
  add_executable(verify_sdl test/verify_sdl.cpp)
  # add_dependencies(verify_sdl ${SDL2_LIBRARIES}) # TODO: somehow this gives error, investigate
  target_link_libraries(verify_sdl ${SDL2_LIBRARIES})
endif()
