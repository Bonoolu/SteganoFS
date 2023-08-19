#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../stegano_file.h"

void extract_payload(struct SteganoFile *steganoFile, const unsigned char *pixeldata, size_t pixel_data_length);
void embedd_payload(struct SteganoFile *steganoFile, unsigned char *pixeldata, size_t pixel_data_length);
struct SteganoFile read_bmp(const char *path);
bool write_bmp(struct SteganoFile);
