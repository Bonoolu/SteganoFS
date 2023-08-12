#include "raw_provider.h"

struct SerializedFilesystem read_raw(const char *path) {
    FILE *file = fopen(path, "rb");
    struct SerializedFilesystem serializedFilesystem = {.size = 0, .buf = NULL};
    if (file) {
        fseek(file, 0L, SEEK_END);
        serializedFilesystem.size = ftell(file);
        rewind(file);
        serializedFilesystem.buf = malloc(serializedFilesystem.size);
        if (serializedFilesystem.buf == NULL) {
            serializedFilesystem.size = 0;
            return serializedFilesystem;
        }
        fread(serializedFilesystem.buf, serializedFilesystem.size, 1, file);
        fflush(file);
        fclose(file);
    }
    return serializedFilesystem;
}

void write_raw(struct SerializedFilesystem serializedFilesystem, const char *path) {
    FILE *file = fopen(path, "wb");
    if (file) {
        fwrite(serializedFilesystem.buf, serializedFilesystem.size, 1, file);
        fflush(file);
        fclose(file);
    }
}
