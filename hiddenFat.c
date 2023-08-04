#include "hiddenFat.h"

HiddenFat *createHiddenFat(size_t diskSize, size_t blockSize) { //unsigned char *buf,
    if (diskSize == 0 || blockSize == 0) {
        fprintf(stderr, "Disk size and blockSize each can not be zero!\n");
        exit(1);
    }
    if (diskSize % blockSize != 0) {
        fprintf(stderr, "Disk size is not dividable by block size!\n");
        exit(1);
    }
    //memset(buf, 0, diskSize);
    size_t amountBlocks = diskSize / blockSize;
    HiddenCluster *clusters = (HiddenCluster *) malloc(amountBlocks * sizeof(HiddenCluster));
    if (!clusters) {
        fprintf(stderr, "Could not allocate memory!\n");
        exit(1);
    }
    memset(clusters, 0, amountBlocks * sizeof(HiddenCluster));
    for (size_t bIndex = 0; bIndex < amountBlocks; bIndex++) {
        clusters[bIndex].bIndex = bIndex;
    }
    HiddenFat *hiddenFat = (HiddenFat *) malloc(sizeof(HiddenFat));
    if (!hiddenFat) {
        fprintf(stderr, "Could not allocate memory!\n");
        exit(1);
    }
    memset(hiddenFat->files, 0, AMOUNT_ROOT_FILES * sizeof(HiddenFile *));
    hiddenFat->blockSize = blockSize;
    hiddenFat->amountBlocks = amountBlocks;
    //hiddenFat->disk = buf;
    hiddenFat->clusters = clusters;
    return hiddenFat;
}

void freeHiddenFat(HiddenFat *hiddenFat) {
    if (hiddenFat == NULL) {
        return;
    }

    // Free the disk memory
    free(hiddenFat->disk);

    // Free the block structures
    free(hiddenFat->clusters);

    // Free the file structures
    for (size_t i = 0; i < AMOUNT_ROOT_FILES; i++) {
        HiddenFile *pFile = hiddenFat->files[i];
        if (pFile != NULL) {
            // Free the cluster structures associated with the file
            free(pFile->hiddenCluster);
            // Free the file structure
            free(pFile);
        }
    }

    // Free the HiddenFat structure itself
    free(hiddenFat);
}

size_t getFreeDiskSpace(HiddenFat *hiddenFat) {
    if (hiddenFat == NULL) {
        fprintf(stderr, "Invalid HiddenFat pointer.\n");
        return 0;
    }

    size_t amountFreeBlocks = 0;
    for (size_t i = 0; i < hiddenFat->amountBlocks; i++) {
        if (hiddenFat->clusters[i].state == free_) {
            amountFreeBlocks++;
        }
    }

    return amountFreeBlocks * hiddenFat->blockSize;
}

void showHiddenFat(HiddenFat *hiddenFat, char *outputMessage) {
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

    for (size_t bIndex = 0; bIndex < hiddenFat->amountBlocks; bIndex++) {
        unsigned int state = hiddenFat->clusters[bIndex].state;
        if (state == allocated && bufferIndex < 508) {
            char clusterIndexChar = (char)(hiddenFat->clusters[bIndex].clusterIndex + '0');
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

bool checkIntegrity(HiddenFat *hiddenFat) {
    bool hasIntegrity = true;
    // Check if all allocated blocks are associated with a cluster
    for (size_t bIndex = 0; bIndex < hiddenFat->amountBlocks; bIndex++) {
        if (hiddenFat->clusters[bIndex].state == allocated && hiddenFat->clusters[bIndex].prev == NULL && hiddenFat->clusters[bIndex].next == NULL) {
            fprintf(stderr, "Inconsistent file system: Allocated block %zu is not associated with a cluster.\n",
                    bIndex);
            hasIntegrity = false;
        }
    }

    // Check if all clusters are associated with a file
    for (size_t fileIndex = 0; fileIndex < AMOUNT_ROOT_FILES; fileIndex++) {
        HiddenFile *pFile = hiddenFat->files[fileIndex];
        if (pFile != NULL) {
            HiddenCluster *hiddenCluster = pFile->hiddenCluster;
            while (hiddenCluster) {
                if (hiddenCluster->file != pFile) {
                    fprintf(stderr,
                            "Inconsistent file system: Cluster %zu in file %s is associated with incorrect file pointer: %s\n",
                            hiddenCluster->clusterIndex, hiddenCluster->file->filename, pFile->filename);
                    hasIntegrity = false;
                }
                hiddenCluster = hiddenCluster->next;
            }
        }
    }

    // Check if all free blocks are not associated with a cluster
    for (size_t bIndex = 0; bIndex < hiddenFat->amountBlocks; bIndex++) {
        if (hiddenFat->clusters[bIndex].state == free_ && (hiddenFat->clusters[bIndex].prev != NULL || hiddenFat->clusters[bIndex].next != NULL)) {
            fprintf(stderr, "Inconsistent file system: Free block %zu is associated with a cluster.\n", bIndex);
            hasIntegrity = false;
        }
    }
    return hasIntegrity;
}

void checkForDefragmentation(HiddenFat *hiddenFat) {
    unsigned int blocksInCorrectPos = 0;
    HiddenFile *currentFile = NULL;
    int currentClusterIndex = -1;
    for(HiddenCluster *hiddenCluster = hiddenFat->clusters; hiddenCluster < hiddenFat->clusters + hiddenFat->amountBlocks; hiddenCluster++) {
        if (hiddenCluster->state != allocated) {
            if (currentFile == NULL || currentClusterIndex == -1) {
                blocksInCorrectPos++;
            }else {
                currentFile = NULL;
                currentClusterIndex = -1;
            }
            continue;
        }
        else if (currentFile == NULL || currentClusterIndex == -1) {
            if(hiddenCluster->clusterIndex == 0) {
                blocksInCorrectPos++;
            }
        } else {
            if (hiddenCluster->file == currentFile && hiddenCluster->clusterIndex == currentClusterIndex + 1) {
                blocksInCorrectPos++;
            }
        }
        if (hiddenCluster->next != NULL) {
            currentFile = hiddenCluster->file;
            currentClusterIndex = (int) hiddenCluster->clusterIndex;
        } else {
            currentFile = NULL;
            currentClusterIndex = -1;
        }
    }
    float fragmentation = 100.0f - ((float) blocksInCorrectPos / (float) hiddenFat->amountBlocks * 100.0f);
    printf("Current fragmentation in percent: %.2f\n", fragmentation);
}

void defragmentate(HiddenFat *hiddenFat) {
    size_t oIndex = 0;
    for (size_t i = 0; i < AMOUNT_ROOT_FILES; i++) {
        if (hiddenFat->files[i] == NULL) {
            continue;
        }
        HiddenCluster *hiddenCluster = hiddenFat->files[i]->hiddenCluster;
        while (hiddenCluster) {
            size_t blockIndexToSwap = hiddenCluster->bIndex;
            swapHiddenClusters(hiddenFat, oIndex, blockIndexToSwap);
            hiddenCluster = hiddenCluster->next;
            oIndex++;
        }
    }
}

size_t getAmountEntries(HiddenFat *hiddenFat, const char* path) {
    if (strcmp(path, "/") == 0) {
        size_t amount = 0;
        for(HiddenFile **pFile = hiddenFat->files; pFile < hiddenFat->files + AMOUNT_ROOT_FILES; pFile++) {
            if (*pFile != NULL) {
                amount++;
            }
        }
        return amount;
    }
    return 2;
}

int writeBlock(HiddenFat *hiddenFat, size_t bIndex, const char* buffer, size_t offset, size_t length) {
    if (offset + length > BLOCKSIZE) {
        fprintf(stderr, "Trying to write to the wrong Block! offset+length is higher than %d\n", BLOCKSIZE);
        return -1;
    }
    if (bIndex > hiddenFat->amountBlocks) {
        fprintf(stderr, "Block Index too high! Can't write outside the disk!!\n");
        return -1;
    }
    if (length == 0) {
        // nothing to do..
        return 0;
    }
    size_t diskOffset = (bIndex * hiddenFat->blockSize) + offset;
    if (hiddenFat->disk + diskOffset + length > hiddenFat->disk + (hiddenFat->amountBlocks * hiddenFat->blockSize)) {
        fprintf(stderr, "Can't write outside the disk!!\n"); // TODO BREAKPOINT
        return -1;
    }
    memcpy(hiddenFat->disk + diskOffset, (void*) buffer + offset, length);
    return (int) length;
}

int readBlock(HiddenFat *hiddenFat, size_t bIndex, const char* buffer, size_t offset, size_t length){
    if (offset + length > BLOCKSIZE) {
        fprintf(stderr, "Trying to read from the wrong Block! offset+length is higher than %d\n", BLOCKSIZE);
        return -1;
    }
    if (bIndex > hiddenFat->amountBlocks) {
        fprintf(stderr, "Block Index too high! Can't read outside the disk!!\n");
        return -1;
    }
    if (length == 0) {
        // nothing to do..
        return 0;
    }
    size_t diskOffset = (bIndex * hiddenFat->blockSize) + offset;
    if (hiddenFat->disk + diskOffset + length > hiddenFat->disk + (hiddenFat->amountBlocks * hiddenFat->blockSize)) {
        fprintf(stderr, "Can't read outside the disk!!\n");
        return -1;
    }
    memcpy((void*) buffer + offset, hiddenFat->disk + diskOffset, length);
    return (int) length;
}