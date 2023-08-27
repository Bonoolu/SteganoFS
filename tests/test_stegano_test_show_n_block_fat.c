#include "../steganofs/steganofs.h"

/**
 * @brief Test function for displaying the FAT structure for a specified number of blocks.
 * @param n The number of blocks in the FAT.
 * @param output_len The expected length of the output.
 * @return `true` if the test passes, otherwise `false`.
 */

bool test_show_n_block_fat (size_t n, size_t output_len)
{
  // Create an empty Fat
  HiddenFat *hidden_fat = create_hidden_fat (n, 1);

  // Call showFat and capture the output
  char output[512];
  show_hidden_fat (hidden_fat, output);

  printf ("Output of show_hidden_fat was %zu chars!\n", strlen (output));

  // Compare the output with the expected output
  bool passed = strlen (output) == output_len;
  if (passed)
    {
      printf ("testShowFatEmptyFat test passed.\n");
    }
  else
    {
      printf ("testShowFatEmptyFat test failed: Incorrect output length.\n");
      printf ("Expected Output length: %zu\n", output_len);
      printf ("Actual: %s\n", output);
      printf ("Actual length: %zu\n", strlen (output));
    }

  free_hidden_fat (hidden_fat);
  return passed;
}

int main(int argc, char** argv) {
    int tests[] = {
        test_show_n_block_fat (1, 23),
        test_show_n_block_fat (239, 504),
        test_show_n_block_fat (240, 507),
        test_show_n_block_fat (241, 509),
        test_show_n_block_fat (242, 509),
        -1};
    size_t passed = 0;
    size_t sum = 0;
    int *p_tests = tests;
    while (*p_tests != -1)
    {
        sum++;
        if (*p_tests == 1)
        {
            passed++;
        }
        p_tests++;
    }
    if (passed == sum) {
        return 0;
    }
    return 1;
}
