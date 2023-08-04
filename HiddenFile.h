#ifndef STEGANOFS_HIDDENFILE_H
#define STEGANOFS_HIDDENFILE_H

#include "hiddenFat.h"

typedef struct HiddenFat HiddenFat;
typedef struct HiddenCluster HiddenCluster;
typedef struct HiddenFile HiddenFile;

struct HiddenFile {
    const char *filename;
    size_t filesize;
    size_t real_filesize;
    long timestamp;
    HiddenCluster *hiddenCluster;
};

void deleteHiddenFile(HiddenFat *hiddenFat, const char *filename);
int countPathComponents(const char *path);
HiddenFile *findFileByPath(HiddenFat *hiddenFat, const char* path);
HiddenFile **createHiddenFile(HiddenFat *hiddenFat, const char *filename, long timestamp);

#endif //STEGANOFS_HIDDENFILE_H
