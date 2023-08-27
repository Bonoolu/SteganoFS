#include "../steganofs/steganofs.h"

/**
 * @brief Test function for creating a hidden file with valid parameters.
 * @return `true` if the test passes, otherwise `false`.
 */
bool test_create_file_valid ()
{
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 4, STEGANOFS_BLOCK_SIZE);

  const char *hidden_filename = "cats.gif";
  long timestamp = time (NULL);
  bool passed = true;

  HiddenFile **hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
  if (hidden_file == NULL)
    {
      printf ("test_create_file_valid test failed: Failed to stgfs_create file.\n");
      passed = false;
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_create_file_valid test failed: Integrity check failed!.\n");
      passed = false;
    }

  if (passed)
    printf ("test_create_file_valid test passed.\n");
  free_hidden_fat (hidden_fat);
  return passed;
}

int main(int argc, char** argv) {
    if (test_create_file_valid()) {
        return 0;
    }
    return 1;
}
