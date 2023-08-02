#include "bsfat.h"

bool testCreateBsFat() {
    size_t diskSize = BLOCKSIZE * 4;  // Example disk size
    size_t blockSize = BLOCKSIZE;  // Example block size
    BsFat *pFat = createBsFat(diskSize, blockSize);
    bool passed = true;
    if (pFat == NULL) {
        printf("testCreateBsFat test failed: Failed to create the BsFat structure.\n");
        passed = false;
    }

    // Verify the blockSize and amountBlocks values
    if (pFat->blockSize != blockSize) {
        printf("testCreateBsFat test failed: Incorrect blockSize value.\n");
        passed = false;
    }

    size_t expectedAmountBlocks = diskSize / blockSize;
    if (pFat->amountBlocks != expectedAmountBlocks) {
        printf("testCreateBsFat test failed: Incorrect amountBlocks value.\n");
        passed = false;
    }

    // Verify the disk and blocks arrays
    if (pFat->disk == NULL) {
        printf("testCreateBsFat test failed: Disk array is not allocated.\n");
        passed = false;
    }

    if (pFat->blocks == NULL) {
        printf("testCreateBsFat test failed: Blocks array is not allocated.\n");
        passed = false;
    }

    // Check if the disk and blocks arrays are properly initialized
    for (size_t i = 0; i < diskSize; i++) {
        if (pFat->disk[i] != 0) {
            printf("testCreateBsFat test failed: Disk array is not properly initialized.\n");
            passed = false;
        }
    }

    for (size_t i = 0; i < expectedAmountBlocks; i++) {
        if (pFat->blocks[i].state != free_ || pFat->blocks[i].bIndex != i || pFat->blocks[i].cluster != NULL) {
            printf("testCreateBsFat test failed: Blocks array is not properly initialized.\n");
            passed = false;
        }
    }

    // Check if all Cluster Block Associations are NULL
    for (size_t bIndex = 0; bIndex < pFat->amountBlocks; bIndex++) {
        if (pFat->blocks[bIndex].cluster != NULL) {
            printf("testCreateBsFat test failed: Cluster associated with block %zu was not freed.\n", bIndex);
            passed = false;
            break;
        }
    }

    // Cleanup
    freeBsFat(pFat);
    if (passed)
        printf("testCreateBsFat test passed.\n");
    return passed;
}

bool testGetFreeDiskSpaceEmptyFat() {
    BsFat *pFat = createBsFat(BLOCKSIZE * 4, BLOCKSIZE);
    size_t freeSpace = getFreeDiskSpace(pFat);
    bool passed;
    if (freeSpace == BLOCKSIZE * 4) {
        printf("testGetFreeDiskSpaceEmptyFat test passed.\n");
        passed = true;
    } else {
        printf("testGetFreeDiskSpaceEmptyFat test failed: Expected free disk space: 1024 bytes, Actual free disk space: %zu bytes.\n",
               freeSpace);
        passed = false;
    }
    freeBsFat(pFat);
    return passed;
}

bool testGetFreeDiskSpaceWithAllocatedBlocks() {
    BsFat *pFat = createBsFat(BLOCKSIZE * 4, BLOCKSIZE);
    // Allocate some blocks or create files within the filesystem
    // Perform actions to allocate blocks or create files
    for (size_t i = 0; i < 2; i++) {
        pFat->blocks[i].state = allocated;
    }
    size_t freeSpace = getFreeDiskSpace(pFat);
    // Calculate the expected free space based on the allocated blocks/files
    size_t expectedFreeSpace = BLOCKSIZE * 2;  // Calculate the expected value based on the specific test case
    bool passed;
    if (freeSpace == expectedFreeSpace) {
        printf("testGetFreeDiskSpaceWithAllocatedBlocks test passed.\n");
        passed = true;
    } else {
        printf("testGetFreeDiskSpaceWithAllocatedBlocks test failed: Expected free disk space: %zu bytes, Actual free disk space: %zu bytes.\n",
               expectedFreeSpace, freeSpace);
        passed = false;
    }
    freeBsFat(pFat);
    return passed;
}

bool testGetFreeDiskSpaceFullDisk() {
    BsFat *pFat = createBsFat(BLOCKSIZE, BLOCKSIZE);
    // Allocate all blocks or create files until the disk is full
    pFat->blocks->state = allocated;
    // Perform actions to allocate blocks or create files
    size_t freeSpace = getFreeDiskSpace(pFat);
    bool passed;
    if (freeSpace == 0) {
        printf("testGetFreeDiskSpaceFullDisk test passed.\n");
        passed = true;
    } else {
        printf("testGetFreeDiskSpaceFullDisk test failed: Expected free disk space: 0 bytes, Actual free disk space: %zu bytes.\n",
               freeSpace);
        passed = false;
    }
    freeBsFat(pFat);
    return passed;
}

bool testCreateFileValid() {
    BsFat *pFat = createBsFat(BLOCKSIZE * 4, BLOCKSIZE);

    size_t szFile = 600u;
    const char *filename = "/home/henry/cats.gif";
    long timestamp = time(NULL);
    bool passed = true;

    BsFile **file = createFile(pFat, filename, timestamp);
    if (file == NULL) {
        printf("testCreateFileValid test failed: Failed to create file.\n");
        passed = false;
    }

    if (!checkIntegrity(pFat)) {
        printf("testCreateFileValid test failed: Integrity check failed!.\n");
        passed = false;
    }

    if (passed)
        printf("testCreateFileValid test passed.\n");
    return passed;
}

bool testCreateFileInsufficientMemory() {
    fflush(stdout);
    BsFat *pFat = createBsFat(BLOCKSIZE * 4, BLOCKSIZE);
    const char *filename = "/home/henry/dogs.gif";
    long timestamp = time(NULL);
    bool passed = true;

    BsFile **file = createFile(pFat, filename, timestamp);
    bool allocated = true;
    for(int i = 0; i < pFat->amountBlocks + 1 && allocated; i++){ // Larger than available memory
        allocated = allocateNewBlockForFile(pFat, *file);
    }
    if (allocated) {
        printf("testCreateFileInsufficientMemory test failed: File created despite insufficient memory.\n");
        passed = false;
    }

    if (!checkIntegrity(pFat)) {
        printf("testCreateFileInsufficientMemory test failed: Integrity check failed!.\n");
        passed = false;
    }

    if (passed)
        printf("testCreateFileInsufficientMemory test passed.\n");
    fflush(stderr);
    return passed;
}

bool testCreateFileNoAvailableFileSlot() {
    fflush(stdout);
    BsFat *pFat = createBsFat(BLOCKSIZE * 4, BLOCKSIZE);
    printf("Free Space is now: %zu\n", getFreeDiskSpace(pFat));
    size_t szFile = 64u;
    const char *filename = "/home/henry/bears.gif";
    long timestamp = time(NULL);
    bool passed = true;

    // Fill all available file slots
    for (size_t i = 0; i < AMOUNT_FILES; i++) {
        BsFile **file = createFile(pFat, filename, timestamp);
        if (file == NULL) {
            printf("testDeleteFileValid test failed: createFile failed and returned NULL.\n");
            return false;
        }
        printf("Free Space is now: %zu\n", getFreeDiskSpace(pFat));
    }

    BsFile **file = createFile(pFat, filename, timestamp);
    if (file != NULL) {
        printf("testCreateFileNoAvailableFileSlot test failed: File created despite no available file slot.\n");
        passed = false;
    }

    if (!checkIntegrity(pFat)) {
        printf("testCreateFileNoAvailableFileSlot test failed: Integrity check failed!.\n");
        passed = false;
    }

    if (passed)
        printf("testCreateFileNoAvailableFileSlot test passed.\n");
    fflush(stderr);
    return passed;
}

// TODO! This test no longer makes sense, as fat/fuse fielsystems will not check for this and just let disaster happen
//bool testCreateFileInsufficientFreeBlocks() {
//    BsFat *pFat = createBsFat(BLOCKSIZE * 4, BLOCKSIZE);
//    size_t szFile = pFat->amountBlocks * pFat->blockSize + 1;  // Requires more blocks than available
//    const char *filename = "/home/henry/sharks.gif";
//    long timestamp = time(NULL);
//    bool passed = true;
//
//    BsFile **file = createFile(pFat, szFile, filename, timestamp);
//    if (file != NULL) {
//        printf("testCreateFileInsufficientFreeBlocks test failed: File created despite insufficient free blocks.\n");
//        passed = false;
//    }
//
//    if (!checkIntegrity(pFat)) {
//        printf("testCreateFileInsufficientFreeBlocks test failed: Integrity check failed!.\n");
//        passed = false;
//    }
//
//    if (passed)
//        printf("testCreateFileInsufficientFreeBlocks test passed.\n");
//    return passed;
//}

bool testCreateFileLinkedList() {
    // Create a file with multiple clusters
    BsFat *pFat = createBsFat(BLOCKSIZE * 4, BLOCKSIZE);
    const char *filename = "/home/henry/dogs.gif";
    long timestamp = time(NULL);
    BsFile **file = createFile(pFat, filename, timestamp);
    allocateNewBlockForFile(pFat, *file);
    allocateNewBlockForFile(pFat, *file);
    if (file == NULL) {
        printf("testCreateFileLinkedList test failed: createFile failed and returned NULL.\n");
        return false;
    }

    // Verify the linked list inside the clusters
    bool passed = true;
    size_t clusterIndex = 0;
    size_t expectedBIndex = (*file)->pCluster[clusterIndex].bIndex;
    BsCluster *pCluster = &((*file)->pCluster[clusterIndex]);

    while (pCluster != NULL) {
        if (pCluster->bIndex != expectedBIndex) {
            printf("testCreateFileLinkedList test failed: Incorrect bIndex in the cluster.\n");
            passed = false;
            break;
        }

        if (pCluster->file != *file) {
            printf("testCreateFileLinkedList test failed: Incorrect fileIndex in the cluster.\n");
            passed = false;
            break;
        }

        if (pCluster->clusterIndex != clusterIndex) {
            printf("testCreateFileLinkedList test failed: Incorrect clusterIndex in the cluster. Got %zu, but expected %zu\n", pCluster->clusterIndex, clusterIndex);
            passed = false;
            break;
        }

        expectedBIndex++;
        clusterIndex++;
        pCluster = pCluster->next;
    }

    if (!checkIntegrity(pFat)) {
        printf("testCreateFileLinkedList test failed: Integrity check failed!.\n");
        passed = false;
    }

    if (passed)
        printf("testCreateFileLinkedList test passed.\n");
    return passed;
}

bool testDeleteFileValid() {
    // Create a valid file
    BsFat *pFat = createBsFat(BLOCKSIZE * 4, BLOCKSIZE);
    const char *filename = "/home/henry/cats.gif";
    long timestamp = time(NULL);
    BsFile **file = createFile(pFat, filename, timestamp);
    if (file == NULL) {
        printf("testDeleteFileValid test failed: createFile failed and returned NULL.\n");
        return false;
    }

    // Delete the file
    deleteFile(pFat, filename);

    // Check if the file was successfully deleted
    bool passed = true;
    for (size_t i = 0; i < AMOUNT_FILES; i++) {
        if (pFat->files[i] != NULL && strcmp(pFat->files[i]->filename, filename) == 0) {
            printf("testDeleteFileValid test failed: File still exists in the file table.\n");
            passed = false;
            break;
        }
    }

    if (*file != NULL) {
        printf("testDeleteFileValid test failed: File structure still exists.\n");
        passed = false;
    }

    if (!checkIntegrity(pFat)) {
        printf("testDeleteFileValid test failed: Integrity check failed!.\n");
        passed = false;
    }

    if (passed)
        printf("testDeleteFileValid test passed.\n");
    return passed;
}

// TODO! unlink not yet implemented
//bool testDeleteFileNonExistent() {
//    // Create a valid file
//    BsFat *pFat = createBsFat(BLOCKSIZE * 4, BLOCKSIZE);
//    const char *filename = "/home/henry/cats.gif";
//    long timestamp = time(NULL);
//    BsFile **file = createFile(pFat, filename, timestamp);
//    if (file == NULL) {
//        printf("testDeleteFileValid test failed: createFile failed and returned NULL.\n");
//        return false;
//    }
//    // Delete a non-existent file
//    const char *nonExistentFilename = "/home/henry/dogs.gif";
//    deleteFile(pFat, nonExistentFilename);
//
//    // Check if the file table remains unchanged
//    bool passed = true;
//
//    if (*file == NULL) {
//        printf("testDeleteFileNonExistent test failed: File in the file table was incorrectly deleted.\n");
//        passed = false;
//    }
//
//    if ((*file)->filename != filename) {
//        printf("testDeleteFileNonExistent test failed: File in the file table was incorrectly deleted.\n");
//        passed = false;
//    }
//
//    if (!checkIntegrity(pFat)) {
//        printf("testDeleteFileNonExistent test failed: Integrity check failed!.\n");
//        passed = false;
//    }
//
//    if (passed)
//        printf("testDeleteFileNonExistent test passed.\n");
//    return passed;
//}

// TODO! unlink not yet implemented
//bool testDeleteFileWithClusters() {
//    // Check if the associated clusters were freed
//    bool passed = true;
//
//    // Create a file with clusters
//    BsFat *pFat = createBsFat(BLOCKSIZE * 4, BLOCKSIZE);
//
//
//    const char *filename = "/home/henry/cats.gif";
//    long timestamp = time(NULL);
//    BsFile **file = createFile(pFat, szFile, filename, timestamp, NULL);
//    if (file == NULL) {
//        printf("testDeleteFileValid test failed: createFile failed and returned NULL.\n");
//        return false;
//    }
//    // Delete the file
//    deleteFile(pFat, filename);
//
//    // Check if the associated clusters were freed
//
//    for (size_t bIndex = 0; bIndex < pFat->amountBlocks; bIndex++) {
//        if (pFat->blocks[bIndex].cluster != NULL) {
//            printf("testDeleteFileWithClusters test failed: Cluster associated with block %zu was not freed.\n",
//                   bIndex);
//            passed = false;
//            break;
//        }
//    }
//
//    if (!checkIntegrity(pFat)) {
//        printf("testDeleteFileWithClusters test failed: Integrity check failed!.\n");
//        passed = false;
//    }
//
//    if (passed)
//        printf("testDeleteFileWithClusters test passed.\n");
//    return passed;
//}

bool testShowNBlockFat(size_t n, size_t outputLen) {
    // Create an empty Fat
    BsFat *pFat = createBsFat(n, 1);

    // Call showFat and capture the output
    char output[512];
    showFat(pFat, output);

    printf("Output of showFat was %zu chars!\n", strlen(output));

    // Compare the output with the expected output
    bool passed = strlen(output) == outputLen;
    if (passed) {
        printf("testShowFatEmptyFat test passed.\n");
    } else {
        printf("testShowFatEmptyFat test failed: Incorrect output length.\n");
        printf("Expected Output length: %zu\n", outputLen);
        printf("Actual: %s\n", output);
        printf("Actual length: %zu\n", strlen(output));
    }

    freeBsFat(pFat);
    return passed;
}

// TODO! implement swap again
//bool testSwapBlocksIntegrity() {
//    BsFat *pFat = createBsFat(BLOCKSIZE * 4, BLOCKSIZE);
//    bool passed = true;
//
//    // Swap the same block
//    bool swapResult = swapBlocks(pFat, 0, 0);
//    if (swapResult) {
//        printf("testSwapBlocksIntegrity test failed: Failed to NOT swap the same Block!\n");
//        passed = false;
//    }
//
//    // Swap two allocated Blocks
//    createFile(pFat, 1, "file1", time(NULL), NULL);
//    createFile(pFat, 1, "file2", time(NULL), NULL);
//    swapResult = swapBlocks(pFat, 0, 1);
//    if (!swapResult || strcmp(pFat->files[pFat->blocks[0].cluster->fileIndex]->filename, "file2") != 0
//        || strcmp(pFat->files[pFat->blocks[1].cluster->fileIndex]->filename, "file1") != 0) {
//        printf("testSwapBlocksIntegrity test failed: Failed to swap two Blocks!\n");
//        passed = false;
//    }
//
//    if (!checkIntegrity(pFat)) {
//        printf("testSwapBlocksIntegrity test failed: Integrity check failed!.\n");
//        passed = false;
//    }
//
//    // Swapping a free block with an allocated block
//    createFile(pFat, 1, "file3", time(NULL), NULL);
//    swapResult = swapBlocks(pFat, 2, 3);
//    if (!swapResult || strcmp(pFat->files[pFat->blocks[3].cluster->fileIndex]->filename, "file3") != 0) {
//        printf("testSwapBlocksIntegrity test failed: Failed to swap a free block with an allocated block.\n");
//        passed = false;
//    }
//
//    if (!checkIntegrity(pFat)) {
//        printf("testSwapBlocksIntegrity test failed: Integrity check failed!.\n");
//        passed = false;
//    }
//
//
//    // Swapping a free block with a defect block
//    pFat->blocks[4].state = defect;
//    swapResult = swapBlocks(pFat, 4, 5);
//    if (swapResult || pFat->blocks[4].state != defect) {
//        printf("testSwapBlocksIntegrity test failed: Failed to NOT swap a free block with a defect block.\n");
//        passed = false;
//    }
//
//    if (!checkIntegrity(pFat)) {
//        printf("testSwapBlocksIntegrity test failed: Integrity check failed!.\n");
//        passed = false;
//    }
//
//    // Swapping a free block with a reserved block
//    pFat->blocks[6].state = reserved;
//    swapResult = swapBlocks(pFat, 6, 7);
//    if (swapResult || pFat->blocks[6].state != reserved) {
//        printf("testSwapBlocksIntegrity test failed: Failed to NOT swap a free block with a defect block.\n");
//        passed = false;
//    }
//
//    if (!checkIntegrity(pFat)) {
//        printf("testSwapBlocksIntegrity test failed: Integrity check failed!.\n");
//        passed = false;
//    }
//
//    // Swapping two free blocks!
//    swapResult = swapBlocks(pFat, 8, 9);
//    if (swapResult) {
//        printf("testSwapBlocksIntegrity test failed: Failed to NOT swap two free blocks!\n");
//        passed = false;
//    }
//
//    if (!checkIntegrity(pFat)) {
//        printf("testSwapBlocksIntegrity test failed: Integrity check failed!.\n");
//        passed = false;
//    }
//
//    // Swapping a free block with a defect block
//    createFile(pFat, "file4", time(NULL));
//    pFat->blocks[10].state = reserved;
//
//    swapResult = swapBlocks(pFat, 10, 11);
//
//    if (swapResult || strcmp(pFat->files[pFat->blocks[2].cluster->fileIndex]->filename, "file4") != 0 ||
//        pFat->blocks[10].state != reserved) {
//        printf("testSwapBlocksIntegrity test failed: Failed to NOT swap a free block with a defect block\n");
//        passed = false;
//    }
//
//    if (!checkIntegrity(pFat)) {
//        printf("testSwapBlocksIntegrity test failed: Integrity check failed!.\n");
//        passed = false;
//    }
//
//    freeBsFat(pFat);
//    return passed;
//}

// TODO! need to implement swapblocks again
//bool testDefragmentation() {
//    // Create a valid file
//    BsFat *pFat = createBsFat(BLOCKSIZE * 4, BLOCKSIZE);
//    size_t szFile = 512u;
//    BsFile **file = createFile(pFat, "cats.gif", time(NULL));
//    if (file == NULL) {
//        printf("testDefragmentation test failed: createFile failed and returned NULL.\n");
//        return false;
//    }
//    file = createFile(pFat, "dogs.gif", time(NULL));
//    if (file == NULL) {
//        printf("testDefragmentation test failed: createFile failed and returned NULL.\n");
//        return false;
//    }
//    file = createFile(pFat, "birds.gif", time(NULL));
//    if (file == NULL) {
//        printf("testDefragmentation test failed: createFile failed and returned NULL.\n");
//        return false;
//    }
//    deleteFile(pFat, "/home/henry/dogs.gif");
//    swapBlocks(pFat, 4, 25);
//    swapBlocks(pFat, 4, 23);
//    swapBlocks(pFat, 2, 24);
//    showFat(pFat, NULL);
//    checkForDefragmentation(pFat);
//    defragmentate(pFat);
//    showFat(pFat, NULL);
//    checkForDefragmentation(pFat);
//    return true;
//}

bool testWriteRead(int argc, char **argv) {
    BsFat *pFat = createBsFat(BLOCKSIZE * 4, BLOCKSIZE);
    //fuse_main(argc, argv, &stegfs_fuse_oper, pFat);
    size_t szFile = 512u;
    const char *filename = "test.txt";
    long timestamp = time(NULL);
    BsFile **file = createFile(pFat, filename, timestamp);
    if (file == NULL) {
        printf("testWrite test failed: createFile failed and returned NULL.\n");
        return false;
    }
    const char *testBuffer = "My testbuffer!";
    int bytesWritten = stegFS_write("/test.txt", testBuffer, 15, 0, (struct fuse_file_info *) pFat);
    if (bytesWritten < 0) {
        printf("testWrite test failed: Errorcode: %d\n", bytesWritten);
        return false;
    }
    if (bytesWritten != 15) {
        printf("testWrite test failed: wrote %d bytes instead of 15\n", bytesWritten);
        return false;
    }
    printf("Printing pFat->Disk to terminal: %s\n", pFat->disk);
    checkForDefragmentation(pFat);
    showFat(pFat, NULL);
    char output[20];
    memset(output, 0, 20);
    stegFS_read("/test.txt", output, 15, 0, (struct fuse_file_info *) pFat);
    printf("Printing result of stegFS_read: %s\n", output);
    return true;
}

void runTests(int argc, char **argv) {
    int tests[] = {
            testCreateBsFat(),
            testGetFreeDiskSpaceEmptyFat(),
            testGetFreeDiskSpaceWithAllocatedBlocks(),
            testGetFreeDiskSpaceFullDisk(),
            testCreateFileValid(),
            testCreateFileInsufficientMemory(),
            testCreateFileNoAvailableFileSlot(),
            //testCreateFileInsufficientFreeBlocks(),
            testCreateFileLinkedList(),
            testDeleteFileValid(),
            //testDeleteFileNonExistent(),
            //testDeleteFileWithClusters(),
            testShowNBlockFat(1, 23),
            testShowNBlockFat(239, 504),
            testShowNBlockFat(240, 507),
            testShowNBlockFat(241, 509),
            testShowNBlockFat(242, 509),
//            //testSwapBlocksIntegrity(),
//            //testDefragmentation(),
            testWriteRead(argc, argv),
            -1};
    size_t passed = 0;
    size_t sum = 0;
    int *pTests = tests;
    while (*pTests != -1) {
        sum++;
        if (*pTests == 1) {
            passed++;
        }
        pTests++;
    }
    printf("%zu/%zu tests passed!\n", passed, sum);
}

int test_fuse(int argc, char** argv){
    BsFat *pFat = createBsFat(BLOCKSIZE * 4, BLOCKSIZE);
    BsFile **file = createFile(pFat, "cats.gif", time(NULL));
    if (file == NULL) {
        printf("testDefragmentation test failed: createFile failed and returned NULL.\n");
        return false;
    }
    file = createFile(pFat, "dogs.gif", time(NULL));
    if (file == NULL) {
        printf("testDefragmentation test failed: createFile failed and returned NULL.\n");
        return false;
    }
    file = createFile(pFat, "birds.gif", time(NULL));
    if (file == NULL) {
        printf("testDefragmentation test failed: createFile failed and returned NULL.\n");
        return false;
    }
    return fuse_main(argc, argv, &stegfs_fuse_oper, pFat);
}

int main(int argc, char** argv) {
    runTests(argc, argv);
    return test_fuse(argc, argv);
}