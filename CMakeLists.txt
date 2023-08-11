cmake_minimum_required(VERSION 3.26)
project(stegano_fs_adapter)

set(CMAKE_CXX_STANDARD 17)

add_executable(stegano_fs_adapter main.cpp
        cpp-wrapper/SteganoFsAdapter.cpp
        cpp-wrapper/SteganoFsAdapter.h)

add_subdirectory(steganofs)

target_link_libraries(stegano_fs_adapter PRIVATE steganofs)
target_include_directories(stegano_fs_adapter PRIVATE steganofs)