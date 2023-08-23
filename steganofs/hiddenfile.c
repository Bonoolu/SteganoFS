#include "hiddenfile.h"

int delete_hidden_file (HiddenFat *hidden_fat, const char *filename)
{
  HiddenFile **p_file = hidden_fat->files;
  bool found = false;
  do
    {
      if (*p_file != NULL && strcmp ((*p_file)->filename, filename) == 0)
        {
          found = true;
          break;
        }
    }
  while (++p_file != hidden_fat->files + STEGANOFS_AMOUNT_ROOT_FILES);

  if (found)
    {
      HiddenCluster *hidden_cluster = (*p_file)->hiddenCluster;
      while (hidden_cluster)
        {
          HiddenCluster *tmp_cluster = hidden_cluster->next;
          size_t tmp_b_index = hidden_cluster->b_index;
          memset (hidden_fat->disk + (hidden_fat->block_size * hidden_cluster->b_index), 0, hidden_fat->block_size);
          memset (hidden_cluster, 0, sizeof (HiddenCluster));
          hidden_cluster->b_index = tmp_b_index;
          hidden_cluster = tmp_cluster;
        }
      free (*p_file);
      *p_file = NULL;
      printf ("Deleted File!\n");
      return 0;
    }
  else
    {
      fprintf (stderr, "Could not find file: %s\n", filename);
      return -ENOENT;
    }
}

int count_path_components (const char *path)
{
  int count = 0;
  for (int i = 0; path[i]; i++)
    {
      if (path[i] == '/')
        count++;
    }
  return count;
}

HiddenFile *find_file_by_path (HiddenFat *hidden_fat, const char *path)
{
  HiddenFile **p_file = hidden_fat->files;
  bool found = false;
  if (strcmp (path, "/") == 0)
    {
      return NULL;
    }
  if (count_path_components (path) == 1)
    {
      const char *filename = path + 1;
      do
        {
          if (*p_file != NULL && strcmp ((*p_file)->filename, filename) == 0)
            {
              found = true;
              break;
            }
        }
      while (++p_file != hidden_fat->files + STEGANOFS_AMOUNT_ROOT_FILES);
    }
  if (found)
    {
      return *p_file;
    }
  else
    {
      return NULL;
    }
}

HiddenFile **create_hidden_file (HiddenFat *hidden_fat, const char *filename, long timestamp)
{
  // Find an available file slot
  HiddenFile **search_result = NULL;
  for (size_t i = 0; i < STEGANOFS_AMOUNT_ROOT_FILES; i++)
    {
      if (hidden_fat->files[i] == NULL)
        {
          search_result = &hidden_fat->files[i];
          break;
        }
    }
  if (search_result == NULL)
    {
      fprintf (stderr, "Maximum amount of files are already allocated!\n");
      return NULL;
    }
  if (strlen (filename) > STEGANOFS_MAX_FILENAME_LENGTH - 1)
    {
      fprintf (stderr, "Filename too long\n");
      return NULL;
    }

  // Create the file structure and update the file table
  HiddenFile *p_file = (HiddenFile *) malloc (sizeof (HiddenFile));  // gets by freed in free_hidden_fat()
  if (!p_file)
    {
      fprintf (stderr, "Could not allocate memory!\n");
      return NULL;
    }
  memset (p_file->filename, 0, STEGANOFS_MAX_FILENAME_LENGTH);
  strncpy (p_file->filename, filename, STEGANOFS_MAX_FILENAME_LENGTH);
  p_file->filesize = 0;
  p_file->timestamp = timestamp;
  p_file->hiddenCluster = NULL;
  *search_result = p_file;

  printf ("Created file!\n");
  return search_result;
}
