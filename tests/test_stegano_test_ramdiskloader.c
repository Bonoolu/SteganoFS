#include "../steganofs/steganofs.h"

/**
 * @brief Test function for loading and unloading a RAM disk image.
 * @return `true` if the test passes, otherwise `false`.
 */
bool test_ramdiskloader ()
{
  HiddenFat *hidden_fat = create_hidden_fat (10 * 4, 4);
  const char *hidden_filename = "test.txt";
  long timestamp = time (NULL);
  HiddenFile **hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
  if (hidden_file == NULL)
    {
      printf ("test_ramdiskloader test failed: create_hidden_file failed and returned NULL.\n");
      return false;
    }
  const char *test_buffer = "My testbuffer!";
  int bytes_written = stgfs_write ("/test.txt", test_buffer, 15, 0, (struct fuse_file_info *) hidden_fat);
  if (bytes_written < 0)
    {
      printf ("test_ramdiskloader test failed: create_hidden_file failed. Errorcode: %d\n", bytes_written);
      return false;
    }

  hidden_filename = "test2.txt";
  hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
  if (hidden_file == NULL)
    {
      printf ("test_ramdiskloader test failed: create_hidden_file failed and returned NULL.\n");
      return false;
    }
  test_buffer = "My testbuffer2!";
  bytes_written = stgfs_write ("/test2.txt", test_buffer, 16, 0, (struct fuse_file_info *) hidden_fat);
  if (bytes_written < 0)
    {
      printf ("test_ramdiskloader test failed: create_hidden_file failed. Errorcode: %d\n", bytes_written);
      return false;
    }
  show_hidden_fat (hidden_fat, NULL);
  bool ret = steganofs_unload_ramdisk (hidden_fat, "test_ramdiskloader.steganofs");
  if (!ret)
    {
      printf ("test_ramdiskloader test failed: Unloading ramdisk failed!\n");
      return false;
    }
  hidden_fat = steganofs_load_ramdisk ("test_ramdiskloader.steganofs");
  if (hidden_fat == NULL)
    {
      printf ("test_ramdiskloader test failed: Loading ramdisk failed!\n");
      return false;
    }
  show_hidden_fat (hidden_fat, NULL);
  ret = check_integrity (hidden_fat);
  if (!ret)
    {
      printf ("test_ramdiskloader test failed: Integrity check failed!\n");
      return false;
    }
  ret = steganofs_unload_ramdisk (hidden_fat, "test_ramdiskloader.steganofs");
  if (!ret)
    {
      printf ("test_ramdiskloader test failed: Unloading ramdisk failed!\n");
      return false;
    }
  return ret;
}

int main (int argc, char **argv)
{
  if (test_ramdiskloader ())
    {
      return 0;
    }
  return 1;
}
