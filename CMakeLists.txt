cmake_minimum_required(VERSION 3.27.4)
project(comput C)

# export compile commands for clangd database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# compiler
set(CMAKE_C_COMPILER clang)

if (NOT DEFINED ENV{COMPUT_DEBUG})
# release
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -std=c17")
else()
# debug
message("comput - Building in debug mode.")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb -std=c17")
endif()

add_executable(main main.c)
