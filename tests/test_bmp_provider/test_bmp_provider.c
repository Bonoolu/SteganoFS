#include "../../steganofs/steganofs.h"
#include "../../steganofs/stegano_providers/bmp/bmp_provider.h"
#include "../../steganofs/stegano_providers/stegano_file.h"

int main() {
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

    struct SteganoFile steganoFile = {.path = "example.bmp", .payload=payload, .payload_length=payloadLength};

    write_bmp(steganoFile);

    HiddenFat *hiddenFat = createHiddenFat(10,2);
    createHiddenFile(hiddenFat, "test.txt", time(NULL));
    unsigned char testbuffer[4] = "abc";
    stgfs_write("/test.txt", (char*) testbuffer, 4, 0, (struct fuse_file_info *) hiddenFat);
    steganofs_unload_ramdisk(hiddenFat, "example.bmp");
    freeHiddenFat(hiddenFat);
    hiddenFat = steganofs_load_ramdisk("example.bmp");
    if (!checkIntegrity(hiddenFat)) {
        printf("Failed to check integrity of filesystem which was embedded in BMP File!\n");
        return -1;
    }
    showHiddenFat(hiddenFat, NULL);
    printf("Passed test successfully!\n");
    return 0;
}