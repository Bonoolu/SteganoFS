#include "../../steganofs/steganofs.h"
#include "../../steganofs/ramdiskloader.h"

bool testCreateHiddenFat() {
    size_t diskSize = BLOCK_SIZE * 4;  // Example disk size
    size_t blockSize = BLOCK_SIZE;  // Example block size
    HiddenFat *hiddenFat = createHiddenFat(diskSize, blockSize);
    bool passed = true;
    if (hiddenFat == NULL) {
        printf("testCreateHiddenFat test failed: Failed to stgfs_create the HiddenFat structure.\n");
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
    HiddenFat *hiddenFat = createHiddenFat(BLOCK_SIZE * 4, BLOCK_SIZE);
    size_t freeSpace = getFreeDiskSpace(hiddenFat);
    bool passed;
    if (freeSpace == BLOCK_SIZE * 4) {
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
    HiddenFat *hiddenFat = createHiddenFat(BLOCK_SIZE * 4, BLOCK_SIZE);
    // Allocate some blocks or create files within the filesystem
    // Perform actions to allocate blocks or create files
    for (size_t i = 0; i < 2; i++) {
        hiddenFat->clusters[i].state = allocated;
    }
    size_t freeSpace = getFreeDiskSpace(hiddenFat);
    // Calculate the expected free space based on the allocated blocks/files
    size_t expectedFreeSpace = BLOCK_SIZE * 2;  // Calculate the expected value based on the specific test case
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
    HiddenFat *hiddenFat = createHiddenFat(BLOCK_SIZE, BLOCK_SIZE);
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
    HiddenFat *hiddenFat = createHiddenFat(BLOCK_SIZE * 4, BLOCK_SIZE);

    const char *hiddenFilename = "cats.gif";
    long timestamp = time(NULL);
    bool passed = true;

    HiddenFile **hiddenFile = createHiddenFile(hiddenFat, hiddenFilename, timestamp);
    if (hiddenFile == NULL) {
        printf("testCreateFileValid test failed: Failed to stgfs_create file.\n");
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
    HiddenFat *hiddenFat = createHiddenFat(BLOCK_SIZE * 4, BLOCK_SIZE);
    const char *hiddenFilename = "dogs.gif";
    long timestamp = time(NULL);
    bool passed = true;

    HiddenFile **hiddenFile = createHiddenFile(hiddenFat, hiddenFilename, timestamp);
    if (hiddenFile == NULL) {
        printf("testCreateFileInsufficientMemory test failed: createHiddenFile failed and returned NULL.\n");
        return false;
    }
    bool allocated = true;
    for (int i = 0; i < hiddenFat->amountBlocks + 1 && allocated; i++) { // Larger than available memory
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
    HiddenFat *hiddenFat = createHiddenFat(BLOCK_SIZE * 4, BLOCK_SIZE);
    printf("Free Space is now: %zu\n", getFreeDiskSpace(hiddenFat));
    const char *hiddenFilename = "bears.gif";
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

bool testCreateFileLinkedList() {
    // Create a file with multiple clusters
    HiddenFat *hiddenFat = createHiddenFat(BLOCK_SIZE * 4, BLOCK_SIZE);
    const char *hiddenFilename = "dogs.gif";
    long timestamp = time(NULL);
    HiddenFile **hiddenFile = createHiddenFile(hiddenFat, hiddenFilename, timestamp);
    if (hiddenFile == NULL) {
        printf("testCreateFileLinkedList test failed: createHiddenFile failed and returned NULL.\n");
        return false;
    }
    extendHiddenCluster(hiddenFat, *hiddenFile);
    extendHiddenCluster(hiddenFat, *hiddenFile);

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
            printf("testCreateFileLinkedList test failed: Incorrect clusterIndex in the cluster. Got %zu, but expected %zu\n",
                   hiddenCluster->clusterIndex, clusterIndex);
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
    HiddenFat *hiddenFat = createHiddenFat(BLOCK_SIZE * 4, BLOCK_SIZE);
    const char *hiddenFilename = "cats.gif";
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

bool testDeleteFileNonExistent() {
    // Create a valid file
    HiddenFat *hiddenFat = createHiddenFat(BLOCK_SIZE * 4, BLOCK_SIZE);
    const char *hiddenFilename = "cats.gif";
    long timestamp = time(NULL);
    HiddenFile **hiddenFile = createHiddenFile(hiddenFat, hiddenFilename, timestamp);
    if (hiddenFile == NULL) {
        printf("testDeleteFileValid test failed: createFile failed and returned NULL.\n");
        return false;
    }
    // Delete a non-existent file
    const char *nonExistentFilename = "dogs.gif";
    deleteHiddenFile(hiddenFat, nonExistentFilename);

    // Check if the file table remains unchanged
    bool passed = true;

    if (*hiddenFile == NULL) {
        printf("testDeleteFileNonExistent test failed: File in the file table was incorrectly deleted.\n");
        passed = false;
    }

    if (strcmp((*hiddenFile)->filename, hiddenFilename) != 0) {
        printf("testDeleteFileNonExistent test failed: File in the file table was incorrectly deleted.\n");
        passed = false;
    }

    if (!checkIntegrity(hiddenFat)) {
        printf("testDeleteFileNonExistent test failed: Integrity check failed!.\n");
        passed = false;
    }

    if (passed)
        printf("testDeleteFileNonExistent test passed.\n");
    return passed;
}

bool testDeleteFileWithClusters() {
    // Check if the associated clusters were freed
    bool passed = true;

    // Create a file with clusters
    HiddenFat *hiddenFat = createHiddenFat(BLOCK_SIZE * 4, BLOCK_SIZE);

    const char *hiddenFilename = "cats.gif";
    long timestamp = time(NULL);
    HiddenFile **hiddenFile = createHiddenFile(hiddenFat, hiddenFilename, timestamp);
    if (hiddenFile == NULL) {
        printf("testDeleteFileValid test failed: createFile failed and returned NULL.\n");
        return false;
    }
    const char *testBuffer = "My testbuffer!";
    stgfs_write("/cats.gif", testBuffer, 15, 0, (struct fuse_file_info *) hiddenFat);

    // Delete the file
    deleteHiddenFile(hiddenFat, hiddenFilename);

    // Check if the associated clusters were freed
    unsigned char zeroBlock[BLOCK_SIZE];
    memset(zeroBlock, 0, sizeof zeroBlock);
    for (size_t bIndex = 0; bIndex < hiddenFat->amountBlocks; bIndex++) {
        if (memcmp(zeroBlock, hiddenFat->disk + (bIndex * BLOCK_SIZE), BLOCK_SIZE) != 0) {
            printf("testDeleteFileWithClusters test failed: Cluster associated with block %zu was not freed.\n",
                   bIndex);
            passed = false;
            break;
        }
    }

    if (!checkIntegrity(hiddenFat)) {
        printf("testDeleteFileWithClusters test failed: Integrity check failed!.\n");
        passed = false;
    }

    if (passed)
        printf("testDeleteFileWithClusters test passed.\n");
    return passed;
}

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

bool testSwapHiddenClustersIntegrity() {
    HiddenFat *hiddenFat = createHiddenFat(BLOCK_SIZE * 20, BLOCK_SIZE);
    bool passed = true;

    // Swap the same block
    bool swapResult = swapHiddenClusters(hiddenFat, 0, 0);
    if (swapResult) {
        printf("testSwapHiddenClustersIntegrity test failed: Failed to NOT swap the same Block!\n");
        passed = false;
    }

    // Swap two allocated Blocks
    createHiddenFile(hiddenFat, "file1", time(NULL));
    const char *test1Buffer = "My file1";
    stgfs_write("/file1", test1Buffer, 9, 0, (struct fuse_file_info *) hiddenFat);

    createHiddenFile(hiddenFat, "file2", time(NULL));
    const char *test2Buffer = "My file2";
    stgfs_write("/file2", test2Buffer, 9, 0, (struct fuse_file_info *) hiddenFat);
    swapResult = swapHiddenClusters(hiddenFat, 0, 1);
    fflush(stdout);
    fflush(stderr);
    if (!swapResult || strcmp(hiddenFat->clusters[0].file->filename, "file2") != 0
        || strcmp(hiddenFat->clusters[1].file->filename, "file1") != 0) {
        printf("testSwapHiddenClustersIntegrity test failed: Failed to swap two Blocks!\n");
        fflush(stdout);
        passed = false;
    }

    if (!checkIntegrity(hiddenFat)) {
        printf("testSwapHiddenClustersIntegrity test failed: Integrity check failed!.\n");
        fflush(stdout);
        passed = false;
    }

    // Swapping a free block with an allocated block
    createHiddenFile(hiddenFat, "file3", time(NULL));
    const char *test3Buffer = "My file3";
    stgfs_write("/file3", test3Buffer, 9, 0, (struct fuse_file_info *) hiddenFat);

    //swapResult = swapHiddenClusters(hiddenFat, 2, 3);
    if (!swapResult || strcmp(hiddenFat->clusters[2].file->filename, "file3") != 0) {
        printf("testSwapHiddenClustersIntegrity test failed: Failed to swap a free block with an allocated block.\n");
        passed = false;
    }

    if (!checkIntegrity(hiddenFat)) {
        printf("testSwapHiddenClustersIntegrity test failed: Integrity check failed!.\n");
        passed = false;
    }


    // Swapping a free block with a defect block
    hiddenFat->clusters[4].state = defect;
    swapResult = swapHiddenClusters(hiddenFat, 4, 5);
    if (swapResult || hiddenFat->clusters[4].state != defect) {
        printf("testSwapHiddenClustersIntegrity test failed: Failed to NOT swap a free block with a defect block.\n");
        passed = false;
    }

    if (!checkIntegrity(hiddenFat)) {
        printf("testSwapHiddenClustersIntegrity test failed: Integrity check failed!.\n");
        passed = false;
    }

    // Swapping a free block with a reserved block
    hiddenFat->clusters[6].state = reserved;
    swapResult = swapHiddenClusters(hiddenFat, 6, 7);
    if (swapResult || hiddenFat->clusters[6].state != reserved) {
        printf("testSwapHiddenClustersIntegrity test failed: Failed to NOT swap a free block with a defect block.\n");
        passed = false;
    }

    if (!checkIntegrity(hiddenFat)) {
        printf("testSwapHiddenClustersIntegrity test failed: Integrity check failed!.\n");
        passed = false;
    }

    // Swapping two free blocks!
    swapResult = swapHiddenClusters(hiddenFat, 8, 9);
    if (swapResult) {
        printf("testSwapHiddenClustersIntegrity test failed: Failed to NOT swap two free blocks!\n");
        passed = false;
    }

    if (!checkIntegrity(hiddenFat)) {
        printf("testSwapHiddenClustersIntegrity test failed: Integrity check failed!.\n");
        passed = false;
    }

    // Swapping a free block with a defect block
    createHiddenFile(hiddenFat, "file4", time(NULL));
    const char *test4Buffer = "My file4";
    stgfs_write("/file4", test2Buffer, 9, 0, (struct fuse_file_info *) hiddenFat);
    size_t bIndex = findFileByPath(hiddenFat ,"/file4")->hiddenCluster->bIndex;
    swapResult = swapHiddenClusters(hiddenFat, 0, 1);

    hiddenFat->clusters[10].state = reserved;

    swapResult = swapHiddenClusters(hiddenFat, 10, 11);

    if (swapResult || strcmp(hiddenFat->clusters[bIndex].file->filename, "file4") != 0 ||
        hiddenFat->clusters[10].state != reserved) {
        printf("testSwapHiddenClustersIntegrity test failed: Failed to NOT swap a free block with a defect block\n");
        passed = false;
    }

    if (!checkIntegrity(hiddenFat)) {
        printf("testSwapHiddenClustersIntegrity test failed: Integrity check failed!.\n");
        passed = false;
    }

    freeHiddenFat(hiddenFat);
    return passed;
}

bool testDefragmentation() {
    // Create a valid file
    HiddenFat *hiddenFat = createHiddenFat(48, 4);

    HiddenFile **hiddenFile = createHiddenFile(hiddenFat, "cats.gif", time(NULL));
    if (hiddenFile == NULL) {
        printf("testDefragmentation test failed: createFile failed and returned NULL.\n");
        return false;
    }
    const char *catBuffer = "cat0cat1";
    stgfs_write("/cats.gif", catBuffer, strlen(catBuffer) + 1, 0, (struct fuse_file_info *) hiddenFat);

    hiddenFile = createHiddenFile(hiddenFat, "dog.gif", time(NULL));
    if (hiddenFile == NULL) {
        printf("testDefragmentation test failed: createFile failed and returned NULL.\n");
        return false;
    }
    const char *dogBuffer = "dog";
    stgfs_write("/dog.gif", dogBuffer, strlen(dogBuffer) + 1, 0, (struct fuse_file_info *) hiddenFat);

    hiddenFile = createHiddenFile(hiddenFat, "birds.gif", time(NULL));
    if (hiddenFile == NULL) {
        printf("testDefragmentation test failed: createFile failed and returned NULL.\n");
        return false;
    }
    const char *birdBuffer = "bird0bird1";
    stgfs_write("/birds.gif", birdBuffer, strlen(birdBuffer) + 1, 0, (struct fuse_file_info *) hiddenFat);

    showHiddenFat(hiddenFat, NULL);
    char output[20];
    memset(output, 0, 20);
    stgfs_read("/cats.gif", output, strlen(catBuffer) + 1, 0, (struct fuse_file_info *) hiddenFat);
    printf("Printing result of stgfs_read: %s\n", output);
    memset(output, 0, 20);
    stgfs_read("/birds.gif", output, strlen(birdBuffer) + 1, 0, (struct fuse_file_info *) hiddenFat);
    printf("Printing result of stgfs_read: %s\n", output);

    HiddenFile *dog = findFileByPath(hiddenFat, "/dog.gif");
    HiddenFile *cat = findFileByPath(hiddenFat, "/cats.gif");
    HiddenFile *bird = findFileByPath(hiddenFat, "/birds.gif");

    size_t a = 0, b = 0;
    srand(time(NULL));

    // shuffle blocks 1000 times
    for(size_t i = 0; i < 1000; i++) {
        a = rand() % 12;
        b = rand() % 12;
        swapHiddenClusters(hiddenFat, a, b);
    }

    // delete a file
    deleteHiddenFile(hiddenFat, "dog.gif");

    // shuffle again
    for(size_t i = 0; i < 1000; i++) {
        a = rand() % 12;
        b = rand() % 12;
        swapHiddenClusters(hiddenFat, a, b);
    }


    memset(output, 0, 20);
    stgfs_read("/cats.gif", output, strlen(catBuffer) + 1, 0, (struct fuse_file_info *) hiddenFat);
    printf("Printing result of stgfs_read: %s\n", output);
    memset(output, 0, 20);
    stgfs_read("/birds.gif", output, strlen(birdBuffer) + 1, 0, (struct fuse_file_info *) hiddenFat);
    printf("Printing result of stgfs_read: %s\n", output);
    showHiddenFat(hiddenFat, NULL);
    checkForDefragmentation(hiddenFat);
    defragmentate(hiddenFat);
    showHiddenFat(hiddenFat, NULL);
    checkForDefragmentation(hiddenFat);

    memset(output, 0, 20);
    stgfs_read("/cats.gif", output, strlen(catBuffer) + 1, 0, (struct fuse_file_info *) hiddenFat);
    printf("Printing result of stgfs_read: %s\n", output);
    memset(output, 0, 20);
    stgfs_read("/birds.gif", output, strlen(birdBuffer) + 1, 0, (struct fuse_file_info *) hiddenFat);
    printf("Printing result of stgfs_read: %s\n", output);
    bool integrity = checkIntegrity(hiddenFat);
    freeHiddenFat(hiddenFat);
    return integrity;
}

bool testWriteRead(int argc, char **argv) {
    HiddenFat *hiddenFat = createHiddenFat(BLOCK_SIZE * 4, BLOCK_SIZE);
    const char *hiddenFilename = "test.txt";
    long timestamp = time(NULL);
    HiddenFile **hiddenFile = createHiddenFile(hiddenFat, hiddenFilename, timestamp);
    if (hiddenFile == NULL) {
        printf("testWrite test failed: createHiddenFile failed and returned NULL.\n");
        return false;
    }
    const char *testBuffer = "My testbuffer!";
    int bytesWritten = stgfs_write("/test.txt", testBuffer, 15, 0, (struct fuse_file_info *) hiddenFat);
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
    stgfs_read("/test.txt", output, 15, 0, (struct fuse_file_info *) hiddenFat);
    printf("Printing result of stgfs_read: %s\n", output);
    return checkIntegrity(hiddenFat);
}

bool testRamdiskloader() {
    HiddenFat *hiddenFat = createHiddenFat(BLOCK_SIZE * 4, BLOCK_SIZE);
    const char *hiddenFilename = "test.txt";
    long timestamp = time(NULL);
    HiddenFile **hiddenFile = createHiddenFile(hiddenFat, hiddenFilename, timestamp);
    if (hiddenFile == NULL) {
        printf("testRamdiskloader test failed: createHiddenFile failed and returned NULL.\n");
        return false;
    }
    const char *testBuffer = "My testbuffer!";
    int bytesWritten = stgfs_write("/test.txt", testBuffer, 15, 0, (struct fuse_file_info *) hiddenFat);
    if (bytesWritten < 0) {
        printf("testRamdiskloader test failed: Errorcode: %d\n", bytesWritten);
        return false;
    }
    steganofs_unload_ramdisk(hiddenFat);
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
            testCreateFileLinkedList(),
            testDeleteFileValid(),
            testDeleteFileNonExistent(),
            testDeleteFileWithClusters(),
            testShowNBlockFat(1, 23),
            testShowNBlockFat(239, 504),
            testShowNBlockFat(240, 507),
            testShowNBlockFat(241, 509),
            testShowNBlockFat(242, 509),
            testWriteRead(argc, argv),
            testSwapHiddenClustersIntegrity(),
            testDefragmentation(),
            testRamdiskloader(),
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

int test_fuse(int argc, char **argv) {
    HiddenFat *hiddenFat = createHiddenFat(BLOCK_SIZE * 100000, BLOCK_SIZE);
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
    return fuse_main(argc, argv, &fuseOperations, hiddenFat);
}

int main(int argc, char **argv) {
    runTests(argc, argv);
    return 0;//test_fuse(argc, argv);
}