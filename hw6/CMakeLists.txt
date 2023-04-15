cmake_minimum_required(VERSION 3.24)

project(hw6 C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(hw6 main.c clog.c clog.h)
