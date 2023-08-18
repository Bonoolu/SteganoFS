#ifndef STEGANOFS_MAIN_BMP_FILE_H
#define STEGANOFS_MAIN_BMP_FILE_H

#include <stddef.h>
#include <stdio.h>

struct BMP_File {
    unsigned char *buf;
    FILE *file;
    size_t pixel_array_length;
};

#endif //STEGANOFS_MAIN_BMP_FILE_H
