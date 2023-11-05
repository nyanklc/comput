cmake_minimum_required(VERSION 3.21)
project(comput)

# export compile commands for clangd database
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# compiler
# set(CMAKE_CXX_COMPILER clang)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall")

# libs
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

if (NOT DEFINED ENV{COMPUT_DEBUG})
  # release
  message("comput - Building in release mode.")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCMAKE_BUILD_TYPE=RelWithDebInfo") # just use cmake release + debinfo for now
else()
  # debug
  message("comput - Building in debug mode.")
  add_definitions(-DCOMPUT_DEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCMAKE_BUILD_TYPE=Debug") # just use cmake debug for now
endif()

# links to all targets defined after this call
link_libraries(${SDL2_LIBRARIES})

add_executable(comput_main src/main.cpp)
target_link_libraries(comput_main
  comput_object
  comput_window_handler
  comput_engine
  comput_bbox
  )

add_library(comput_object src/object.cpp)
add_library(comput_window_handler src/window_handler.cpp)
add_library(comput_engine src/engine.cpp)
add_library(comput_bbox src/bbox.cpp)

# tests
if (DEFINED ENV{COMPUT_TEST})
  message("comput - Building tests.")
  add_executable(verify_sdl test/verify_sdl.cpp)
  # add_dependencies(verify_sdl ${SDL2_LIBRARIES}) # TODO: somehow this gives error, investigate
  target_link_libraries(verify_sdl ${SDL2_LIBRARIES})
endif()
