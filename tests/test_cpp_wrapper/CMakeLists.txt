cmake_minimum_required(VERSION 3.5)
project(test_cpp_wrapper)

set(CMAKE_CXX_STANDARD 17)
add_executable(test_cpp_wrapper test_cpp_wrapper.cpp
        ../../cpp-wrapper/SteganoFsAdapter.cpp
        ../../cpp-wrapper/SteganoFsAdapter.h)

add_custom_target(copy_fs
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/filesystem.steganofs ${CMAKE_CURRENT_BINARY_DIR}
)
add_dependencies(test_cpp_wrapper copy_fs)

# Link against the steganofs library
target_link_libraries(test_cpp_wrapper PRIVATE steganofs)