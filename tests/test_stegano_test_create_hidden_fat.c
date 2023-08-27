#include "../steganofs/steganofs.h"

/**
 * @brief Test function for creating a hidden FAT structure.
 * @return `true` if the test passes, otherwise `false`.
 */
bool test_create_hidden_fat ()
{
  size_t disk_size = STEGANOFS_BLOCK_SIZE * 4;  // Example disk size
  size_t block_size = STEGANOFS_BLOCK_SIZE;  // Example block size
  HiddenFat *hidden_fat = create_hidden_fat (disk_size, block_size);
  bool passed = true;
  if (hidden_fat == NULL)
    {
      printf ("test_create_hidden_fat test failed: Failed to stgfs_create the HiddenFat structure.\n");
      passed = false;
    }

  // Verify the blockSize and amountBlocks values
  if (hidden_fat->block_size != block_size)
    {
      printf ("test_create_hidden_fat test failed: Incorrect blockSize value.\n");
      passed = false;
    }

  size_t expected_amount_blocks = disk_size / block_size;
  if (hidden_fat->amount_blocks != expected_amount_blocks)
    {
      printf ("test_create_hidden_fat test failed: Incorrect amountBlocks value.\n");
      passed = false;
    }

  // Verify the disk and blocks arrays
  if (hidden_fat->disk == NULL)
    {
      printf ("test_create_hidden_fat test failed: Disk array is not allocated.\n");
      passed = false;
    }

  if (hidden_fat->clusters == NULL)
    {
      printf ("test_create_hidden_fat test failed: Blocks array is not allocated.\n");
      passed = false;
    }

  // Check if the disk and blocks arrays are properly initialized
  for (size_t i = 0; i < disk_size; i++)
    {
      if (hidden_fat->disk[i] != 0)
        {
          printf ("test_create_hidden_fat test failed: Disk array is not properly initialized.\n");
          passed = false;
        }
    }

  for (size_t i = 0; i < expected_amount_blocks; i++)
    {
      if (hidden_fat->clusters[i].state != FREE || hidden_fat->clusters[i].b_index != i)
        {
          printf ("test_create_hidden_fat test failed: Blocks array is not properly initialized.\n");
          passed = false;
        }
    }

  // Check if all Cluster Block Associations are not NULL
  for (size_t b_index = 0; b_index < hidden_fat->amount_blocks; b_index++)
    {
      if (hidden_fat->clusters[b_index].prev != NULL || hidden_fat->clusters[b_index].next != NULL)
        {
          printf ("test_create_hidden_fat test failed: Cluster associated with block %zu was not freed.\n", b_index);
          passed = false;
          break;
        }
    }

  // Cleanup
  free_hidden_fat (hidden_fat);
  if (passed)
    printf ("test_create_hidden_fat test passed.\n");
  return passed;
}

int main(int argc, char** argv) {
    if (test_create_hidden_fat()) {
        return 0;
    }
    return 1;
}
