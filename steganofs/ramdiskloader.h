#ifndef _RAMDISKLOADER_H_
#define _RAMDISKLOADER_H_

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
    u_int16_t block_size;
    u_int64_t amount_blocks;
    u_int32_t clusters_offset;
    u_int32_t files_offset;
    u_int8_t amount_root_files;
    u_int32_t disk_offset;
};

struct __attribute__((__packed__)) PackedCluster {
    u_int64_t b_index;
    u_int16_t cluster_index;
    u_int8_t state;
    int64_t prev_cluster_b_index;
    int64_t next_cluster_b_index;
};

struct __attribute__((__packed__)) PackedFile {
    u_int64_t filesize;
    u_int64_t real_filesize;
    u_int32_t timestamp;
    int64_t hidden_cluster_b_index;
    char filename[12];
};

struct SerializedFilesystem {
    size_t size;
    bool rle;
    unsigned char *buf;
};

struct SerializedFilesystem serialize_filesystem (HiddenFat *hidden_fat);

HiddenFat *load_ramdisk (struct SerializedFilesystem serialized_filesystem);

#endif //_RAMDISKLOADER_H_