#ifndef _BMP_PROVIDER_H_
#define _BMP_PROVIDER_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../stegano_file.h"

void exract_payload_from_generic_buffer (unsigned char **payload_buffer, size_t *payload_length,
                                         const unsigned char *data, size_t data_length);
void embedd_payload_in_generic_buffer (const unsigned char *payload_buffer, size_t payload_length, unsigned char *data);
void extract_payload (struct SteganoFile *stegano_file, const unsigned char *pixeldata, size_t pixel_data_length);
size_t embedd_payload (struct SteganoFile stegano_file, unsigned char *pixeldata, size_t pixel_data_length);
struct SteganoFile read_bmp (const char *path);
size_t write_bmp (struct SteganoFile);
#endif // _BMP_PROVIDER_H_
