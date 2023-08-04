#ifndef STEGANOFS_HIDDENFAT_H
#define STEGANOFS_HIDDENFAT_H

#define AMOUNT_ROOT_FILES 10
#define BLOCKSIZE 4096

#include "hiddencluster.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct HiddenCluster HiddenCluster;
typedef struct HiddenFile HiddenFile;
typedef struct HiddenFat HiddenFat;

struct HiddenFat {
    size_t blockSize;
    size_t amountBlocks;
    unsigned char *disk;
    HiddenCluster *clusters;
    HiddenFile *files[AMOUNT_ROOT_FILES];
};

// HiddenFat
HiddenFat *createHiddenFat(size_t diskSize, size_t blockSize);

void freeHiddenFat(HiddenFat *hiddenFat);

size_t getAmountEntries(HiddenFat *hiddenFat, const char *path);

size_t getFreeDiskSpace(HiddenFat *hiddenFat);

void showHiddenFat(HiddenFat *hiddenFat, char *outputMessage);

bool checkIntegrity(HiddenFat *hiddenFat);

void checkForDefragmentation(HiddenFat *hiddenFat);

void defragmentate(HiddenFat *hiddenFat);

int writeBlock(HiddenFat *hiddenFat, size_t bIndex, const char *buffer, size_t offset, size_t length);

int readBlock(HiddenFat *hiddenFat, size_t bIndex, const char *buffer, size_t offset, size_t length);

#endif //STEGANOFS_HIDDENFAT_H
