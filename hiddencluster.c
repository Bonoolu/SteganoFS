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
    //TODO! check if bIndex is out of range
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

    // Swap the state
    unsigned int tempState = hiddenFat->clusters[bIndexA].state;
    hiddenFat->clusters[bIndexA].state = hiddenFat->clusters[bIndexB].state;
    hiddenFat->clusters[bIndexB].state = tempState;

    // Update the block indices in the cluster structure if applicable
    hiddenFat->clusters[bIndexA].bIndex = bIndexA;
    hiddenFat->clusters[bIndexB].bIndex = bIndexB;

    // Swap blocks on disk
    unsigned char buffer[BLOCKSIZE];
    memcpy(buffer, hiddenFat->disk + (BLOCKSIZE * bIndexA), BLOCKSIZE);
    memcpy(hiddenFat->disk + (BLOCKSIZE * bIndexA), hiddenFat->disk + (BLOCKSIZE * bIndexB), BLOCKSIZE);
    memcpy(hiddenFat->disk + (BLOCKSIZE * bIndexB), buffer, BLOCKSIZE);

    return true;
}