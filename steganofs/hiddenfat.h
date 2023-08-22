#ifndef STEGANOFS_HIDDENFAT_H
#define STEGANOFS_HIDDENFAT_H

#include "hiddencluster.h"
#include "steganofs.h"
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
    HiddenFile *files[STEGANOFS_AMOUNT_ROOT_FILES];
};

// HiddenFat
HiddenFat *createHiddenFat(size_t diskSize, size_t blockSize);

void freeHiddenFat(HiddenFat *hiddenFat);

size_t getAmountEntries(HiddenFat *hiddenFat, const char *path);

size_t getFreeDiskSpace(HiddenFat *hiddenFat);

void showHiddenFat(HiddenFat *hiddenFat, char *outputMessage);

bool checkIntegrity(HiddenFat *hiddenFat);

float checkForFragmentation(HiddenFat *hiddenFat);

void defragmentate(HiddenFat *hiddenFat);

int writeBlock(HiddenFat *hiddenFat, size_t bIndex, const char *buffer, size_t offset, size_t length);

int readBlock(HiddenFat *hiddenFat, size_t bIndex, const char *buffer, size_t offset, size_t length);

size_t getFragmentationArray(HiddenFat *hiddenFat, size_t **array);

#endif //STEGANOFS_HIDDENFAT_H
