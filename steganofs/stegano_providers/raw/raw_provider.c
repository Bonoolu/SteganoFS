#include "raw_provider.h"

struct SteganoFile read_raw (const char *path)
{
  FILE *file = fopen (path, "rb");
  struct SteganoFile stegano_file = {.payload = NULL, .payload_length = 0};
  if (file)
    {
      fseek (file, 0L, SEEK_END);
      stegano_file.payload_length = ftell (file);
      rewind (file);
      stegano_file.payload = malloc (stegano_file.payload_length); // gets freed in stegano_provider_read()
      if (stegano_file.payload == NULL)
        {
          stegano_file.payload_length = 0;
          return stegano_file;
        }
      fread (stegano_file.payload, stegano_file.payload_length, 1, file);
      fflush (file);
      fclose (file);
    }
  return stegano_file;
}

size_t write_raw (struct SteganoFile stegano_file)
{
  FILE *file = fopen ((char *) stegano_file.path, "wb");
  if (file)
    {
      fwrite (stegano_file.payload, stegano_file.payload_length, 1, file);
      fflush (file);
      fclose (file);
      return stegano_file.payload_length;
    }
  return 0;
}
