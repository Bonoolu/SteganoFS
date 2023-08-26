#ifndef _RUNLENGTHENCODING_H_
#define _RUNLENGTHENCODING_H_

/**
 * @file runlengthencoding.h
 * @brief This file contains function declarations related to run-length encoding and decoding of serialized filesystems.
 * @defgroup runlengthencoding.h
 * This file contains function declarations related to run-length encoding and decoding of serialized filesystems.
 * @{
 */

#include "ramdiskloader.h"

typedef struct SerializedFilesystem SerializedFilesystem;

/**
 * @brief Run-length encodes a serialized filesystem.
 *
 * This function performs run-length encoding on the provided serialized filesystem.
 * It replaces consecutive zero bytes with a range specification for efficient storage.
 *
 * @param serialized_filesystem A pointer to the serialized filesystem structure to be encoded.
 */
void run_length_encoding (struct SerializedFilesystem *serialized_filesystem);

/**
 * @brief Run-length decodes a serialized filesystem.
 *
 * This function performs run-length decoding on a previously run-length encoded serialized filesystem.
 * It reconstructs the original data by expanding the zero ranges specified during encoding.
 *
 * @param serialized_filesystem A pointer to the serialized filesystem structure to be decoded.
 */
void run_length_decoding (struct SerializedFilesystem *serialized_filesystem);
/** @} */
#endif //_RUNLENGTHENCODING_H_
