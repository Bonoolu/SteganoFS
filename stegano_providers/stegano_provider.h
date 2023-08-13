#ifndef STEGANOFS_MAIN_STEGANO_PROVIDER_H
#define STEGANOFS_MAIN_STEGANO_PROVIDER_H

#include "filetype.h"
#include "raw/raw_provider.h"

// RAW = 0, BMP = 1, JPG = 2, PDF = 3
typedef struct SerializedFilesystem (*ProviderRead) (const char*);
typedef bool (*ProviderWrite) (struct SerializedFilesystem, const char*);

static ProviderRead providerRead[] = {0};
static ProviderWrite providerWrite[] = {0};

static size_t amountProviders = 1;

struct SerializedFilesystem stegano_provider_read(const char *path, enum Filetype filetype);
bool stegano_provider_write(struct SerializedFilesystem serializedFilesystem, const char *path, enum Filetype filetype);

#endif //STEGANOFS_MAIN_STEGANO_PROVIDER_H
