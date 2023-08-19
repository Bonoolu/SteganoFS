#include "runlengthencoding.h"

void run_length_encoding(struct SerializedFilesystem serialFilesystem) {
    if (serialFilesystem.rle) {
        return;
    }
    size_t readIndex = 0;
    size_t writeIndex = 0;
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
        if (serialFilesystem.buf[readIndex] == 0) {
            zeroCount++;
            if (zeroCount == 1) {
                zeroRanges->offsetFrom = readIndex;
            }

            serialFilesystem.buf[writeIndex++] = serialFilesystem.buf[readIndex];

            if (zeroCount >= 9 && (readIndex == serialFilesystem.size - 1 || serialFilesystem.buf[readIndex + 1] != 0)) {
                zeroRanges->offsetTo = readIndex;
                zeroRanges->next = malloc(sizeof(struct LinkedList));
                memset(zeroRanges->next, 0, sizeof(struct LinkedList));
                zeroRanges = zeroRanges->next;
            }
        } else {
            zeroCount = 0;
            serialFilesystem.buf[writeIndex++] = serialFilesystem.buf[readIndex];
        }

        readIndex++;
    }

    while (zeroCount > 0 && zeroCount <= 9) {
        serialFilesystem.buf[writeIndex++] = 0;
        zeroCount--;
    }

    if (zeroCount >= 9) {
        zeroRanges->offsetTo = readIndex - 1; // End of range
        (rangesCount)++;
    }
    size_t buffer_length = writeIndex;
    size_t buffer_full_length = buffer_length + (rangesCount * 2 * 8) + 8;
    unsigned char * new_buffer = malloc(buffer_full_length);
    struct LinkedList *zero_ranges_end = zeroRanges;
    zeroRanges = zeroRangesBegin;
    size_t writeIndexNewBuffer = 0;
    while (zeroRanges != zero_ranges_end) {
        new_buffer[writeIndexNewBuffer] = zeroRanges->offsetFrom;
        new_buffer[writeIndexNewBuffer + 4] = zeroRanges->offsetTo;
        writeIndexNewBuffer += 4;
        zeroRanges = zeroRanges->next;
    }
    new_buffer[writeIndexNewBuffer] = 0;
    writeIndexNewBuffer += 4;
    memcpy(new_buffer + writeIndexNewBuffer, serialFilesystem.buf, writeIndex);
    free(serialFilesystem.buf);
    serialFilesystem.buf = new_buffer;
    serialFilesystem.size = buffer_full_length;
}