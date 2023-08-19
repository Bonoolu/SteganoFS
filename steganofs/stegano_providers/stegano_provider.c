#include "stegano_provider.h"

struct SteganoProvider providers[] = {
        {.extension = "BIN", .providerRead = &read_raw, .providerWrite = &write_raw},
        {.extension = "BMP", .providerRead = &read_bmp, .providerWrite = &write_bmp}
};

struct SerializedFilesystem stegano_provider_read(const char *path) {

    // check if path is a directory
    struct stat filepath_stat;
    stat(path, &filepath_stat);

    struct SerializedFilesystem serializedFilesystem = {.buf = NULL, .size = 0};

    if(filepath_stat.st_mode & S_IFDIR) {
        // if directory, iterate over it and count files with correct extension
        size_t amount_stegano_files;
        // create array which holds all valid SteganoFiles
        // iterate over array and fill each payloads by calling the respective providers
        // create buffer large enough to hold all payloads
        // return Serialized Filesystem
    }

    if (strlen(path) < 3) {
        return serializedFilesystem;
    }
    const char *dot = strrchr(path, '.');
    if (dot == NULL) {
        return serializedFilesystem;
    }
    char *extension = strdup(dot + 1);
    for (char *i = extension; *i != 0; i++) {
        *i = (char) toupper(*i);
    }

    for (size_t i = 0; i < sizeof(providers) / sizeof(providers[0]); i++) {
        struct SteganoProvider provider = providers[i];
        if (strcmp(provider.extension,extension) == 0) {
            struct SteganoFile steganoFile = provider.providerRead(path);
            if (steganoFile.payload_length == 0 || steganoFile.payload == NULL) {
                return serializedFilesystem;
            }
            serializedFilesystem.buf = malloc(steganoFile.payload_length);
            if (serializedFilesystem.buf == NULL) {
                return serializedFilesystem;
            }
            serializedFilesystem.size = steganoFile.payload_length;
            memcpy(serializedFilesystem.buf, steganoFile.payload, serializedFilesystem.size);
            return serializedFilesystem;
        }
    }
    return serializedFilesystem;
}

bool stegano_provider_write(struct SerializedFilesystem serializedFilesystem, const char *path) {

    // check if path is a directory
    struct stat filepath_stat;
    stat(path, &filepath_stat);

    if(filepath_stat.st_mode & S_IFDIR) {
        // if directory, iterate over it and count files with correct extension
        size_t amount_stegano_files;
        // create array which holds all valid SteganoFiles
        // iterate over array and fill each payloads by calling the respective providers
        // create buffer large enough to hold all payloads
        // return Serialized Filesystem
    }

    if (strlen(path) < 3) {
        return false;
    }
    const char *dot = strrchr(path, '.');
    if (dot == NULL) {
        return false;
    }
    char *extension = strdup(dot + 1);
    for (char *i = extension; *i != 0; i++) {
        *i = (char) toupper(*i);
    }

    for (size_t i = 0; i < sizeof(providers) / sizeof(providers[0]); i++) {
        struct SteganoProvider provider = providers[i];
        if (strcmp(provider.extension,extension) == 0) {
            struct SteganoFile steganoFile = {};
            steganoFile.path = strdup(path);
            steganoFile.payload = malloc(serializedFilesystem.size);
            memcpy(steganoFile.payload, serializedFilesystem.buf, serializedFilesystem.size);
            steganoFile.payload_length = serializedFilesystem.size;
            return provider.providerWrite(steganoFile);
        }
    }
    return false;
}