#include "../steganofs/steganofs.h"

/**
 * @brief Test function for creating a hidden file when no available file slots remain.
 * @return `true` if the test passes, otherwise `false`.
 */
bool test_create_file_no_available_file_slot ()
{
  fflush (stdout);
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 4, STEGANOFS_BLOCK_SIZE);
  printf ("Free Space is now: %zu\n", get_free_disk_space (hidden_fat));
  const char *hidden_filename = "bears.gif";
  long timestamp = time (NULL);
  bool passed = true;

  // Fill all available file slots
  for (size_t i = 0; i < STEGANOFS_AMOUNT_ROOT_FILES; i++)
    {
      HiddenFile **hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
      if (hidden_file == NULL)
        {
          printf ("test_create_file_no_available_file_slot test failed: create_hidden_file failed and returned NULL.\n");
          return false;
        }
    }

  HiddenFile **hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
  if (hidden_file != NULL)
    {
      printf ("test_create_file_no_available_file_slot test failed: File created despite no available file slot.\n");
      passed = false;
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_create_file_no_available_file_slot test failed: Integrity check failed!.\n");
      passed = false;
    }

  if (passed)
    printf ("test_create_file_no_available_file_slot test passed.\n");
  fflush (stderr);
  free_hidden_fat (hidden_fat);
  return passed;
}

int main(int argc, char** argv) {
    if (test_create_file_no_available_file_slot()) {
        return 0;
    }
    return 1;
}
