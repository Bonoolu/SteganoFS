#include "../steganofs/steganofs.h"

/**
 * @brief Test function for testing Run Length Encoding (RLE).
 * @return `true` if the test passes, otherwise `false`.
 */
bool test_rle ()
{
  HiddenFat *hidden_fat = create_hidden_fat (10, 2);
  create_hidden_file (hidden_fat, "test.txt", time (NULL));
  unsigned char testbuffer[4] = "abc";
  stgfs_write ("/test.txt", (char *) testbuffer, 4, 0, (struct fuse_file_info *) hidden_fat);
  struct SerializedFilesystem serialized_filesystem = serialize_filesystem (hidden_fat);
  unsigned char *buffer_before = malloc (serialized_filesystem.size); // see free() below
  memcpy (buffer_before, serialized_filesystem.buf, serialized_filesystem.size);
  run_length_encoding (&serialized_filesystem);
  run_length_decoding (&serialized_filesystem);
  int ret = memcmp (buffer_before, serialized_filesystem.buf, serialized_filesystem.size);
  printf ("Memory comparison value is %d\n", ret);
  if (ret == 0)
    {
      free(buffer_before);
      return true;
    }
  for (size_t i = 0; i < serialized_filesystem.size; i++)
    {
      if (buffer_before[i] != serialized_filesystem.buf[i])
        {
          unsigned char *before_pointer = buffer_before + i;
          unsigned char *after_pointer = serialized_filesystem.buf + i;
          printf ("First difference is at offset %zu!\n", i);
          break;
        }
    }
  free(buffer_before);
  free_hidden_fat (hidden_fat);
  return false;
}

int main(int argc, char** argv) {
    if (test_rle()) {
        return 0;
    }
    return 1;
}
