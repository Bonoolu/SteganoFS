#include "../../steganofs/steganofs.h"

/**
 * @file test_bmp_provider.c
 * @brief This file contains a test suite for the BMP Provider implementation.
 */

/**
 * @brief Test the functions for generic buffer manipulation.
 *
 * @return True if the test passes, false otherwise.
 */
bool test_generic_buffer ()
{
  unsigned char buffer_ff[17] = "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
                                "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF";
  unsigned char buffer_00[17] = "\x00\x00\x00\x00\x00\x00\x00"
                                "\x00\x00\x00\x00\x00\x00\x00";
  const size_t length = 16;
  unsigned char *extracted_buffer = NULL;
  size_t extracted_length = 0;

  exract_payload_from_generic_buffer (&extracted_buffer, &extracted_length, buffer_ff, length);
  printf ("The exracted bytes are %d and %d\n", extracted_buffer[0], extracted_buffer[1]);

  unsigned char payload[2] = {54, 27};
  size_t payload_length = 2;

  embedd_payload_in_generic_buffer (payload, payload_length, buffer_00);

  printf ("Buffer with payload:\n");
  for (size_t i = 0; i < length; i++)
    {
      printf ("%d", buffer_00[i]);
      if (i == 7 || i == 15)
        {
          printf ("\n");
        }
      else
        {
          printf (", ");
        }
    }
  return true;
}

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
  steganofs_unload_ramdisk (hidden_fat, "example.bmp");
  free_hidden_fat (hidden_fat);
  hidden_fat = steganofs_load_ramdisk ("example.bmp");
  if (!hidden_fat)
    {
      printf ("Could not load anything from example.bmp\n");
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

/**
 * @brief Test creating a folder with files and integrity check in a BMP image.
 *
 * @return True if the test passes, false otherwise.
 */
bool test_bmp_folder ()
{
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 100, BLOCK_SIZE);
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
  bool ret = steganofs_unload_ramdisk (hidden_fat, "example_pictures");
  if (!ret)
    {
      printf ("test_bmp_folder test failed: Unloading ramdisk failed!\n");
      return false;
    }
  free_hidden_fat (hidden_fat);
  hidden_fat = steganofs_load_ramdisk ("example_pictures");
  if (hidden_fat == NULL)
    {
      printf ("test_bmp_folder test failed: Loading ramdisk failed!\n");
      return false;
    }
  ret = steganofs_unload_ramdisk (hidden_fat, "example_pictures");
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

/**
 * @brief Test formatting a filesystem.
 *
 * @return True if the test passes, false otherwise.
 */
bool test_format_bmp_folder ()
{
  size_t filesystem_size = steganofs_format ("example_pictures");
  if (filesystem_size == 0)
    {
      printf ("test_format_bmp_folder test failed: formatted filesystem is of size 0.\n");
      return false;
    }
  printf ("Formatted filesystem is of size: %zu\n", filesystem_size);
  HiddenFat *hidden_fat = steganofs_load_ramdisk ("example_pictures");
  if (hidden_fat == NULL)
    {
      printf ("test_format_bmp_folder test failed: Loading ramdisk failed!\n");
      return false;
    }
  bool ret = steganofs_unload_ramdisk (hidden_fat, "example_pictures");
  if (!ret)
    {
      printf ("test_format_bmp_folder test failed: Unloading ramdisk failed!\n");
      return false;
    }
  show_hidden_fat (hidden_fat, NULL);
  ret = check_integrity (hidden_fat);
  if (!ret)
    {
      printf ("test_format_bmp_folder test failed: Integrity check failed!\n");
      return false;
    }
  free_hidden_fat (hidden_fat);
  return ret;
}

/**
 * @brief The main entry point for the test suite.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of pointers to command-line arguments.
 * @return 0 on successful execution.
 */

int main (int argc, char **argv)
{
  int tests[] = {
      test_generic_buffer (),
      test_single_bmp_file (),
      test_bmp_folder (),
      test_format_bmp_folder (),
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
  printf ("%zu/%zu tests passed!\n", passed, sum);
}