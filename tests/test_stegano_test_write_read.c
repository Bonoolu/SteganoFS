#include "../steganofs/steganofs.h"

/**
 * @brief Test function for writing and reading data from the filesystem.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return `true` if the test passes, otherwise `false`.
 */
bool test_write_read ()
{
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 4, STEGANOFS_BLOCK_SIZE);
  const char *hidden_filename = "test.txt";
  long timestamp = time (NULL);
  HiddenFile **hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
  if (hidden_file == NULL)
    {
      printf ("testWrite test failed: create_hidden_file failed and returned NULL.\n");
      return false;
    }
  const char *test_buffer = "My testbuffer!";
  int bytes_written = stgfs_write ("/test.txt", test_buffer, 15, 0, (struct fuse_file_info *) hidden_fat);
  if (bytes_written < 0)
    {
      printf ("testWrite test failed: Errorcode: %d\n", bytes_written);
      return false;
    }
  if (bytes_written != 15)
    {
      printf ("testWrite test failed: wrote %d bytes instead of 15\n", bytes_written);
      return false;
    }
  printf ("Printing hiddenFat->Disk to terminal: %s\n", hidden_fat->disk);
  check_for_fragmentation (hidden_fat);
  show_hidden_fat (hidden_fat, NULL);
  char output[20];
  memset (output, 0, 20);
  stgfs_read ("/test.txt", output, 15, 0, (struct fuse_file_info *) hidden_fat);
  printf ("Printing result of stgfs_read: %s\n", output);
  bool ret = check_integrity (hidden_fat);
  free_hidden_fat (hidden_fat);
  return ret;
}

int main(int argc, char** argv) {
    if (test_write_read()) {
        return 0;
    }
    return 1;
}
