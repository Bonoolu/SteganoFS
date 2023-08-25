#include "hiddenfat.h"

HiddenFat *create_hidden_fat (size_t disk_size, size_t block_size)
{
  if (disk_size == 0 || block_size == 0)
    {
      fprintf (stderr, "Disk size and blockSize each can not be zero!\n");
      return NULL;
    }
  if (disk_size % block_size != 0)
    {
      fprintf (stderr, "Disk size is not dividable by block size!\n");
      return NULL;
    }
  unsigned char *disk = (unsigned char *) malloc (disk_size * sizeof (unsigned char)); // gets freed in free_hidden_fat
  if (!disk)
    {
      fprintf (stderr, "Could not allocate memory!\n");
      return NULL;
    }
  memset (disk, 0, disk_size);
  size_t amount_blocks = disk_size / block_size;
  HiddenCluster
      *clusters = (HiddenCluster *) malloc (amount_blocks * sizeof (HiddenCluster)); // gets freed in free_hidden_fat
  if (!clusters)
    {
      fprintf (stderr, "Could not allocate memory!\n");
      return NULL;
    }
  memset (clusters, 0, amount_blocks * sizeof (HiddenCluster));
  for (size_t b_index = 0; b_index < amount_blocks; b_index++)
    {
      clusters[b_index].b_index = b_index;
    }
  HiddenFat *hidden_fat = (HiddenFat *) malloc (sizeof (HiddenFat)); // gets freed in freeHiddenFat
  if (!hidden_fat)
    {
      fprintf (stderr, "Could not allocate memory!\n");
      return NULL;
    }
  memset (hidden_fat->files, 0, STEGANOFS_AMOUNT_ROOT_FILES * sizeof (HiddenFile *));
  hidden_fat->block_size = block_size;
  hidden_fat->amount_blocks = amount_blocks;
  hidden_fat->disk = disk;
  hidden_fat->clusters = clusters;
  return hidden_fat;
}

void free_hidden_fat (HiddenFat *hidden_fat)
{
  if (hidden_fat == NULL)
    {
      return;
    }

  // Free the disk memory
  free (hidden_fat->disk);

  // Free the clusters structures
  free (hidden_fat->clusters);

  // Free the file structures
  for (size_t i = 0; i < STEGANOFS_AMOUNT_ROOT_FILES; i++)
    {
      HiddenFile *p_file = hidden_fat->files[i];
      if (p_file != NULL)
        {
          // Free the file structure
          free (p_file);
        }
    }

  // Free the HiddenFat structure itself
  free (hidden_fat);
}

size_t get_free_disk_space (HiddenFat *hidden_fat)
{
  if (hidden_fat == NULL)
    {
      fprintf (stderr, "Invalid HiddenFat pointer.\n");
      return 0;
    }

  size_t amount_free_blocks = 0;
  for (size_t i = 0; i < hidden_fat->amount_blocks; i++)
    {
      if (hidden_fat->clusters[i].state == FREE)
        {
          amount_free_blocks++;
        }
    }

  return amount_free_blocks * hidden_fat->block_size;
}

void show_hidden_fat (HiddenFat *hidden_fat, char *output_message)
{
  char letter_map[3] = {'F', 'R', 'D'};
  char buffer[512];
  size_t buffer_index = 0;
  size_t ccount = 1;

  // Assemble the output string
  buffer[buffer_index++] = 'S';
  buffer[buffer_index++] = 'h';
  buffer[buffer_index++] = 'o';
  buffer[buffer_index++] = 'w';
  buffer[buffer_index++] = 'i';
  buffer[buffer_index++] = 'n';
  buffer[buffer_index++] = 'g';
  buffer[buffer_index++] = ' ';
  buffer[buffer_index++] = 'F';
  buffer[buffer_index++] = 'i';
  buffer[buffer_index++] = 'l';
  buffer[buffer_index++] = 'e';
  buffer[buffer_index++] = 's';
  buffer[buffer_index++] = 'y';
  buffer[buffer_index++] = 's';
  buffer[buffer_index++] = 't';
  buffer[buffer_index++] = 'e';
  buffer[buffer_index++] = 'm';
  buffer[buffer_index++] = ':';
  buffer[buffer_index++] = '\n';

  for (size_t b_index = 0; b_index < hidden_fat->amount_blocks; b_index++)
    {
      unsigned int state = hidden_fat->clusters[b_index].state;
      if (state == ALLOCATED && buffer_index < 508)
        {
          char cluster_index_char = (char) (hidden_fat->clusters[b_index].cluster_index + '0');
          buffer[buffer_index++] = cluster_index_char;
        }
      else if (buffer_index < 508)
        {
          buffer[buffer_index++] = letter_map[state]; // 508
        }

      buffer[buffer_index++] = '|'; // 509
      ccount += 2;
      if (buffer_index >= 508)
        {
          break;
        }
      if (ccount >= 80)
        {
          buffer[buffer_index++] = '\n';
          ccount = 0;
        }
    }

  buffer[buffer_index++] = '\n'; // 510

  // Null-terminate the buffer
  buffer[buffer_index] = '\0'; // 511

  // Print the output to terminal
  printf ("%s", buffer);

  // Write the output to the provided outputMessage, if not null
  if (output_message != NULL)
    {
      strcpy (output_message, buffer);
    }
}

bool check_integrity (HiddenFat *hidden_fat)
{
  if (hidden_fat == NULL)
    {
      fprintf (stderr,
               "HiddenFat is NULL! No filesystem to check!\n");

      return false;
    }
  bool has_integrity = true;

  // Check if all clusters are associated with a file
  for (size_t file_index = 0; file_index < STEGANOFS_AMOUNT_ROOT_FILES; file_index++)
    {
      HiddenFile *p_file = hidden_fat->files[file_index];
      if (p_file != NULL)
        {
          HiddenCluster *hidden_cluster = p_file->hiddenCluster;
          while (hidden_cluster)
            {
              if (hidden_cluster == hidden_cluster->next)
                {
                  fprintf (stderr,
                           "Inconsistent file system: Cluster %zu in file %s points at itself in next\n",
                           hidden_cluster->cluster_index, hidden_cluster->file->filename);
                  return false;
                }
              if (hidden_cluster == hidden_cluster->prev)
                {
                  fprintf (stderr,
                           "Inconsistent file system: Cluster %zu in file %s points at itself in prev\n",
                           hidden_cluster->cluster_index, hidden_cluster->file->filename);
                  return false;
                }
              if (hidden_cluster->file != p_file)
                {
                  fprintf (stderr,
                           "Inconsistent file system: Cluster %zu in file %s is associated with incorrect file pointer: %s\n",
                           hidden_cluster->cluster_index,
                           hidden_cluster->file->filename,
                           p_file->filename);
                  has_integrity = false;
                }
              hidden_cluster = hidden_cluster->next;
            }
        }
    }

  // Check if all free blocks are not associated with a cluster
  for (size_t b_index = 0; b_index < hidden_fat->amount_blocks; b_index++)
    {
      if (hidden_fat->clusters[b_index].state == FREE &&
          (hidden_fat->clusters[b_index].prev != NULL || hidden_fat->clusters[b_index].next != NULL))
        {
          fprintf (stderr, "Inconsistent file system: Free block %zu is associated with a cluster.\n", b_index);
          has_integrity = false;
        }
    }
  return has_integrity;
}

float check_for_fragmentation (HiddenFat *hidden_fat)
{
  unsigned int blocks_in_correct_pos = 0;
  HiddenFile *current_file = NULL;
  int current_cluster_index = -1;
  for (HiddenCluster *hidden_cluster = hidden_fat->clusters;
       hidden_cluster < hidden_fat->clusters + hidden_fat->amount_blocks; hidden_cluster++)
    {
      if (hidden_cluster->state != ALLOCATED)
        {
          if (current_file == NULL || current_cluster_index == -1)
            {
              blocks_in_correct_pos++;
            }
          else
            {
              current_file = NULL;
              current_cluster_index = -1;
            }
          continue;
        }
      else if (current_file == NULL || current_cluster_index == -1)
        {
          if (hidden_cluster->cluster_index == 0)
            {
              blocks_in_correct_pos++;
            }
        }
      else
        {
          if (hidden_cluster->file == current_file && hidden_cluster->cluster_index == current_cluster_index + 1)
            {
              blocks_in_correct_pos++;
            }
        }
      if (hidden_cluster->next != NULL)
        {
          current_file = hidden_cluster->file;
          current_cluster_index = (int) hidden_cluster->cluster_index;
        }
      else
        {
          current_file = NULL;
          current_cluster_index = -1;
        }
    }
  float fragmentation = 100.0f - ((float) blocks_in_correct_pos / (float) hidden_fat->amount_blocks * 100.0f);
  printf ("Current fragmentation in percent: %.2f\n", fragmentation);
  return fragmentation;
}

void defragmentate (HiddenFat *hidden_fat)
{
  size_t b_index = 0;
  for (size_t i = 0; i < STEGANOFS_AMOUNT_ROOT_FILES; i++)
    {
      if (hidden_fat->files[i] == NULL)
        {
          continue;
        }
      HiddenCluster *hidden_cluster = hidden_fat->files[i]->hiddenCluster;
      while (hidden_cluster)
        {
          size_t block_index_to_swap = hidden_cluster->b_index;
          if (swap_hidden_clusters (hidden_fat, b_index, block_index_to_swap))
            {
              hidden_cluster = hidden_fat->clusters[b_index].next;
            }
          else
            {
              hidden_cluster = hidden_cluster->next;
            }
          b_index++;
        }
    }
}

size_t get_fragmentation_array (HiddenFat *hidden_fat, size_t **array)
{
  *array = malloc (hidden_fat->amount_blocks * sizeof (size_t)); // gets in SteganoFsAdapter::getFilesystemVector()
  memset (*array, 0, hidden_fat->amount_blocks * sizeof (size_t));
  if (*array == NULL)
    {
      return 0;
    }
  size_t b_index = 0;
  for (size_t i = 0; i < STEGANOFS_AMOUNT_ROOT_FILES; i++)
    {
      if (hidden_fat->files[i] == NULL)
        {
          continue;
        }
      HiddenCluster *hidden_cluster = hidden_fat->files[i]->hiddenCluster;
      while (hidden_cluster)
        {
          size_t block_index_cluster = hidden_cluster->b_index;
          (*array)[block_index_cluster] = b_index;
          b_index++;
          hidden_cluster = hidden_cluster->next;
        }
    }
  return hidden_fat->amount_blocks;
}

size_t get_amount_entries (HiddenFat *hidden_fat, const char *path)
{
  if (strcmp (path, "/") == 0)
    {
      size_t amount = 0;
      for (HiddenFile **p_file = hidden_fat->files; p_file < hidden_fat->files + STEGANOFS_AMOUNT_ROOT_FILES; p_file++)
        {
          if (*p_file != NULL)
            {
              amount++;
            }
        }
      return amount;
    }
  return 2;
}

int write_block (HiddenFat *hidden_fat, size_t b_index, const char *buffer, size_t offset, size_t length)
{
  if (offset + length > hidden_fat->block_size)
    {
      fprintf (stderr, "Trying to write to the wrong Block! offset+length is higher than %zu\n", hidden_fat
          ->block_size);
      return -1;
    }
  if (b_index > hidden_fat->amount_blocks)
    {
      fprintf (stderr, "Block Index too high! Can't write outside the disk!!\n");
      return -1;
    }
  if (length == 0)
    {
      // nothing to do..
      return 0;
    }
  size_t disk_offset = (b_index * hidden_fat->block_size) + offset;
  if (hidden_fat->disk + disk_offset + length > hidden_fat->disk + (hidden_fat->amount_blocks * hidden_fat->block_size))
    {
      fprintf (stderr, "Can't write outside the disk!!\n");
      return -1;
    }
  memcpy (hidden_fat->disk + disk_offset, (void *) buffer + offset, length);
  return (int) length;
}

int read_block (HiddenFat *hidden_fat, size_t b_index, const char *buffer, size_t offset, size_t length)
{
  if (offset + length > hidden_fat->block_size)
    {
      fprintf (stderr, "Trying to read from the wrong Block! offset+length is higher than %zu\n",
               hidden_fat->block_size);
      return -1;
    }
  if (b_index > hidden_fat->amount_blocks)
    {
      fprintf (stderr, "Block Index too high! Can't read outside the disk!!\n");
      return -1;
    }
  if (length == 0)
    {
      // nothing to do..
      return 0;
    }
  size_t disk_offset = (b_index * hidden_fat->block_size) + offset;
  if (hidden_fat->disk + disk_offset + length > hidden_fat->disk + (hidden_fat->amount_blocks * hidden_fat->block_size))
    {
      fprintf (stderr, "Can't read outside the disk!!\n");
      return -1;
    }
  memcpy ((void *) buffer + offset, hidden_fat->disk + disk_offset, length);
  return (int) length;
}