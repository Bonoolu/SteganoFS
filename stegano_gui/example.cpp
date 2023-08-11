#include "example.h"

void Example::example() {
    SteganoFsAdapter steganoFsAdapter("/example/path/to/pictures");
    steganoFsAdapter.loadRamdisk();
    float fragmentation = steganoFsAdapter.getFragmentationInPercent();
    std::cout << "Fragmentation: " << fragmentation << "%" << std::endl;
}
