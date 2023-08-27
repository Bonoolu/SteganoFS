#include "../steganofs/steganofs.h"

/**
 * @brief Test function for deleting a non-existent hidden file.
 * @return `true` if the test passes, otherwise `false`.
 */
bool test_delete_file_with_clusters ()
{
  // Check if the associated clusters were freed
  bool passed = true;

  // Create a file with clusters
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 4, STEGANOFS_BLOCK_SIZE);

  const char *hidden_filename = "cats.gif";
  long timestamp = time (NULL);
  HiddenFile **hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
  if (hidden_file == NULL)
    {
      printf ("test_delete_file_valid test failed: createFile failed and returned NULL.\n");
      return false;
    }
  const char *test_buffer = "My testbuffer!";
  stgfs_write ("/cats.gif", test_buffer, 15, 0, (struct fuse_file_info *) hidden_fat);

  // Delete the file
  delete_hidden_file (hidden_fat, hidden_filename);

  // Check if the associated clusters were freed
  unsigned char zero_block[STEGANOFS_BLOCK_SIZE];
  memset (zero_block, 0, sizeof zero_block);
  for (size_t b_index = 0; b_index < hidden_fat->amount_blocks; b_index++)
    {
      if (memcmp (zero_block, hidden_fat->disk + (b_index * STEGANOFS_BLOCK_SIZE), STEGANOFS_BLOCK_SIZE) != 0)
        {
          printf ("test_delete_file_with_clusters test failed: Cluster associated with block %zu was not freed.\n",
                  b_index);
          passed = false;
          break;
        }
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_delete_file_with_clusters test failed: Integrity check failed!.\n");
      passed = false;
    }

  if (passed)
    printf ("test_delete_file_with_clusters test passed.\n");
  free_hidden_fat (hidden_fat);
  return passed;
}

int main(int argc, char** argv) {
    if (test_delete_file_with_clusters()) {
        return 0;
    }
    return 1;
}
