cmake_minimum_required(VERSION 3.5)
project(steganofs_cli)

set(CMAKE_CXX_STANDARD 17)
add_executable(steganofs_cli steganocli.cpp
        ../cpp-wrapper/SteganoFsAdapter.cpp
        ../cpp-wrapper/SteganoFsAdapter.h)

# Link against the steganofs library
target_link_libraries(steganofs_cli PRIVATE steganofs)