cmake_minimum_required(VERSION 3.26)
project(stegano_fs_adapter)

set(CMAKE_CXX_STANDARD 17)

add_executable(stegano_fs_adapter main.cpp
        SteganoFsAdapter.cpp
        SteganoFsAdapter.h)
