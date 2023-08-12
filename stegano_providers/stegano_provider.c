#include "stegano_provider.h"

struct SerializedFilesystem stegano_read(const char *path, enum Filetype filetype) {
    if (filetype > amountProviders - 1){
        struct SerializedFilesystem serializedFilesystem = {.buf = NULL, .size = 0};
        return serializedFilesystem;
    }
    return providerRead[filetype](path);
}
void stegano_write(struct SerializedFilesystem serializedFilesystem, const char *path, enum Filetype filetype) {
    if (filetype > amountProviders - 1){
        return;
    }
    return providerWrite[filetype](serializedFilesystem, path);
}