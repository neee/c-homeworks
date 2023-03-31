cmake_minimum_required(VERSION 3.24)

project(hw3 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(word_counter main.c hashtable.h hashtable.c)
