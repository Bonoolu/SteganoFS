#include "ramdiskloader.h"

struct SerializedFilesystem serializeFilesystem(HiddenFat *hiddenFat) {
    size_t sizePackedFat = sizeof(PackedFat);
    size_t sizePackedClusters = sizeof(PackedCluster) * hiddenFat->amountBlocks;
    size_t sizePackedFiles = sizeof(PackedFile) * AMOUNT_ROOT_FILES;
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
    packedFat->clusters = offsetPackedCluster;
    packedFat->amount_root_files = AMOUNT_ROOT_FILES;
    packedFat->files = offsetPackedFiles;
    packedFat->disk = offsetBlocks;

    PackedFile *fileIterator = packedFiles;
    for (HiddenFile **hiddenFile = hiddenFat->files; hiddenFile < hiddenFat->files + AMOUNT_ROOT_FILES; hiddenFile++) {
        if (*hiddenFile == NULL) {
            continue;
        }
        fileIterator->filesize = (*hiddenFile)->filesize;
        if ((*hiddenFile)->hiddenCluster == NULL) {
            fileIterator->hiddenCluster = - 1;
        }else {
            fileIterator->hiddenCluster = (int64_t)((*hiddenFile)->hiddenCluster->bIndex);
        }
        strncpy(fileIterator->filename, (*hiddenFile)->filename, MAX_FILENAME_LENGTH - 1);
        fileIterator->real_filesize = (*hiddenFile)->real_filesize;
        fileIterator->timestamp = (*hiddenFile)->timestamp;


        HiddenCluster *hiddenCluster = (*hiddenFile)->hiddenCluster;
        while(hiddenCluster) {
            size_t bIndex = hiddenCluster->bIndex;
            packedClusters[bIndex].bIndex = hiddenCluster->bIndex;
            packedClusters[bIndex].clusterIndex = hiddenCluster->clusterIndex;
            packedClusters[bIndex].state = hiddenCluster->state;
            packedClusters[bIndex].file = fileIterator - packedFiles;
            if (hiddenCluster->prev == NULL) {
                packedClusters[bIndex].prev = -1;
            }else {
                packedClusters[bIndex].prev = (int64_t) hiddenCluster->prev->bIndex;
            }
            if (hiddenCluster->next == NULL) {
                packedClusters[bIndex].next = -1;
            }else {
                packedClusters[bIndex].next = (int64_t) hiddenCluster->next->bIndex;
            }
            hiddenCluster = hiddenCluster->next;
        }
    }
    memcpy(disk, hiddenFat->disk, hiddenFat->amountBlocks * hiddenFat->blockSize);
    struct SerializedFilesystem serializedFilesystem = {.size = sizeFilesystem, .buf = bufferFilesystem};
    return serializedFilesystem;
}

//HiddenFat *deserializeFilesystem(struct SerializedFilesystem serializedFilesystem) {
//
//}