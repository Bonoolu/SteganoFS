## Test Suite

SteganoFS includes a comprehensive test suite to ensure the reliability and functionality of its core components. The test suite covers a wide range of scenarios and functions, including filesystem behavior, RAM disk loader functionality, run-length encoding, and steganography.

### Types of Tests

The test suite comprises both unit tests and integration tests. These tests are designed to validate the behavior of individual functions as well as the interactions between various components of the project.

### Running the Test Suite

To run the test suite, navigate to the build directory and execute the following command:

```bash
ctest
```

This command will automatically run all the available tests and provide you with feedback on their success or failure.

At the time of writing. Running the test suit should result in this output:

```
Test project /home/admin/CLionProjects/SteganoFS/build
      Start  1: test_bmp_provider_test_format_bmp_folder
 1/21 Test  #1: test_bmp_provider_test_format_bmp_folder ......................   Passed    6.81 sec
      Start  2: test_bmp_provider_test_generic_buffer
 2/21 Test  #2: test_bmp_provider_test_generic_buffer .........................   Passed    0.00 sec
      Start  3: test_bmp_provider_test_single_bmp_file
 3/21 Test  #3: test_bmp_provider_test_single_bmp_file ........................   Passed    0.00 sec
      Start  4: test_steganofs_test_create_file_linked_list
 4/21 Test  #4: test_steganofs_test_create_file_linked_list ...................   Passed    0.00 sec
      Start  5: test_steganofs_test_delete_file_valid
 5/21 Test  #5: test_steganofs_test_delete_file_valid .........................   Passed    0.00 sec
      Start  6: test_stegano_test_create_file_insufficient_memory
 6/21 Test  #6: test_stegano_test_create_file_insufficient_memory .............   Passed    0.00 sec
      Start  7: test_stegano_test_create_file_no_available_file_slot
 7/21 Test  #7: test_stegano_test_create_file_no_available_file_slot ..........   Passed    0.00 sec
      Start  8: test_stegano_test_create_file_valid
 8/21 Test  #8: test_stegano_test_create_file_valid ...........................   Passed    0.00 sec
      Start  9: test_stegano_test_create_hidden_fat
 9/21 Test  #9: test_stegano_test_create_hidden_fat ...........................   Passed    0.00 sec
      Start 10: test_stegano_test_defragmentation
10/21 Test #10: test_stegano_test_defragmentation .............................   Passed    0.00 sec
      Start 11: test_stegano_test_delete_file_non_existent
11/21 Test #11: test_stegano_test_delete_file_non_existent ....................   Passed    0.00 sec
      Start 12: test_stegano_test_delete_file_with_clusters
12/21 Test #12: test_stegano_test_delete_file_with_clusters ...................   Passed    0.00 sec
      Start 13: test_stegano_test_get_free_disk_space_empty_fat
13/21 Test #13: test_stegano_test_get_free_disk_space_empty_fat ...............   Passed    0.00 sec
      Start 14: test_stegano_test_get_free_disk_space_full_disk
14/21 Test #14: test_stegano_test_get_free_disk_space_full_disk ...............   Passed    0.00 sec
      Start 15: test_stegano_test_get_free_disk_space_with_allocated_blocks
15/21 Test #15: test_stegano_test_get_free_disk_space_with_allocated_blocks ...   Passed    0.00 sec
      Start 16: test_stegano_test_ramdiskloader
16/21 Test #16: test_stegano_test_ramdiskloader ...............................   Passed    0.22 sec
      Start 17: test_stegano_test_rle
17/21 Test #17: test_stegano_test_rle .........................................   Passed    0.00 sec
      Start 18: test_stegano_test_show_n_block_fat
18/21 Test #18: test_stegano_test_show_n_block_fat ............................   Passed    0.00 sec
      Start 19: test_stegano_test_swap_hidden_clusters_integrity
19/21 Test #19: test_stegano_test_swap_hidden_clusters_integrity ..............   Passed    0.00 sec
      Start 20: test_stegano_test_write_read
20/21 Test #20: test_stegano_test_write_read ..................................   Passed    0.00 sec
      Start 21: test_cpp_wrapper_test_defragmenting
21/21 Test #21: test_cpp_wrapper_test_defragmenting ...........................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 21

```

### Test Structure

Each test is implemented as a separate executable. The test files are organized in the `test` directory and follow a consistent naming convention, such as `test_bmp_provider_test_bmp_folder.c` and `test_stegano_test_create_file_valid.c`.

### Adding New Tests

Contributors are encouraged to expand the test suite by adding new tests that cover specific scenarios or functions. When adding new tests, it's recommended to follow the established naming convention and structure to maintain consistency.

### Testing Guidelines

While there are no strict testing guidelines, contributors are encouraged to create tests that thoroughly cover the functionality they are testing. This helps ensure the overall quality and reliability of the project.

### Example Test

Here's an example of a unit test from the test suite:

```c
#include "../steganofs/steganofs.h"

bool test_your-test-name-here()
{
// ... Test implementation ...
return true;
}

int main(int argc, char** argv)
{
if (test_your-test-name-here())
{
return 0;
}
return 1;
}
```

Afterwards please add your test to the CMakeLists.txt file in the tests folder and register your test in the CMakeLists.txt in the root folder of this repository.