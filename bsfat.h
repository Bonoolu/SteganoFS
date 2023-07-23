#ifndef BSFAT_H
#define BSFAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define AMOUNT_FILES 10

typedef struct BsCluster BsCluster;
typedef struct BsFile BsFile;
typedef struct BsBlock BsBlock;
typedef struct BsFat BsFat;

struct BsCluster {
    BsCluster *prev;
    BsCluster *next;
    size_t clusterIndex;
    size_t fileIndex;
    unsigned int bIndex;
};

struct BsFile {
    const char *filename;
    size_t filesize;
    long timestamp;
    BsCluster *pCluster;
};

struct BsBlock {
    size_t bIndex;
    unsigned int state;
    BsCluster *cluster;
};

enum State {
    free_ = 0, reserved = 1, defect = 2, allocated = 3
};

struct BsFat {
    size_t blockSize;
    size_t amountBlocks;
    unsigned char *disk;
    BsBlock *blocks;
    BsFile *files[AMOUNT_FILES];
};

BsFat *createBsFat(size_t diskSize, size_t blockSize);
void freeBsFat(BsFat *pFat);
size_t getFreeDiskSpace(BsFat *pFat);
BsFile **createFile(BsFat *pFat, size_t szFile, const char *filename, long timestamp);
void deleteFile(BsFat *pFat, const char *filename);
void showFat(BsFat *pFat, char* outputMessage);
bool checkIntegrity(BsFat *pFat);
bool swapBlocks(BsFat *pFat, size_t bIndexA, size_t bIndexB);
void checkForDefragmentation(BsFat *pFat);
void defragmentate(BsFat *pFat);

#endif