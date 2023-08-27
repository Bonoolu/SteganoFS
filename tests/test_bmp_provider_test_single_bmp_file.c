#include "../steganofs/steganofs.h"

/**
 * @brief Test embedding and extracting a single file within a BMP image.
 *
 * @return True if the test passes, false otherwise.
 */
bool test_single_bmp_file ()
{
  HiddenFat *hidden_fat = create_hidden_fat (10, 2);
  create_hidden_file (hidden_fat, "test.txt", time (NULL));
  unsigned char testbuffer[4] = "abc";
  stgfs_write ("/test.txt", (char *) testbuffer, 4, 0, (struct fuse_file_info *) hidden_fat);
  steganofs_unload_ramdisk (hidden_fat, "tests/example.bmp");
  free_hidden_fat (hidden_fat);
  hidden_fat = steganofs_load_ramdisk ("tests/example.bmp");
  if (!hidden_fat)
    {
      printf ("Could not load anything from tests/example.bmp\n");
      return false;
    }
  if (!check_integrity (hidden_fat))
    {
      printf ("Failed to check integrity of filesystem which was embedded in BMP File!\n");
      return false;
    }
  show_hidden_fat (hidden_fat, NULL);
  printf ("Passed test successfully!\n");
  return true;
}

int main(int argc, char** argv) {
    if (test_single_bmp_file()) {
        return 0;
    }
    return 1;
}
