#include "../steganofs/steganofs.h"

/**
 * @brief Test function for deleting a non-existent hidden file.
 * @return `true` if the test passes, otherwise `false`.
 */
bool test_delete_file_non_existent ()
{
  // Create a valid file
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 4, STEGANOFS_BLOCK_SIZE);
  const char *hidden_filename = "cats.gif";
  long timestamp = time (NULL);
  HiddenFile **hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
  if (hidden_file == NULL)
    {
      printf ("test_delete_file_valid test failed: createFile failed and returned NULL.\n");
      return false;
    }
  // Delete a non-existent file
  const char *non_existent_filename = "dogs.gif";
  delete_hidden_file (hidden_fat, non_existent_filename);

  // Check if the file table remains unchanged
  bool passed = true;

  if (*hidden_file == NULL)
    {
      printf ("test_delete_file_non_existent test failed: File in the file table was incorrectly deleted.\n");
      passed = false;
    }

  if (strcmp ((*hidden_file)->filename, hidden_filename) != 0)
    {
      printf ("test_delete_file_non_existent test failed: File in the file table was incorrectly deleted.\n");
      passed = false;
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_delete_file_non_existent test failed: Integrity check failed!.\n");
      passed = false;
    }

  if (passed)
    printf ("test_delete_file_non_existent test passed.\n");
  free_hidden_fat (hidden_fat);
  return passed;
}

int main(int argc, char** argv) {
    if (test_delete_file_non_existent()) {
        return 0;
    }
    return 1;
}
