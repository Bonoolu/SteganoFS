#include "../steganofs/steganofs.h"

/**
 * @brief Test the functions for generic buffer manipulation.
 *
 * @return True if the test passes, false otherwise.
 */
bool test_generic_buffer ()
{
  unsigned char buffer_ff[17] = "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
                                "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF";
  unsigned char buffer_00[17] = "\x00\x00\x00\x00\x00\x00\x00"
                                "\x00\x00\x00\x00\x00\x00\x00";
  const size_t length = 16;
  unsigned char *extracted_buffer = NULL;
  size_t extracted_length = 0;

  exract_payload_from_generic_buffer (&extracted_buffer, &extracted_length, buffer_ff, length);
  printf ("The exracted bytes are %d and %d\n", extracted_buffer[0], extracted_buffer[1]);

  unsigned char payload[2] = {54, 27};
  size_t payload_length = 2;

  embedd_payload_in_generic_buffer (payload, payload_length, buffer_00);

  printf ("Buffer with payload:\n");
  for (size_t i = 0; i < length; i++)
    {
      printf ("%d", buffer_00[i]);
      if (i == 7 || i == 15)
        {
          printf ("\n");
        }
      else
        {
          printf (", ");
        }
    }
  return true;
}

int main(int argc, char** argv) {
    if (test_generic_buffer()) {
        return 0;
    }
    return 1;
}
