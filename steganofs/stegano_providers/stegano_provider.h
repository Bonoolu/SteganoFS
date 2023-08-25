#ifndef _STEGANO_PROVIDER_H_
#define _STEGANO_PROVIDER_H_

/**
 * @file stegano_provider.h
 * @brief Header file for steganography provider selection and operations.
 */

#include "../../steganofs/ramdiskloader.h"
#include "raw/raw_provider.h"
#include "bmp/bmp_provider.h"
#include "stegano_file.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>

/**
 * @typedef ProviderRead
 * @brief Function pointer type for reading data using a specific provider.
 */
typedef struct SteganoFile (*ProviderRead) (const char *);

/**
 * @typedef ProviderWrite
 * @brief Function pointer type for writing data using a specific provider.
 */
typedef size_t (*ProviderWrite) (struct SteganoFile);

/**
 * @struct SteganoProvider
 * @brief Structure to represent a steganography provider and its operations.
 */
struct SteganoProvider {
    const char *extension; /**< File extension associated with the provider. */
    ProviderRead provider_read; /**< Function pointer for reading data using the provider. */
    ProviderWrite provider_write; /**< Function pointer for writing data using the provider. */
};

/**
 * @brief Reads a serialized filesystem from a path using steganography providers.
 *
 * This function reads a serialized filesystem from a path, utilizing appropriate steganography providers.
 *
 * @param path Path to the serialized filesystem data.
 * @return SerializedFilesystem structure containing the read data. * This function allocates heap for buf inside SerializedFilesystem, which can be freed with free() by
 * the caller of this function. This buffer needs to be freed with free() by the caller of this function
 */
struct SerializedFilesystem stegano_provider_read (const char *path);

/**
 * @brief Writes a serialized filesystem to a path using steganography providers.
 *
 * This function writes a serialized filesystem to a path, utilizing appropriate steganography providers.
 *
 * @param serialized_filesystem The SerializedFilesystem structure containing data to be written.
 * @param path Path where the data should be written.
 * @return Returns true if writing is successful, false otherwise.
 */
bool stegano_provider_write (struct SerializedFilesystem serialized_filesystem, const char *path);

#endif //_STEGANO_PROVIDER_H_
