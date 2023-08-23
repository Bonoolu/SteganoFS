#include "bmp_provider.h"

void exract_payload_from_generic_buffer(unsigned char **payload_buffer, size_t *payloadLength,
                                               const unsigned char *data, size_t dataLength) {
    *payloadLength = dataLength / 8;
    *payload_buffer = malloc(*payloadLength);
    memset(*payload_buffer, 0, *payloadLength);
    for (size_t i = 0; i < *payloadLength; i++) {
        unsigned char *currentByteToWriteTo = (*payload_buffer) + i;
        *currentByteToWriteTo = 0x00;
        for (size_t bit = 0; bit < 8; bit++) {
            unsigned char currentBitToWrite = ((data[(i * 8) + bit] & 0x01));
            *currentByteToWriteTo ^= currentBitToWrite << bit;
        }
    }
}

void extract_payload(struct SteganoFile *steganoFile, const unsigned char *pixeldata, size_t pixel_data_length) {
    exract_payload_from_generic_buffer(&(steganoFile->payload), &steganoFile->payload_length, pixeldata,
                                       pixel_data_length);
}

void embedd_payload_in_generic_buffer(unsigned char *payload_buffer, size_t payloadLength,
                                      unsigned char *data, size_t dataLength) {
    for (size_t i = 0; i < payloadLength; i++) {
        unsigned char byteToWrite = payload_buffer[i];
        for (size_t bitIndex = 0; bitIndex < 8; bitIndex++) {
            unsigned char currentBit = data[(i * 8) + bitIndex] & 0x01;
            unsigned char bitToWrite = (byteToWrite >> bitIndex) & 0x01;
            if (bitToWrite != currentBit) {
                data[(i * 8) + bitIndex] ^= 1;
            }
        }
    }
}

size_t embedd_payload(struct SteganoFile steganoFile, unsigned char *pixeldata, size_t pixel_data_length) {
    if (pixel_data_length / 8 < steganoFile.payload_length) {
        steganoFile.payload_length = pixel_data_length / 8;
    }
    embedd_payload_in_generic_buffer(steganoFile.payload, steganoFile.payload_length, pixeldata, pixel_data_length);
    return steganoFile.payload_length;
}

struct SteganoFile read_bmp(const char *path) {
    FILE *file = fopen(path, "rb");
    struct SteganoFile steganoFile = {.payload = NULL, .payload_length = 0};
    if (file) {
        fseek(file, 0L, SEEK_END);
        size_t pixel_data_length = ftell(file) - 36;
        rewind(file);
        fseek(file, 36, 0);
        unsigned char *pixeldata = malloc(pixel_data_length);
        if (pixeldata == NULL) {
            return steganoFile;
        }
        fread(pixeldata, pixel_data_length, 1, file);
        extract_payload(&steganoFile, pixeldata, pixel_data_length);
        fflush(file);
        fclose(file);
    }
    return steganoFile;
}

size_t write_bmp(struct SteganoFile steganoFile) {
    FILE *file = fopen(steganoFile.path, "rb");
    if (file) {
        fseek(file, 0L, SEEK_END);
        size_t pixel_data_length = ftell(file) - 36;
        rewind(file);
        fseek(file, 36, 0);
        unsigned char *pixeldata = malloc(pixel_data_length);
        if (pixeldata == NULL) {
            return 0;
        }
        fread(pixeldata, pixel_data_length, 1, file);
        fflush(file);
        fclose(file);
        size_t payload_written = embedd_payload(steganoFile, pixeldata, pixel_data_length);
        fopen(steganoFile.path, "wb");
        fseek(file, 36, 0);
        size_t bytes_written = fwrite(pixeldata, pixel_data_length, 1, file);
        fflush(file);
        fclose(file);
        return payload_written;
    }
    return 0;
}


