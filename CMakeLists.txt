cmake_minimum_required(VERSION 3.5)
project(steganofs_main)

add_custom_target(copy_example_folder
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/examples/ ${CMAKE_CURRENT_BINARY_DIR}/examples
)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/examples/mnt)
add_subdirectory(steganofs)
add_subdirectory(stegano_gui)
add_subdirectory(cli)
add_subdirectory(tests)
