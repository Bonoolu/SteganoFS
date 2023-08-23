#ifndef _RAW_PROVIDER_H_
#define _RAW_PROVIDER_H_

/**
 * @file raw_provider.h
 * @brief Header file for raw data steganography provider.
 */

#include "../stegano_file.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Reads raw data from a file.
 *
 * This function reads raw data from a file and encapsulates it in a SteganoFile structure.
 *
 * @param path Path to the file containing raw data to be read.
 * @return SteganoFile structure containing the read payload data.
 */
struct SteganoFile read_raw (const char *path);

/**
 * @brief Writes raw data to a file.
 *
 * This function writes raw payload data to a file.
 *
 * @param stegano_file The SteganoFile structure containing payload data to be written.
 * @return The number of payload bytes successfully written.
 */
size_t write_raw (struct SteganoFile);

#endif //_RAW_PROVIDER_H_
