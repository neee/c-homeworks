cmake_minimum_required(VERSION 3.24)
project(hw2 C)

set(CMAKE_C_STANDARD 11)

add_executable(hw2 main.c encdoing/koi8r.c encdoing/iso88595.c encdoing/iso88595.h encdoing/cp1251.c encdoing/cp1251.h)

add_compile_options(-Wall -Wextra -Wpedantic)
