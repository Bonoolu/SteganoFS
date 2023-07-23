cmake_minimum_required(VERSION 3.25)
project(steganoFS_C C)

set(CMAKE_C_STANDARD 99)

add_executable(steganoFS_C main.c bsfat.h bsfat.c)
