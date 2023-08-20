#include "../../steganofs/steganofs.h"

int main() {
    HiddenFat *hiddenFat = createHiddenFat(10,2);
    createHiddenFile(hiddenFat, "test.txt", time(NULL));
    unsigned char testbuffer[4] = "abc";
    stgfs_write("/test.txt", (char*) testbuffer, 4, 0, (struct fuse_file_info *) hiddenFat);
    steganofs_unload_ramdisk(hiddenFat, "/tmp/example.bmp");
    return 0;
}