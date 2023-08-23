#include "runlengthencoding.h"

void run_length_encoding (struct SerializedFilesystem *serialized_filesystem)
{
  if (serialized_filesystem->rle)
    {
      return;
    }
  size_t read_index = 0;
  size_t write_index = 0;
  size_t data_block_begin = 0;
  size_t zero_count = 0;
  size_t ranges_count = 0;

  struct LinkedList {
      uint64_t offset_from;
      uint64_t offset_to;
      struct LinkedList *next;
  };

  struct LinkedList linked_list;

  struct LinkedList *zero_ranges_begin = &linked_list;
  struct LinkedList *zero_ranges = &linked_list;
  printf ("Previous Disk size: %zu\n", serialized_filesystem->size);
  while (read_index < serialized_filesystem->size)
    {
      unsigned char *current_read_pointer = serialized_filesystem->buf + read_index;
      if (serialized_filesystem->buf[read_index] == 0)
        {
          zero_count++;
          if (zero_count == 1)
            {
              zero_ranges->offset_from = read_index;
            }
          else
            {
              zero_ranges->offset_to = read_index;
            }
        }
      else
        {
          if (zero_count > 16)
            {
              printf ("Copying over bytes %zu to %zu  (%zu bytes)\n",
                      data_block_begin,
                      zero_ranges->offset_from,
                      zero_ranges->offset_from - data_block_begin);
              unsigned char *move_from = serialized_filesystem->buf + data_block_begin;
              unsigned char *move_to = serialized_filesystem->buf + write_index;
              size_t move_size = zero_ranges->offset_from - data_block_begin;
              memmove (move_to, move_from, move_size);
              write_index += move_size;
              data_block_begin = read_index;
              ranges_count++;
              zero_ranges->offset_to = read_index;
              zero_ranges->next = malloc (sizeof (struct LinkedList)); // gets freed in the while loop below
              memset (zero_ranges->next, 0, sizeof (struct LinkedList));
              zero_ranges = zero_ranges->next;
            }
          zero_count = 0;
        }
      read_index++;
    }

  if (data_block_begin != 0)
    {
      size_t length = serialized_filesystem->size - data_block_begin;
      unsigned char *move_from = serialized_filesystem->buf + length;
      unsigned char *move_to = serialized_filesystem->buf + write_index;
      memmove (move_to, move_from, length);
      printf ("Datablock begin was: %zu. Copying over %zu bytes\n", data_block_begin, length);
    }

  size_t buffer_length = write_index;
  size_t header_length = (ranges_count * 2 * 8) + 8;
  printf ("Allocated %zu + %zu = %zu bytes!\n", buffer_length, header_length, buffer_length + header_length);
  unsigned char *new_buffer = malloc (buffer_length + header_length); // See free below
  struct LinkedList *zero_ranges_end = zero_ranges;
  zero_ranges = zero_ranges_begin;
  size_t write_index_new_buffer = 0;
  while (zero_ranges != zero_ranges_end)
    {
      *((uint64_t *) &(new_buffer[write_index_new_buffer])) = zero_ranges->offset_from;
      *((uint64_t *) &(new_buffer[write_index_new_buffer + 8])) = zero_ranges->offset_to;
      printf ("From: %zu, To: %zu\n", zero_ranges->offset_from, zero_ranges->offset_to);
      write_index_new_buffer += 16;
      struct LinkedList *tmp = zero_ranges;
      zero_ranges = zero_ranges->next;
      if (tmp != zero_ranges_begin)
        {
          free (tmp);
        }
    }
  new_buffer[write_index_new_buffer] = 0;
  write_index_new_buffer += 8;
  printf ("Wrote %zu Bytes as header to buffer!\n", write_index_new_buffer);
  printf ("Wrote %zu Bytes as Data.\n", buffer_length);
  memcpy (new_buffer + write_index_new_buffer, serialized_filesystem->buf, buffer_length);
  free (serialized_filesystem->buf);
  serialized_filesystem->buf = new_buffer;
  serialized_filesystem->size = buffer_length + header_length;
  serialized_filesystem->rle = true;
}

void run_length_decoding (struct SerializedFilesystem *serialized_filesystem)
{
  if (!serialized_filesystem->rle)
    {
      return;
    }
  const uint64_t *zero_ranges = (uint64_t *) serialized_filesystem->buf;
  uint64_t *length_pointer = (uint64_t *) serialized_filesystem->buf;
  size_t amount_zeros_to_place = 0;
  while ((length_pointer == zero_ranges || *length_pointer != 0)
         && length_pointer < (uint64_t *) ((serialized_filesystem->buf + serialized_filesystem->size) - 3))
    {
      uint64_t from = length_pointer[0];
      uint64_t to = length_pointer[1];
      amount_zeros_to_place += (to - from);
      length_pointer += 2;
    }
  const size_t zero_ranges_length = length_pointer - zero_ranges;
  unsigned char *encoded_buffer = serialized_filesystem->buf + ((zero_ranges_length + 1) * 8);
  size_t encoded_buffer_length = serialized_filesystem->size - ((zero_ranges_length + 1) * 8);
  printf ("Length of Ranges: %zu\n", zero_ranges_length);
  printf ("Amount Zeros to place: %zu\n", amount_zeros_to_place);
  printf ("Length of DataBuffer: %zu\n", encoded_buffer_length);
  printf ("Length of decoded Filesystem: %zu\n", encoded_buffer_length + amount_zeros_to_place);
  size_t decoded_filesystem_length = encoded_buffer_length + amount_zeros_to_place;
  unsigned char *decoded_filesystem = malloc (decoded_filesystem_length); // See free below
  memset (decoded_filesystem, 0, decoded_filesystem_length);
  length_pointer = (uint64_t *) zero_ranges;
  unsigned char *read_pointer = (unsigned char *) encoded_buffer;
  unsigned char *write_pointer = decoded_filesystem;
  while ((length_pointer == zero_ranges || *length_pointer != 0)
         && length_pointer < (uint64_t *) ((serialized_filesystem->buf + serialized_filesystem->size) - 3))
    {
      uint64_t from = length_pointer[0];
      uint64_t to = length_pointer[1];
      size_t length = from - (write_pointer - decoded_filesystem);
      printf ("Wrote %zu bytes! to offset:%zu\n", length, write_pointer - decoded_filesystem);
      memcpy (write_pointer, read_pointer, length);
      write_pointer = decoded_filesystem + to;
      read_pointer += length;
      length_pointer += 2;
    }
  length_pointer--;
  if (*length_pointer < decoded_filesystem_length)
    {
      printf ("Wrote %zu bytes! to offset:%zu\n",
              decoded_filesystem_length - *length_pointer,
              write_pointer - decoded_filesystem);
      memcpy (write_pointer, read_pointer, decoded_filesystem_length - *length_pointer);
    }
  free (serialized_filesystem->buf);
  serialized_filesystem->buf = decoded_filesystem;
  serialized_filesystem->size = decoded_filesystem_length;
  serialized_filesystem->rle = false;
}
