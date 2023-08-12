#ifndef STEGANOFS_MAIN_STEGANO_PROVIDER_H
#define STEGANOFS_MAIN_STEGANO_PROVIDER_H

#include "filetype.h"
#include "raw/raw_provider.h"

// RAW = 0, BMP = 1, JPG = 2, PDF = 3
struct SerializedFilesystem (*providerRead[]) (const char*) = {&read_raw, };
void (*providerWrite[]) (struct SerializedFilesystem, const char*) = {&write_raw};
size_t amountProviders = 1;

struct SerializedFilesystem stegano_read(const char *path, enum Filetype filetype);
void stegano_write(struct SerializedFilesystem serializedFilesystem, const char *path, enum Filetype filetype);

#endif //STEGANOFS_MAIN_STEGANO_PROVIDER_H
