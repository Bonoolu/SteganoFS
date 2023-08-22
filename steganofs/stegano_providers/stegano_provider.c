#include "stegano_provider.h"

struct SteganoProvider providers[] = {
        {.extension = "STEGANOFS", .providerRead = &read_raw, .providerWrite = &write_raw},
        {.extension = "BMP", .providerRead = &read_bmp, .providerWrite = &write_bmp}
};

struct SerializedFilesystem stegano_provider_read(const char *path) {

    // check if path is a directory
    struct stat filepath_stat;
    stat(path, &filepath_stat);

    struct SerializedFilesystem serializedFilesystem = {.buf = NULL, .size = 0};

    size_t writeOffset = 0;
    if(filepath_stat.st_mode & S_IFDIR) {
        struct stat file_info;
        struct dirent **namelist;
        const int n = scandir(path, &namelist, NULL, alphasort);
        for(int fileIndex = 0; fileIndex < n ; fileIndex++) {
            memset(&file_info, 0, sizeof(struct stat));
            char path_buffer[256];
            memset(path_buffer, 0, sizeof(char));
            char dash[2] = "/";
            strcat(path_buffer, path);
            strcat(path_buffer, dash);
            strcat(path_buffer, namelist[fileIndex]->d_name);
            const char *full_path = path_buffer;
            stat(full_path, &file_info);
            if (!S_ISREG(file_info.st_mode)) {
                continue;
            }
            if (!strlen(namelist[fileIndex]->d_name)) {
                continue;
            }
            const char *dot = strrchr(full_path, '.');
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
                    struct SteganoFile steganoFile = provider.providerRead(full_path);
                    size_t new_length = writeOffset + steganoFile.payload_length;
                    printf("Loaded %zu bytes of payload from %s\n", steganoFile.payload_length, full_path);
                    unsigned char *tmp = NULL;
                    if (serializedFilesystem.buf == NULL) {
                        tmp = malloc(new_length);
                    }else {
                        tmp = realloc(serializedFilesystem.buf, new_length);
                    }
                    if (tmp == NULL) {
                        fprintf(stderr, "Out of memory!\n");
                        return serializedFilesystem;
                    }
                    serializedFilesystem.buf = tmp;
                    serializedFilesystem.size = new_length;
                    memcpy(serializedFilesystem.buf + writeOffset, steganoFile.payload, steganoFile.payload_length);
                    writeOffset = new_length;
                }
            }
        }
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

    size_t bytes_written = 0;
    if(filepath_stat.st_mode & S_IFDIR) {
        struct stat file_info;
        struct dirent **namelist;
        const int n = scandir(path, &namelist, NULL, alphasort);
        for(int fileIndex = 0; fileIndex < n && serializedFilesystem.size != bytes_written; fileIndex++) {
            memset(&file_info, 0, sizeof(struct stat));
            char path_buffer[256];
            memset(path_buffer, 0, sizeof(char));
            char dash[2] = "/";
            strcat(path_buffer, path);
            strcat(path_buffer, dash);
            strcat(path_buffer, namelist[fileIndex]->d_name);
            const char *full_path = path_buffer;
            stat(full_path, &file_info);
            if (!S_ISREG(file_info.st_mode)) {
                continue;
            }
            if (!strlen(namelist[fileIndex]->d_name)) {
                continue;
            }
            const char *dot = strrchr(full_path, '.');
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
                    steganoFile.path = strdup(full_path);
                    steganoFile.payload = serializedFilesystem.buf + bytes_written;
                    steganoFile.payload_length = serializedFilesystem.size - bytes_written;
                    size_t written = provider.providerWrite(steganoFile);
                    bytes_written += written;
                    printf("Wrote %zu bytes of payload to %s\n", written, full_path);
                    if (serializedFilesystem.size == bytes_written) {
                        break;
                    }
                }

            }
        }
        return serializedFilesystem.size == bytes_written;
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