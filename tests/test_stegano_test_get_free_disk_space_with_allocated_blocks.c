#include "../steganofs/steganofs.h"

/**
 * @brief Test function for getting free disk space with allocated blocks/files.
 * @return `true` if the test passes, otherwise `false`.
 */
bool test_get_free_disk_space_with_allocated_blocks ()
{
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 4, STEGANOFS_BLOCK_SIZE);
  // Allocate some blocks or create files within the filesystem
  // Perform actions to allocate blocks or create files
  for (size_t i = 0; i < 2; i++)
    {
      hidden_fat->clusters[i].state = ALLOCATED;
    }
  size_t free_space = get_free_disk_space (hidden_fat);
  // Calculate the expected free space based on the allocated blocks/files
  size_t expected_free_space =
      STEGANOFS_BLOCK_SIZE * 2;  // Calculate the expected value based on the specific test case
  bool passed;
  if (free_space == expected_free_space)
    {
      printf ("test_get_free_disk_space_with_allocated_blocks test passed.\n");
      passed = true;
    }
  else
    {
      printf (
          "test_get_free_disk_space_with_allocated_blocks test failed: Expected free disk space: %zu bytes, Actual free disk space: %zu bytes.\n",
          expected_free_space,
          free_space);
      passed = false;
    }
  free_hidden_fat (hidden_fat);
  return passed;
}

int main(int argc, char** argv) {
    if (test_get_free_disk_space_with_allocated_blocks()) {
        return 0;
    }
    return 1;
}
