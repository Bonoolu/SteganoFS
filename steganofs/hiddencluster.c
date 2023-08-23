#include "hiddencluster.h"

bool extend_hidden_cluster (HiddenFat *hidden_fat, HiddenFile *p_file)
{
  size_t b_index;
  for (b_index = 0; b_index < hidden_fat->amount_blocks; b_index++)
    {
      if (hidden_fat->clusters[b_index].state == FREE)
        {
          break;
        }
      if (b_index == hidden_fat->amount_blocks - 1)
        {
          fprintf (stderr, "Partition is full!\n");
          return false;
        }
    }
  // Allocate the block for the file
  hidden_fat->clusters[b_index].state = ALLOCATED;
  hidden_fat->clusters[b_index].b_index = b_index;
  int cluster_index = 0;
  HiddenCluster *last_cluster = p_file->hiddenCluster;
  while (last_cluster)
    {
      cluster_index++;
      if (last_cluster->next == NULL)
        {
          break;
        }
      last_cluster = last_cluster->next;
    }
  if (last_cluster != NULL)
    {
      hidden_fat->clusters[b_index].prev = last_cluster;
      last_cluster->next = &(hidden_fat->clusters[b_index]);
    }
  else
    {
      p_file->hiddenCluster = &(hidden_fat->clusters[b_index]);
    }
  hidden_fat->clusters[b_index].cluster_index = cluster_index;
  hidden_fat->clusters[b_index].file = p_file;
  p_file->filesize += hidden_fat->block_size;
  return true;
}

bool swap_hidden_clusters (HiddenFat *hidden_fat, size_t b_index_a, size_t b_index_b)
{
  if (b_index_a == b_index_b)
    {
      // fprintf(stderr, "Swapping the same block is not possible!\n");
      return false;
    }
  if (b_index_a >= hidden_fat->amount_blocks || b_index_b >= hidden_fat->amount_blocks)
    {
      fprintf (stderr, "Invalid block indices for swap_hidden_clusters.\n");
      return false;
    }
  if (hidden_fat->clusters[b_index_a].state == FREE && hidden_fat->clusters[b_index_b].state == FREE)
    {
      // fprintf(stderr, "No need to swap two free Blocks!\n");
      return false;
    }
  if (hidden_fat->clusters[b_index_a].state == RESERVED || hidden_fat->clusters[b_index_b].state == RESERVED)
    {
      fprintf (stderr, "\"Invalid block for swap_hidden_clusters! Can't swap with a reserved block!\n");
      return false;
    }
  if (hidden_fat->clusters[b_index_a].state == DEFECT || hidden_fat->clusters[b_index_b].state == DEFECT)
    {
      fprintf (stderr, "\"Invalid block for swap_hidden_clusters! Can't swap with a defect block!\n");
      return false;
    }

  size_t cluster_index_cluster_a = hidden_fat->clusters[b_index_a].cluster_index;
  unsigned int state_cluster_a = hidden_fat->clusters[b_index_a].state;
  HiddenCluster *prev_cluster_a = hidden_fat->clusters[b_index_a].prev;
  HiddenCluster *next_cluster_a = hidden_fat->clusters[b_index_a].next;
  HiddenFile *file_cluster_a = hidden_fat->clusters[b_index_a].file;

  hidden_fat->clusters[b_index_a].cluster_index = hidden_fat->clusters[b_index_b].cluster_index;
  hidden_fat->clusters[b_index_a].state = hidden_fat->clusters[b_index_b].state;
  hidden_fat->clusters[b_index_a].prev = hidden_fat->clusters[b_index_b].prev;
  hidden_fat->clusters[b_index_a].next = hidden_fat->clusters[b_index_b].next;
  hidden_fat->clusters[b_index_a].file = hidden_fat->clusters[b_index_b].file;

  hidden_fat->clusters[b_index_b].cluster_index = cluster_index_cluster_a;
  hidden_fat->clusters[b_index_b].state = state_cluster_a;
  hidden_fat->clusters[b_index_b].prev = prev_cluster_a;
  hidden_fat->clusters[b_index_b].next = next_cluster_a;
  hidden_fat->clusters[b_index_b].file = file_cluster_a;

  if (hidden_fat->clusters[b_index_a].next == &(hidden_fat->clusters[b_index_a]))
    {
      hidden_fat->clusters[b_index_a].next = &(hidden_fat->clusters[b_index_b]);
    }
  if (hidden_fat->clusters[b_index_a].prev == &(hidden_fat->clusters[b_index_a]))
    {
      hidden_fat->clusters[b_index_a].prev = &(hidden_fat->clusters[b_index_b]);
    }
  if (hidden_fat->clusters[b_index_b].next == &(hidden_fat->clusters[b_index_b]))
    {
      hidden_fat->clusters[b_index_b].next = &(hidden_fat->clusters[b_index_a]);
    }
  if (hidden_fat->clusters[b_index_b].prev == &(hidden_fat->clusters[b_index_b]))
    {
      hidden_fat->clusters[b_index_b].prev = &(hidden_fat->clusters[b_index_a]);
    }

  if (hidden_fat->clusters[b_index_a].prev != NULL)
    {
      hidden_fat->clusters[b_index_a].prev->next = &(hidden_fat->clusters[b_index_a]);
    }
  else if (hidden_fat->clusters[b_index_a].file != NULL)
    {
      hidden_fat->clusters[b_index_a].file->hiddenCluster = &(hidden_fat->clusters[b_index_a]);
    }

  if (hidden_fat->clusters[b_index_a].next != NULL)
    {
      hidden_fat->clusters[b_index_a].next->prev = &(hidden_fat->clusters[b_index_a]);
    }

  if (hidden_fat->clusters[b_index_b].prev != NULL)
    {
      hidden_fat->clusters[b_index_b].prev->next = &(hidden_fat->clusters[b_index_b]);
    }
  else if (hidden_fat->clusters[b_index_b].file != NULL)
    {
      hidden_fat->clusters[b_index_b].file->hiddenCluster = &(hidden_fat->clusters[b_index_b]);
    }

  if (hidden_fat->clusters[b_index_b].next != NULL)
    {
      hidden_fat->clusters[b_index_b].next->prev = &(hidden_fat->clusters[b_index_b]);
    }

  size_t block_size = hidden_fat->block_size;
  // Swap blocks on disk
  unsigned char buffer_a[block_size];
  memcpy (buffer_a, hidden_fat->disk + (block_size * b_index_a), block_size);
  memcpy (hidden_fat->disk + (block_size * b_index_a), hidden_fat->disk + (block_size * b_index_b), block_size);
  memcpy (hidden_fat->disk + (block_size * b_index_b), buffer_a, block_size);

  return true;
}