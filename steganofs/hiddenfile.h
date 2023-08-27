#ifndef _HIDDENFILE_H_
#define _HIDDENFILE_H_

/**
 * @file hiddenfile.h
 * @brief This file contains the structures and function declarations for hidden file operations.
 * @defgroup hiddenfile.h
 * This file contains the structures and function declarations for hidden file operations.
 * @{
 */

#include "hiddenfat.h"
#include "steganofs.h"
#include <errno.h>

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
 * @struct HiddenFile
 * @brief Represents a hidden file in the hidden FAT filesystem.
 */
struct HiddenFile {
  size_t filesize;
  size_t real_filesize;
  long timestamp;
  HiddenCluster *hiddenCluster;
  char filename[STEGANOFS_MAX_FILENAME_LENGTH];
};

/**
 * @brief Deletes a hidden file from the hidden FAT filesystem.
 *
 * @param hidden_fat A pointer to the HiddenFat structure.
 * @param filename The name of the file to be deleted.
 * @return 0 on success, or -ENOENT if the file was not found.
 */
int delete_hidden_file (HiddenFat *hidden_fat, const char *filename);

/**
 * @brief Counts the number of components in a given path.
 *
 * @param path The path string to be analyzed.
 * @return The number of components in the path.
 */
int count_path_components (const char *path);

/**
 * @brief Finds a hidden file by its path.
 *
 * @param hidden_fat A pointer to the HiddenFat structure.
 * @param path The path of the file to be found.
 * @return A pointer to the HiddenFile structure if found, otherwise NULL.
 */
HiddenFile *find_file_by_path (HiddenFat *hidden_fat, const char *path);

/**
 * @brief Creates a hidden file in the hidden FAT filesystem.
 *
 * @param hidden_fat A pointer to the HiddenFat structure.
 * @param filename The name of the file to be created.
 * @param timestamp The timestamp of the file.
 * @return A pointer to the HiddenFile pointer if created successfully, otherwise NULL.
 */
HiddenFile **create_hidden_file (HiddenFat *hidden_fat, const char *filename, long timestamp);
/** @} */
#endif //_HIDDENFILE_H_