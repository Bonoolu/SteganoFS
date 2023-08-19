#ifndef STEGANOFS_MAIN_STEGANO_PROVIDER_H
#define STEGANOFS_MAIN_STEGANO_PROVIDER_H

#include "../../steganofs/ramdiskloader.h"
#include "raw/raw_provider.h"
#include "bmp/bmp_provider.h"
#include "stegano_file.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>

typedef struct SteganoFile (*ProviderRead) (const char*);
typedef bool (*ProviderWrite) (struct SteganoFile);

struct SteganoProvider {
    const char *extension;
    ProviderRead providerRead;
    ProviderWrite  providerWrite;
};

struct SerializedFilesystem stegano_provider_read(const char *path);
bool stegano_provider_write(struct SerializedFilesystem serializedFilesystem, const char *path);

#endif //STEGANOFS_MAIN_STEGANO_PROVIDER_H
