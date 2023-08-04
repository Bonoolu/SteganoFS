#ifndef BSFAT_H
#define BSFAT_H

#define FUSE_USE_VERSION 31

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <fuse3/fuse.h>
#include <errno.h>

#define AMOUNT_ROOT_FILES 10
#define BLOCKSIZE 4096

typedef struct HiddenFile HiddenFile;
typedef struct HiddenCluster HiddenCluster;
typedef struct HiddenFat HiddenFat;

struct HiddenFile {
    const char *filename;
    size_t filesize;
    size_t real_filesize;
    long timestamp;
    HiddenCluster *hiddenCluster;
};

struct HiddenCluster{
    size_t bIndex;
    unsigned int state;
    HiddenCluster *prev;
    HiddenCluster *next;
    size_t clusterIndex;
    HiddenFile *file;
};

enum State {
    free_ = 0, reserved = 1, defect = 2, allocated = 3
};

struct HiddenFat {
    size_t blockSize;
    size_t amountBlocks;
    unsigned char *disk;
    HiddenCluster *clusters;
    HiddenFile *files[AMOUNT_ROOT_FILES];
};

HiddenFat *createHiddenFat(size_t diskSize, size_t blockSize);
void freeHiddenFat(HiddenFat *hiddenFat);
size_t getAmountEntries(HiddenFat *hiddenFat, const char* path);
size_t getFreeDiskSpace(HiddenFat *hiddenFat);
void deleteHiddenFile(HiddenFat *hiddenFat, const char *filename);
void showHiddenFat(HiddenFat *hiddenFat, char* outputMessage);
bool checkIntegrity(HiddenFat *hiddenFat);
bool swapHiddenClusters(HiddenFat *hiddenFat, size_t bIndexA, size_t bIndexB);
void checkForDefragmentation(HiddenFat *hiddenFat);
void defragmentate(HiddenFat *hiddenFat);
int countPathComponents(const char *path);
HiddenFile *findFileByPath(HiddenFat *hiddenFat, const char* path);
int getattrSteganoFS(const char *path, struct stat *stbuf, struct fuse_file_info *fi);
int readdirSteganoFS(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi, enum fuse_readdir_flags flags);
HiddenFile **createHiddenFile(HiddenFat *hiddenFat, const char *filename, long timestamp);
int createSteganoFS(const char *path, mode_t mode, struct fuse_file_info *fi);
bool extendHiddenCluster(HiddenFat *hiddenFat, HiddenFile *hiddenFile);
int writeBlock(HiddenFat *hiddenFat, size_t bIndex, const char* buffer, size_t offset, size_t length);
int writeSteganoFS(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
int readBlock(HiddenFat *hiddenFat, size_t bIndex, const char* buffer, size_t offset, size_t length);
int readSteganoFS(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi);

extern struct fuse_operations fuseOperationsSteagnoFS;
///**
// * @brief Delete a file.
// */
//static int stegFS_unlink(const char *path);
//
///**
// * @brief Delete a directory.
// *
// * @param path The path to the directory to be deleted.
// * @return 0 on success, or a negative value on failure.
// */
//static int stegFS_rmdir(const char *path);
//
///**
// * @brief Rename or move a file or directory.
// *
// * @param oldpath The path to the existing file or directory.
// * @param newpath The path to the new file or directory after renaming/moving.
// * @param flags Flags to control the behavior of the rename operation.
// * @return 0 on success, or a negative value on failure.
// */
//static int stegFS_rename(const char *oldpath, const char *newpath, unsigned int flags);
//
///**
// * @brief Change the size of a file.
// *
// * @param path The path to the file.
// * @param size The new size of the file.
// * @return 0 on success, or a negative value on failure.
// */
//static int stegFS_truncate(const char *path, off_t size);
//
///**
// * @brief Update file timestamps (modification and access time).
// *
// * @param path The path to the file.
// * @param tv An array of two timespec structures representing the new timestamps.
// * @param fi A pointer to the fuse_file_info structure containing information about the file.
// * @return 0 on success, or a negative value on failure.
// */
//static int stegFS_utimens(const char *path, const struct timespec tv[2], struct fuse_file_info *fi);
//
///**
// * @brief Change file permissions.
// *
// * @param path The path to the file.
// * @param mode The new file mode/permissions.
// * @return 0 on success, or a negative value on failure.
// */
//static int stegFS_chmod(const char *path, mode_t mode);
//
///**
// * @brief Change file ownership.
// *
// * @param path The path to the file.
// * @param uid The new user ID (owner) for the file.
// * @param gid The new group ID for the file.
// * @return 0 on success, or a negative value on failure.
// */
//static int stegFS_chown(const char *path, uid_t uid, gid_t gid);
//
///**
// * @brief Get filesystem statistics.
// *
// * @param path The path to the filesystem.
// * @param stbuf A pointer to the struct where the statistics will be stored.
// * @return 0 on success, or a negative value on failure.
// */
//static int stegFS_statfs(const char *path, struct statvfs *stbuf);
//
///**
// * @brief Create a symbolic link.
// *
// * @param target The target path for the symbolic link.
// * @param linkpath The path to the symbolic link to be created.
// * @return 0 on success, or a negative value on failure.
// */
//static int stegFS_symlink(const char *target, const char *linkpath);
//
///**
// * @brief Read the target of a symbolic link.
// *
// * @param path The path to the symbolic link.
// * @param buf A buffer to store the target of the symbolic link.
// * @param size The size of the buffer.
// * @return The number of bytes read on success, or a negative value on failure.
// */
//static int stegFS_readlink(const char *path, char *buf, size_t size);

#endif