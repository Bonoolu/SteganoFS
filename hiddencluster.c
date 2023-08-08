#include "hiddencluster.h"


bool extendHiddenCluster(HiddenFat *hiddenFat, HiddenFile *pFile) {
    size_t bIndex;
    for (bIndex = 0; bIndex < hiddenFat->amountBlocks; bIndex++) {
        if (hiddenFat->clusters[bIndex].state == free_) {
            break;
        }
        if (bIndex == hiddenFat->amountBlocks - 1) {
            fprintf(stderr, "Partition is full!\n");
            return false;
        }
    }
    // Allocate the block for the file
    hiddenFat->clusters[bIndex].state = allocated;
    hiddenFat->clusters[bIndex].bIndex = bIndex;
    int clusterIndex = 0;
    HiddenCluster *lastCluster = pFile->hiddenCluster;
    while (lastCluster) {
        clusterIndex++;
        if (lastCluster->next == NULL) {
            break;
        }
        lastCluster = lastCluster->next;
    }
    if (lastCluster != NULL) {
        hiddenFat->clusters[bIndex].prev = lastCluster;
        lastCluster->next = &(hiddenFat->clusters[bIndex]);
    } else {
        pFile->hiddenCluster = &(hiddenFat->clusters[bIndex]);
    }
    hiddenFat->clusters[bIndex].clusterIndex = clusterIndex;
    hiddenFat->clusters[bIndex].file = pFile;
    pFile->filesize += hiddenFat->blockSize;
    return true;
}


bool swapHiddenClusters(HiddenFat *hiddenFat, size_t bIndexA, size_t bIndexB) {
    if (bIndexA == bIndexB) {
        fprintf(stderr, "Swapping the same block is not possible!\n");
        return false;
    }
    if (bIndexA >= hiddenFat->amountBlocks || bIndexB >= hiddenFat->amountBlocks) {
        fprintf(stderr, "Invalid block indices for swapHiddenClusters.\n");
        return false;
    }
    if (hiddenFat->clusters[bIndexA].state == free_ && hiddenFat->clusters[bIndexB].state == free_) {
        fprintf(stderr, "No need to swap two free Blocks!\n");
        return false;
    }
    if (hiddenFat->clusters[bIndexA].state == reserved || hiddenFat->clusters[bIndexB].state == reserved) {
        fprintf(stderr, "\"Invalid block for swapHiddenClusters! Can't swap with a reserved block!\n");
        return false;
    }
    if (hiddenFat->clusters[bIndexA].state == defect || hiddenFat->clusters[bIndexB].state == defect) {
        fprintf(stderr, "\"Invalid block for swapHiddenClusters! Can't swap with a defect block!\n");
        return false;
    }

    size_t clusterIndexClusterA = hiddenFat->clusters[bIndexA].clusterIndex;
    unsigned int stateClusterA = hiddenFat->clusters[bIndexA].state;
    HiddenCluster *prevClusterA = hiddenFat->clusters[bIndexA].prev;
    HiddenCluster *nextClusterA = hiddenFat->clusters[bIndexA].next;
    HiddenFile *fileClusterA = hiddenFat->clusters[bIndexA].file;

    hiddenFat->clusters[bIndexA].clusterIndex = hiddenFat->clusters[bIndexB].clusterIndex;
    hiddenFat->clusters[bIndexA].state = hiddenFat->clusters[bIndexB].state;
    hiddenFat->clusters[bIndexA].prev = hiddenFat->clusters[bIndexB].prev;
    hiddenFat->clusters[bIndexA].next = hiddenFat->clusters[bIndexB].next;
    hiddenFat->clusters[bIndexA].file = hiddenFat->clusters[bIndexB].file;

    hiddenFat->clusters[bIndexB].clusterIndex = clusterIndexClusterA;
    hiddenFat->clusters[bIndexB].state = stateClusterA;
    hiddenFat->clusters[bIndexB].prev = prevClusterA;
    hiddenFat->clusters[bIndexB].next = nextClusterA;
    hiddenFat->clusters[bIndexB].file = fileClusterA;

    if (hiddenFat->clusters[bIndexA].next == &(hiddenFat->clusters[bIndexA])) {
        hiddenFat->clusters[bIndexA].next = &(hiddenFat->clusters[bIndexB]);
    }
    if (hiddenFat->clusters[bIndexA].prev == &(hiddenFat->clusters[bIndexA])) {
        hiddenFat->clusters[bIndexA].prev = &(hiddenFat->clusters[bIndexB]);
    }
    if (hiddenFat->clusters[bIndexB].next == &(hiddenFat->clusters[bIndexB])) {
        hiddenFat->clusters[bIndexB].next = &(hiddenFat->clusters[bIndexA]);
    }
    if (hiddenFat->clusters[bIndexB].prev == &(hiddenFat->clusters[bIndexB])) {
        hiddenFat->clusters[bIndexB].prev = &(hiddenFat->clusters[bIndexA]);
    }

    if (hiddenFat->clusters[bIndexA].prev != NULL) {
        hiddenFat->clusters[bIndexA].prev->next = &(hiddenFat->clusters[bIndexA]);
    } else if (hiddenFat->clusters[bIndexA].file != NULL) {
        hiddenFat->clusters[bIndexA].file->hiddenCluster = &(hiddenFat->clusters[bIndexA]);
    }

    if (hiddenFat->clusters[bIndexA].next != NULL) {
        hiddenFat->clusters[bIndexA].next->prev = &(hiddenFat->clusters[bIndexA]);
    }

    if (hiddenFat->clusters[bIndexB].prev != NULL) {
        hiddenFat->clusters[bIndexB].prev->next = &(hiddenFat->clusters[bIndexB]);
    } else if (hiddenFat->clusters[bIndexB].file != NULL) {
        hiddenFat->clusters[bIndexB].file->hiddenCluster = &(hiddenFat->clusters[bIndexB]);
    }

    if (hiddenFat->clusters[bIndexB].next != NULL) {
        hiddenFat->clusters[bIndexB].next->prev = &(hiddenFat->clusters[bIndexB]);
    }


    size_t blockSize = hiddenFat->blockSize;
    // Swap blocks on disk
    unsigned char bufferA[blockSize];
    memcpy(bufferA, hiddenFat->disk + (blockSize * bIndexA), blockSize);
    memcpy(hiddenFat->disk + (blockSize * bIndexA), hiddenFat->disk + (blockSize * bIndexB), blockSize);
    memcpy(hiddenFat->disk + (blockSize * bIndexB), bufferA, blockSize);

    return true;
}