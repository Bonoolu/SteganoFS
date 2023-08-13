#include "example.h"

void Example::example() {
    SteganoFsAdapter steganoFsAdapter("/example/path/to/pictures");
    steganoFsAdapter.formatNewRamdisk(5120000);
    float fragmentation = steganoFsAdapter.getFragmentationInPercent();
    std::cout << "Fragmentation: " << fragmentation << "%" << std::endl;
}
