cmake_minimum_required(VERSION 3.27.4)
project(comput C)

# export compile commands for clangd database
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# compiler
set(CMAKE_C_COMPILER clang)

# libs
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

if (NOT DEFINED ENV{COMPUT_BUILD_DEBUG})
  if (NOT DEFINED ENV{COMPUT_BUILD_O3})
    # release
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -std=c17")
  else()
    # o3 optimized
    message("comput - Building with O3 optimizations.")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -std=c17")
  endif()
else()
  # debug
  message("comput - Building in debug mode.")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb -std=c17")
endif()

add_executable(main src/main.c)
target_link_libraries(main ${SDL2_LIBRARIES})

# tests
if (DEFINED ENV{COMPUT_BUILD_TEST})
  message("comput - Building tests.")
  add_executable(verify_sdl test/verify_sdl.c)
  # add_dependencies(verify_sdl ${SDL2_LIBRARIES}) # TODO: somehow this gives error, investigate
  target_link_libraries(verify_sdl ${SDL2_LIBRARIES})
endif()
