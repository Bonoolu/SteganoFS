cmake_minimum_required(VERSION 3.5)
project(steganofs_main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage")

add_custom_target(copy_example_folder
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/examples/ ${CMAKE_CURRENT_BINARY_DIR}/examples
)
add_custom_target(copy_example_folder_cpp_wrapper
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/examples/ ${CMAKE_CURRENT_BINARY_DIR}/tests/examples
)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/examples/mnt)
add_subdirectory(steganofs)
add_subdirectory(stegano_gui)
add_subdirectory(cli)
add_subdirectory(tests)

enable_testing()

# This test was superseded by test_cpp_wrapper_test_defragmenting
#add_test(NAME test_bmp_provider_test_bmp_folder COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_bmp_provider_test_bmp_folder)

add_test(NAME test_bmp_provider_test_format_bmp_folder COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_bmp_provider_test_format_bmp_folder)
add_test(NAME test_bmp_provider_test_generic_buffer COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_bmp_provider_test_generic_buffer)
add_test(NAME test_bmp_provider_test_single_bmp_file COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_bmp_provider_test_single_bmp_file)
add_test(NAME test_steganofs_test_create_file_linked_list COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_steganofs_test_create_file_linked_list)
add_test(NAME test_steganofs_test_delete_file_valid COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_steganofs_test_delete_file_valid)
add_test(NAME test_stegano_test_create_file_insufficient_memory COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_stegano_test_create_file_insufficient_memory)
add_test(NAME test_stegano_test_create_file_no_available_file_slot COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_stegano_test_create_file_no_available_file_slot)
add_test(NAME test_stegano_test_create_file_valid COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_stegano_test_create_file_valid)
add_test(NAME test_stegano_test_create_hidden_fat COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_stegano_test_create_hidden_fat)
add_test(NAME test_stegano_test_defragmentation COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_stegano_test_defragmentation)
add_test(NAME test_stegano_test_delete_file_non_existent COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_stegano_test_delete_file_non_existent)
add_test(NAME test_stegano_test_delete_file_with_clusters COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_stegano_test_delete_file_with_clusters)

# This test is not suitable for automated testing as it relies on the user to umount the filesystem
#add_test(NAME test_stegano_test_fuse COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_stegano_test_fuse)

add_test(NAME test_stegano_test_get_free_disk_space_empty_fat COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_stegano_test_get_free_disk_space_empty_fat)
add_test(NAME test_stegano_test_get_free_disk_space_full_disk COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_stegano_test_get_free_disk_space_full_disk)
add_test(NAME test_stegano_test_get_free_disk_space_with_allocated_blocks COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_stegano_test_get_free_disk_space_with_allocated_blocks)
add_test(NAME test_stegano_test_ramdiskloader COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_stegano_test_ramdiskloader)
add_test(NAME test_stegano_test_rle COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_stegano_test_rle)
add_test(NAME test_stegano_test_show_n_block_fat COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_stegano_test_show_n_block_fat)
add_test(NAME test_stegano_test_swap_hidden_clusters_integrity COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_stegano_test_swap_hidden_clusters_integrity)
add_test(NAME test_stegano_test_write_read COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_stegano_test_write_read)
add_test(NAME test_cpp_wrapper_test_defragmenting COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/test_cpp_wrapper_test_defragmenting)
