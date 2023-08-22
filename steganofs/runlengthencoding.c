#include "runlengthencoding.h"

void run_length_encoding(struct SerializedFilesystem *serialFilesystem) {
    if (serialFilesystem->rle) {
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
    printf("Previous Disk size: %zu\n", serialFilesystem->size);
    while (readIndex < serialFilesystem->size) {
        unsigned char *currentReadPointer = serialFilesystem->buf + readIndex;
        if (serialFilesystem->buf[readIndex] == 0) {
            zeroCount++;
            if (zeroCount == 1) {
                zeroRanges->offsetFrom = readIndex;
            } else {
                zeroRanges->offsetTo = readIndex;
            }
        } else {
            if (zeroCount > 16) {
                printf("Copying over bytes %zu to %zu  (%zu bytes)\n", dataBlockBegin, zeroRanges->offsetFrom, zeroRanges->offsetFrom - dataBlockBegin);
                unsigned char *moveFrom = serialFilesystem->buf + dataBlockBegin;
                unsigned char *moveTo = serialFilesystem->buf + writeIndex;
                size_t moveSize = zeroRanges->offsetFrom - dataBlockBegin;
                memmove(moveTo, moveFrom, moveSize);
                writeIndex += moveSize;
                dataBlockBegin = readIndex;
                rangesCount++;
                zeroRanges->offsetTo = readIndex;
                zeroRanges->next = malloc(sizeof(struct LinkedList)); // gets freed in the while loop below
                memset(zeroRanges->next, 0, sizeof(struct LinkedList));
                zeroRanges = zeroRanges->next;
            }
            zeroCount = 0;
        }
        readIndex++;
    }

    if (dataBlockBegin != 0) {
        size_t length = serialFilesystem->size - dataBlockBegin;
        unsigned char *moveFrom = serialFilesystem->buf + length;
        unsigned char *moveTo = serialFilesystem->buf + writeIndex;
        memmove(moveTo, moveFrom, length);
        printf("Datablock begin was: %zu. Copying over %zu bytes\n", dataBlockBegin, length);
    }

    size_t buffer_length = writeIndex;
    size_t header_length =  (rangesCount * 2 * 8) + 8;
    printf("Allocated %zu + %zu = %zu bytes!\n", buffer_length, header_length, buffer_length + header_length);
    unsigned char *new_buffer = malloc(buffer_length + header_length); // See free below
    struct LinkedList *zero_ranges_end = zeroRanges;
    zeroRanges = zeroRangesBegin;
    size_t writeIndexNewBuffer = 0;
    while (zeroRanges != zero_ranges_end) {
        *((uint64_t*) &(new_buffer[writeIndexNewBuffer])) = zeroRanges->offsetFrom;
        *((uint64_t*) &(new_buffer[writeIndexNewBuffer + 8])) = zeroRanges->offsetTo;
        printf("From: %zu, To: %zu\n", zeroRanges->offsetFrom,zeroRanges->offsetTo);
        writeIndexNewBuffer += 16;
        struct LinkedList *tmp = zeroRanges;
        zeroRanges = zeroRanges->next;
        if (tmp != zeroRangesBegin) {
            free(tmp);
        }
    }
    new_buffer[writeIndexNewBuffer] = 0;
    writeIndexNewBuffer += 8;
    printf("Wrote %zu Bytes as header to buffer!\n", writeIndexNewBuffer);
    printf("Wrote %zu Bytes as Data.\n", buffer_length);
    memcpy(new_buffer + writeIndexNewBuffer, serialFilesystem->buf, buffer_length);
    free(serialFilesystem->buf);
    serialFilesystem->buf = new_buffer;
    serialFilesystem->size = buffer_length + header_length;
    serialFilesystem->rle = true;
}

void run_length_decoding(struct SerializedFilesystem *serializedFilesystem) {
    if (!serializedFilesystem->rle) {
        return;
    }
    const uint64_t *zeroRanges = (uint64_t*) serializedFilesystem->buf;
    uint64_t *lengthPointer = (uint64_t*) serializedFilesystem->buf;
    size_t amountZerosToPlace = 0;
    while((lengthPointer == zeroRanges || *lengthPointer != 0) && lengthPointer < (uint64_t*) ((serializedFilesystem->buf + serializedFilesystem->size) - 3)) {
        uint64_t from = lengthPointer[0];
        uint64_t to = lengthPointer[1];
        amountZerosToPlace += (to - from);
        lengthPointer += 2;
    }
    const size_t zeroRangesLength = lengthPointer - zeroRanges;
    unsigned char *encodedBuffer = serializedFilesystem->buf + ((zeroRangesLength + 1) * 8);
    size_t encodedBufferLength = serializedFilesystem->size - ((zeroRangesLength + 1) * 8);
    printf("Length of Ranges: %zu\n", zeroRangesLength);
    printf("Amount Zeros to place: %zu\n", amountZerosToPlace);
    printf("Length of DataBuffer: %zu\n", encodedBufferLength);
    printf("Length of decoded Filesystem: %zu\n", encodedBufferLength + amountZerosToPlace);
    size_t decodedFilesystemLength = encodedBufferLength + amountZerosToPlace;
    unsigned char *decodedFilesystem = malloc(decodedFilesystemLength); // See free below
    memset(decodedFilesystem, 0, decodedFilesystemLength);
    lengthPointer = (uint64_t*) zeroRanges;
    unsigned char *readPointer = (unsigned char*) encodedBuffer;
    unsigned char *writePointer = decodedFilesystem;
    while((lengthPointer == zeroRanges || *lengthPointer != 0) && lengthPointer < (uint64_t*) ((serializedFilesystem->buf + serializedFilesystem->size) - 3)) {
        uint64_t from = lengthPointer[0];
        uint64_t to = lengthPointer[1];
        size_t length = from - (writePointer - decodedFilesystem);
        printf("Wrote %zu bytes! to offset:%zu\n", length, writePointer - decodedFilesystem);
        memcpy(writePointer, readPointer, length);
        writePointer = decodedFilesystem + to;
        readPointer += length;
        lengthPointer += 2;
    }
    lengthPointer--;
    if (*lengthPointer < decodedFilesystemLength) {
        printf("Wrote %zu bytes! to offset:%zu\n", decodedFilesystemLength - *lengthPointer, writePointer - decodedFilesystem);
        memcpy(writePointer, readPointer, decodedFilesystemLength - *lengthPointer);
    }
    free(serializedFilesystem->buf);
    serializedFilesystem->buf = decodedFilesystem;
    serializedFilesystem->size = decodedFilesystemLength;
    serializedFilesystem->rle = false;
}
