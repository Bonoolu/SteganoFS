#ifndef _HIDDENCLUSTER_H_
#define _HIDDENCLUSTER_H_

#include <stdbool.h>
#include <stddef.h>

#include "hiddenfat.h"
#include "hiddenfile.h"

typedef struct HiddenFat HiddenFat;
typedef struct HiddenCluster HiddenCluster;
typedef struct HiddenFile HiddenFile;

enum State {
    FREE = 0, RESERVED = 1, DEFECT = 2, ALLOCATED = 3
};

struct HiddenCluster {
    size_t b_index;
    size_t cluster_index;
    unsigned int state;
    HiddenCluster *prev;
    HiddenCluster *next;
    HiddenFile *file;
};

bool swap_hidden_clusters (HiddenFat *hidden_fat, size_t b_index_a, size_t b_index_b);

bool extend_hidden_cluster (HiddenFat *hidden_fat, HiddenFile *p_file);

#endif //_HIDDENCLUSTER_H_