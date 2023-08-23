#include "ramdiskloader.h"

struct SerializedFilesystem serialize_filesystem (HiddenFat *hidden_fat)
{
  size_t size_packed_fat = sizeof (PackedFat);
  size_t size_packed_clusters = sizeof (PackedCluster) * hidden_fat->amount_blocks;
  size_t size_packed_files = sizeof (PackedFile) * STEGANOFS_AMOUNT_ROOT_FILES;
  size_t size_blocks = hidden_fat->amount_blocks * hidden_fat->block_size;

  size_t offset_packed_fat = 0;
  size_t offset_packed_cluster = offset_packed_fat + size_packed_fat;
  size_t offset_packed_files = offset_packed_cluster + size_packed_clusters;
  size_t offset_blocks = offset_packed_files + size_packed_files;

  size_t size_filesystem = offset_blocks + size_blocks;

  unsigned char *buffer_filesystem = malloc (size_filesystem); // gets freed by steganofs_unload_ramdisk()
  memset (buffer_filesystem, 0, size_filesystem);

  PackedFat *packed_fat = (PackedFat *) (buffer_filesystem + offset_packed_fat);
  PackedCluster *packed_clusters = (PackedCluster *) (buffer_filesystem + offset_packed_cluster);
  PackedFile *packed_files = (PackedFile *) (buffer_filesystem + offset_packed_files);
  unsigned char *disk = buffer_filesystem + offset_blocks;

  packed_fat->block_size = hidden_fat->block_size;
  packed_fat->amount_blocks = hidden_fat->amount_blocks;
  packed_fat->clusters_offset = offset_packed_cluster;
  packed_fat->amount_root_files = STEGANOFS_AMOUNT_ROOT_FILES;
  packed_fat->files_offset = offset_packed_files;
  packed_fat->disk_offset = offset_blocks;

  PackedFile *packed_file_iterator = packed_files;
  for (HiddenFile **hidden_file = hidden_fat->files; hidden_file < hidden_fat->files + STEGANOFS_AMOUNT_ROOT_FILES;
       hidden_file++)
    {
      if (*hidden_file == NULL)
        {
          packed_file_iterator++;
          continue;
        }
      packed_file_iterator->filesize = (*hidden_file)->filesize;
      if ((*hidden_file)->hiddenCluster == NULL)
        {
          packed_file_iterator->hidden_cluster_b_index = -1;
        }
      else
        {
          packed_file_iterator->hidden_cluster_b_index = (int64_t) ((*hidden_file)->hiddenCluster->b_index);
        }
      strncpy (packed_file_iterator->filename, (*hidden_file)->filename, STEGANOFS_MAX_FILENAME_LENGTH - 1);
      packed_file_iterator->real_filesize = (*hidden_file)->real_filesize;
      packed_file_iterator->timestamp = (*hidden_file)->timestamp;

      HiddenCluster *hidden_cluster = (*hidden_file)->hiddenCluster;
      while (hidden_cluster)
        {
          size_t b_index = hidden_cluster->b_index;
          packed_clusters[b_index].b_index = hidden_cluster->b_index;
          packed_clusters[b_index].cluster_index = hidden_cluster->cluster_index;
          packed_clusters[b_index].state = hidden_cluster->state;
          if (hidden_cluster->prev == NULL)
            {
              packed_clusters[b_index].prev_cluster_b_index = -1;
            }
          else
            {
              packed_clusters[b_index].prev_cluster_b_index = (int64_t) hidden_cluster->prev->b_index;
            }
          if (hidden_cluster->next == NULL)
            {
              packed_clusters[b_index].next_cluster_b_index = -1;
            }
          else
            {
              packed_clusters[b_index].next_cluster_b_index = (int64_t) hidden_cluster->next->b_index;
            }
          hidden_cluster = hidden_cluster->next;
        }
      packed_file_iterator++;
    }
  memcpy (disk, hidden_fat->disk, hidden_fat->amount_blocks * hidden_fat->block_size);
  struct SerializedFilesystem serialized_filesystem = {.size = size_filesystem, .buf = buffer_filesystem};
  return serialized_filesystem;
}

HiddenFat *load_ramdisk (struct SerializedFilesystem serialized_filesystem)
{
  PackedFat *packed_fat = (PackedFat *) serialized_filesystem.buf;
  PackedCluster *packed_clusters = (PackedCluster *) (serialized_filesystem.buf + packed_fat->clusters_offset);
  PackedFile *packed_files = (PackedFile *) (serialized_filesystem.buf + packed_fat->files_offset);
  unsigned char *disk = serialized_filesystem.buf + packed_fat->disk_offset;

  HiddenFat *hidden_fat = create_hidden_fat (packed_fat->block_size * packed_fat->amount_blocks,
                                             packed_fat->block_size); // gets freed by free_hidden_fat()

  HiddenFile **hidden_file_iterator = hidden_fat->files;
  struct PackedFile empty_file;
  memset (&empty_file, 0, sizeof (PackedFile));
  for (PackedFile *packed_file = packed_files; packed_file < packed_files + packed_fat->amount_root_files;
       packed_file++)
    {
      if (memcmp (packed_file, &empty_file, sizeof (PackedFile)) == 0)
        {
          hidden_file_iterator++;
          continue;
        }
      *hidden_file_iterator = malloc (sizeof (HiddenFile)); // gets freed by free_hidden_fat()
      memset (*hidden_file_iterator, 0, sizeof (HiddenFile));
      (*hidden_file_iterator)->filesize = (packed_file)->filesize;
      if (packed_file->hidden_cluster_b_index == -1)
        {
          (*hidden_file_iterator)->hiddenCluster = NULL;
        }
      else
        {
          (*hidden_file_iterator)->hiddenCluster = hidden_fat->clusters + packed_file->hidden_cluster_b_index;
        }
      strncpy ((*hidden_file_iterator)->filename, packed_file->filename, STEGANOFS_MAX_FILENAME_LENGTH - 1);
      (*hidden_file_iterator)->real_filesize = packed_file->real_filesize;
      (*hidden_file_iterator)->timestamp = packed_file->timestamp;

      HiddenCluster *hidden_cluster = (*hidden_file_iterator)->hiddenCluster;
      size_t b_index = 0;
      while (hidden_cluster != NULL && b_index != -1)
        {
          b_index = hidden_cluster->b_index;
          hidden_cluster->b_index = packed_clusters[b_index].b_index;
          hidden_cluster->cluster_index = packed_clusters[b_index].cluster_index;
          hidden_cluster->state = packed_clusters[b_index].state;
          hidden_cluster->file = *hidden_file_iterator;
          if (packed_clusters[b_index].prev_cluster_b_index == -1)
            {
              hidden_cluster->prev = NULL;
            }
          else
            {
              hidden_cluster->prev = hidden_fat->clusters + packed_clusters[b_index].prev_cluster_b_index;
            }
          if (packed_clusters[b_index].next_cluster_b_index == -1)
            {
              hidden_cluster->next = NULL;
            }
          else
            {
              hidden_cluster->next = hidden_fat->clusters + packed_clusters[b_index].next_cluster_b_index;
            }
          hidden_cluster = hidden_cluster->next;
          b_index = packed_clusters[b_index].next_cluster_b_index;
        }
      hidden_file_iterator++;
    }
  memcpy (hidden_fat->disk, disk, hidden_fat->amount_blocks * hidden_fat->block_size);
  return hidden_fat;
}