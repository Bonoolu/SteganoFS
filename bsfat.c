#include "bsfat.h"

// TODO:
//
// allow non consecutive writes
// implement reading and writing files
// implement directories
// implement export
// implement import

// write doxygen

BsFat *createBsFat(size_t diskSize, size_t blockSize) {
    if (diskSize == 0 || blockSize == 0) {
        fprintf(stderr, "Disk size and blockSize each can not be zero!\n");
        exit(1);
    }
    if (diskSize % blockSize != 0) {
        fprintf(stderr, "Disk size is not dividable by block size!\n");
        exit(1);
    }
    unsigned char *disk = (unsigned char *) malloc(diskSize * sizeof(unsigned char));
    if (!disk) {
        fprintf(stderr, "Could not allocate memory!\n");
        exit(1);
    }
    memset(disk, 0, diskSize);
    size_t amountBlocks = diskSize / blockSize;
    BsBlock *blocks = (BsBlock *) malloc(amountBlocks * sizeof(BsBlock));
    if (!blocks) {
        fprintf(stderr, "Could not allocate memory!\n");
        exit(1);
    }
    memset(blocks, 0, amountBlocks * sizeof(BsBlock));
    for (size_t bIndex = 0; bIndex < amountBlocks; bIndex++) {
        blocks[bIndex].bIndex = bIndex;
    }
    BsFat *pFat = (BsFat *) malloc(sizeof(BsFat));
    if (!pFat) {
        fprintf(stderr, "Could not allocate memory!\n");
        exit(1);
    }
    memset(pFat->files, 0, AMOUNT_FILES * sizeof(BsFile *));
    pFat->blockSize = blockSize;
    pFat->amountBlocks = amountBlocks;
    pFat->disk = disk;
    pFat->blocks = blocks;
    return pFat;
}

void freeBsFat(BsFat *pFat) {
    if (pFat == NULL) {
        return;
    }

    // Free the disk memory
    free(pFat->disk);

    // Free the block structures
    free(pFat->blocks);

    // Free the file structures
    for (size_t i = 0; i < AMOUNT_FILES; i++) {
        BsFile *pFile = pFat->files[i];
        if (pFile != NULL) {
            // Free the cluster structures associated with the file
            free(pFile->pCluster);
            // Free the file structure
            free(pFile);
        }
    }

    // Free the BsFat structure itself
    free(pFat);
}

size_t getFreeDiskSpace(BsFat *pFat) {
    if (pFat == NULL) {
        fprintf(stderr, "Invalid BsFat pointer.\n");
        return 0;
    }

    size_t amountFreeBlocks = 0;
    for (size_t i = 0; i < pFat->amountBlocks; i++) {
        if (pFat->blocks[i].state == free_) {
            amountFreeBlocks++;
        }
    }

    return amountFreeBlocks * pFat->blockSize;
}

BsFile **createFile(BsFat *pFat, size_t szFile, const char *filename, long timestamp) {
    // Find an available file slot
    BsFile **searchResult = NULL;
    for (size_t i = 0; i < AMOUNT_FILES; i++) {
        if (pFat->files[i] == NULL) {
            searchResult = &pFat->files[i];
            break;
        }
    }
    if (searchResult == NULL) {
        fprintf(stderr, "Maximum amount of files are already allocated!\n");
        return NULL;
    }

    // Calculate the number of blocks needed for the file
    size_t amountBlocksToAllocate = szFile / pFat->blockSize;
    if (szFile % pFat->blockSize != 0) {
        amountBlocksToAllocate++;
    }

    // Check if enough consecutive free blocks are available
    size_t consecutiveFreeBlocks = 0;
    size_t startBlockIndex = 0;
    for (size_t bIndex = 0; bIndex < pFat->amountBlocks; bIndex++) {
        if (pFat->blocks[bIndex].state == free_) {
            if (consecutiveFreeBlocks == 0) {
                startBlockIndex = bIndex;
            }
            consecutiveFreeBlocks++;
            if (consecutiveFreeBlocks >= amountBlocksToAllocate) {
                break;
            }
        } else {
            consecutiveFreeBlocks = 0;
        }
    }

    if (consecutiveFreeBlocks < amountBlocksToAllocate) {
        fprintf(stderr, "There are not enough consecutive free blocks for this file!\n");
        return NULL;
    }

    // Allocate the blocks for the file
    BsCluster *pCluster = (BsCluster *) malloc(amountBlocksToAllocate * sizeof(BsCluster));
    if (!pCluster) {
        fprintf(stderr, "Could not allocate memory!\n");
        return NULL;
    }
    memset(pCluster, 0, amountBlocksToAllocate * sizeof(BsCluster));

    size_t clusterIndex = 0;
    for (size_t bIndex = startBlockIndex; bIndex < startBlockIndex + amountBlocksToAllocate; bIndex++) {
        pFat->blocks[bIndex].state = allocated;
        pFat->blocks[bIndex].bIndex = bIndex;
        pFat->blocks[bIndex].cluster = &pCluster[clusterIndex];
        pCluster[clusterIndex].bIndex = bIndex;
        pCluster[clusterIndex].clusterIndex = clusterIndex;
        pCluster[clusterIndex].fileIndex = searchResult - pFat->files;
        if (clusterIndex > 0) {
            pCluster[clusterIndex].prev = pCluster + clusterIndex - 1;
            pCluster[clusterIndex - 1].next = pCluster + clusterIndex;
        }
        clusterIndex++;
    }

    // Create the file structure and update the file table
    BsFile *pFile = (BsFile *) malloc(sizeof(BsFile));
    if (!pFile) {
        fprintf(stderr, "Could not allocate memory!\n");
        free(pCluster);
        return NULL;
    }
    pFile->filename = filename;
    pFile->filesize = szFile;
    pFile->timestamp = timestamp;
    pFile->pCluster = pCluster;
    *searchResult = pFile;

    printf("Created file!\n");
    return searchResult;
}

void deleteFile(BsFat *pFat, const char *filename) {
    BsFile **pFile = pFat->files;
    bool found = false;
    do {
        if (*pFile != NULL && strcmp((*pFile)->filename, filename) == 0) {
            found = true;
            break;
        }
    } while (++pFile != pFat->files + AMOUNT_FILES);

    if (found) {
        BsCluster *pCluster = (*pFile)->pCluster;
        while (pCluster) {
            pFat->blocks[pCluster->bIndex].state = free_;
            pFat->blocks[pCluster->bIndex].cluster = NULL;
            pCluster = pCluster->next;
        }
        free((*pFile)->pCluster);
        free(*pFile);
        *pFile = NULL;
        printf("Deleted File!\n");
    } else {
        fprintf(stderr, "Could not find file: %s\n", filename);
    }
}

void showFat(BsFat *pFat, char *outputMessage) {
    char letterMap[3] = {'F', 'R', 'D'};
    char buffer[512];
    size_t bufferIndex = 0;
    size_t ccount = 1;

    // Assemble the output string
    buffer[bufferIndex++] = 'S';
    buffer[bufferIndex++] = 'h';
    buffer[bufferIndex++] = 'o';
    buffer[bufferIndex++] = 'w';
    buffer[bufferIndex++] = 'i';
    buffer[bufferIndex++] = 'n';
    buffer[bufferIndex++] = 'g';
    buffer[bufferIndex++] = ' ';
    buffer[bufferIndex++] = 'F';
    buffer[bufferIndex++] = 'i';
    buffer[bufferIndex++] = 'l';
    buffer[bufferIndex++] = 'e';
    buffer[bufferIndex++] = 's';
    buffer[bufferIndex++] = 'y';
    buffer[bufferIndex++] = 's';
    buffer[bufferIndex++] = 't';
    buffer[bufferIndex++] = 'e';
    buffer[bufferIndex++] = 'm';
    buffer[bufferIndex++] = ':';
    buffer[bufferIndex++] = '\n';

    for (size_t bIndex = 0; bIndex < pFat->amountBlocks; bIndex++) {
        unsigned int state = pFat->blocks[bIndex].state;
        if (state == allocated && bufferIndex < 508) {
            unsigned char clusterIndexChar = pFat->blocks[bIndex].cluster->clusterIndex + '0';
            buffer[bufferIndex++] = clusterIndexChar;
        } else if (bufferIndex < 508) {
            buffer[bufferIndex++] = letterMap[state]; // 508
        }

        buffer[bufferIndex++] = '|'; // 509
        ccount += 2;
        if (bufferIndex >= 508) {
            break;
        }
        if (ccount >= 80) {
            buffer[bufferIndex++] = '\n';
            ccount = 0;
        }
    }

    buffer[bufferIndex++] = '\n'; // 510

    // Null-terminate the buffer
    buffer[bufferIndex] = '\0'; // 511

    // Print the output to terminal
    printf("%s", buffer);

    // Write the output to the provided outputMessage, if not null
    if (outputMessage != NULL) {
        strcpy(outputMessage, buffer);
    }
}

bool checkIntegrity(BsFat *pFat) {
    bool hasIntegrity = true;
    // Check if all allocated blocks are associated with a cluster
    for (size_t bIndex = 0; bIndex < pFat->amountBlocks; bIndex++) {
        if (pFat->blocks[bIndex].state == allocated && pFat->blocks[bIndex].cluster == NULL) {
            fprintf(stderr, "Inconsistent file system: Allocated block %zu is not associated with a cluster.\n",
                    bIndex);
            hasIntegrity = false;
        }
    }

    // Check if all allocated blocks are associated with a file
    for (size_t bIndex = 0; bIndex < pFat->amountBlocks; bIndex++) {
        if (pFat->blocks[bIndex].state == allocated && pFat->blocks[bIndex].cluster != NULL) {
            size_t fileIndex = pFat->blocks[bIndex].cluster->fileIndex;
            if (fileIndex >= AMOUNT_FILES || pFat->files[fileIndex] == NULL) {
                fprintf(stderr,
                        "Inconsistent file system: Allocated block %zu is associated with an invalid file index.\n",
                        bIndex);
                hasIntegrity = false;
            }
        }
    }

    // Check if all clusters are associated with a file
    for (size_t fileIndex = 0; fileIndex < AMOUNT_FILES; fileIndex++) {
        BsFile *pFile = pFat->files[fileIndex];
        if (pFile != NULL) {
            BsCluster *pCluster = pFile->pCluster;
            while (pCluster) {
                if (pCluster->fileIndex != fileIndex) {
                    fprintf(stderr,
                            "Inconsistent file system: Cluster %zu in file %zu is associated with incorrect file index: %zu\n",
                            pCluster->clusterIndex, fileIndex, pCluster->fileIndex);
                    hasIntegrity = false;
                }
                pCluster = pCluster->next;
            }
        }
    }

    // Check if all free blocks are not associated with a cluster
    for (size_t bIndex = 0; bIndex < pFat->amountBlocks; bIndex++) {
        if (pFat->blocks[bIndex].state == free_ && pFat->blocks[bIndex].cluster != NULL) {
            fprintf(stderr, "Inconsistent file system: Free block %zu is associated with a cluster.\n", bIndex);
            hasIntegrity = false;
        }
    }
    return hasIntegrity;
}

void checkForDefragmentation(BsFat *pFat) {
    BsFile **pFile = pFat->files;
    unsigned int blocksInCorrectPos = 0;
    int currentFileIndex = -1;
    int currentClusterIndex = -1;
    for(BsBlock *pBlock = pFat->blocks; pBlock < pFat->blocks + pFat->amountBlocks; pBlock++) {
        if (pBlock->state != allocated) {
            if (currentFileIndex == -1 || currentClusterIndex == -1) {
                blocksInCorrectPos++;
            }else {
                currentFileIndex = -1;
                currentClusterIndex = -1;
            }
            continue;
        }
        else if (currentFileIndex == -1 || currentClusterIndex == -1) {
            if(pBlock->cluster->clusterIndex == 0) {
                blocksInCorrectPos++;
            }
        } else {
            if (pBlock->cluster->fileIndex == currentFileIndex && pBlock->cluster->clusterIndex == currentClusterIndex + 1) {
                blocksInCorrectPos++;
            }
        }
        if (pBlock->cluster->next != NULL) {
            currentFileIndex = pBlock->cluster->fileIndex;
            currentClusterIndex = pBlock->cluster->clusterIndex;
        } else {
            currentFileIndex = -1;
            currentClusterIndex = -1;
        }
    }
    float fragmentation = 100.0f - ((float) blocksInCorrectPos / (float) pFat->amountBlocks * 100.0f);
    printf("Current fragmentation in percent: %.2f\n", fragmentation);
}

void defragmentate(BsFat *pFat) {
    size_t oIndex = 0;
    for (size_t i = 0; i < AMOUNT_FILES; i++) {
        if (pFat->files[i] == NULL) {
            continue;
        }
        BsCluster *pCluster = pFat->files[i]->pCluster;
        while (pCluster) {
            size_t blockIndexToSwap = pCluster->bIndex;
            swapBlocks(pFat, oIndex, blockIndexToSwap);
            pCluster = pCluster->next;
            oIndex++;
        }
    }
}

bool swapBlocks(BsFat *pFat, size_t bIndexA, size_t bIndexB) {
    if (bIndexA == bIndexB) {
        fprintf(stderr, "Swapping the same block is not possible!\n");
        return false;
    }
    if (bIndexA >= pFat->amountBlocks || bIndexB >= pFat->amountBlocks) {
        fprintf(stderr, "Invalid block indices for swapBlocks.\n");
        return false;
    }
    if (pFat->blocks[bIndexA].state == free_ && pFat->blocks[bIndexB].state == free_) {
        fprintf(stderr, "No need to swap two free Blocks!\n");
        return false;
    }
    if (pFat->blocks[bIndexA].state == reserved || pFat->blocks[bIndexB].state == reserved) {
        fprintf(stderr, "\"Invalid block for swapBlocks! Can't swap with a reserved block!\n");
        return false;
    }
    if (pFat->blocks[bIndexA].state == defect || pFat->blocks[bIndexB].state == defect) {
        fprintf(stderr, "\"Invalid block for swapBlocks! Can't swap with a defect block!\n");
        return false;
    }

    // Swap the state
    unsigned int tempState = pFat->blocks[bIndexA].state;
    pFat->blocks[bIndexA].state = pFat->blocks[bIndexB].state;
    pFat->blocks[bIndexB].state = tempState;

    // Swap the cluster pointers
    BsCluster *tempCluster = pFat->blocks[bIndexA].cluster;
    pFat->blocks[bIndexA].cluster = pFat->blocks[bIndexB].cluster;
    pFat->blocks[bIndexB].cluster = tempCluster;

    // Update the block indices in the cluster structure if applicable
    if (pFat->blocks[bIndexA].cluster != NULL) {
        pFat->blocks[bIndexA].cluster->bIndex = bIndexA;
    }
    if (pFat->blocks[bIndexB].cluster != NULL) {
        pFat->blocks[bIndexB].cluster->bIndex = bIndexB;
    }

    return true;
}

