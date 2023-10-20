cmake_minimum_required(VERSION 3.27.4)
project(comput)

# export compile commands for clangd database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

add_executable(main main.cpp)
