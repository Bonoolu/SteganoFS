#include "../steganofs/steganofs.h"

/**
 * @brief Test fuse mounting
 *
 * @param argc The number of command line arguments.
 * @param argv An array of C-style strings containing the command line arguments.
 * @return The result code of the test_fuse operation.
 */
int test_fuse (int argc, char **argv)
{
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 100000, STEGANOFS_BLOCK_SIZE);
  HiddenFile **hidden_file = create_hidden_file (hidden_fat, "cats.gif", time (NULL));
  if (hidden_file == NULL)
    {
      printf ("test_defragmentation test failed: create_hidden_file failed and returned NULL.\n");
      return false;
    }
  hidden_file = create_hidden_file (hidden_fat, "dogs.gif", time (NULL));
  if (hidden_file == NULL)
    {
      printf ("test_defragmentation test failed: create_hidden_file failed and returned NULL.\n");
      return false;
    }
  hidden_file = create_hidden_file (hidden_fat, "birds.gif", time (NULL));
  if (hidden_file == NULL)
    {
      printf ("test_defragmentation test failed: create_hidden_file failed and returned NULL.\n");
      return false;
    }
  return fuse_main(argc, argv, &fuse_operations, hidden_fat);
}

int main(int argc, char** argv) {
    if (test_fuse()) {
        return 0;
    }
    return 1;
}
