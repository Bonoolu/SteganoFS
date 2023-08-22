#include "../../steganofs/steganofs.h"
#include "../../steganofs/stegano_providers/bmp/bmp_provider.h"
#include "../../steganofs/stegano_providers/stegano_file.h"

bool test_generic_buffer(){
    unsigned char bufferFF[17] = "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
                                 "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF";
    unsigned char buffer00[17] = "\x00\x00\x00\x00\x00\x00\x00"
                                 "\x00\x00\x00\x00\x00\x00\x00";
    const size_t length = 16;
    unsigned char *extractedBuffer = NULL;
    size_t extractedLength = 0;

    exract_payload_from_generic_buffer(&extractedBuffer, &extractedLength, bufferFF, length);
    printf("The exracted bytes are %d and %d\n", extractedBuffer[0], extractedBuffer[1]);

    unsigned char payload[2] = {54, 27};
    size_t payloadLength = 2;

    embedd_payload_in_generic_buffer(payload, payloadLength, buffer00, length);

    printf("Buffer with payload:\n");
    for (size_t i = 0; i < length; i ++) {
        printf("%d", buffer00[i]);
        if (i == 7 || i == 15) {
            printf("\n");
        }else {
            printf(", ");
        }
    }
    return true;
}

bool test_single_bmp_file () {
    HiddenFat *hiddenFat = createHiddenFat(10,2);
    createHiddenFile(hiddenFat, "test.txt", time(NULL));
    unsigned char testbuffer[4] = "abc";
    stgfs_write("/test.txt", (char*) testbuffer, 4, 0, (struct fuse_file_info *) hiddenFat);
    steganofs_unload_ramdisk(hiddenFat, "example.bmp");
    freeHiddenFat(hiddenFat);
    hiddenFat = steganofs_load_ramdisk("example.bmp");
    if (!hiddenFat){
        printf("Could not load anything from example.bmp\n");
        return false;
    }
    if (!checkIntegrity(hiddenFat)) {
        printf("Failed to check integrity of filesystem which was embedded in BMP File!\n");
        return false;
    }
    showHiddenFat(hiddenFat, NULL);
    printf("Passed test successfully!\n");
    return true;
}

bool test_bmp_folder () {
    HiddenFat *hiddenFat = createHiddenFat(STEGANOFS_BLOCK_SIZE * 100, BLOCK_SIZE);
    const char *hiddenFilename = "test.txt";
    long timestamp = time(NULL);
    HiddenFile **hiddenFile = createHiddenFile(hiddenFat, hiddenFilename, timestamp);
    if (hiddenFile == NULL) {
        printf("test_bmp_folder test failed: createHiddenFile failed and returned NULL.\n");
        return false;
    }
    const char *testBuffer = "My testbuffer!";
    int bytesWritten = stgfs_write("/test.txt", testBuffer, 15, 0, (struct fuse_file_info *) hiddenFat);
    if (bytesWritten < 0) {
        printf("test_bmp_folder test failed: createHiddenFile failed. Errorcode: %d\n", bytesWritten);
        return false;
    }

    hiddenFilename = "test2.txt";
    hiddenFile = createHiddenFile(hiddenFat, hiddenFilename, timestamp);
    if (hiddenFile == NULL) {
        printf("test_bmp_folder test failed: createHiddenFile failed and returned NULL.\n");
        return false;
    }
    testBuffer = "My testbuffer2!";
    bytesWritten = stgfs_write("/test2.txt", testBuffer, 16, 0, (struct fuse_file_info *) hiddenFat);
    if (bytesWritten < 0) {
        printf("test_bmp_folder test failed: createHiddenFile failed. Errorcode: %d\n", bytesWritten);
        return false;
    }
    showHiddenFat(hiddenFat, NULL);
    bool ret = steganofs_unload_ramdisk(hiddenFat, "example_pictures");
    if (!ret) {
        printf("test_bmp_folder test failed: Unloading ramdisk failed!\n");
        return false;
    }
    freeHiddenFat(hiddenFat);
    hiddenFat = steganofs_load_ramdisk("example_pictures");
    if (hiddenFat == NULL) {
        printf("test_bmp_folder test failed: Loading ramdisk failed!\n");
        return false;
    }
    ret = steganofs_unload_ramdisk(hiddenFat, "example_pictures");
    if (!ret) {
        printf("test_bmp_folder test failed: Unloading ramdisk failed!\n");
        return false;
    }
    showHiddenFat(hiddenFat, NULL);
    ret = checkIntegrity(hiddenFat);
    if (!ret) {
        printf("test_bmp_folder test failed: Integrity check failed!\n");
        return false;
    }
    freeHiddenFat(hiddenFat);
    return ret;
}

int main() {
    int tests[] = {
            test_generic_buffer(),
            test_single_bmp_file(),
            test_bmp_folder(),
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