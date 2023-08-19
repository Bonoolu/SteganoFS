#ifndef STEGANOFS_MAIN_STEGANO_FILE_H
#define STEGANOFS_MAIN_STEGANO_FILE_H

#include <stdio.h>

struct SteganoFile {
    char *path;
    //FILE *file;
    unsigned char *payload;
    size_t payload_length;
};

#endif //STEGANOFS_MAIN_STEGANO_FILE_H
