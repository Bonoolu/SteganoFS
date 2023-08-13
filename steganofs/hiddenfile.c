#include "hiddenfile.h"

int deleteHiddenFile(HiddenFat *hiddenFat, const char *filename) {
    HiddenFile **pFile = hiddenFat->files;
    bool found = false;
    do {
        if (*pFile != NULL && strcmp((*pFile)->filename, filename) == 0) {
            found = true;
            break;
        }
    } while (++pFile != hiddenFat->files + STEGANOFS_AMOUNT_ROOT_FILES);

    if (found) {
        HiddenCluster *hiddenCluster = (*pFile)->hiddenCluster;
        while (hiddenCluster) {
            HiddenCluster *tmpCluster = hiddenCluster->next;
            size_t tmpBIndex = hiddenCluster->bIndex;
            memset(hiddenFat->disk + (hiddenFat->blockSize * hiddenCluster->bIndex), 0, hiddenFat->blockSize);
            memset(hiddenCluster, 0, sizeof(HiddenCluster));
            hiddenCluster->bIndex = tmpBIndex;
            hiddenCluster = tmpCluster;
        }
        free(*pFile);
        *pFile = NULL;
        printf("Deleted File!\n");
        return 0;
    } else {
        fprintf(stderr, "Could not find file: %s\n", filename);
        return -ENOENT;
    }
}

int countPathComponents(const char *path) {
    int count = 0;
    for (int i = 0; path[i]; i++) {
        if (path[i] == '/')
            count++;
    }
    return count;
}

HiddenFile *findFileByPath(HiddenFat *hiddenFat, const char *path) {
    HiddenFile **pFile = hiddenFat->files;
    bool found = false;
    if (strcmp(path, "/") == 0) {
        return NULL;
    }
    if (countPathComponents(path) == 1) {
        const char *filename = path + 1;
        do {
            if (*pFile != NULL && strcmp((*pFile)->filename, filename) == 0) {
                found = true;
                break;
            }
        } while (++pFile != hiddenFat->files + STEGANOFS_AMOUNT_ROOT_FILES);
    }
    if (found) {
        return *pFile;
    } else {
        return NULL;
    }
}

HiddenFile **createHiddenFile(HiddenFat *hiddenFat, const char *filename, long timestamp) {
    // Find an available file slot
    HiddenFile **searchResult = NULL;
    for (size_t i = 0; i < STEGANOFS_AMOUNT_ROOT_FILES; i++) {
        if (hiddenFat->files[i] == NULL) {
            searchResult = &hiddenFat->files[i];
            break;
        }
    }
    if (searchResult == NULL) {
        fprintf(stderr, "Maximum amount of files are already allocated!\n");
        return NULL;
    }
    if (strlen(filename) > STEGANOFS_MAX_FILENAME_LENGTH - 1) {
        fprintf(stderr, "Filename too long\n");
        return NULL;
    }

    // Create the file structure and update the file table
    HiddenFile *pFile = (HiddenFile *) malloc(sizeof(HiddenFile));
    if (!pFile) {
        fprintf(stderr, "Could not allocate memory!\n");
        return NULL;
    }
    memset(pFile->filename, 0, STEGANOFS_MAX_FILENAME_LENGTH);
    strncpy(pFile->filename, filename, STEGANOFS_MAX_FILENAME_LENGTH);
    pFile->filesize = 0;
    pFile->timestamp = timestamp;
    pFile->hiddenCluster = NULL;
    *searchResult = pFile;

    printf("Created file!\n");
    return searchResult;
}
