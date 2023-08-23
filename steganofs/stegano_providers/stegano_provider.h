#ifndef _STEGANO_PROVIDER_H_
#define _STEGANO_PROVIDER_H_

#include "../../steganofs/ramdiskloader.h"
#include "raw/raw_provider.h"
#include "bmp/bmp_provider.h"
#include "stegano_file.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>

typedef struct SteganoFile (*ProviderRead) (const char *);
typedef size_t (*ProviderWrite) (struct SteganoFile);

struct SteganoProvider {
    const char *extension;
    ProviderRead provider_read;
    ProviderWrite provider_write;
};

struct SerializedFilesystem stegano_provider_read (const char *path);
bool stegano_provider_write (struct SerializedFilesystem serialized_filesystem, const char *path);

#endif //_STEGANO_PROVIDER_H_
