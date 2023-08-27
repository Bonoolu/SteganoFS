#include "../steganofs/steganofs.h"

/**
 * @brief Test function for getting free disk space on an empty hidden FAT.
 * @return `true` if the test passes, otherwise `false`.
 */
bool test_get_free_disk_space_empty_fat ()
{
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 4, STEGANOFS_BLOCK_SIZE);
  size_t free_space = get_free_disk_space (hidden_fat);
  bool passed;
  if (free_space == STEGANOFS_BLOCK_SIZE * 4)
    {
      printf ("test_get_free_disk_space_empty_fat test passed.\n");
      passed = true;
    }
  else
    {
      printf (
          "test_get_free_disk_space_empty_fat test failed: Expected free disk space: 1024 bytes, Actual free disk space: %zu bytes.\n",
          free_space);
      passed = false;
    }
  free_hidden_fat (hidden_fat);
  return passed;
}

int main(int argc, char** argv) {
    if (test_get_free_disk_space_empty_fat()) {
        return 0;
    }
    return 1;
}
