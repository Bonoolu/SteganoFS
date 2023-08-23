#include "../../steganofs/steganofs.h"

bool test_create_hidden_fat ()
{
  size_t disk_size = STEGANOFS_BLOCK_SIZE * 4;  // Example disk size
  size_t block_size = STEGANOFS_BLOCK_SIZE;  // Example block size
  HiddenFat *hidden_fat = create_hidden_fat (disk_size, block_size);
  bool passed = true;
  if (hidden_fat == NULL)
    {
      printf ("test_create_hidden_fat test failed: Failed to stgfs_create the HiddenFat structure.\n");
      passed = false;
    }

  // Verify the blockSize and amountBlocks values
  if (hidden_fat->block_size != block_size)
    {
      printf ("test_create_hidden_fat test failed: Incorrect blockSize value.\n");
      passed = false;
    }

  size_t expected_amount_blocks = disk_size / block_size;
  if (hidden_fat->amount_blocks != expected_amount_blocks)
    {
      printf ("test_create_hidden_fat test failed: Incorrect amountBlocks value.\n");
      passed = false;
    }

  // Verify the disk and blocks arrays
  if (hidden_fat->disk == NULL)
    {
      printf ("test_create_hidden_fat test failed: Disk array is not allocated.\n");
      passed = false;
    }

  if (hidden_fat->clusters == NULL)
    {
      printf ("test_create_hidden_fat test failed: Blocks array is not allocated.\n");
      passed = false;
    }

  // Check if the disk and blocks arrays are properly initialized
  for (size_t i = 0; i < disk_size; i++)
    {
      if (hidden_fat->disk[i] != 0)
        {
          printf ("test_create_hidden_fat test failed: Disk array is not properly initialized.\n");
          passed = false;
        }
    }

  for (size_t i = 0; i < expected_amount_blocks; i++)
    {
      if (hidden_fat->clusters[i].state != FREE || hidden_fat->clusters[i].b_index != i)
        {
          printf ("test_create_hidden_fat test failed: Blocks array is not properly initialized.\n");
          passed = false;
        }
    }

  // Check if all Cluster Block Associations are not NULL
  for (size_t b_index = 0; b_index < hidden_fat->amount_blocks; b_index++)
    {
      if (hidden_fat->clusters[b_index].prev != NULL || hidden_fat->clusters[b_index].next != NULL)
        {
          printf ("test_create_hidden_fat test failed: Cluster associated with block %zu was not freed.\n", b_index);
          passed = false;
          break;
        }
    }

  // Cleanup
  free_hidden_fat (hidden_fat);
  if (passed)
    printf ("test_create_hidden_fat test passed.\n");
  return passed;
}

bool test_get_free_disk_space_empty_fat ()
{
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 4, STEGANOFS_BLOCK_SIZE);
  size_t free_space = get_free_disk_space (hidden_fat);
  bool passed;
  if (free_space == STEGANOFS_BLOCK_SIZE * 4)
    {
      printf ("test_get_free_disk_space_empty_fat test passed.\n");
      passed = true;
    }
  else
    {
      printf (
          "test_get_free_disk_space_empty_fat test failed: Expected free disk space: 1024 bytes, Actual free disk space: %zu bytes.\n",
          free_space);
      passed = false;
    }
  free_hidden_fat (hidden_fat);
  return passed;
}

bool test_get_free_disk_space_with_allocated_blocks ()
{
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 4, STEGANOFS_BLOCK_SIZE);
  // Allocate some blocks or create files within the filesystem
  // Perform actions to allocate blocks or create files
  for (size_t i = 0; i < 2; i++)
    {
      hidden_fat->clusters[i].state = ALLOCATED;
    }
  size_t free_space = get_free_disk_space (hidden_fat);
  // Calculate the expected free space based on the allocated blocks/files
  size_t expected_free_space =
      STEGANOFS_BLOCK_SIZE * 2;  // Calculate the expected value based on the specific test case
  bool passed;
  if (free_space == expected_free_space)
    {
      printf ("test_get_free_disk_space_with_allocated_blocks test passed.\n");
      passed = true;
    }
  else
    {
      printf (
          "test_get_free_disk_space_with_allocated_blocks test failed: Expected free disk space: %zu bytes, Actual free disk space: %zu bytes.\n",
          expected_free_space,
          free_space);
      passed = false;
    }
  free_hidden_fat (hidden_fat);
  return passed;
}

bool test_get_free_disk_space_full_disk ()
{
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE, STEGANOFS_BLOCK_SIZE);
  // Allocate all blocks or create files until the disk is full
  hidden_fat->clusters->state = ALLOCATED;
  // Perform actions to allocate blocks or create files
  size_t free_space = get_free_disk_space (hidden_fat);
  bool passed;
  if (free_space == 0)
    {
      printf ("test_get_free_disk_space_full_disk test passed.\n");
      passed = true;
    }
  else
    {
      printf (
          "test_get_free_disk_space_full_disk test failed: Expected free disk space: 0 bytes, Actual free disk space: %zu bytes.\n",
          free_space);
      passed = false;
    }
  free_hidden_fat (hidden_fat);
  return passed;
}

bool test_create_file_valid ()
{
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 4, STEGANOFS_BLOCK_SIZE);

  const char *hidden_filename = "cats.gif";
  long timestamp = time (NULL);
  bool passed = true;

  HiddenFile **hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
  if (hidden_file == NULL)
    {
      printf ("test_create_file_valid test failed: Failed to stgfs_create file.\n");
      passed = false;
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_create_file_valid test failed: Integrity check failed!.\n");
      passed = false;
    }

  if (passed)
    printf ("test_create_file_valid test passed.\n");
  return passed;
}

bool test_create_file_insufficient_memory ()
{
  fflush (stdout);
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 4, STEGANOFS_BLOCK_SIZE);
  const char *hidden_filename = "dogs.gif";
  long timestamp = time (NULL);
  bool passed = true;

  HiddenFile **hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
  if (hidden_file == NULL)
    {
      printf ("test_create_file_insufficient_memory test failed: create_hidden_file failed and returned NULL.\n");
      return false;
    }
  bool allocated = true;
  for (int i = 0; i < hidden_fat->amount_blocks + 1 && allocated; i++)
    { // Larger than available memory
      allocated = extend_hidden_cluster (hidden_fat, *hidden_file);
    }
  if (allocated)
    {
      printf ("test_create_file_insufficient_memory test failed: File created despite insufficient memory.\n");
      passed = false;
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_create_file_insufficient_memory test failed: Integrity check failed!.\n");
      passed = false;
    }

  if (passed)
    printf ("test_create_file_insufficient_memory test passed.\n");
  fflush (stderr);
  return passed;
}

bool test_create_file_no_available_file_slot ()
{
  fflush (stdout);
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 4, STEGANOFS_BLOCK_SIZE);
  printf ("Free Space is now: %zu\n", get_free_disk_space (hidden_fat));
  const char *hidden_filename = "bears.gif";
  long timestamp = time (NULL);
  bool passed = true;

  // Fill all available file slots
  for (size_t i = 0; i < STEGANOFS_AMOUNT_ROOT_FILES; i++)
    {
      HiddenFile **hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
      if (hidden_file == NULL)
        {
          printf ("test_create_file_no_available_file_slot test failed: create_hidden_file failed and returned NULL.\n");
          return false;
        }
    }

  HiddenFile **hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
  if (hidden_file != NULL)
    {
      printf ("test_create_file_no_available_file_slot test failed: File created despite no available file slot.\n");
      passed = false;
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_create_file_no_available_file_slot test failed: Integrity check failed!.\n");
      passed = false;
    }

  if (passed)
    printf ("test_create_file_no_available_file_slot test passed.\n");
  fflush (stderr);
  return passed;
}

bool test_create_file_linked_list ()
{
  // Create a file with multiple clusters
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 4, STEGANOFS_BLOCK_SIZE);
  const char *hidden_filename = "dogs.gif";
  long timestamp = time (NULL);
  HiddenFile **hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
  if (hidden_file == NULL)
    {
      printf ("test_create_file_linked_list test failed: create_hidden_file failed and returned NULL.\n");
      return false;
    }
  extend_hidden_cluster (hidden_fat, *hidden_file);
  extend_hidden_cluster (hidden_fat, *hidden_file);

  // Verify the linked list inside the clusters
  bool passed = true;
  size_t cluster_index = 0;
  size_t expected_b_index = (*hidden_file)->hiddenCluster->b_index;
  HiddenCluster *hidden_cluster = (*hidden_file)->hiddenCluster;

  while (hidden_cluster != NULL)
    {
      if (hidden_cluster->b_index != expected_b_index)
        {
          printf ("test_create_file_linked_list test failed: Incorrect b_index in the cluster.\n");
          passed = false;
          break;
        }

      if (hidden_cluster->file != *hidden_file)
        {
          printf ("test_create_file_linked_list test failed: Incorrect fileIndex in the cluster.\n");
          passed = false;
          break;
        }

      if (hidden_cluster->cluster_index != cluster_index)
        {
          printf ("test_create_file_linked_list test failed: Incorrect cluster_index in the cluster. Got %zu, but expected %zu\n",
                  hidden_cluster->cluster_index, cluster_index);
          passed = false;
          break;
        }

      expected_b_index++;
      cluster_index++;
      hidden_cluster = hidden_cluster->next;
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_create_file_linked_list test failed: Integrity check failed!.\n");
      passed = false;
    }

  if (passed)
    printf ("test_create_file_linked_list test passed.\n");
  return passed;
}

bool test_delete_file_valid ()
{
  // Create a valid file
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 4, STEGANOFS_BLOCK_SIZE);
  const char *hidden_filename = "cats.gif";
  long timestamp = time (NULL);
  HiddenFile **hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
  if (hidden_file == NULL)
    {
      printf ("test_delete_file_valid test failed: create_hidden_file failed and returned NULL.\n");
      return false;
    }

  // Delete the file
  delete_hidden_file (hidden_fat, hidden_filename);

  // Check if the file was successfully deleted
  bool passed = true;
  for (size_t i = 0; i < STEGANOFS_AMOUNT_ROOT_FILES; i++)
    {
      if (hidden_fat->files[i] != NULL && strcmp (hidden_fat->files[i]->filename, hidden_filename) == 0)
        {
          printf ("test_delete_file_valid test failed: File still exists in the file table.\n");
          passed = false;
          break;
        }
    }

  if (*hidden_file != NULL)
    {
      printf ("test_delete_file_valid test failed: File structure still exists.\n");
      passed = false;
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_delete_file_valid test failed: Integrity check failed!.\n");
      passed = false;
    }

  if (passed)
    printf ("test_delete_file_valid test passed.\n");
  return passed;
}

bool test_delete_file_non_existent ()
{
  // Create a valid file
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 4, STEGANOFS_BLOCK_SIZE);
  const char *hidden_filename = "cats.gif";
  long timestamp = time (NULL);
  HiddenFile **hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
  if (hidden_file == NULL)
    {
      printf ("test_delete_file_valid test failed: createFile failed and returned NULL.\n");
      return false;
    }
  // Delete a non-existent file
  const char *non_existent_filename = "dogs.gif";
  delete_hidden_file (hidden_fat, non_existent_filename);

  // Check if the file table remains unchanged
  bool passed = true;

  if (*hidden_file == NULL)
    {
      printf ("test_delete_file_non_existent test failed: File in the file table was incorrectly deleted.\n");
      passed = false;
    }

  if (strcmp ((*hidden_file)->filename, hidden_filename) != 0)
    {
      printf ("test_delete_file_non_existent test failed: File in the file table was incorrectly deleted.\n");
      passed = false;
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_delete_file_non_existent test failed: Integrity check failed!.\n");
      passed = false;
    }

  if (passed)
    printf ("test_delete_file_non_existent test passed.\n");
  return passed;
}

bool test_delete_file_with_clusters ()
{
  // Check if the associated clusters were freed
  bool passed = true;

  // Create a file with clusters
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 4, STEGANOFS_BLOCK_SIZE);

  const char *hidden_filename = "cats.gif";
  long timestamp = time (NULL);
  HiddenFile **hidden_file = create_hidden_file (hidden_fat, hidden_filename, timestamp);
  if (hidden_file == NULL)
    {
      printf ("test_delete_file_valid test failed: createFile failed and returned NULL.\n");
      return false;
    }
  const char *test_buffer = "My testbuffer!";
  stgfs_write ("/cats.gif", test_buffer, 15, 0, (struct fuse_file_info *) hidden_fat);

  // Delete the file
  delete_hidden_file (hidden_fat, hidden_filename);

  // Check if the associated clusters were freed
  unsigned char zero_block[STEGANOFS_BLOCK_SIZE];
  memset (zero_block, 0, sizeof zero_block);
  for (size_t b_index = 0; b_index < hidden_fat->amount_blocks; b_index++)
    {
      if (memcmp (zero_block, hidden_fat->disk + (b_index * STEGANOFS_BLOCK_SIZE), STEGANOFS_BLOCK_SIZE) != 0)
        {
          printf ("test_delete_file_with_clusters test failed: Cluster associated with block %zu was not freed.\n",
                  b_index);
          passed = false;
          break;
        }
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_delete_file_with_clusters test failed: Integrity check failed!.\n");
      passed = false;
    }

  if (passed)
    printf ("test_delete_file_with_clusters test passed.\n");
  return passed;
}

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

bool test_swap_hidden_clusters_integrity ()
{
  HiddenFat *hidden_fat = create_hidden_fat (STEGANOFS_BLOCK_SIZE * 20, STEGANOFS_BLOCK_SIZE);
  bool passed = true;

  // Swap the same block
  bool swap_result = swap_hidden_clusters (hidden_fat, 0, 0);
  if (swap_result)
    {
      printf ("test_swap_hidden_clusters_integrity test failed: Failed to NOT swap the same Block!\n");
      passed = false;
    }

  // Swap two allocated Blocks
  create_hidden_file (hidden_fat, "file1", time (NULL));
  const char *test_1_buffer = "My file1";
  stgfs_write ("/file1", test_1_buffer, 9, 0, (struct fuse_file_info *) hidden_fat);

  create_hidden_file (hidden_fat, "file2", time (NULL));
  const char *test_2_buffer = "My file2";
  stgfs_write ("/file2", test_2_buffer, 9, 0, (struct fuse_file_info *) hidden_fat);
  swap_result = swap_hidden_clusters (hidden_fat, 0, 1);
  fflush (stdout);
  fflush (stderr);
  if (!swap_result || strcmp (hidden_fat->clusters[0].file->filename, "file2") != 0
      || strcmp (hidden_fat->clusters[1].file->filename, "file1") != 0)
    {
      printf ("test_swap_hidden_clusters_integrity test failed: Failed to swap two Blocks!\n");
      fflush (stdout);
      passed = false;
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_swap_hidden_clusters_integrity test failed: Integrity check failed!.\n");
      fflush (stdout);
      passed = false;
    }

  // Swapping a free block with an allocated block
  create_hidden_file (hidden_fat, "file3", time (NULL));
  const char *test_3_buffer = "My file3";
  stgfs_write ("/file3", test_3_buffer, 9, 0, (struct fuse_file_info *) hidden_fat);

  //swapResult = swapHiddenClusters(hiddenFat, 2, 3);
  if (!swap_result || strcmp (hidden_fat->clusters[2].file->filename, "file3") != 0)
    {
      printf ("test_swap_hidden_clusters_integrity test failed: Failed to swap a free block with an allocated block.\n");
      passed = false;
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_swap_hidden_clusters_integrity test failed: Integrity check failed!.\n");
      passed = false;
    }


  // Swapping a free block with a defect block
  hidden_fat->clusters[4].state = DEFECT;
  swap_result = swap_hidden_clusters (hidden_fat, 4, 5);
  if (swap_result || hidden_fat->clusters[4].state != DEFECT)
    {
      printf ("test_swap_hidden_clusters_integrity test failed: Failed to NOT swap a free block with a defect block.\n");
      passed = false;
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_swap_hidden_clusters_integrity test failed: Integrity check failed!.\n");
      passed = false;
    }

  // Swapping a free block with a reserved block
  hidden_fat->clusters[6].state = RESERVED;
  swap_result = swap_hidden_clusters (hidden_fat, 6, 7);
  if (swap_result || hidden_fat->clusters[6].state != RESERVED)
    {
      printf ("test_swap_hidden_clusters_integrity test failed: Failed to NOT swap a free block with a defect block.\n");
      passed = false;
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_swap_hidden_clusters_integrity test failed: Integrity check failed!.\n");
      passed = false;
    }

  // Swapping two free blocks!
  swap_result = swap_hidden_clusters (hidden_fat, 8, 9);
  if (swap_result)
    {
      printf ("test_swap_hidden_clusters_integrity test failed: Failed to NOT swap two free blocks!\n");
      passed = false;
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_swap_hidden_clusters_integrity test failed: Integrity check failed!.\n");
      passed = false;
    }

  // Swapping a free block with a defect block
  create_hidden_file (hidden_fat, "file4", time (NULL));
  const char *test_4_buffer = "My file4";
  stgfs_write ("/file4", test_2_buffer, 9, 0, (struct fuse_file_info *) hidden_fat);
  size_t b_index = find_file_by_path (hidden_fat, "/file4")->hiddenCluster->b_index;
  swap_result = swap_hidden_clusters (hidden_fat, 0, 1);

  hidden_fat->clusters[10].state = RESERVED;

  swap_result = swap_hidden_clusters (hidden_fat, 10, 11);

  if (swap_result || strcmp (hidden_fat->clusters[b_index].file->filename, "file4") != 0 ||
      hidden_fat->clusters[10].state != RESERVED)
    {
      printf ("test_swap_hidden_clusters_integrity test failed: Failed to NOT swap a free block with a defect block\n");
      passed = false;
    }

  if (!check_integrity (hidden_fat))
    {
      printf ("test_swap_hidden_clusters_integrity test failed: Integrity check failed!.\n");
      passed = false;
    }

  free_hidden_fat (hidden_fat);
  return passed;
}

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

bool test_write_read (int argc, char **argv)
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
  return check_integrity (hidden_fat);
}

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
  bool ret = steganofs_unload_ramdisk (hidden_fat, "/tmp/filesystem.steganofs");
  if (!ret)
    {
      printf ("test_ramdiskloader test failed: Unloading ramdisk failed!\n");
      return false;
    }
  free_hidden_fat (hidden_fat);
  hidden_fat = steganofs_load_ramdisk ("/tmp/filesystem.steganofs");
  if (hidden_fat == NULL)
    {
      printf ("test_ramdiskloader test failed: Loading ramdisk failed!\n");
      return false;
    }
  ret = steganofs_unload_ramdisk (hidden_fat, "/tmp/filesystem2.steganofs");
  if (!ret)
    {
      printf ("test_ramdiskloader test failed: Unloading ramdisk failed!\n");
      return false;
    }
  show_hidden_fat (hidden_fat, NULL);
  ret = check_integrity (hidden_fat);
  if (!ret)
    {
      printf ("test_ramdiskloader test failed: Integrity check failed!\n");
      return false;
    }
  free_hidden_fat (hidden_fat);
  return ret;
}

bool test_rle ()
{
  HiddenFat *hidden_fat = create_hidden_fat (10, 2);
  create_hidden_file (hidden_fat, "test.txt", time (NULL));
  unsigned char testbuffer[4] = "abc";
  stgfs_write ("/test.txt", (char *) testbuffer, 4, 0, (struct fuse_file_info *) hidden_fat);
  struct SerializedFilesystem serialized_filesystem = serialize_filesystem (hidden_fat);
  unsigned char *buffer_before = malloc (serialized_filesystem.size);
  memcpy (buffer_before, serialized_filesystem.buf, serialized_filesystem.size);
  run_length_encoding (&serialized_filesystem);
  run_length_decoding (&serialized_filesystem);
  int ret = memcmp (buffer_before, serialized_filesystem.buf, serialized_filesystem.size);
  printf ("Memory comparison value is %d\n", ret);
  if (ret == 0)
    {
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
  return false;
}

void run_tests (int argc, char **argv)
{
  int tests[] = {
      test_create_hidden_fat (),
      test_get_free_disk_space_empty_fat (),
      test_get_free_disk_space_with_allocated_blocks (),
      test_get_free_disk_space_full_disk (),
      test_create_file_valid (),
      test_create_file_insufficient_memory (),
      test_create_file_no_available_file_slot (),
      test_create_file_linked_list (),
      test_delete_file_valid (),
      test_delete_file_non_existent (),
      test_delete_file_with_clusters (),
      test_show_n_block_fat (1, 23),
      test_show_n_block_fat (239, 504),
      test_show_n_block_fat (240, 507),
      test_show_n_block_fat (241, 509),
      test_show_n_block_fat (242, 509),
      test_write_read (argc, argv),
      test_swap_hidden_clusters_integrity (),
      test_defragmentation (),
      test_ramdiskloader (),
      test_rle (),
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

int main (int argc, char **argv)
{
  run_tests (argc, argv);
  return 0;//test_fuse(argc, argv);
}