#ifndef _HIDDENFILE_H_
#define _HIDDENFILE_H_

#include "hiddenfat.h"
#include <errno.h>

typedef struct HiddenFat HiddenFat;
typedef struct HiddenCluster HiddenCluster;
typedef struct HiddenFile HiddenFile;

struct HiddenFile {
    size_t filesize;
    size_t real_filesize;
    long timestamp;
    HiddenCluster *hiddenCluster;
    char filename[12];
};

int delete_hidden_file (HiddenFat *hidden_fat, const char *filename);

int count_path_components (const char *path);

HiddenFile *find_file_by_path (HiddenFat *hidden_fat, const char *path);

HiddenFile **create_hidden_file (HiddenFat *hidden_fat, const char *filename, long timestamp);

#endif //_HIDDENFILE_H_