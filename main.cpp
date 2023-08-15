#include "SteganoFsAdapter.h"

bool fail(const std::string& msg) {
    std::cout << "Step " << msg << " failed!" << std::endl;
    std::cout << "This is bad! Something went wrong! :(" << std::endl;
    exit(-1);
    return false;
}

int main() {
    SteganoFsAdapter steganoFsAdapter("/home/admin/test");
    steganoFsAdapter.createNewFilesystem(512*64) || fail("createFilesystem 1");
    steganoFsAdapter.mount("/home/admin/test_mnt") || fail("mount 1");
    SteganoFsAdapter::statvfs statvfs = steganoFsAdapter.getFilesystemInfo();
    std::vector<size_t> vector = steganoFsAdapter.getFilesystemVector();
    for (size_t b: vector) {
        std::cout << b << ",";
    }
    std::cout << std::endl;
    float fragmentation = steganoFsAdapter.getFragmentationInPercent();
    std::cout << "Fragmentation in Percent: " << fragmentation << std::endl;
    steganoFsAdapter.defragmentateFilesystem() || fail("defragmentateFilesystem 1");
    vector = steganoFsAdapter.getFilesystemVector();
    for (size_t b: vector) {
        std::cout << b << ",";
    }
    std::cout << std::endl;
    fragmentation = steganoFsAdapter.getFragmentationInPercent();
    std::cout << "Fragmentation in Percent: " << fragmentation << std::endl;
    steganoFsAdapter.umount() || fail("mount 1");
    steganoFsAdapter.writeFilesystemToSteganoProvider() || fail("writeFilesystemToSteganoProvider 1");

    steganoFsAdapter.loadFilesystemFromSteganoProvider() || fail("loadFilesystemFromSteganoProvider 2");
    steganoFsAdapter.mount("/home/admin/test_mnt") || fail("mount 2");
    vector = steganoFsAdapter.getFilesystemVector();
    for (size_t b: vector) {
        std::cout << b << ",";
    }
    std::cout << std::endl;
    fragmentation = steganoFsAdapter.getFragmentationInPercent();
    std::cout << "Fragmentation in Percent: " << fragmentation << std::endl;
    steganoFsAdapter.defragmentateFilesystem() || fail("defragmentateFilesystem 2");
    vector = steganoFsAdapter.getFilesystemVector();
    for (size_t b: vector) {
        std::cout << b << ",";
    }
    std::cout << std::endl;
    fragmentation = steganoFsAdapter.getFragmentationInPercent();
    std::cout << "Fragmentation in Percent: " << fragmentation << std::endl;
    steganoFsAdapter.umount() || fail("mount 2");
    steganoFsAdapter.writeFilesystemToSteganoProvider() || fail("writeFilesystemToSteganoProvider 2");

    std::cout << "Everything works!" << std::endl;
    return 0;
}
