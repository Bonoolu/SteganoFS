#include "example.h"

void Example::example() {
    SteganoFsAdapter steganoFsAdapter("/home/minaboo/filesystem.steganofs");
    steganoFsAdapter.createNewFilesystem(5120000);
    steganoFsAdapter.writeFilesystemToSteganoProvider();
    // Erstelle einene Zweiten SteganoAdapter
    SteganoFsAdapter NEUERsteganoAdapter("/home/minaboo/filesystem.steganofs");
    NEUERsteganoAdapter.loadFilesytemFromSteganoProvider();

    float fragmentation = NEUERsteganoAdapter.getFragmentationInPercent();
    std::cout << "Fragmentation: " << fragmentation << "%" << std::endl;
    NEUERsteganoAdapter.defragmentateFilesystem();
}
