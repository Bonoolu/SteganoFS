#include "ramdiskloader.h"

struct SerializedFilesystem serializeFilesystem(HiddenFat *hiddenFat) {
    size_t sizePackedFat = sizeof(PackedFat);
    size_t sizePackedClusters = sizeof(PackedCluster) * hiddenFat->amountBlocks;
    size_t sizePackedFiles = sizeof(PackedFile) * STEGANOFS_AMOUNT_ROOT_FILES;
    size_t sizeBlocks = hiddenFat->amountBlocks * hiddenFat->blockSize;

    size_t offsetPackedFat = 0;
    size_t offsetPackedCluster = offsetPackedFat + sizePackedFat;
    size_t offsetPackedFiles = offsetPackedCluster + sizePackedClusters;
    size_t offsetBlocks = offsetPackedFiles + sizePackedFiles;

    size_t sizeFilesystem = offsetBlocks + sizeBlocks;

    unsigned char *bufferFilesystem = malloc(sizeFilesystem);
    memset(bufferFilesystem, 0, sizeFilesystem);

    PackedFat *packedFat = (PackedFat*) (bufferFilesystem + offsetPackedFat);
    PackedCluster *packedClusters = (PackedCluster*) (bufferFilesystem + offsetPackedCluster);
    PackedFile *packedFiles = (PackedFile*) (bufferFilesystem + offsetPackedFiles);
    unsigned char *disk = bufferFilesystem + offsetBlocks;

    packedFat->blockSize = hiddenFat->blockSize;
    packedFat->amountBlocks = hiddenFat->amountBlocks;
    packedFat->clustersOffset = offsetPackedCluster;
    packedFat->amount_root_files = STEGANOFS_AMOUNT_ROOT_FILES;
    packedFat->filesOffset = offsetPackedFiles;
    packedFat->diskOffset = offsetBlocks;

    PackedFile *fileIterator = packedFiles;
    for (HiddenFile **hiddenFile = hiddenFat->files; hiddenFile < hiddenFat->files + STEGANOFS_AMOUNT_ROOT_FILES; hiddenFile++) {
        if (*hiddenFile == NULL) {
            continue;
        }
        fileIterator->filesize = (*hiddenFile)->filesize;
        if ((*hiddenFile)->hiddenCluster == NULL) {
            fileIterator->hiddenClusterBIndex = - 1;
        }else {
            fileIterator->hiddenClusterBIndex = (int64_t)((*hiddenFile)->hiddenCluster->bIndex);
        }
        strncpy(fileIterator->filename, (*hiddenFile)->filename, STEGANOFS_MAX_FILENAME_LENGTH - 1);
        fileIterator->real_filesize = (*hiddenFile)->real_filesize;
        fileIterator->timestamp = (*hiddenFile)->timestamp;


        HiddenCluster *hiddenCluster = (*hiddenFile)->hiddenCluster;
        while(hiddenCluster) {
            size_t bIndex = hiddenCluster->bIndex;
            packedClusters[bIndex].bIndex = hiddenCluster->bIndex;
            packedClusters[bIndex].clusterIndex = hiddenCluster->clusterIndex;
            packedClusters[bIndex].state = hiddenCluster->state;
            packedClusters[bIndex].fileOffset = fileIterator - packedFiles;
            if (hiddenCluster->prev == NULL) {
                packedClusters[bIndex].prevClusterBIndex = -1;
            }else {
                packedClusters[bIndex].prevClusterBIndex = (int64_t) hiddenCluster->prev->bIndex;
            }
            if (hiddenCluster->next == NULL) {
                packedClusters[bIndex].nextClusterBIndex = -1;
            }else {
                packedClusters[bIndex].nextClusterBIndex = (int64_t) hiddenCluster->next->bIndex;
            }
            hiddenCluster = hiddenCluster->next;
        }
    }
    memcpy(disk, hiddenFat->disk, hiddenFat->amountBlocks * hiddenFat->blockSize);
    struct SerializedFilesystem serializedFilesystem = {.size = sizeFilesystem, .buf = bufferFilesystem};
    return serializedFilesystem;
}

HiddenFat *loadRamdisk(struct SerializedFilesystem serializedFilesystem) {
    PackedFat *packedFat = (PackedFat*) serializedFilesystem.buf;
    PackedCluster *packedClusters = (PackedCluster*) serializedFilesystem.buf + packedFat->clustersOffset;
    PackedFile *packedFiles = (PackedFile*) serializedFilesystem.buf + packedFat->filesOffset;
    unsigned char *disk = serializedFilesystem.buf + packedFat->diskOffset;

    HiddenFat *hiddenFat = createHiddenFat(packedFat->blockSize * packedFat->amountBlocks, packedFat->blockSize);

    HiddenFile **fileIterator = hiddenFat->files;
    struct PackedFile emptyFile;
    memset(&emptyFile, 0, sizeof(PackedFile));
    for (PackedFile *packedFile = packedFiles; packedFile < packedFiles + STEGANOFS_AMOUNT_ROOT_FILES; packedFile++) {
        if (memcmp(packedFile, &emptyFile, sizeof(PackedFile)) == 0) {
            continue;
        }
        *fileIterator = malloc(sizeof(HiddenFile));
        (*fileIterator)->filesize = (packedFile)->filesize;
        if (packedFile->hiddenClusterBIndex == -1) {
            (*fileIterator)->hiddenCluster = NULL;
        }else {
            (*fileIterator)->hiddenCluster = hiddenFat->clusters + packedFile->hiddenClusterBIndex;
        }
        strncpy(packedFile->filename, (*fileIterator)->filename,STEGANOFS_MAX_FILENAME_LENGTH - 1);
        (*fileIterator)->real_filesize = packedFile->real_filesize;
        (*fileIterator)->timestamp = packedFile->timestamp;

        HiddenCluster *hiddenCluster = (*fileIterator)->hiddenCluster;
        // TODO: continue from here
        while(hiddenCluster) {
            size_t bIndex = hiddenCluster->bIndex;
            packedClusters[bIndex].bIndex = hiddenCluster->bIndex;
            packedClusters[bIndex].clusterIndex = hiddenCluster->clusterIndex;
            packedClusters[bIndex].state = hiddenCluster->state;
            packedClusters[bIndex].fileOffset = fileIterator - packedFiles;
            if (hiddenCluster->prev == NULL) {
                packedClusters[bIndex].prevClusterBIndex = -1;
            }else {
                packedClusters[bIndex].prevClusterBIndex = (int64_t) hiddenCluster->prev->bIndex;
            }
            if (hiddenCluster->next == NULL) {
                packedClusters[bIndex].nextClusterBIndex = -1;
            }else {
                packedClusters[bIndex].nextClusterBIndex = (int64_t) hiddenCluster->next->bIndex;
            }
            hiddenCluster = hiddenCluster->next;
        }
    }
    memcpy(disk, hiddenFat->disk, hiddenFat->amountBlocks * hiddenFat->blockSize);


    return NULL;
}