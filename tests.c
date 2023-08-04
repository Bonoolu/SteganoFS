#include "steganoFS.h"

bool testCreateHiddenFat() {
    size_t diskSize = BLOCKSIZE * 4;  // Example disk size
    size_t blockSize = BLOCKSIZE;  // Example block size
    HiddenFat *hiddenFat = createHiddenFat(diskSize, blockSize);
    bool passed = true;
    if (hiddenFat == NULL) {
        printf("testCreateHiddenFat test failed: Failed to create the HiddenFat structure.\n");
        passed = false;
    }

    // Verify the blockSize and amountBlocks values
    if (hiddenFat->blockSize != blockSize) {
        printf("testCreateHiddenFat test failed: Incorrect blockSize value.\n");
        passed = false;
    }

    size_t expectedAmountBlocks = diskSize / blockSize;
    if (hiddenFat->amountBlocks != expectedAmountBlocks) {
        printf("testCreateHiddenFat test failed: Incorrect amountBlocks value.\n");
        passed = false;
    }

    // Verify the disk and blocks arrays
    if (hiddenFat->disk == NULL) {
        printf("testCreateHiddenFat test failed: Disk array is not allocated.\n");
        passed = false;
    }

    if (hiddenFat->clusters == NULL) {
        printf("testCreateHiddenFat test failed: Blocks array is not allocated.\n");
        passed = false;
    }

    // Check if the disk and blocks arrays are properly initialized
    for (size_t i = 0; i < diskSize; i++) {
        if (hiddenFat->disk[i] != 0) {
            printf("testCreateHiddenFat test failed: Disk array is not properly initialized.\n");
            passed = false;
        }
    }

    for (size_t i = 0; i < expectedAmountBlocks; i++) {
        if (hiddenFat->clusters[i].state != free_ || hiddenFat->clusters[i].bIndex != i) {
            printf("testCreateHiddenFat test failed: Blocks array is not properly initialized.\n");
            passed = false;
        }
    }

    // Check if all Cluster Block Associations are not NULL
    for (size_t bIndex = 0; bIndex < hiddenFat->amountBlocks; bIndex++) {
        if (hiddenFat->clusters[bIndex].prev != NULL || hiddenFat->clusters[bIndex].next != NULL) {
            printf("testCreateHiddenFat test failed: Cluster associated with block %zu was not freed.\n", bIndex);
            passed = false;
            break;
        }
    }

    // Cleanup
    freeHiddenFat(hiddenFat);
    if (passed)
        printf("testCreateHiddenFat test passed.\n");
    return passed;
}

bool testGetFreeDiskSpaceEmptyFat() {
    HiddenFat *hiddenFat = createHiddenFat(BLOCKSIZE * 4, BLOCKSIZE);
    size_t freeSpace = getFreeDiskSpace(hiddenFat);
    bool passed;
    if (freeSpace == BLOCKSIZE * 4) {
        printf("testGetFreeDiskSpaceEmptyFat test passed.\n");
        passed = true;
    } else {
        printf("testGetFreeDiskSpaceEmptyFat test failed: Expected free disk space: 1024 bytes, Actual free disk space: %zu bytes.\n",
               freeSpace);
        passed = false;
    }
    freeHiddenFat(hiddenFat);
    return passed;
}

bool testGetFreeDiskSpaceWithAllocatedBlocks() {
    HiddenFat *hiddenFat = createHiddenFat(BLOCKSIZE * 4, BLOCKSIZE);
    // Allocate some blocks or create files within the filesystem
    // Perform actions to allocate blocks or create files
    for (size_t i = 0; i < 2; i++) {
        hiddenFat->clusters[i].state = allocated;
    }
    size_t freeSpace = getFreeDiskSpace(hiddenFat);
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
    freeHiddenFat(hiddenFat);
    return passed;
}

bool testGetFreeDiskSpaceFullDisk() {
    HiddenFat *hiddenFat = createHiddenFat(BLOCKSIZE, BLOCKSIZE);
    // Allocate all blocks or create files until the disk is full
    hiddenFat->clusters->state = allocated;
    // Perform actions to allocate blocks or create files
    size_t freeSpace = getFreeDiskSpace(hiddenFat);
    bool passed;
    if (freeSpace == 0) {
        printf("testGetFreeDiskSpaceFullDisk test passed.\n");
        passed = true;
    } else {
        printf("testGetFreeDiskSpaceFullDisk test failed: Expected free disk space: 0 bytes, Actual free disk space: %zu bytes.\n",
               freeSpace);
        passed = false;
    }
    freeHiddenFat(hiddenFat);
    return passed;
}

bool testCreateFileValid() {
    HiddenFat *hiddenFat = createHiddenFat(BLOCKSIZE * 4, BLOCKSIZE);

    const char *hiddenFilename = "/home/henry/cats.gif";
    long timestamp = time(NULL);
    bool passed = true;

    HiddenFile **hiddenFile = createHiddenFile(hiddenFat, hiddenFilename, timestamp);
    if (hiddenFile == NULL) {
        printf("testCreateFileValid test failed: Failed to create file.\n");
        passed = false;
    }

    if (!checkIntegrity(hiddenFat)) {
        printf("testCreateFileValid test failed: Integrity check failed!.\n");
        passed = false;
    }

    if (passed)
        printf("testCreateFileValid test passed.\n");
    return passed;
}

bool testCreateFileInsufficientMemory() {
    fflush(stdout);
    HiddenFat *hiddenFat = createHiddenFat(BLOCKSIZE * 4, BLOCKSIZE);
    const char *hiddenFilename = "/home/henry/dogs.gif";
    long timestamp = time(NULL);
    bool passed = true;

    HiddenFile **hiddenFile = createHiddenFile(hiddenFat, hiddenFilename, timestamp);
    bool allocated = true;
    for(int i = 0; i < hiddenFat->amountBlocks + 1 && allocated; i++){ // Larger than available memory
        allocated = extendHiddenCluster(hiddenFat, *hiddenFile);
    }
    if (allocated) {
        printf("testCreateFileInsufficientMemory test failed: File created despite insufficient memory.\n");
        passed = false;
    }

    if (!checkIntegrity(hiddenFat)) {
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
    HiddenFat *hiddenFat = createHiddenFat(BLOCKSIZE * 4, BLOCKSIZE);
    printf("Free Space is now: %zu\n", getFreeDiskSpace(hiddenFat));
    const char *hiddenFilename = "/home/henry/bears.gif";
    long timestamp = time(NULL);
    bool passed = true;

    // Fill all available file slots
    for (size_t i = 0; i < AMOUNT_ROOT_FILES; i++) {
        HiddenFile **hiddenFile = createHiddenFile(hiddenFat, hiddenFilename, timestamp);
        if (hiddenFile == NULL) {
            printf("testCreateFileNoAvailableFileSlot test failed: createHiddenFile failed and returned NULL.\n");
            return false;
        }
    }

    HiddenFile **hiddenFile = createHiddenFile(hiddenFat, hiddenFilename, timestamp);
    if (hiddenFile != NULL) {
        printf("testCreateFileNoAvailableFileSlot test failed: File created despite no available file slot.\n");
        passed = false;
    }

    if (!checkIntegrity(hiddenFat)) {
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
//    HiddenFat *hiddenFat = createHiddenFat(BLOCKSIZE * 4, BLOCKSIZE);
//    size_t szFile = hiddenFat->amountBlocks * hiddenFat->blockSize + 1;  // Requires more blocks than available
//    const char *hiddenFilename = "/home/henry/sharks.gif";
//    long timestamp = time(NULL);
//    bool passed = true;
//
//    BsFile **hiddenFile = createFile(hiddenFat, szFile, hiddenFilename, timestamp);
//    if (hiddenFile != NULL) {
//        printf("testCreateFileInsufficientFreeBlocks test failed: File created despite insufficient free blocks.\n");
//        passed = false;
//    }
//
//    if (!checkIntegrity(hiddenFat)) {
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
    HiddenFat *hiddenFat = createHiddenFat(BLOCKSIZE * 4, BLOCKSIZE);
    const char *hiddenFilename = "/home/henry/dogs.gif";
    long timestamp = time(NULL);
    HiddenFile **hiddenFile = createHiddenFile(hiddenFat, hiddenFilename, timestamp);
    extendHiddenCluster(hiddenFat, *hiddenFile);
    extendHiddenCluster(hiddenFat, *hiddenFile);
    if (hiddenFile == NULL) {
        printf("testCreateFileLinkedList test failed: createHiddenFile failed and returned NULL.\n");
        return false;
    }

    // Verify the linked list inside the clusters
    bool passed = true;
    size_t clusterIndex = 0;
    size_t expectedBIndex = (*hiddenFile)->hiddenCluster->bIndex;
    HiddenCluster *hiddenCluster = (*hiddenFile)->hiddenCluster;

    while (hiddenCluster != NULL) {
        if (hiddenCluster->bIndex != expectedBIndex) {
            printf("testCreateFileLinkedList test failed: Incorrect bIndex in the cluster.\n");
            passed = false;
            break;
        }

        if (hiddenCluster->file != *hiddenFile) {
            printf("testCreateFileLinkedList test failed: Incorrect fileIndex in the cluster.\n");
            passed = false;
            break;
        }

        if (hiddenCluster->clusterIndex != clusterIndex) {
            printf("testCreateFileLinkedList test failed: Incorrect clusterIndex in the cluster. Got %zu, but expected %zu\n", hiddenCluster->clusterIndex, clusterIndex);
            passed = false;
            break;
        }

        expectedBIndex++;
        clusterIndex++;
        hiddenCluster = hiddenCluster->next;
    }

    if (!checkIntegrity(hiddenFat)) {
        printf("testCreateFileLinkedList test failed: Integrity check failed!.\n");
        passed = false;
    }

    if (passed)
        printf("testCreateFileLinkedList test passed.\n");
    return passed;
}

bool testDeleteFileValid() {
    // Create a valid file
    HiddenFat *hiddenFat = createHiddenFat(BLOCKSIZE * 4, BLOCKSIZE);
    const char *hiddenFilename = "/home/henry/cats.gif";
    long timestamp = time(NULL);
    HiddenFile **hiddenFile = createHiddenFile(hiddenFat, hiddenFilename, timestamp);
    if (hiddenFile == NULL) {
        printf("testDeleteFileValid test failed: createHiddenFile failed and returned NULL.\n");
        return false;
    }

    // Delete the file
    deleteHiddenFile(hiddenFat, hiddenFilename);

    // Check if the file was successfully deleted
    bool passed = true;
    for (size_t i = 0; i < AMOUNT_ROOT_FILES; i++) {
        if (hiddenFat->files[i] != NULL && strcmp(hiddenFat->files[i]->filename, hiddenFilename) == 0) {
            printf("testDeleteFileValid test failed: File still exists in the file table.\n");
            passed = false;
            break;
        }
    }

    if (*hiddenFile != NULL) {
        printf("testDeleteFileValid test failed: File structure still exists.\n");
        passed = false;
    }

    if (!checkIntegrity(hiddenFat)) {
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
//    HiddenFat *hiddenFat = createHiddenFat(BLOCKSIZE * 4, BLOCKSIZE);
//    const char *hiddenFilename = "/home/henry/cats.gif";
//    long timestamp = time(NULL);
//    BsFile **hiddenFile = createFile(hiddenFat, hiddenFilename, timestamp);
//    if (hiddenFile == NULL) {
//        printf("testDeleteFileValid test failed: createFile failed and returned NULL.\n");
//        return false;
//    }
//    // Delete a non-existent file
//    const char *nonExistentFilename = "/home/henry/dogs.gif";
//    deleteFile(hiddenFat, nonExistentFilename);
//
//    // Check if the file table remains unchanged
//    bool passed = true;
//
//    if (*hiddenFile == NULL) {
//        printf("testDeleteFileNonExistent test failed: File in the file table was incorrectly deleted.\n");
//        passed = false;
//    }
//
//    if ((*hiddenFile)->filename != filename) {
//        printf("testDeleteFileNonExistent test failed: File in the file table was incorrectly deleted.\n");
//        passed = false;
//    }
//
//    if (!checkIntegrity(hiddenFat)) {
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
//    HiddenFat *hiddenFat = createHiddenFat(BLOCKSIZE * 4, BLOCKSIZE);
//
//
//    const char *hiddenFilename = "/home/henry/cats.gif";
//    long timestamp = time(NULL);
//    BsFile **hiddenFile = createFile(hiddenFat, szFile, hiddenFilename, timestamp, NULL);
//    if (hiddenFile == NULL) {
//        printf("testDeleteFileValid test failed: createFile failed and returned NULL.\n");
//        return false;
//    }
//    // Delete the file
//    deleteFile(hiddenFat, filename);
//
//    // Check if the associated clusters were freed
//
//    for (size_t bIndex = 0; bIndex < hiddenFat->amountBlocks; bIndex++) {
//        if (hiddenFat->blocks[bIndex].cluster != NULL) {
//            printf("testDeleteFileWithClusters test failed: Cluster associated with block %zu was not freed.\n",
//                   bIndex);
//            passed = false;
//            break;
//        }
//    }
//
//    if (!checkIntegrity(hiddenFat)) {
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
    HiddenFat *hiddenFat = createHiddenFat(n, 1);

    // Call showFat and capture the output
    char output[512];
    showHiddenFat(hiddenFat, output);

    printf("Output of showHiddenFat was %zu chars!\n", strlen(output));

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

    freeHiddenFat(hiddenFat);
    return passed;
}

// TODO! implement swap again
//bool testSwahiddenClustersIntegrity() {
//    HiddenFat *hiddenFat = createHiddenFat(BLOCKSIZE * 4, BLOCKSIZE);
//    bool passed = true;
//
//    // Swap the same block
//    bool swapResult = swahiddenClusters(hiddenFat, 0, 0);
//    if (swapResult) {
//        printf("testSwahiddenClustersIntegrity test failed: Failed to NOT swap the same Block!\n");
//        passed = false;
//    }
//
//    // Swap two allocated Blocks
//    createFile(hiddenFat, 1, "file1", time(NULL), NULL);
//    createFile(hiddenFat, 1, "file2", time(NULL), NULL);
//    swapResult = swahiddenClusters(hiddenFat, 0, 1);
//    if (!swapResult || strcmp(hiddenFat->files[hiddenFat->blocks[0].cluster->fileIndex]->filename, "file2") != 0
//        || strcmp(hiddenFat->files[hiddenFat->blocks[1].cluster->fileIndex]->filename, "file1") != 0) {
//        printf("testSwahiddenClustersIntegrity test failed: Failed to swap two Blocks!\n");
//        passed = false;
//    }
//
//    if (!checkIntegrity(hiddenFat)) {
//        printf("testSwahiddenClustersIntegrity test failed: Integrity check failed!.\n");
//        passed = false;
//    }
//
//    // Swapping a free block with an allocated block
//    createFile(hiddenFat, 1, "file3", time(NULL), NULL);
//    swapResult = swahiddenClusters(hiddenFat, 2, 3);
//    if (!swapResult || strcmp(hiddenFat->files[hiddenFat->blocks[3].cluster->fileIndex]->filename, "file3") != 0) {
//        printf("testSwahiddenClustersIntegrity test failed: Failed to swap a free block with an allocated block.\n");
//        passed = false;
//    }
//
//    if (!checkIntegrity(hiddenFat)) {
//        printf("testSwahiddenClustersIntegrity test failed: Integrity check failed!.\n");
//        passed = false;
//    }
//
//
//    // Swapping a free block with a defect block
//    hiddenFat->blocks[4].state = defect;
//    swapResult = swahiddenClusters(hiddenFat, 4, 5);
//    if (swapResult || hiddenFat->blocks[4].state != defect) {
//        printf("testSwahiddenClustersIntegrity test failed: Failed to NOT swap a free block with a defect block.\n");
//        passed = false;
//    }
//
//    if (!checkIntegrity(hiddenFat)) {
//        printf("testSwahiddenClustersIntegrity test failed: Integrity check failed!.\n");
//        passed = false;
//    }
//
//    // Swapping a free block with a reserved block
//    hiddenFat->blocks[6].state = reserved;
//    swapResult = swahiddenClusters(hiddenFat, 6, 7);
//    if (swapResult || hiddenFat->blocks[6].state != reserved) {
//        printf("testSwahiddenClustersIntegrity test failed: Failed to NOT swap a free block with a defect block.\n");
//        passed = false;
//    }
//
//    if (!checkIntegrity(hiddenFat)) {
//        printf("testSwahiddenClustersIntegrity test failed: Integrity check failed!.\n");
//        passed = false;
//    }
//
//    // Swapping two free blocks!
//    swapResult = swahiddenClusters(hiddenFat, 8, 9);
//    if (swapResult) {
//        printf("testSwahiddenClustersIntegrity test failed: Failed to NOT swap two free blocks!\n");
//        passed = false;
//    }
//
//    if (!checkIntegrity(hiddenFat)) {
//        printf("testSwahiddenClustersIntegrity test failed: Integrity check failed!.\n");
//        passed = false;
//    }
//
//    // Swapping a free block with a defect block
//    createFile(hiddenFat, "file4", time(NULL));
//    hiddenFat->blocks[10].state = reserved;
//
//    swapResult = swahiddenClusters(hiddenFat, 10, 11);
//
//    if (swapResult || strcmp(hiddenFat->files[hiddenFat->blocks[2].cluster->fileIndex]->filename, "file4") != 0 ||
//        hiddenFat->blocks[10].state != reserved) {
//        printf("testSwahiddenClustersIntegrity test failed: Failed to NOT swap a free block with a defect block\n");
//        passed = false;
//    }
//
//    if (!checkIntegrity(hiddenFat)) {
//        printf("testSwahiddenClustersIntegrity test failed: Integrity check failed!.\n");
//        passed = false;
//    }
//
//    freeHiddenFat(hiddenFat);
//    return passed;
//}

// TODO! need to implement swahiddenClusters again
//bool testDefragmentation() {
//    // Create a valid file
//    HiddenFat *hiddenFat = createHiddenFat(BLOCKSIZE * 4, BLOCKSIZE);
//    size_t szFile = 512u;
//    BsFile **hiddenFile = createFile(hiddenFat, "cats.gif", time(NULL));
//    if (hiddenFile == NULL) {
//        printf("testDefragmentation test failed: createFile failed and returned NULL.\n");
//        return false;
//    }
//    file = createFile(hiddenFat, "dogs.gif", time(NULL));
//    if (hiddenFile == NULL) {
//        printf("testDefragmentation test failed: createFile failed and returned NULL.\n");
//        return false;
//    }
//    file = createFile(hiddenFat, "birds.gif", time(NULL));
//    if (hiddenFile == NULL) {
//        printf("testDefragmentation test failed: createFile failed and returned NULL.\n");
//        return false;
//    }
//    deleteFile(hiddenFat, "/home/henry/dogs.gif");
//    swahiddenClusters(hiddenFat, 4, 25);
//    swahiddenClusters(hiddenFat, 4, 23);
//    swahiddenClusters(hiddenFat, 2, 24);
//    showFat(hiddenFat, NULL);
//    checkForDefragmentation(hiddenFat);
//    defragmentate(hiddenFat);
//    showFat(hiddenFat, NULL);
//    checkForDefragmentation(hiddenFat);
//    return true;
//}

bool testWriteRead(int argc, char **argv) {
    HiddenFat *hiddenFat = createHiddenFat(BLOCKSIZE * 4, BLOCKSIZE);
    const char *hiddenFilename = "test.txt";
    long timestamp = time(NULL);
    HiddenFile **hiddenFile = createHiddenFile(hiddenFat, hiddenFilename, timestamp);
    if (hiddenFile == NULL) {
        printf("testWrite test failed: createHiddenFile failed and returned NULL.\n");
        return false;
    }
    const char *testBuffer = "My testbuffer!";
    int bytesWritten = writeSteganoFS("/test.txt", testBuffer, 15, 0, (struct fuse_file_info *) hiddenFat);
    if (bytesWritten < 0) {
        printf("testWrite test failed: Errorcode: %d\n", bytesWritten);
        return false;
    }
    if (bytesWritten != 15) {
        printf("testWrite test failed: wrote %d bytes instead of 15\n", bytesWritten);
        return false;
    }
    printf("Printing hiddenFat->Disk to terminal: %s\n", hiddenFat->disk);
    checkForDefragmentation(hiddenFat);
    showHiddenFat(hiddenFat, NULL);
    char output[20];
    memset(output, 0, 20);
    readSteganoFS("/test.txt", output, 15, 0, (struct fuse_file_info *) hiddenFat);
    printf("Printing result of readSteganoFS: %s\n", output);
    return true;
}

void runTests(int argc, char **argv) {
    int tests[] = {
            testCreateHiddenFat(),
            testGetFreeDiskSpaceEmptyFat(),
            testGetFreeDiskSpaceWithAllocatedBlocks(),
            testGetFreeDiskSpaceFullDisk(),
            testCreateFileValid(),
            testCreateFileInsufficientMemory(),
            testCreateFileNoAvailableFileSlot(),
            //testCreateFileInsufficientFreeBlocks(),
            testCreateFileLinkedList(),
            //testDeleteFileValid(),
            //testDeleteFileNonExistent(),
            //testDeleteFileWithClusters(),
            testShowNBlockFat(1, 23),
            testShowNBlockFat(239, 504),
            testShowNBlockFat(240, 507),
            testShowNBlockFat(241, 509),
            testShowNBlockFat(242, 509),
//            //testSwahiddenClustersIntegrity(),
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
    HiddenFat *hiddenFat = createHiddenFat(BLOCKSIZE * 4, BLOCKSIZE);
    HiddenFile **hiddenFile = createHiddenFile(hiddenFat, "cats.gif", time(NULL));
    if (hiddenFile == NULL) {
        printf("testDefragmentation test failed: createHiddenFile failed and returned NULL.\n");
        return false;
    }
    hiddenFile = createHiddenFile(hiddenFat, "dogs.gif", time(NULL));
    if (hiddenFile == NULL) {
        printf("testDefragmentation test failed: createHiddenFile failed and returned NULL.\n");
        return false;
    }
    hiddenFile = createHiddenFile(hiddenFat, "birds.gif", time(NULL));
    if (hiddenFile == NULL) {
        printf("testDefragmentation test failed: createHiddenFile failed and returned NULL.\n");
        return false;
    }
    return fuse_main(argc, argv, &fuseOperationsSteagnoFS, hiddenFat);
}

int main(int argc, char** argv) {
    runTests(argc, argv);
    return test_fuse(argc, argv);
}