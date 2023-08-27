#include "../steganofs/steganofs.h"

/**
 * @brief Tests the integrity of hidden clusters swapping.
 *
 * This function tests whether swapping of hidden clusters maintains the integrity
 * of the data structure.
 *
 * @return `true` if hidden cluster swapping passes integrity check, otherwise `false`.
 */
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

int main(int argc, char** argv) {
    if (test_swap_hidden_clusters_integrity()) {
        return 0;
    }
    return 1;
}
