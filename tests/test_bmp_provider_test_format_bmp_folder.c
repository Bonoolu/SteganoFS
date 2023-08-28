#include "../steganofs/steganofs.h"

/**
 * @brief Test formatting a filesystem.
 *
 * @return True if the test passes, false otherwise.
 */
bool test_format_bmp_folder ()
{
  size_t filesystem_size = steganofs_format ("examples/pictures");
  if (filesystem_size == 0)
    {
      printf ("test_format_bmp_folder test failed: formatted filesystem is of size 0.\n");
      return false;
    }
  printf ("Formatted filesystem is of size: %zu\n", filesystem_size);
  HiddenFat *hidden_fat = steganofs_load_ramdisk ("examples/pictures");
  if (hidden_fat == NULL)
    {
      printf ("test_format_bmp_folder test failed: Loading ramdisk failed!\n");
      return false;
    }
  show_hidden_fat (hidden_fat, NULL);
  bool ret = check_integrity (hidden_fat);
  if (!ret)
    {
      printf ("test_format_bmp_folder test failed: Integrity check failed!\n");
      return false;
    }
  ret = steganofs_unload_ramdisk (hidden_fat, "examples/pictures");

  if (!ret)
    {
      printf ("test_format_bmp_folder test failed: Unloading ramdisk failed!\n");
      return false;
    }
  return ret;
}

int main (int argc, char **argv)
{
  if (test_format_bmp_folder ())
    {
      return 0;
    }
  return 1;
}

