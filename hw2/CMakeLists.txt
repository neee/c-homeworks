cmake_minimum_required(VERSION 3.24)
project(hw2 C)

set(CMAKE_C_STANDARD 11)

add_executable(hw2 main.c encoding/koi8r.c encoding/iso88595.c encoding/iso88595.h encoding/cp1251.c encoding/cp1251.h)

add_compile_options(-Wall -Wextra -Wpedantic)
