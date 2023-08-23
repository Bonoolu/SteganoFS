#ifndef STEGANOFS_HIDDENCLUSTER_H
#define STEGANOFS_HIDDENCLUSTER_H

#include <stdbool.h>
#include <stddef.h>

#include "hiddenfat.h"
#include "hiddenfile.h"

typedef struct HiddenFat HiddenFat;
typedef struct HiddenCluster HiddenCluster;
typedef struct HiddenFile HiddenFile;

enum State {
    free_ = 0, reserved = 1, defect = 2, allocated = 3
};

struct HiddenCluster {
    size_t bIndex;
    size_t clusterIndex;
    unsigned int state;
    HiddenCluster *prev;
    HiddenCluster *next;
    HiddenFile *file;
};

bool swapHiddenClusters(HiddenFat *hiddenFat, size_t bIndexA, size_t bIndexB);

bool extendHiddenCluster(HiddenFat *hiddenFat, HiddenFile *hiddenFile);

#endif //STEGANOFS_HIDDENCLUSTER_H