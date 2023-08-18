#include "../../steganofs/ramdiskloader.h"

struct SerializedFilesystem read_bmp(const char *path);
bool write_bmp(struct SerializedFilesystem serializedFilesystem, const char *path);
static