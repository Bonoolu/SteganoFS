#include "../steganofs/steganofs.h"

/**
 * @brief Test function for creating a hidden file with linked cluster blocks.
 * @return `true` if the test passes, otherwise `false`.
 */
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
  free_hidden_fat (hidden_fat);
  return passed;
}

int main(int argc, char** argv) {
    if (test_create_file_linked_list()) {
        return 0;
    }
    return 1;
}
