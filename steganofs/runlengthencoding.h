#ifndef _RUNLENGTHENCODING_H_
#define _RUNLENGTHENCODING_H_

#include "ramdiskloader.h"

typedef struct SerializedFilesystem SerializedFilesystem;

void run_length_encoding (struct SerializedFilesystem *serialized_filesystem);
void run_length_decoding (struct SerializedFilesystem *serialized_filesystem);

#endif //_RUNLENGTHENCODING_H_
