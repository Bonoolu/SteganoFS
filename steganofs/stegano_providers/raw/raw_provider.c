#include "raw_provider.h"

struct SteganoFile read_raw(const char *path) {
    FILE *file = fopen(path, "rb");
    struct SteganoFile steganoFile = {.payload = NULL, .payload_length = 0};
    if (file) {
        fseek(file, 0L, SEEK_END);
        steganoFile.payload_length = ftell(file);
        rewind(file);
        steganoFile.payload = malloc(steganoFile.payload_length);
        if (steganoFile.payload == NULL) {
            steganoFile.payload_length = 0;
            return steganoFile;
        }
        fread(steganoFile.payload, steganoFile.payload_length, 1, file);
        fflush(file);
        fclose(file);
    }
    return steganoFile;
}

size_t write_raw(struct SteganoFile steganoFile) {
    FILE *file = fopen((char*) steganoFile.path, "wb");
    if (file) {
        size_t written = fwrite(steganoFile.payload, steganoFile.payload_length, 1, file);
        fflush(file);
        fclose(file);
        return steganoFile.payload_length;
    }
    return 0;
}
