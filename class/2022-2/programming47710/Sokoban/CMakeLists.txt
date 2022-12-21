cmake_minimum_required(VERSION 3.16)
project(Sokoban C)

set(CMAKE_C_STANDARD 99)

add_executable(Sokoban main.c)
target_include_directories(Sokoban PUBLIC .)
