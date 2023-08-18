#ifndef __cplusplus
#ifndef STEGANOFS_RAMDISKLOADER_H
#define STEGANOFS_RAMDISKLOADER_H

#include "hiddencluster.h"
#include "hiddenfat.h"
#include "hiddenfile.h"

typedef struct HiddenCluster HiddenCluster;
typedef struct HiddenFile HiddenFile;
typedef struct HiddenFat HiddenFat;

typedef struct PackedCluster PackedCluster;
typedef struct PackedFile PackedFile;
typedef struct PackedFat PackedFat;

struct __attribute__((__packed__)) PackedFat {
    u_int16_t blockSize;
    u_int64_t amountBlocks;
    u_int32_t clustersOffset;
    u_int32_t filesOffset;
    u_int8_t amount_root_files;
    u_int32_t diskOffset;
};

struct __attribute__((__packed__)) PackedCluster{
    u_int64_t bIndex;
    u_int16_t clusterIndex;
    u_int8_t state;
    int64_t prevClusterBIndex;
    int64_t nextClusterBIndex;
};

struct __attribute__((__packed__)) PackedFile {
    u_int64_t filesize;
    u_int64_t real_filesize;
    u_int32_t timestamp;
    int64_t hiddenClusterBIndex;
    char filename[12];
};

struct SerializedFilesystem {
    size_t size;
    unsigned char *buf;
};

struct SerializedFilesystem serializeFilesystem(HiddenFat *hiddenFat);

HiddenFat *loadRamdisk(struct SerializedFilesystem serializedFilesystem);

#endif //STEGANOFS_RAMDISKLOADER_H
#endif // __cplusplus
