#ifndef STEGANOFS_MAIN_STEGANO_FILE_H
#define STEGANOFS_MAIN_STEGANO_FILE_H

/**
 * @file stegano_file.h
 * @brief Header file defining the SteganoFile structure.
 * @defgroup stegano_file.h
 * Header file defining the SteganoFile structure.
 * @{
 */

#include <stdio.h>

/**
 * @struct SteganoFile
 * @brief Structure to hold steganography-related file data.
 */
struct SteganoFile {
    char *path; /**< Path to the stegano file. */
    //FILE *file;
    unsigned char *payload; /**< Pointer to the payload data. */
    size_t payload_length; /**< Length of the payload data. */
};
/** @} */
#endif //STEGANOFS_MAIN_STEGANO_FILE_H
