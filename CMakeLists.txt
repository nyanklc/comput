cmake_minimum_required(VERSION 3.21)
project(comput)

# export compile commands for clangd database
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# compiler
# set(CMAKE_CXX_COMPILER clang)
set(CMAKE_CXX_COMPILER g++)

# libs
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

if (NOT DEFINED ENV{COMPUT_DEBUG})
  # release
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCMAKE_BUILD_TYPE=RelWithDebInfo -std=c++20 -Wall") # just use cmake release + debinfo for now
else()
  # debug
  message("comput - Building in debug mode.")
  add_definitions(-DCOMPUT_DEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCMAKE_BUILD_TYPE=Debug -std=c++20 -Wall") # just use cmake debug for now
endif()

add_executable(comput src/main.cpp)
target_link_libraries(comput ${SDL2_LIBRARIES})

# tests
if (DEFINED ENV{COMPUT_TEST})
  message("comput - Building tests.")
  add_executable(verify_sdl test/verify_sdl.cpp)
  # add_dependencies(verify_sdl ${SDL2_LIBRARIES}) # TODO: somehow this gives error, investigate
  target_link_libraries(verify_sdl ${SDL2_LIBRARIES})
endif()
