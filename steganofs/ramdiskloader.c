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

    PackedFile *packedFileIterator = packedFiles;
    for (HiddenFile **hiddenFile = hiddenFat->files; hiddenFile < hiddenFat->files + STEGANOFS_AMOUNT_ROOT_FILES; hiddenFile++) {
        if (*hiddenFile == NULL) {
            packedFileIterator++;
            continue;
        }
        packedFileIterator->filesize = (*hiddenFile)->filesize;
        if ((*hiddenFile)->hiddenCluster == NULL) {
            packedFileIterator->hiddenClusterBIndex = - 1;
        }else {
            packedFileIterator->hiddenClusterBIndex = (int64_t)((*hiddenFile)->hiddenCluster->bIndex);
        }
        strncpy(packedFileIterator->filename, (*hiddenFile)->filename, STEGANOFS_MAX_FILENAME_LENGTH - 1);
        packedFileIterator->real_filesize = (*hiddenFile)->real_filesize;
        packedFileIterator->timestamp = (*hiddenFile)->timestamp;


        HiddenCluster *hiddenCluster = (*hiddenFile)->hiddenCluster;
        while(hiddenCluster) {
            size_t bIndex = hiddenCluster->bIndex;
            packedClusters[bIndex].bIndex = hiddenCluster->bIndex;
            packedClusters[bIndex].clusterIndex = hiddenCluster->clusterIndex;
            packedClusters[bIndex].state = hiddenCluster->state;
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
        packedFileIterator++;
    }
    memcpy(disk, hiddenFat->disk, hiddenFat->amountBlocks * hiddenFat->blockSize);
    struct SerializedFilesystem serializedFilesystem = {.size = sizeFilesystem, .buf = bufferFilesystem};
    return serializedFilesystem;
}

HiddenFat *loadRamdisk(struct SerializedFilesystem serializedFilesystem) {
    PackedFat *packedFat = (PackedFat*) serializedFilesystem.buf;
    PackedCluster *packedClusters = (PackedCluster*) (serializedFilesystem.buf + packedFat->clustersOffset);
    PackedFile *packedFiles = (PackedFile*) (serializedFilesystem.buf + packedFat->filesOffset);
    unsigned char *disk = serializedFilesystem.buf + packedFat->diskOffset;

    HiddenFat *hiddenFat = createHiddenFat(packedFat->blockSize * packedFat->amountBlocks, packedFat->blockSize);

    HiddenFile **hiddenFileIterator = hiddenFat->files;
    struct PackedFile emptyFile;
    memset(&emptyFile, 0, sizeof(PackedFile));
    for (PackedFile *packedFile = packedFiles; packedFile < packedFiles + packedFat->amount_root_files; packedFile++) {
        if (memcmp(packedFile, &emptyFile, sizeof(PackedFile)) == 0) {
            hiddenFileIterator++;
            continue;
        }
        *hiddenFileIterator = malloc(sizeof(HiddenFile));
        memset(*hiddenFileIterator, 0, sizeof(HiddenFile));
        (*hiddenFileIterator)->filesize = (packedFile)->filesize;
        if (packedFile->hiddenClusterBIndex == -1) {
            (*hiddenFileIterator)->hiddenCluster = NULL;
        }else {
            (*hiddenFileIterator)->hiddenCluster = hiddenFat->clusters + packedFile->hiddenClusterBIndex;
        }
        strncpy((*hiddenFileIterator)->filename, packedFile->filename, STEGANOFS_MAX_FILENAME_LENGTH - 1);
        (*hiddenFileIterator)->real_filesize = packedFile->real_filesize;
        (*hiddenFileIterator)->timestamp = packedFile->timestamp;

        HiddenCluster *hiddenCluster = (*hiddenFileIterator)->hiddenCluster;
        size_t bIndex = 0;
        while(hiddenCluster != NULL && bIndex != -1) {
            bIndex = hiddenCluster->bIndex;
            hiddenCluster->bIndex = packedClusters[bIndex].bIndex;
            hiddenCluster->clusterIndex = packedClusters[bIndex].clusterIndex;
            hiddenCluster->state = packedClusters[bIndex].state;
            hiddenCluster->file = *hiddenFileIterator;
            if (packedClusters[bIndex].prevClusterBIndex == -1) {
                hiddenCluster->prev = NULL;
            }else {
               hiddenCluster->prev = hiddenFat->clusters + packedClusters[bIndex].prevClusterBIndex;
            }
            if (packedClusters[bIndex].nextClusterBIndex == -1) {
                hiddenCluster->next = NULL;
            }else {
                hiddenCluster->next = hiddenFat->clusters + packedClusters[bIndex].nextClusterBIndex;
            }
            hiddenCluster = hiddenCluster->next;
            bIndex = packedClusters[bIndex].nextClusterBIndex;
        }
        hiddenFileIterator++;
    }
    memcpy(hiddenFat->disk, disk, hiddenFat->amountBlocks * hiddenFat->blockSize);

    return hiddenFat;
}