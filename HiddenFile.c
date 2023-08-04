//
// Created by Group 80 on 8/4/23.
//

#include "HiddenFile.h"


void deleteHiddenFile(HiddenFat *hiddenFat, const char *filename) {
//    BsFile **pFile = hiddenFat->files;
//    bool found = false;
//    do {
//        if (*pFile != NULL && strcmp((*pFile)->filename, filename) == 0) {
//            found = true;
//            break;
//        }
//    } while (++pFile != hiddenFat->files + AMOUNT_FILES);
//
//    if (found) {
//        BsBlock *hiddenCluster = (*pFile)->hiddenCluster;
//        while (hiddenCluster) {
//            hiddenFat->blocks[hiddenCluster->bIndex].state = free_;
//            hiddenFat->blocks[hiddenCluster->bIndex].prev  = NULL;
//            pCluster = pCluster->next;
//        }
//        free((*pFile)->pCluster);
//        free(*pFile);
//        *pFile = NULL;
//        printf("Deleted File!\n");
//    } else {
//        fprintf(stderr, "Could not find file: %s\n", filename);
//    }
}


int countPathComponents(const char *path) {
    int count = 0;
    for (int i = 0; path[i]; i++) {
        if (path[i] == '/')
            count++;
    }
    return count;
}

HiddenFile *findFileByPath(HiddenFat *hiddenFat, const char* path){
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
        } while (++pFile != hiddenFat->files + AMOUNT_ROOT_FILES);
    }
    if (found) {
        return *pFile;
    }else {
        return NULL;
    }
}


HiddenFile **createHiddenFile(HiddenFat *hiddenFat, const char *filename, long timestamp) {
    // Find an available file slot
    HiddenFile **searchResult = NULL;
    for (size_t i = 0; i < AMOUNT_ROOT_FILES; i++) {
        if (hiddenFat->files[i] == NULL) {
            searchResult = &hiddenFat->files[i];
            break;
        }
    }
    if (searchResult == NULL) {
        fprintf(stderr, "Maximum amount of files are already allocated!\n");
        return NULL;
    }

    // Create the file structure and update the file table
    HiddenFile *pFile = (HiddenFile *) malloc(sizeof(HiddenFile));
    if (!pFile) {
        fprintf(stderr, "Could not allocate memory!\n");
        return NULL;
    }
    char* dup_filename = strdup(filename);
    pFile->filename = dup_filename;
    pFile->filesize = 0;
    pFile->timestamp = timestamp;
    pFile->hiddenCluster = NULL;
    *searchResult = pFile;

    printf("Created file!\n");
    return searchResult;
}