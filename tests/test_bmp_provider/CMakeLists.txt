cmake_minimum_required(VERSION 3.5)
project(test_bmp_provider C)

set(CMAKE_C_STANDARD 99)

add_executable(test_bmp_provider test_bmp_provider.c)

add_custom_target(copy_example_bmp
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/example.bmp ${CMAKE_CURRENT_BINARY_DIR}
)
add_dependencies(test_cpp_wrapper copy_example_bmp)

# Link against the steganofs library
target_link_libraries(test_bmp_provider PRIVATE steganofs)