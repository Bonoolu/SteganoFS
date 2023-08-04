#include <unistd.h>
#include "steganoFS.h"
#define DEBUG // TODO!


// TODO:
// implement unlink
// implement export
// implement import

// write doxygen

HiddenFat *createHiddenFat(size_t diskSize, size_t blockSize) {
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
    hiddenFat->disk = disk;
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

void deleteHiddenFile(HiddenFat *hiddenFat, const char *filename) {
//    BsFile **pFile = hiddenFat->files;
//    bool found = false;
//    do {
//        if (*pFile != NULL && strcmp((*pFile)->filename, filename) == 0) {
//            found = true;
//            break;
//        }
//    } while (++pFile != hiddenFat->files + AMOUNT_FILES);
//
//    if (found) {
//        BsBlock *hiddenCluster = (*pFile)->hiddenCluster;
//        while (hiddenCluster) {
//            hiddenFat->blocks[hiddenCluster->bIndex].state = free_;
//            hiddenFat->blocks[hiddenCluster->bIndex].prev  = NULL;
//            pCluster = pCluster->next;
//        }
//        free((*pFile)->pCluster);
//        free(*pFile);
//        *pFile = NULL;
//        printf("Deleted File!\n");
//    } else {
//        fprintf(stderr, "Could not find file: %s\n", filename);
//    }
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

    // Check if all allocated blocks are associated with a file
//    for (size_t bIndex = 0; bIndex < hiddenFat->amountBlocks; bIndex++) {
//        if (hiddenFat->blocks[bIndex].state == allocated && hiddenFat->blocks[bIndex].cluster != NULL) {
//            size_t fileIndex = hiddenFat->blocks[bIndex].cluster->fileIndex;
//            if (fileIndex >= AMOUNT_FILES || hiddenFat->files[fileIndex] == NULL) {
//                fprintf(stderr,
//                        "Inconsistent file system: Allocated block %zu is associated with an invalid file index.\n",
//                        bIndex);
//                hasIntegrity = false;
//            }
//        }
//    }

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

bool swapHiddenClusters(HiddenFat *hiddenFat, size_t bIndexA, size_t bIndexB) {
    //TODO! check if bIndex i s out of range
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

int countPathComponents(const char *path) {
    int count = 0;
    for (int i = 0; path[i]; i++) {
        if (path[i] == '/')
            count++;
    }
    return count;
}


HiddenFile *findFileByPath(HiddenFat *hiddenFat, const char* path){
    HiddenFile **pFile = hiddenFat->files;
    bool found = false;
    if (strcmp(path, "/") == 0) {
        return NULL;
    }
    if (countPathComponents(path) == 1) {
        const char *filename = path + 1;
        do {
            if (*pFile != NULL && strcmp((*pFile)->filename, filename) == 0) {
                found = true;
                break;
            }
        } while (++pFile != hiddenFat->files + AMOUNT_ROOT_FILES);
    }
    if (found) {
        return *pFile;
    }else {
        return NULL;
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

int getattrSteganoFS(const char *path, struct stat *stbuf, struct fuse_file_info *fi) {
    HiddenFat *hiddenFat = (HiddenFat *)fuse_get_context()->private_data;

    // Check if the path corresponds to the root directory
    if (strcmp(path, "/") == 0) {
        // Set default values for the root directory
        stbuf->st_mode = S_IFDIR | 0777; // Directory with 755 permissions
        stbuf->st_nlink = 2; // Number of hard links (including . and ..)
        stbuf->st_nlink += getAmountEntries(hiddenFat, path);
        // Other fields can be set as per your requirements (e.g., st_uid, st_gid, st_size, st_atime, st_mtime, etc.)

        return 0; // Return success
    }else {
        HiddenFile *pFile = findFileByPath(hiddenFat, path);
        if (pFile != NULL) {
            stbuf->st_mode = S_IFREG | 0666; // Regular file with 666 permissions
            stbuf->st_nlink = 1; // Number of hard links (including . and ..)
            stbuf->st_size = (__off_t) pFile->real_filesize;
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

int readdirSteganoFS(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi,
                     enum fuse_readdir_flags flags) {
    // Add entries for the root directory
    if (strcmp(path, "/") == 0)
    {
        filler(buf, "..", NULL, 0, 0);
        filler(buf, ".", NULL, 0, 0);
        HiddenFat *hiddenFat = (HiddenFat *)fuse_get_context()->private_data;
        for(HiddenFile **pFile = hiddenFat->files; pFile < hiddenFat->files + AMOUNT_ROOT_FILES; pFile++) {
            if (*pFile != NULL) {
                filler(buf, (*pFile)->filename, NULL, 0, 0);
            }
        }
        return 0;
    }
    return -ENOENT;
}

HiddenFile **createHiddenFile(HiddenFat *hiddenFat, const char *filename, long timestamp) {
    // Find an available file slot
    HiddenFile **searchResult = NULL;
    for (size_t i = 0; i < AMOUNT_ROOT_FILES; i++) {
        if (hiddenFat->files[i] == NULL) {
            searchResult = &hiddenFat->files[i];
            break;
        }
    }
    if (searchResult == NULL) {
        fprintf(stderr, "Maximum amount of files are already allocated!\n");
        return NULL;
    }

    // Create the file structure and update the file table
    HiddenFile *pFile = (HiddenFile *) malloc(sizeof(HiddenFile));
    if (!pFile) {
        fprintf(stderr, "Could not allocate memory!\n");
        return NULL;
    }
    char* dup_filename = strdup(filename);
    pFile->filename = dup_filename;
    pFile->filesize = 0;
    pFile->timestamp = timestamp;
    pFile->hiddenCluster = NULL;
    *searchResult = pFile;

    printf("Created file!\n");
    return searchResult;
}

int createSteganoFS(const char *path, mode_t mode, struct fuse_file_info *fi) {
    HiddenFat *hiddenFat = (HiddenFat *)fuse_get_context()->private_data;

    mode = S_IFREG | 0666;
    if (countPathComponents(path) == 1) {
        const char *filename = path + 1;
        HiddenFile **pFile = createHiddenFile(hiddenFat, filename, time(NULL));
        if (pFile != NULL) {
            return 0;
        }
        return -ENOMEM;
    }
    return -ENOENT;
}

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

int writeSteganoFS(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    if (countPathComponents(path) != 1) {
        return -ENOENT;
    }
    struct fuse_context *private = fuse_get_context();
    HiddenFat *hiddenFat;
    if (private != NULL) {
        hiddenFat = (HiddenFat *)(private->private_data);
    }else {
#ifdef DEBUG
        hiddenFat = (HiddenFat *) fi;
#else
        fprintf(stderr, "Couldn't get fuse context, is null!!\n");
        return -1;
#endif
    }
    HiddenFile *pFile = findFileByPath(hiddenFat, path);
    if (pFile == NULL) {
        return -ENOENT;
    }

    // Check if file is already large enough, if no, allocate
    while (offset + size > pFile->filesize) {
        if (!extendHiddenCluster(hiddenFat, pFile)) {
            return -ENOMEM;
        }
    }
    pFile->real_filesize = offset + size;
    size_t bytesWritten = 0;

    // Find correct clusterblock to write to
    HiddenCluster *hiddenCluster = pFile->hiddenCluster;
    size_t fileOffset = 0;
    int size_signed = (int) size;
    while (size_signed > 0) {
        if (hiddenCluster == NULL) {
            fprintf(stderr, "Tried to write at an offset for a file which is not large enough, did you forget to allocate?");
            return -errno;
        }
        // First we search for the block where the offset is in
        if (fileOffset >= offset) {
            // Next we get the amount of blocks to write
            size_t amountBytesToWrite;
            size_t offsetInsideBlock = offset % hiddenFat->blockSize;
            if (offset + size_signed < fileOffset + hiddenFat->blockSize) {
                amountBytesToWrite = size_signed;
            } else {
                amountBytesToWrite = hiddenFat->blockSize - offsetInsideBlock;
            }
            int written = writeBlock(hiddenFat,hiddenCluster->bIndex, buf, offsetInsideBlock, amountBytesToWrite);
            if (written < 0) {
                return -errno;
            }
            bytesWritten += written;
            if (written != amountBytesToWrite) {
                fprintf(stderr, "Meant to write %zu bytes in Block %zu at block offset %zu (which is disk offset %zu),"
                                " but %d bytes were written!\n", amountBytesToWrite, hiddenCluster->bIndex,
                                offsetInsideBlock, offset, written);
                return -errno;
            }
            offset += (off_t) written;
            buf += written;
            size_signed -= (int) written;
        }
        hiddenCluster = hiddenCluster->next;
        fileOffset += hiddenFat->blockSize;
    }
    return (int) bytesWritten;
}

int readSteganoFS(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    if (countPathComponents(path) != 1) {
        return -ENOENT;
    }
    struct fuse_context *private = fuse_get_context();
    HiddenFat *hiddenFat;
    if (private != NULL) {
        hiddenFat = (HiddenFat *)(private->private_data);
    }else {
#ifdef DEBUG
        hiddenFat = (HiddenFat *) fi;
#else
        fprintf(stderr, "Couldn't get fuse context, is null!!\n");
        return -1;
#endif
    }
    HiddenFile *pFile = findFileByPath(hiddenFat, path);
    if (pFile == NULL) {
        return -ENOENT;
    }

    // Check if we read outside file, if yes return 0 bytes readcd
    if (offset + size > pFile->filesize) {
        return 0;
    }
    size_t bytesRead = 0;

    // Find correct clusterblock to write to
    HiddenCluster *hiddenCluster = pFile->hiddenCluster;
    size_t fileOffset = 0;
    int size_signed = (int) size;
    while (size_signed > 0) {
        if (hiddenCluster == NULL) {
            fprintf(stderr, "Tried to write at an offset for a file which is not large enough, did you forget to allocate?");
            return -errno;
        }
        // First we search for the block where the offset is in
        if (fileOffset >= offset) {
            // Next we get the amount of bytes to write
            size_t amountBytesToRead;
            size_t offsetInsideBlock = offset % hiddenFat->blockSize;
            if (offset + size_signed < fileOffset + hiddenFat->blockSize) {
                amountBytesToRead = size_signed;
            } else {
                amountBytesToRead = hiddenFat->blockSize - offsetInsideBlock;
            }
            int read_ = readBlock(hiddenFat, hiddenCluster->bIndex, buf, offsetInsideBlock, amountBytesToRead);
            if (read_ < 0) {
                return -errno;
            }
            bytesRead += read_;
            if (read_ != amountBytesToRead) {
                fprintf(stderr, "Meant to read %zu bytes from Block %zu at block offset %zu (which is disk offset %zu),"
                                " but %d bytes were read!\n", amountBytesToRead, hiddenCluster->bIndex,
                        offsetInsideBlock, offset, read_);
                return -errno;
            }
            offset += (off_t) read_;
            buf += read_;
            size_signed -= (int) read_;
        }
        hiddenCluster = hiddenCluster->next;
        fileOffset += hiddenFat->blockSize;
    }
    return (int) bytesRead;
}

struct fuse_operations fuseOperationsSteagnoFS = {
        .getattr = getattrSteganoFS,
        .readdir = readdirSteganoFS,
        .create = createSteganoFS,
        .write = writeSteganoFS,
        .read = readSteganoFS
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

