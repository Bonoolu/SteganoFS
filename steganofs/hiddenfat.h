#ifndef _HIDDENFAT_H_
#define _HIDDENFAT_H_

#include "hiddencluster.h"
#include "steganofs.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
 * @struct HiddenFat
 * @brief Structure representing a hidden FAT filesystem.
 */
struct HiddenFat {
    size_t block_size; /**< Size of a block in bytes. */
    size_t amount_blocks; /**< Total number of blocks in the filesystem. */
    unsigned char *disk; /**< Pointer to the disk data. */
    HiddenCluster *clusters; /**< Pointer to an array of HiddenCluster structures. */
    HiddenFile *files[STEGANOFS_AMOUNT_ROOT_FILES]; /**< Array of pointers to HiddenFile structures. */
};

/**
 * @brief Creates a new hidden FAT filesystem.
 *
 * @param disk_size The total size of the disk in bytes.
 * @param block_size The size of each block in bytes.
 * @return A pointer to the newly created HiddenFat structure, or NULL on failure.
 */
HiddenFat *create_hidden_fat (size_t disk_size, size_t block_size);

/**
 * @brief Frees the memory associated with a hidden FAT filesystem.
 *
 * @param hidden_fat A pointer to the HiddenFat structure to be freed.
 */
void free_hidden_fat (HiddenFat *hidden_fat);

/**
 * @brief Gets the amount of entries (files and directories) in a given path.
 *
 * @param hidden_fat A pointer to the HiddenFat structure.
 * @param path The path to the directory to be checked.
 * @return The amount of entries in the directory.
 */
size_t get_amount_entries (HiddenFat *hidden_fat, const char *path);

/**
 * @brief Gets the amount of free disk space in bytes in the hidden FAT filesystem.
 *
 * @param hidden_fat A pointer to the HiddenFat structure.
 * @return The amount of free disk space in bytes.
 */
size_t get_free_disk_space (HiddenFat *hidden_fat);

/**
 * @brief Shows the structure of the hidden FAT filesystem.
 *
 * @param hidden_fat A pointer to the HiddenFat structure.
 * @param output_message If not NULL, the output will be copied to this string.
 */
void show_hidden_fat (HiddenFat *hidden_fat, char *output_message);

/**
 * @brief Checks the integrity of the hidden FAT filesystem.
 *
 * @param hidden_fat A pointer to the HiddenFat structure.
 * @return True if the filesystem has integrity, false otherwise.
 */
bool check_integrity (HiddenFat *hidden_fat);

/**
 * @brief Checks the filesystem for fragmentation and calculates the fragmentation percentage.
 *
 * @param hidden_fat A pointer to the HiddenFat structure.
 * @return The fragmentation percentage.
 */
float check_for_fragmentation (HiddenFat *hidden_fat);

/**
 * @brief Defragments the hidden FAT filesystem.
 *
 * @param hidden_fat A pointer to the HiddenFat structure.
 */
void defragmentate (HiddenFat *hidden_fat);

/**
 * @brief Writes data to a block in the hidden FAT filesystem.
 *
 * @param hidden_fat A pointer to the HiddenFat structure.
 * @param b_index The index of the block to write to.
 * @param buffer The buffer containing the data to be written.
 * @param offset The offset within the block to start writing.
 * @param length The length of data to be written.
 * @return The number of bytes written, or -1 on failure.
 */
int write_block (HiddenFat *hidden_fat, size_t b_index, const char *buffer, size_t offset, size_t length);

/**
 * @brief Reads data from a block in the hidden FAT filesystem.
 *
 * @param hidden_fat A pointer to the HiddenFat structure.
 * @param b_index The index of the block to read from.
 * @param buffer The buffer to store the read data.
 * @param offset The offset within the block to start reading.
 * @param length The length of data to be read.
 * @return The number of bytes read, or -1 on failure.
 */
int read_block (HiddenFat *hidden_fat, size_t b_index, const char *buffer, size_t offset, size_t length);

/**
 * @brief Gets an array indicating the fragmentation status of blocks in the hidden FAT filesystem.
 *
 * @param hidden_fat A pointer to the HiddenFat structure.
 * @param array A pointer to an array that will be allocated to hold the fragmentation data. This array is allocated on
 * the heap an can freed with free() by the caller of this function
 * @return The total number of blocks in the filesystem.
 */
size_t get_fragmentation_array (HiddenFat *hidden_fat, size_t **array);

#endif //_HIDDENFAT_H_
