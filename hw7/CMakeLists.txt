cmake_minimum_required(VERSION 3.25)
project(hw7 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(hw7 main.c)
