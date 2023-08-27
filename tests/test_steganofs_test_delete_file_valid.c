#include "../steganofs/steganofs.h"

/**
 * @brief Test function for deleting a valid hidden file.
 * @return `true` if the test passes, otherwise `false`.
 */
bool test_delete_file_valid ()
{
  // Create a valid file
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 4, STEGANOFS_BLOCK_SIZE);
  const char *hidden_filename = "cats.gif";
  long timestamp = time (NULL);
  HiddenFile **hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
  if (hidden_file == NULL)
    {
      printf ("test_delete_file_valid test failed: create_hidden_file failed and returned NULL.\n");
      return false;
    }

  // Delete the file
  delete_hidden_file (hidden_fat, hidden_filename);

  // Check if the file was successfully deleted
  bool passed = true;
  for (size_t i = 0; i < STEGANOFS_AMOUNT_ROOT_FILES; i++)
    {
      if (hidden_fat->files[i] != NULL && strcmp (hidden_fat->files[i]->filename, hidden_filename) == 0)
        {
          printf ("test_delete_file_valid test failed: File still exists in the file table.\n");
          passed = false;
          break;
        }
    }

  if (*hidden_file != NULL)
    {
      printf ("test_delete_file_valid test failed: File structure still exists.\n");
      passed = false;
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_delete_file_valid test failed: Integrity check failed!.\n");
      passed = false;
    }

  if (passed)
    printf ("test_delete_file_valid test passed.\n");
  return passed;
}

int main(int argc, char** argv) {
    if (test_delete_file_valid()) {
        return 0;
    }
    return 1;
}
