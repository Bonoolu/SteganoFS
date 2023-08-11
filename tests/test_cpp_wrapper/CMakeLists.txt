cmake_minimum_required(VERSION 3.25)
project(test_cpp_wrapper)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_cpp_wrapper test_cpp_wrapper.cpp
        ../../cpp-wrapper/SteganoFsAdapter.cpp
        ../../cpp-wrapper/SteganoFsAdapter.h)

# Link against the steganofs library
target_link_libraries(test_cpp_wrapper PRIVATE steganofs)