cmake_minimum_required(VERSION 3.27.4)
project(comput C)

# export compile commands for clangd database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# compiler
set(CMAKE_C_COMPILER clang)

# libs
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

if (NOT DEFINED ENV{COMPUT_DEBUG})
  # release
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -std=c17")
else()
  # debug
  message("comput - Building in debug mode.")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb -std=c17")
endif()

add_executable(main src/main.c)

# tests
if (DEFINED ENV{COMPUT_BUILD_TESTS})
  message("comput - Building tests.")
  add_executable(verify_sdl test/verify_sdl.c)
  # add_dependencies(verify_sdl ${SDL2_LIBRARIES}) # TODO: somehow this gives error, investigate
  target_link_libraries(verify_sdl ${SDL2_LIBRARIES})
endif()
