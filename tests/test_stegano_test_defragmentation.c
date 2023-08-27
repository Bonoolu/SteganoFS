#include "../steganofs/steganofs.h"

/**
 * @brief Test function for defragmenting the filesystem.
 * @return `true` if the test passes, otherwise `false`.
 */
bool test_defragmentation ()
{
  // Create a valid file
  HiddenFat *hidden_fat = create_hidden_fat (48, 4);

  HiddenFile **hidden_file = create_hidden_file (hidden_fat, "cats.gif", time (NULL));
  if (hidden_file == NULL)
    {
      printf ("test_defragmentation test failed: createFile failed and returned NULL.\n");
      return false;
    }
  const char *cat_buffer = "cat0cat1";
  stgfs_write ("/cats.gif", cat_buffer, strlen (cat_buffer) + 1, 0, (struct fuse_file_info *) hidden_fat);

  hidden_file = create_hidden_file (hidden_fat, "dog.gif", time (NULL));
  if (hidden_file == NULL)
    {
      printf ("test_defragmentation test failed: createFile failed and returned NULL.\n");
      return false;
    }
  const char *dog_buffer = "dog";
  stgfs_write ("/dog.gif", dog_buffer, strlen (dog_buffer) + 1, 0, (struct fuse_file_info *) hidden_fat);

  hidden_file = create_hidden_file (hidden_fat, "birds.gif", time (NULL));
  if (hidden_file == NULL)
    {
      printf ("test_defragmentation test failed: createFile failed and returned NULL.\n");
      return false;
    }
  const char *bird_buffer = "bird0bird1";
  stgfs_write ("/birds.gif", bird_buffer, strlen (bird_buffer) + 1, 0, (struct fuse_file_info *) hidden_fat);

  show_hidden_fat (hidden_fat, NULL);
  char output[20];
  memset (output, 0, 20);
  stgfs_read ("/cats.gif", output, strlen (cat_buffer) + 1, 0, (struct fuse_file_info *) hidden_fat);
  printf ("Printing result of stgfs_read: %s\n", output);
  memset (output, 0, 20);
  stgfs_read ("/birds.gif", output, strlen (bird_buffer) + 1, 0, (struct fuse_file_info *) hidden_fat);
  printf ("Printing result of stgfs_read: %s\n", output);

  HiddenFile *dog = find_file_by_path (hidden_fat, "/dog.gif");
  HiddenFile *cat = find_file_by_path (hidden_fat, "/cats.gif");
  HiddenFile *bird = find_file_by_path (hidden_fat, "/birds.gif");

  size_t a = 0, b = 0;
  srand (time (NULL));

  // shuffle blocks 1000 times
  for (size_t i = 0; i < 1000; i++)
    {
      a = rand () % 12;
      b = rand () % 12;
      swap_hidden_clusters (hidden_fat, a, b);
    }

  // delete a file
  delete_hidden_file (hidden_fat, "dog.gif");

  // shuffle again
  for (size_t i = 0; i < 1000; i++)
    {
      a = rand () % 12;
      b = rand () % 12;
      swap_hidden_clusters (hidden_fat, a, b);
    }

  memset (output, 0, 20);
  stgfs_read ("/cats.gif", output, strlen (cat_buffer) + 1, 0, (struct fuse_file_info *) hidden_fat);
  printf ("Printing result of stgfs_read: %s\n", output);
  memset (output, 0, 20);
  stgfs_read ("/birds.gif", output, strlen (bird_buffer) + 1, 0, (struct fuse_file_info *) hidden_fat);
  printf ("Printing result of stgfs_read: %s\n", output);
  show_hidden_fat (hidden_fat, NULL);
  check_for_fragmentation (hidden_fat);
  defragmentate (hidden_fat);
  show_hidden_fat (hidden_fat, NULL);
  check_for_fragmentation (hidden_fat);

  memset (output, 0, 20);
  stgfs_read ("/cats.gif", output, strlen (cat_buffer) + 1, 0, (struct fuse_file_info *) hidden_fat);
  printf ("Printing result of stgfs_read: %s\n", output);
  memset (output, 0, 20);
  stgfs_read ("/birds.gif", output, strlen (bird_buffer) + 1, 0, (struct fuse_file_info *) hidden_fat);
  printf ("Printing result of stgfs_read: %s\n", output);
  bool integrity = check_integrity (hidden_fat);
  free_hidden_fat (hidden_fat);
  return integrity;
}

int main(int argc, char** argv) {
    if (test_defragmentation()) {
        return 0;
    }
    return 1;
}
