#ifndef STEGANOFS_MAIN_RAW_PROVIDER_H
#define STEGANOFS_MAIN_RAW_PROVIDER_H

#include "../../steganofs/ramdiskloader.h"

struct SerializedFilesystem read_raw(const char *path);
void write_raw(struct SerializedFilesystem serializedFilesystem, const char *path);

#endif //STEGANOFS_MAIN_RAW_PROVIDER_H
