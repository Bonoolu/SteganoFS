#include "../../cpp-wrapper/SteganoFsAdapter.h"

int main(int argc, char **argv) {
    SteganoFsAdapter steganoFsAdapter("/tmp/filesystem.bin");
    steganoFsAdapter.loadRamdisk();
    steganoFsAdapter.getFilesystemVector();
    steganoFsAdapter.mount("/home/admin/test_mnt");
    steganoFsAdapter.umount();
    steganoFsAdapter.unloadRamdisk();
    return 0;
}
