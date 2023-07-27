#include <utime.h>
#include <unistd.h>
#include "bsfat.h"

// TODO:
//
// implement reading and writing files
// allow non consecutive writes
// implement directories
// implement export
// implement import
// createFile itself needs to allocate string filename

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

//
//void readBlock(BsFat *pFat, size_t bIndex, unsigned char* buffer, size_t offset, size_t length) {
//    if (bIndex > pFat->amountBlocks) {
//        fprintf(stderr, "Block Index too high! Can't read outside the disk!!\n");
//        return;
//    }
//    size_t diskOffset = bIndex * pFat->blockSize;
//    if (pFat->disk + diskOffset > pFat->disk + (pFat->amountBlocks * pFat->blockSize)) {
//        fprintf(stderr, "Can't read outside the disk!!\n");
//        return;
//    }
//    memcpy(pFat->disk + diskOffset, buffer, pFat->blockSize);
//}


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
            char clusterIndexChar = pFat->blocks[bIndex].cluster->clusterIndex + '0';
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
            currentFileIndex = (int) pBlock->cluster->fileIndex;
            currentClusterIndex = (int) pBlock->cluster->clusterIndex;
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

int count_path_components(const char *path) {
    int count = 0;
    for (int i = 0; path[i]; i++) {
        if (path[i] == '/')
            count++;
    }
    return count;
}


BsFile *findFileByPath(BsFat *pFat, const char* path){
    BsFile **pFile = pFat->files;
    bool found = false;
    if (strcmp(path, "/") == 0) {
        return NULL;
    }
    if (count_path_components(path) == 1) {
        const char *filename = path + 1;
        do {
            if (*pFile != NULL && strcmp((*pFile)->filename, filename) == 0) {
                found = true;
                break;
            }
        } while (++pFile != pFat->files + AMOUNT_FILES);
    }
    if (found) {
        return *pFile;
    }else {
        return NULL;
    }

}

size_t getAmountEntries(BsFat *pFat, const char* path) {
    if (strcmp(path, "/") == 0) {
        size_t amount = 0;
        for(BsFile **pFile = pFat->files; pFile < pFat->files + AMOUNT_FILES; pFile++) {
            if (*pFile != NULL) {
                amount++;
            }
        }
        return amount;
    }
    return 2;
}

int stegFS_getattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi) {
    BsFat *pFat = (BsFat *)fuse_get_context()->private_data;

    // Check if the path corresponds to the root directory
    if (strcmp(path, "/") == 0) {
        // Set default values for the root directory
        stbuf->st_mode = S_IFDIR | 0777; // Directory with 755 permissions
        stbuf->st_nlink = 2; // Number of hard links (including . and ..)
        stbuf->st_nlink += getAmountEntries(pFat, path);
        // Other fields can be set as per your requirements (e.g., st_uid, st_gid, st_size, st_atime, st_mtime, etc.)

        return 0; // Return success
    }else {
        BsFile *pFile = findFileByPath(pFat, path);
        if (pFile != NULL) {
            stbuf->st_mode = S_IFREG | 0666; // Regular file with 666 permissions
            stbuf->st_nlink = 1; // Number of hard links (including . and ..)
            stbuf->st_size = (__off_t) pFile->filesize;
            stbuf->st_uid = 1000;
            stbuf->st_gid = 1000;


            // Set access time and modification time based on the Unix timestamp
            time_t timestamp = pFile->timestamp;

            // Set access time (st_atim)
            stbuf->st_atim.tv_sec = timestamp;
            stbuf->st_atim.tv_nsec = 0;

            // Set modification time (st_mtim)
            stbuf->st_mtim.tv_sec = timestamp;
            stbuf->st_mtim.tv_nsec = 0;

            return 0;
        }
        return -ENOENT; // ENOENT indicates "No such file or directory"
    }
}

int stegFS_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi,
                   enum fuse_readdir_flags flags) {
    // Add entries for the root directory
    if (strcmp(path, "/") == 0)
    {
        filler(buf, "..", NULL, 0, 0);
        filler(buf, ".", NULL, 0, 0);
        BsFat *pFat = (BsFat *)fuse_get_context()->private_data;
        for(BsFile **pFile = pFat->files; pFile < pFat->files + AMOUNT_FILES; pFile++) {
            if (*pFile != NULL) {
                filler(buf, (*pFile)->filename, NULL, 0, 0);
            }
        }
        return 0;
    }
    return -ENOENT;
}

BsFile **createFile(BsFat *pFat, const char *filename, long timestamp) {
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

    // Create the file structure and update the file table
    BsFile *pFile = (BsFile *) malloc(sizeof(BsFile));
    if (!pFile) {
        fprintf(stderr, "Could not allocate memory!\n");
        return NULL;
    }
    char* dup_filename = strdup(filename);
    pFile->filename = dup_filename;
    pFile->filesize = 0;
    pFile->timestamp = timestamp;
    pFile->pCluster = NULL;
    *searchResult = pFile;

    printf("Created file!\n");
    return searchResult;
}

int stegFS_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
    BsFat *pFat = (BsFat *)fuse_get_context()->private_data;

    mode = S_IFREG | 0666;
    if (count_path_components(path) == 1) {
        const char *filename = path + 1;
        BsFile **pFile = createFile(pFat, filename, time(NULL));
        if (pFile != NULL) {
            return 0;
        }
        return -ENOMEM;
    }
    return -ENOENT;
}

bool allocateNewBlockForFile(BsFat *pFat, BsFile *pFile) {
    size_t bIndex;
    for (bIndex = 0; bIndex < pFat->amountBlocks; bIndex++) {
        if (pFat->blocks[bIndex].state == free_) {
            break;
        }
        if (bIndex == pFat->amountBlocks - 1) {
            return false;
        }
    }
    // Allocate the block for the file
    BsCluster *pCluster = (BsCluster *) malloc(sizeof(BsCluster));
    if (!pCluster) {
        fprintf(stderr, "Could not allocate memory!\n");
        return false;
    }
    memset(pCluster, 0, sizeof(BsCluster));
    pFat->blocks[bIndex].state = allocated;
    pFat->blocks[bIndex].bIndex = bIndex;
    pFat->blocks[bIndex].cluster = pCluster;
    pCluster->bIndex = bIndex;
    int clusterIndex = -1;
    if (pFile->pCluster == NULL) {
        pFile->pCluster = pCluster;
        pCluster->clusterIndex = 0;
    }
    pCluster[clusterIndex].clusterIndex = clusterIndex;
    pCluster[clusterIndex].fileIndex = pFile->;//TODO!
    if (clusterIndex > 0) {
        pCluster[clusterIndex].prev = pCluster + clusterIndex - 1;
        pCluster[clusterIndex - 1].next = pCluster + clusterIndex;
    }
}

int writeBlock(BsFat *pFat, size_t bIndex, unsigned char* buffer, size_t offset, size_t length) {
    if (offset + length > 512) {
        fprintf(stderr, "Trying to write to the wrong Block! offset+length is higher than 512\n");
        return -1;
    }
    if (bIndex > pFat->amountBlocks) {
        fprintf(stderr, "Block Index too high! Can't write outside the disk!!\n");
        return -1;
    }
    if (length == 0) {
        // nothing to do..
        return 0;
    }
    size_t diskOffset = (bIndex * pFat->blockSize) + offset;
    if (pFat->disk + diskOffset + length > pFat->disk + (pFat->amountBlocks * pFat->blockSize)) {
        fprintf(stderr, "Can't write outside the disk!!\n");
        return -1;
    }
    memcpy(buffer + offset, pFat->disk + diskOffset, length);
    return (int) length;
}

int stegFS_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    if (count_path_components(path) != 1) {
        return -ENOENT;
    }
    BsFat *pFat = (BsFat *)fuse_get_context()->private_data;
    BsFile *pFile = findFileByPath(pFat, path);
    if (pFile == NULL) {
        return -ENOENT;
    }



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
    if ()
}

struct fuse_operations stegfs_fuse_oper = {
        .getattr = stegFS_getattr,
        .readdir = stegFS_readdir,
        .create = stegFS_create
};

///**
// * @brief Open a file.
// *
// * @param path The path to the file.
// * @param fi A pointer to the fuse_file_info structure containing information about the file.
// * @return 0 on success, or a negative value on failure.
// */
//static int stegFS_open(const char *path, struct fuse_file_info *fi);
//
///**
// * @brief Read data from a file.
// *
// * @param path The path to the file.
// * @param buf A buffer to store the read data.
// * @param size The number of bytes to read.
// * @param offset The offset to read from in the file.
// * @param fi A pointer to the fuse_file_info structure containing information about the file.
// * @return The number of bytes read on success, or a negative value on failure.
// */
//static int stegFS_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
//
///**
// * @brief Write data to a file.
// *
// * @param path The path to the file.
// * @param buf A buffer containing the data to write.
// * @param size The number of bytes to write.
// * @param offset The offset to write to in the file.
// * @param fi A pointer to the fuse_file_info structure containing information about the file.
// * @return The number of bytes written on success, or a negative value on failure.
// */
//static int stegFS_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
//
///**
///**
// * @brief Create a new directory.
// *
// * @param path The path to the new directory.
// * @param mode The directory mode/permissions.
// * @return 0 on success, or a negative value on failure.
// */
//static int stegFS_mkdir(const char *path, mode_t mode);
//
///**
// * @brief Delete a file.
// *
// * @param path The path to the file to be deleted.
// * @return 0 on success, or a negative value on failure.
// */
//static int stegFS_unlink(const char *path);

