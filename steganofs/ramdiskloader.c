#include "ramdiskloader.h"

struct FilesystemBuffer unloadFilesystem(HiddenFat *hiddenFat) {
    size_t sizePackedFat = sizeof(PackedFat);
    size_t sizePackedClusters = sizeof(PackedCluster) * hiddenFat->amountBlocks;
    size_t sizePackedFiles = sizeof(PackedFile) * AMOUNT_ROOT_FILES;
    size_t sizeBlocks = hiddenFat->amountBlocks * hiddenFat->blockSize;

    size_t offsetPackedFat = 0;
    size_t offsetPackedCluster = sizePackedFat;
    size_t offsetPackedFiles = offsetPackedCluster + sizePackedClusters;
    size_t offsetBlocks = offsetPackedFiles + sizePackedFiles;

    size_t sizeFilesystem = offsetBlocks + sizeBlocks;

    unsigned char *bufferFilesystem = malloc(sizeFilesystem);
    memset(bufferFilesystem, 0, sizeFilesystem);

    PackedFat *packedFat = (PackedFat*) bufferFilesystem;
    PackedCluster *packedClusters = (PackedCluster*) (bufferFilesystem + offsetPackedCluster);
    PackedFile *packedFiles = (PackedFile*) (bufferFilesystem + offsetPackedFiles);
    unsigned char *disk = bufferFilesystem + offsetBlocks;

    packedFat->blockSize = hiddenFat->blockSize;
    packedFat->amountBlocks = hiddenFat->amountBlocks;
    packedFat->clusters = offsetPackedCluster;
    packedFat->amount_root_files = AMOUNT_ROOT_FILES;
    packedFat->files = offsetPackedFiles;
    packedFat->disk = offsetBlocks;

    // TODO! You should iterate over the files as they have a 1 to n relation with the clusters, much easier to implement
    for (size_t i = 0; i < hiddenFat->amountBlocks; i++) {
        packedClusters[i].bIndex = hiddenFat->clusters[i].bIndex;
        packedClusters[i].clusterIndex = hiddenFat->clusters[i].clusterIndex;
        packedClusters[i].state = hiddenFat->
    }

}

HiddenFat *loadFilesystem(struct FilesystemBuffer filesystemBuffer) {

}