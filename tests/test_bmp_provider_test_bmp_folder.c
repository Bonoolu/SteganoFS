#include "../steganofs/steganofs.h"

/**
 * @brief Test creating a folder with files and integrity check in a BMP image.
 *
 * @return True if the test passes, false otherwise.
 */
bool test_bmp_folder ()
{
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 100, STEGANOFS_BLOCK_SIZE);
  const char *hidden_filename = "test.txt";
  long timestamp = time (NULL);
  HiddenFile **hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
  if (hidden_file == NULL)
    {
      printf ("test_bmp_folder test failed: create_hidden_file failed and returned NULL.\n");
      return false;
    }
  const char *test_buffer = "My testbuffer!";
  int bytes_written = stgfs_write ("/test.txt", test_buffer, 15, 0, (struct fuse_file_info *) hidden_fat);
  if (bytes_written < 0)
    {
      printf ("test_bmp_folder test failed: create_hidden_file failed. Errorcode: %d\n", bytes_written);
      return false;
    }

  hidden_filename = "test2.txt";
  hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
  if (hidden_file == NULL)
    {
      printf ("test_bmp_folder test failed: create_hidden_file failed and returned NULL.\n");
      return false;
    }
  test_buffer = "My testbuffer2!";
  bytes_written = stgfs_write ("/test2.txt", test_buffer, 16, 0, (struct fuse_file_info *) hidden_fat);
  if (bytes_written < 0)
    {
      printf ("test_bmp_folder test failed: create_hidden_file failed. Errorcode: %d\n", bytes_written);
      return false;
    }
  show_hidden_fat (hidden_fat, NULL);
  bool ret = steganofs_unload_ramdisk (hidden_fat, "./examples/pictures");
  if (!ret)
    {
      printf ("test_bmp_folder test failed: Unloading ramdisk failed!\n");
      return false;
    }
  free_hidden_fat (hidden_fat);
  hidden_fat = steganofs_load_ramdisk ("./examples/pictures");
  if (hidden_fat == NULL)
    {
      printf ("test_bmp_folder test failed: Loading ramdisk failed!\n");
      return false;
    }
  ret = steganofs_unload_ramdisk (hidden_fat, "./examples/pictures");
  if (!ret)
    {
      printf ("test_bmp_folder test failed: Unloading ramdisk failed!\n");
      return false;
    }
  show_hidden_fat (hidden_fat, NULL);
  ret = check_integrity (hidden_fat);
  if (!ret)
    {
      printf ("test_bmp_folder test failed: Integrity check failed!\n");
      return false;
    }
  free_hidden_fat (hidden_fat);
  return ret;
}

int main(int argc, char** argv) {
    if (test_bmp_folder()) {
        return 0;
    }
    return 1;
}
