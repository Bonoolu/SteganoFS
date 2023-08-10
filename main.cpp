#include "SteganoFsAdapter.h"

int main() {
    SteganoFsAdapter steganoFsAdapter("/Path/to/Pictures/");
    steganoFsAdapter.loadRamdisk();
    steganoFsAdapter.getFilesystemVector();
    //steganoFsAdapter.mount("/home/admin/test_mnt");
    //steganoFsAdapter.umount();
    //steganoFsAdapter.unloadRamdisk();
    return 0;
}
