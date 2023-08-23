#ifndef STEGANOFS_MAIN_RUNLENGTHENCODING_H
#define STEGANOFS_MAIN_RUNLENGTHENCODING_H

#include "ramdiskloader.h"

typedef struct SerializedFilesystem SerializedFilesystem;

void run_length_encoding(struct SerializedFilesystem *serializedFilesystem);
void run_length_decoding(struct SerializedFilesystem *serializedFilesystem);


#endif //STEGANOFS_MAIN_RUNLENGTHENCODING_H
