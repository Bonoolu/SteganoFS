#include "../steganofs/steganofs.h"

/**
 * @brief Test function for creating a hidden file with insufficient memory.
 * @return `true` if the test passes, otherwise `false`.
 */
bool test_create_file_insufficient_memory ()
{
  fflush (stdout);
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 4, STEGANOFS_BLOCK_SIZE);
  const char *hidden_filename = "dogs.gif";
  long timestamp = time (NULL);
  bool passed = true;

  HiddenFile **hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
  if (hidden_file == NULL)
    {
      printf ("test_create_file_insufficient_memory test failed: create_hidden_file failed and returned NULL.\n");
      return false;
    }
  bool allocated = true;
  for (int i = 0; i < hidden_fat->amount_blocks + 1 && allocated; i++)
    { // Larger than available memory
      allocated = extend_hidden_cluster (hidden_fat, *hidden_file);
    }
  if (allocated)
    {
      printf ("test_create_file_insufficient_memory test failed: File created despite insufficient memory.\n");
      passed = false;
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_create_file_insufficient_memory test failed: Integrity check failed!.\n");
      passed = false;
    }

  if (passed)
    printf ("test_create_file_insufficient_memory test passed.\n");
  fflush (stderr);
  free_hidden_fat (hidden_fat);
  return passed;
}

int main(int argc, char** argv) {
    if (test_create_file_insufficient_memory()) {
        return 0;
    }
    return 1;
}
