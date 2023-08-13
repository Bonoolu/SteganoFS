#include "stegano_provider.h"

void registerProviders() {
    providerRead[0] = &read_raw;
    providerWrite[0] = &write_raw;
}

struct SerializedFilesystem stegano_provider_read(const char *path, enum Filetype filetype) {
    registerProviders();
    if (filetype > amountProviders - 1){
        struct SerializedFilesystem serializedFilesystem = {.buf = NULL, .size = 0};
        return serializedFilesystem;
    }
    return providerRead[filetype](path);
}
bool stegano_provider_write(struct SerializedFilesystem serializedFilesystem, const char *path, enum Filetype filetype) {
    registerProviders();
    if (filetype > amountProviders - 1){
        return false;
    }
    return providerWrite[filetype](serializedFilesystem, path);
}