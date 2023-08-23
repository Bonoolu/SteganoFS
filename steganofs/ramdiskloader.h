#ifndef _RAMDISKLOADER_H_
#define _RAMDISKLOADER_H_

/**
 * @file ramdiskloader.h
 * @brief This file contains the structures and function declarations for RAM disk loading and serialization.
 */

#include "hiddencluster.h"
#include "hiddenfat.h"
#include "hiddenfile.h"

/**
 * @struct HiddenFile
 * @brief Represents a hidden file in the hidden FAT filesystem.
 */
typedef struct HiddenFat HiddenFat;

/**
 * @struct HiddenCluster
 * @brief Structure representing a hidden cluster.
 */
typedef struct HiddenCluster HiddenCluster;

/**
 * @struct HiddenFile
 * @brief Represents a hidden file in the hidden FAT filesystem.
 */

typedef struct HiddenFile HiddenFile;

/**
 * @brief Represents a packed cluster for serialization.
 */
typedef struct PackedCluster PackedCluster;

/**
 * @brief Represents a packed file for serialization.
 */
typedef struct PackedFile PackedFile;

/**
 * @brief Represents a packed FAT structure for serialization.
 */
typedef struct PackedFat PackedFat;

/**
 * @brief Represents a packed FAT structure for serialization.
 */
struct __attribute__((__packed__)) PackedFat {
    u_int16_t block_size; /**< Size of a disk block in bytes. */
    u_int64_t amount_blocks; /**< Total number of blocks in the RAM disk. */
    u_int32_t clusters_offset; /**< Offset to the packed cluster data within the serialized data. */
    u_int32_t files_offset; /**< Offset to the packed file data within the serialized data. */
    u_int8_t amount_root_files; /**< Number of root files in the filesystem. */
    u_int32_t disk_offset; /**< Offset to the disk data within the serialized data. */
};

/**
 * @brief Represents a packed cluster for serialization.
 */
struct __attribute__((__packed__)) PackedCluster {
    u_int64_t b_index;
    u_int16_t cluster_index;
    u_int8_t state;
    int64_t prev_cluster_b_index;
    int64_t next_cluster_b_index;
};

/**
 * @brief Represents a packed file for serialization.
 */
struct __attribute__((__packed__)) PackedFile {
    u_int64_t filesize;
    u_int64_t real_filesize;
    u_int32_t timestamp;
    int64_t hidden_cluster_b_index;
    char filename[12];
};

/**
 * @struct SerializedFilesystem
 * @brief Represents a serialized filesystem that holds the serialized data.
 */
struct SerializedFilesystem {
    size_t size; /**< Size of the serialized data in bytes. */
    bool rle; /**< Flag if the Fielsystem is compressed with Run-Length Encoding flag. */
    unsigned char *buf; /**< Pointer to the serialized data buffer. */
};

/**
 * @brief Serializes a HiddenFat structure into a SerializedFilesystem structure.
 *
 * This function takes a HiddenFat structure and converts it into a serialized representation
 * suitable for storage or transmission.
 *
 * @param hidden_fat A pointer to the HiddenFat structure.
 * @return A SerializedFilesystem structure containing the serialized data.
 */
struct SerializedFilesystem serialize_filesystem (HiddenFat *hidden_fat);

/**
 * @brief Loads a RAM disk from a serialized filesystem data.
 *
 * This function takes a SerializedFilesystem structure containing serialized data and reconstructs
 * a HiddenFat structure representing the RAM disk filesystem.
 *
 * @param serialized_filesystem The SerializedFilesystem structure containing the serialized data.
 * @return A pointer to the loaded HiddenFat structure, or NULL if loading fails.
 */
HiddenFat *load_ramdisk (struct SerializedFilesystem serialized_filesystem);

#endif //_RAMDISKLOADER_H_