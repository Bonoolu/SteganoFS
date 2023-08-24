#ifndef _STEGANOFS_H_
#define _STEGANOFS_H_

/**
 * @file steganofs.h
 * @brief This file contains function declarations and structures related to the SteganoFS FUSE filesystem.
 */

#ifndef __cplusplus

#define FUSE_USE_VERSION 31
#define STEGANOFS_AMOUNT_ROOT_FILES 16
#define STEGANOFS_BLOCK_SIZE 512
#define STEGANOFS_MAX_FILENAME_LENGTH 12
#define STEGANOFS_DEBUG

#include <fuse3/fuse.h>
#include <errno.h>
#include "hiddenfat.h"
#include "hiddenfile.h"
#include "hiddencluster.h"
#include "ramdiskloader.h"
#include "runlengthencoding.h"
#include "stegano_providers/stegano_provider.h"

int stgfs_getattr (const char *path, struct stat *stbuf, __attribute__((unused)) struct fuse_file_info *fi);

int stgfs_readdir (const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi,
                   enum fuse_readdir_flags flags);

int stgfs_create (const char *path, mode_t mode, struct fuse_file_info *fi);

int stgfs_write (const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi);

int stgfs_read (const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi);

int stgfs_unlink (const char *path);

int stgfs_statfs (__attribute__((unused)) const char *path, struct statvfs *stbuf);

extern struct fuse_operations fuse_operations;

#endif

#ifdef __cplusplus
extern "C" {
/** @defgroup steg_structs Structures
* Structures used in SteganoFS.
* @{
*/
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
#endif

/** @} */

/** @defgroup steg_functions Functions
 * Function declarations for SteganoFS.
 * @{
 */

/**
 * @brief Create a new RAM disk for SteganoFS.
 *
 * @param disk_size The size of the RAM disk in bytes.
 * @return A pointer to the created HiddenFat structure, or NULL on failure.
 */
struct HiddenFat *steganofs_create_new_ramdisk (size_t disk_size);

/**
 * @brief Formats a new SteganoFS Filesystem into an imagefolder.
 *
 * @param stegano_image_folder The path to the folder containing the image.
 * @return The size of the new filesystem. zero if fails.
 */
size_t steganofs_format (const char *stegano_image_folder);

/**
 * @brief Load a SteganoFS RAM disk from an image folder.
 *
 * @param stegano_image_folder The path to the folder containing the image.
 * @return A pointer to the loaded HiddenFat structure, or NULL on failure.
 */
struct HiddenFat *steganofs_load_ramdisk (const char *stegano_image_folder);

/**
 * @brief Unload a SteganoFS RAM disk to an image folder.
 *
 * @param hidden_fat A pointer to the HiddenFat structure to unload.
 * @param stegano_folder The path to the folder where the image will be saved.
 * @return True if successful, false otherwise.
 */
bool steganofs_unload_ramdisk (HiddenFat *hidden_fat, const char *stegano_folder);

/**
 * @brief Mount a SteganoFS RAM disk to a mount point.
 *
 * @param hidden_fat A pointer to the HiddenFat structure to mount.
 * @param mnt_point The path to the mount point.
 * @return True if successful, false otherwise.
 */
bool steganofs_mount (struct HiddenFat *hidden_fat, const char *mnt_point);

/**
 * @brief Unmount a SteganoFS RAM disk from a mount point.
 *
 * @param mnt_point The path to the mount point.
 * @return True if successful, false otherwise.
 */
bool steganofs_umount (const char *mnt_point);

/**
 * @brief Display fragmentation information of a SteganoFS RAM disk.
 *
 * @param hidden_fat A pointer to the HiddenFat structure.
 * @param output_message A pointer to the message buffer to store the output.
 */
void steganofs_show_fragmentation (HiddenFat *hidden_fat, char *output_message);

/**
 * @brief Get an array of fragmentation information for a SteganoFS RAM disk.
 *
 * @param hidden_fat A pointer to the HiddenFat structure.
 * @param array A pointer to the variable where the fragmentation array will be stored.
 * @return The number of entries in the fragmentation array.
 */
size_t steganofs_fragmentation_array (HiddenFat *hidden_fat, size_t **array);

/**
 * @brief Check the integrity of a SteganoFS RAM disk.
 *
 * @param hidden_fat A pointer to the HiddenFat structure.
 * @return True if the RAM disk is intact, false otherwise.
 */
bool steganofs_check_integrity (HiddenFat *hidden_fat);

/**
 * @brief Calculate the defragmentation percentage for a SteganoFS RAM disk.
 *
 * @param hidden_fat A pointer to the HiddenFat structure.
 * @return The percentage of fragmentation that can be defragmented.
 */
float steganofs_defragmentation_percent (HiddenFat *hidden_fat);

/**
 * @brief Defragment a SteganoFS RAM disk.
 *
 * @param hidden_fat A pointer to the HiddenFat structure.
 */
void steganofs_defragmentate_filesystem (HiddenFat *hidden_fat);

#ifdef __cplusplus
}
#endif

/** @} */
#endif // _STEGANOFS_H_