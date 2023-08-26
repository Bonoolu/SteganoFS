#ifndef _BMP_PROVIDER_H_
#define _BMP_PROVIDER_H_

/**
 * @file bmp_provider.h
 * @brief Header file for BMP steganography provider.
 * @defgroup bmp_provider.h
 * Header file for BMP steganography provider.
 * @{
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../stegano_file.h"

/**
 * @brief Extracts payload data from a generic buffer.
 *
 * This function extracts payload data from a generic buffer containing steganographic data.
 *
 * @param payload_buffer Pointer to the pointer that will hold the extracted payload data. This buffer is on the heap
 * and needs to get freed with free() by the caller of this function
 * @param payload_length Pointer to the variable that will hold the length of the extracted payload.
 * @param data Pointer to the buffer containing steganographic data.
 * @param data_length Length of the steganographic data buffer.
 */
void exract_payload_from_generic_buffer (unsigned char **payload_buffer, size_t *payload_length,
                                         const unsigned char *data, size_t data_length);

/**
 * @brief Embeds payload data into a generic buffer.
 *
 * This function embeds payload data into a generic buffer for steganography.
 *
 * @param payload_buffer Pointer to the payload data buffer to be embedded.
 * @param payload_length Length of the payload data.
 * @param data Pointer to the buffer where payload will be embedded.
 */
void embedd_payload_in_generic_buffer (const unsigned char *payload_buffer, size_t payload_length, unsigned char *data);

/**
 * @brief Extracts payload from steganographic pixel data.
 *
 * This function extracts payload data from steganographic pixel data.
 *
 * @param stegano_file Pointer to the SteganoFile structure holding payload information. The payload buffer
 * inside SteganoFile is allocated on the heap and needs to get freed with free() by the caller of this
 * function
 * and needs to get freed with free() by the caller of this function
 * @param pixeldata Pointer to the steganographic pixel data.
 * @param pixel_data_length Length of the steganographic pixel data.
 */
void extract_payload (struct SteganoFile *stegano_file, const unsigned char *pixeldata, size_t pixel_data_length);

/**
 * @brief Embeds payload into steganographic pixel data.
 *
 * This function embeds payload data into steganographic pixel data.
 *
 * @param stegano_file The SteganoFile structure containing payload information.
 * @param pixeldata Pointer to the steganographic pixel data.
 * @param pixel_data_length Length of the steganographic pixel data.
 * @return The number of payload bytes successfully embedded.
 */
size_t embedd_payload (struct SteganoFile stegano_file, unsigned char *pixeldata, size_t pixel_data_length);

/**
 * @brief Reads BMP file and extracts payload data.
 *
 * This function reads a BMP file, extracts pixel data, and extracts payload data from it.
 *
 * @param path Path to the BMP file to be read.
 * @return SteganoFile structure containing extracted payload data. The payload buffer
 * inside SteganoFile is allocated on the heap and needs to get freed with free() by the caller of this
 * function
 * and needs to get freed with free() by the caller of this function
 */
struct SteganoFile read_bmp (const char *path);

/**
 * @brief Writes BMP file with embedded payload data.
 *
 * This function writes a BMP file with embedded payload data.
 *
 * @param stegano_file The SteganoFile structure containing payload data.
 * @return The number of payload bytes successfully written.
 */
size_t write_bmp (struct SteganoFile);
/** @} */
#endif // _BMP_PROVIDER_H_
