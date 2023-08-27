#include "../steganofs/steganofs.h"

/**
 * @brief Test function for getting free disk space on a completely filled disk.
 * @return `true` if the test passes, otherwise `false`.
 */
bool test_get_free_disk_space_full_disk ()
{
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE, STEGANOFS_BLOCK_SIZE);
  // Allocate all blocks or create files until the disk is full
  hidden_fat->clusters->state = ALLOCATED;
  // Perform actions to allocate blocks or create files
  size_t free_space = get_free_disk_space (hidden_fat);
  bool passed;
  if (free_space == 0)
    {
      printf ("test_get_free_disk_space_full_disk test passed.\n");
      passed = true;
    }
  else
    {
      printf (
          "test_get_free_disk_space_full_disk test failed: Expected free disk space: 0 bytes, Actual free disk space: %zu bytes.\n",
          free_space);
      passed = false;
    }
  free_hidden_fat (hidden_fat);
  return passed;
}

int main(int argc, char** argv) {
    if (test_get_free_disk_space_full_disk()) {
        return 0;
    }
    return 1;
}
