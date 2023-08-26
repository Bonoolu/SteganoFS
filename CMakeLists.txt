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

enable_testing()
add_test(
    NAME test_steganofs
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_steganofs/test_steganofs
)
add_test(
        NAME test_bmp_provider
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_bmp_provider/test_bmp_provider
)
add_test( # this test defragments example.steganofs
        NAME test_cpp_wrapper
        COMMAND tests/test_cpp_wrapper/test_cpp_wrapper
)

