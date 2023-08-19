#include "bmp_provider.h"

void extract_payload(struct SteganoFile *steganoFile, const unsigned char *pixeldata, size_t pixel_data_length) {
    steganoFile->payload_length = pixel_data_length / 8;
    steganoFile->payload = malloc(steganoFile->payload_length);
    memset(steganoFile->payload, 0, steganoFile->payload_length);
    for(size_t i = 0; i < steganoFile->payload_length; i++) {
        steganoFile->payload[i] = 0xFF;
        for (size_t bit = 0; bit < 8; bit++) {
            steganoFile->payload[i] &= ((pixeldata[(i * 8) + bit] & 0x01) << bit);
        }
    }
}

void embedd_payload(struct SteganoFile *steganoFile, unsigned char *pixeldata, size_t pixel_data_length) {
    for(size_t i = 0; i < steganoFile->payload_length; i++) {
        unsigned char byteToWrite = steganoFile->payload[i];
        for (size_t bitIndex = 0; bitIndex < 8; bitIndex++) {
            unsigned char currentBit = pixeldata[(i * 8) + bitIndex] & 0x01;
            unsigned char bitToWrite = (byteToWrite >> bitIndex) & 0x01;
            if (bitToWrite != currentBit) {
                pixeldata[(i * 8) + bitIndex] ^= 1;
            }
        }
    }
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

bool write_bmp(struct SteganoFile steganoFile) {
    FILE *file = fopen(steganoFile.path, "rb");
    if (file) {
        fseek(file, 0L, SEEK_END);
        size_t pixel_data_length = ftell(file) - 36;
        rewind(file);
        fseek(file, 36, 0);
        unsigned char *pixeldata = malloc(pixel_data_length);
        if (pixeldata == NULL) {
            return false;
        }
        fread(pixeldata, pixel_data_length, 1, file);
        embedd_payload(&steganoFile, pixeldata, pixel_data_length);
        rewind(file);
        fseek(file, 36, 0);
        size_t bytes_written = fwrite(pixeldata, pixel_data_length, 1, file);
        fflush(file);
        fclose(file);
        return bytes_written == 1;
    }
    return false;
}


