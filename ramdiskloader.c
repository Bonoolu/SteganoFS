#include "ramdiskloader.h"

void calculateSizeOnDisk(){
    printf("PackedFat:\t%zu Bytes\nPackedCluster:\t%zu Bytes\nPackedFile:\t%zu\n", sizeof(PackedFat), sizeof(PackedCluster), sizeof(PackedFile));
}