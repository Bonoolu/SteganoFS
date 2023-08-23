#include "bmp_provider.h"

void exract_payload_from_generic_buffer (unsigned char **payload_buffer, size_t *payload_length,
                                         const unsigned char *data, size_t data_length)
{
  *payload_length = data_length / 8;
  *payload_buffer = malloc (*payload_length);
  memset (*payload_buffer, 0, *payload_length);
  for (size_t i = 0; i < *payload_length; i++)
    {
      unsigned char *current_byte_to_write_to = (*payload_buffer) + i;
      *current_byte_to_write_to = 0x00;
      for (size_t bit = 0; bit < 8; bit++)
        {
          unsigned char current_bit_to_write = ((data[(i * 8) + bit] & 0x01));
          *current_byte_to_write_to ^= current_bit_to_write << bit;
        }
    }
}

void extract_payload (struct SteganoFile *stegano_file, const unsigned char *pixeldata, size_t pixel_data_length)
{
  exract_payload_from_generic_buffer (&(stegano_file->payload), &stegano_file->payload_length, pixeldata,
                                      pixel_data_length);
}

void embedd_payload_in_generic_buffer (const unsigned char *payload_buffer, size_t payload_length, unsigned char *data)
{
  for (size_t i = 0; i < payload_length; i++)
    {
      unsigned char byte_to_write = payload_buffer[i];
      for (size_t bit_index = 0; bit_index < 8; bit_index++)
        {
          unsigned char current_bit = data[(i * 8) + bit_index] & 0x01;
          unsigned char bit_to_write = (byte_to_write >> bit_index) & 0x01;
          if (bit_to_write != current_bit)
            {
              data[(i * 8) + bit_index] ^= 1;
            }
        }
    }
}

size_t embedd_payload (struct SteganoFile stegano_file, unsigned char *pixeldata, size_t pixel_data_length)
{
  if (pixel_data_length / 8 < stegano_file.payload_length)
    {
      stegano_file.payload_length = pixel_data_length / 8;
    }
  embedd_payload_in_generic_buffer (stegano_file.payload, stegano_file.payload_length, pixeldata);
  return stegano_file.payload_length;
}

struct SteganoFile read_bmp (const char *path)
{
  FILE *file = fopen (path, "rb");
  struct SteganoFile stegano_file = {.payload = NULL, .payload_length = 0};
  if (file)
    {
      fseek (file, 0L, SEEK_END);
      size_t pixel_data_length = ftell (file) - 36;
      rewind (file);
      fseek (file, 36, 0);
      unsigned char *pixeldata = malloc (pixel_data_length);
      if (pixeldata == NULL)
        {
          return stegano_file;
        }
      fread (pixeldata, pixel_data_length, 1, file);
      extract_payload (&stegano_file, pixeldata, pixel_data_length);
      fflush (file);
      fclose (file);
    }
  return stegano_file;
}

size_t write_bmp (struct SteganoFile stegano_file)
{
  FILE *file = fopen (stegano_file.path, "rb");
  if (file)
    {
      fseek (file, 0L, SEEK_END);
      size_t pixel_data_length = ftell (file) - 36;
      rewind (file);
      fseek (file, 36, 0);
      unsigned char *pixeldata = malloc (pixel_data_length);
      if (pixeldata == NULL)
        {
          return 0;
        }
      fread (pixeldata, pixel_data_length, 1, file);
      fflush (file);
      fclose (file);
      size_t payload_written = embedd_payload (stegano_file, pixeldata, pixel_data_length);
      fopen (stegano_file.path, "wb");
      fseek (file, 36, 0);
      fwrite (pixeldata, pixel_data_length, 1, file);
      fflush (file);
      fclose (file);
      return payload_written;
    }
  return 0;
}


