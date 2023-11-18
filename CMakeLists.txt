cmake_minimum_required(VERSION 3.21)
project(comput)

# export compile commands for clangd database
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# c++ version
set(CXX_STANDARD C++17)

# compiler
# set(CMAKE_CXX_COMPILER clang)
# set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall")

# external libs
if (WIN32)
  SET(SDL2_LIBRARIES "${PROJECT_SOURCE_DIR}\\libs\\SDL2\\build\\RelWithDebInfo\\SDL2.lib")
  SET(SDL2_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}\\libs\\SDL2\\include")
  SET(EIGEN3_INCLUDE_DIR "${PROJECT_SOURCE_DIR}\\libs\\eigen")
else()
  find_package(SDL2 REQUIRED)
  find_package(Eigen3 REQUIRED)
endif()

# include directories
include_directories(${SDL2_INCLUDE_DIRS})
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

# main
if (WIN32)
  add_executable(comput_main WIN32 ${PROJECT_SOURCE_DIR}/src/main.cpp)
else()
  add_executable(comput_main ${PROJECT_SOURCE_DIR}/src/main.cpp)
endif()

target_link_libraries(comput_main
  comput_engine
  comput_object
  comput_object_properties
  comput_window_handler
  comput_bbox
  comput_collision_system_brute_force
  comput_util
  )

# internal libs
add_library(comput_engine ${PROJECT_SOURCE_DIR}/src/engine.cpp)
add_library(comput_object ${PROJECT_SOURCE_DIR}/src/object.cpp)
add_library(comput_object_properties ${PROJECT_SOURCE_DIR}/src/object_properties.cpp)
add_library(comput_window_handler ${PROJECT_SOURCE_DIR}/src/window_handler.cpp)
add_library(comput_bbox ${PROJECT_SOURCE_DIR}/src/bbox.cpp)
add_library(comput_collision_system_brute_force ${PROJECT_SOURCE_DIR}/src/util/collision_system/brute_force.cpp)
add_library(comput_util ${PROJECT_SOURCE_DIR}/src/util/util.cpp)

# tests
if (DEFINED ENV{COMPUT_TEST})
  message("comput - Building tests.")
  if (WIN32)
    add_executable(verify_sdl WIN32 test/verify_sdl.cpp)
  else()
    add_executable(verify_sdl test/verify_sdl.cpp)
  endif()
endif()
