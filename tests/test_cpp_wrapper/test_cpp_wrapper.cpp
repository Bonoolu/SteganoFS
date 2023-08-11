#include "../../cpp-wrapper/SteganoFsAdapter.h"

int main(int argc, char **argv) {
    SteganoFsAdapter steganoFsAdapter("/Path/to/Pictures/");
    // load filesystem into memory (this is where the )
    steganoFsAdapter.loadRamdisk();
    steganoFsAdapter.getFilesystemVector();
    // create file

    steganoFsAdapter.mount("/home/admin/test_mnt");
    steganoFsAdapter.umount();
    steganoFsAdapter.unloadRamdisk();
    return 0;
}
