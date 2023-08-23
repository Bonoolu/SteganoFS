#include "stegano_provider.h"

struct SteganoProvider providers[] = {
    {.extension = "STEGANOFS", .provider_read = &read_raw, .provider_write = &write_raw},
    {.extension = "BMP", .provider_read = &read_bmp, .provider_write = &write_bmp}
};

struct SerializedFilesystem stegano_provider_read (const char *path)
{

  // check if path is a directory
  struct stat filepath_stat;
  stat (path, &filepath_stat);

  struct SerializedFilesystem serialized_filesystem = {.buf = NULL, .size = 0};

  size_t write_offset = 0;
  if (filepath_stat.st_mode & S_IFDIR)
    {
      struct stat file_info;
      struct dirent **namelist;
      const int n = scandir (path, &namelist, NULL, alphasort);
      for (int file_index = 0; file_index < n; file_index++)
        {
          memset (&file_info, 0, sizeof (struct stat));
          char path_buffer[256];
          memset (path_buffer, 0, sizeof (char));
          char dash[2] = "/";
          strcat (path_buffer, path);
          strcat (path_buffer, dash);
          strcat (path_buffer, namelist[file_index]->d_name);
          const char *full_path = path_buffer;
          stat (full_path, &file_info);
          if (!S_ISREG(file_info.st_mode))
            {
              continue;
            }
          if (!strlen (namelist[file_index]->d_name))
            {
              continue;
            }
          const char *dot = strrchr (full_path, '.');
          if (dot == NULL)
            {
              return serialized_filesystem;
            }
          char *extension = strdup (dot + 1);
          for (char *i = extension; *i != 0; i++)
            {
              *i = (char) toupper (*i);
            }
          for (size_t i = 0; i < sizeof (providers) / sizeof (providers[0]); i++)
            {
              struct SteganoProvider provider = providers[i];
              if (strcmp (provider.extension, extension) == 0)
                {
                  struct SteganoFile stegano_file = provider.provider_read (full_path);
                  size_t new_length = write_offset + stegano_file.payload_length;
                  printf ("Loaded %zu bytes of payload from %s\n", stegano_file.payload_length, full_path);
                  unsigned char *tmp = NULL;
                  if (serialized_filesystem.buf == NULL)
                    {
                      tmp = malloc (new_length); // gets freed by steganofs_load_ramdisk()
                    }
                  else
                    {
                      tmp = realloc (serialized_filesystem.buf, new_length); // gets freed by steganofs_load_ramdisk()
                    }
                  if (tmp == NULL)
                    {
                      fprintf (stderr, "Out of memory!\n");
                      return serialized_filesystem;
                    }
                  serialized_filesystem.buf = tmp;
                  serialized_filesystem.size = new_length;
                  memcpy (serialized_filesystem.buf + write_offset, stegano_file.payload, stegano_file.payload_length);
                  free(stegano_file.payload);
                  write_offset = new_length;
                }
            }
        }
      return serialized_filesystem;
    }

  const char *dot = strrchr (path, '.');
  if (dot == NULL)
    {
      return serialized_filesystem;
    }
  char *extension = strdup (dot + 1);
  for (char *i = extension; *i != 0; i++)
    {
      *i = (char) toupper (*i);
    }

  for (size_t i = 0; i < sizeof (providers) / sizeof (providers[0]); i++)
    {
      struct SteganoProvider provider = providers[i];
      if (strcmp (provider.extension, extension) == 0)
        {
          struct SteganoFile stegano_file = provider.provider_read (path);
          if (stegano_file.payload_length == 0 || stegano_file.payload == NULL)
            {
              return serialized_filesystem;
            }
          serialized_filesystem.buf = malloc (stegano_file.payload_length);  // gets freed by steganofs_load_ramdisk()
          if (serialized_filesystem.buf == NULL)
            {
              return serialized_filesystem;
            }
          serialized_filesystem.size = stegano_file.payload_length;
          memcpy (serialized_filesystem.buf, stegano_file.payload, serialized_filesystem.size);
          free(stegano_file.payload);
          return serialized_filesystem;
        }
    }
  return serialized_filesystem;
}

bool stegano_provider_write (struct SerializedFilesystem serialized_filesystem, const char *path)
{

  // check if path is a directory
  struct stat filepath_stat;
  stat (path, &filepath_stat);

  size_t bytes_written = 0;
  if ((access(path, F_OK) == 0) && filepath_stat.st_mode & S_IFDIR)
    {
      struct stat file_info;
      struct dirent **namelist;
      const int n = scandir (path, &namelist, NULL, alphasort);
      for (int file_index = 0; file_index < n && serialized_filesystem.size != bytes_written; file_index++)
        {
          memset (&file_info, 0, sizeof (struct stat));
          char path_buffer[256];
          memset (path_buffer, 0, sizeof (char));
          char dash[2] = "/";
          strcat (path_buffer, path);
          strcat (path_buffer, dash);
          strcat (path_buffer, namelist[file_index]->d_name);
          const char *full_path = path_buffer;
          stat (full_path, &file_info);
          if (!S_ISREG(file_info.st_mode))
            {
              continue;
            }
          if (!strlen (namelist[file_index]->d_name))
            {
              continue;
            }
          const char *dot = strrchr (full_path, '.');
          if (dot == NULL)
            {
              continue;
            }
          char *extension = strdup (dot + 1);
          for (char *i = extension; *i != 0; i++)
            {
              *i = (char) toupper (*i);
            }
          for (size_t i = 0; i < sizeof (providers) / sizeof (providers[0]); i++)
            {
              struct SteganoProvider provider = providers[i];
              if (strcmp (provider.extension, extension) == 0)
                {
                  struct SteganoFile stegano_file = {};
                  stegano_file.path = strdup (full_path);
                  stegano_file.payload = serialized_filesystem.buf + bytes_written;
                  stegano_file.payload_length = serialized_filesystem.size - bytes_written;
                  size_t written = provider.provider_write (stegano_file);
                  bytes_written += written;
                  printf ("Wrote %zu bytes of payload to %s\n", written, full_path);
                  if (serialized_filesystem.size == bytes_written)
                    {
                      break;
                    }
                }

            }
        }
      return serialized_filesystem.size == bytes_written;
    }

  const char *dot = strrchr (path, '.');
  if (dot == NULL)
    {
      return false;
    }
  char *extension = strdup (dot + 1);
  for (char *i = extension; *i != 0; i++)
    {
      *i = (char) toupper (*i);
    }

  for (size_t i = 0; i < sizeof (providers) / sizeof (providers[0]); i++)
    {
      struct SteganoProvider provider = providers[i];
      if (strcmp (provider.extension, extension) == 0)
        {
          struct SteganoFile stegano_file = {};
          stegano_file.path = strdup (path);
          stegano_file.payload = malloc (serialized_filesystem.size); // see free() below
          memcpy (stegano_file.payload, serialized_filesystem.buf, serialized_filesystem.size);
          stegano_file.payload_length = serialized_filesystem.size;
          bool ret = provider.provider_write (stegano_file);
          free(stegano_file.payload);
          return ret;
        }
    }
  return false;
}