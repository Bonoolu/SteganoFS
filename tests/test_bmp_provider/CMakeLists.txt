cmake_minimum_required(VERSION 3.5)
project(test_bmp_provider C)

set(CMAKE_C_STANDARD 99)

add_executable(test_bmp_provider test_bmp_provider.c)

# Link against the steganofs library
target_link_libraries(test_bmp_provider PRIVATE steganofs)