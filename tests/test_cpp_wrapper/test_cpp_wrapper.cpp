#include <iostream>
#include "../../cpp-wrapper/SteganoFsAdapter.h"

int main(int argc, char **argv) {
    SteganoFsAdapter steganoFsAdapter("/tmp/filesystem.bin");
    //steganoFsAdapter.loadRamdisk();
    bool status = steganoFsAdapter.formatNewRamdisk(5120000);
    if (!status) {
        std::cout << "Creating new Ramdisk failed!" << std::endl;
    }
    std::vector<size_t> vector = steganoFsAdapter.getFilesystemVector();
    if (vector.empty()) {
        std::cout << "Getting Filesystemvector failed, is empty!" << std::endl;
    }
    status = steganoFsAdapter.mount("/home/admin/test_mnt");
    if (!status) {
        std::cout << "Mounting to /home/admin/test_mnt failed!" << std::endl;
    }
    status = steganoFsAdapter.umount();
    if (!status) {
        std::cout << "Unmounting to /home/admin/test_mnt failed!" << std::endl;
    }
    status = steganoFsAdapter.unloadRamdisk();
    if (!status) {
        std::cout << "Unloading Ramdisk failed!" << std::endl;
    }
    return 0;
}
