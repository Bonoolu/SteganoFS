cmake_minimum_required(VERSION 3.25)
project(test_steganofs C)

set(CMAKE_C_STANDARD 99)

add_executable(test_steganofs test_steganofs.c)

# Link against the steganofs library
target_link_libraries(test_steganofs PRIVATE steganofs)