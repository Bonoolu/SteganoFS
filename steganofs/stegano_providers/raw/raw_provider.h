#ifndef STEGANOFS_MAIN_RAW_PROVIDER_H
#define STEGANOFS_MAIN_RAW_PROVIDER_H

#include "../stegano_file.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct SteganoFile read_raw(const char *path);
size_t write_raw(struct SteganoFile);

#endif //STEGANOFS_MAIN_RAW_PROVIDER_H
