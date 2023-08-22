#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../stegano_file.h"

void exract_payload_from_generic_buffer(unsigned char **payload_buffer, size_t *payloadLength,
                                               const unsigned char *data, size_t dataLength);
void embedd_payload_in_generic_buffer(unsigned char *payload_buffer, size_t payloadLength,
                                      unsigned char *data, size_t dataLength);
void extract_payload(struct SteganoFile *steganoFile, const unsigned char *pixeldata, size_t pixel_data_length);
size_t embedd_payload(struct SteganoFile steganoFile, unsigned char *pixeldata, size_t pixel_data_length);
struct SteganoFile read_bmp(const char *path);
size_t write_bmp(struct SteganoFile);
