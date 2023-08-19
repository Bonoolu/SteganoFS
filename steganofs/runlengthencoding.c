#include "runlengthencoding.h"

void run_length_encoding(struct SerializedFilesystem serialFilesystem) {
    if (serialFilesystem.rle) {
        return;
    }
    size_t readIndex = 0;
    size_t writeIndex = 0;
    size_t dataBlockBegin = 0;
    size_t zeroCount = 0;
    size_t rangesCount = 0;

    struct LinkedList {
        uint64_t offsetFrom;
        uint64_t offsetTo;
        struct LinkedList *next;
    };

    struct LinkedList linkedList;

    struct LinkedList *zeroRangesBegin = &linkedList;
    struct LinkedList *zeroRanges = &linkedList;
    while (readIndex < serialFilesystem.size) {
        unsigned char *currentReadPointer = serialFilesystem.buf + readIndex;
        if (serialFilesystem.buf[readIndex] == 0) {
            zeroCount++;
            if (zeroCount == 1) {
                zeroRanges->offsetFrom = readIndex;
            } else {
                zeroRanges->offsetTo = readIndex;
            }
        } else {
            if (zeroCount > 16) {
                printf("Copying over bytes %zu to %zu  (%zu bytes)\n", dataBlockBegin, zeroRanges->offsetFrom, zeroRanges->offsetFrom - dataBlockBegin);
                unsigned char *moveFrom = serialFilesystem.buf + dataBlockBegin;
                unsigned char *moveTo = serialFilesystem.buf + writeIndex;
                size_t moveSize = zeroRanges->offsetFrom - dataBlockBegin;
                memmove(moveTo, moveFrom, moveSize);
                writeIndex += moveSize;
                dataBlockBegin = readIndex;
                rangesCount++;
                zeroRanges->offsetTo = readIndex;
                zeroRanges->next = malloc(sizeof(struct LinkedList));
                memset(zeroRanges->next, 0, sizeof(struct LinkedList));
                zeroRanges = zeroRanges->next;
            }
            zeroCount = 0;
        }
        readIndex++;
    }

    if (dataBlockBegin != 0) {
        printf("Datablock begin was: %zu. Copying over %zu bytes\n", dataBlockBegin, serialFilesystem.size - dataBlockBegin);
        for (size_t i = dataBlockBegin; i < serialFilesystem.size; i++) {
            serialFilesystem.buf[writeIndex++] = serialFilesystem.buf[readIndex++];
        }
    }

    size_t buffer_length = writeIndex;
    size_t header_length =  (rangesCount * 2 * 8) + 8;
    printf("Allocated %zu + %zu = %zu bytes!\n", buffer_length, header_length, buffer_length + header_length);
    unsigned char * new_buffer = malloc(buffer_length + header_length);
    struct LinkedList *zero_ranges_end = zeroRanges;
    zeroRanges = zeroRangesBegin;
    size_t writeIndexNewBuffer = 0;
    while (zeroRanges != zero_ranges_end) {
        new_buffer[writeIndexNewBuffer] = zeroRanges->offsetFrom;
        new_buffer[writeIndexNewBuffer + 8] = zeroRanges->offsetTo;
        printf("From: %zu, To: %zu\n", zeroRanges->offsetFrom,zeroRanges->offsetTo);
        writeIndexNewBuffer += 16;
        zeroRanges = zeroRanges->next;
    }
    new_buffer[writeIndexNewBuffer] = 0;
    writeIndexNewBuffer += 8;
    printf("Wrote %zu Bytes as header to buffer!\n", writeIndexNewBuffer);
    printf("Wrote %zu Bytes as Data.\n", buffer_length);
    memcpy(new_buffer + writeIndexNewBuffer, serialFilesystem.buf, buffer_length);
    free(serialFilesystem.buf);
    serialFilesystem.buf = new_buffer;
    serialFilesystem.size = buffer_length + header_length;
    serialFilesystem.rle = true;
}

void run_length_decoding(struct SerializedFilesystem serializedFilesystem) {
    if (!serializedFilesystem.rle) {
        return;
    }

}