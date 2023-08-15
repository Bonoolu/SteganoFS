cmake_minimum_required(VERSION 3.5)
project(adapter_dummy)

set(CMAKE_CXX_STANDARD 17)

add_executable(adapter_dummy main.cpp SteganoFsAdapter.cpp SteganoFsAdapter.h)