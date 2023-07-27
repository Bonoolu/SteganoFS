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

#define AMOUNT_FILES 10

typedef struct BsCluster BsCluster;
typedef struct BsFile BsFile;
typedef struct BsBlock BsBlock;
typedef struct BsFat BsFat;

struct BsCluster {
    BsCluster *prev;
    BsCluster *next;
    size_t clusterIndex;
    size_t fileIndex;
    unsigned int bIndex;
};

struct BsFile {
    const char *filename;
    size_t filesize;
    long timestamp;
    BsCluster *pCluster;
};

struct BsBlock {
    size_t bIndex;
    unsigned int state;
    BsCluster *cluster;
};

enum State {
    free_ = 0, reserved = 1, defect = 2, allocated = 3
};

struct BsFat {
    size_t blockSize;
    size_t amountBlocks;
    unsigned char *disk;
    BsBlock *blocks;
    BsFile *files[AMOUNT_FILES];
};

BsFat *createBsFat(size_t diskSize, size_t blockSize);
void freeBsFat(BsFat *pFat);
size_t getAmountEntries(BsFat *pFat, const char* path);
size_t getFreeDiskSpace(BsFat *pFat);
//void readBlock(BsFat *pFat, size_t bIndex, unsigned char* buffer);
void deleteFile(BsFat *pFat, const char *filename);
void showFat(BsFat *pFat, char* outputMessage);
bool checkIntegrity(BsFat *pFat);
bool swapBlocks(BsFat *pFat, size_t bIndexA, size_t bIndexB);
void checkForDefragmentation(BsFat *pFat);
void defragmentate(BsFat *pFat);
int count_path_components(const char *path);
BsFile *findFileByPath(BsFat *pFat, const char* path);
int stegFS_getattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi);
int stegFS_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi, enum fuse_readdir_flags flags);
BsFile **createFile(BsFat *pFat, const char *filename, long timestamp);
int stegFS_create(const char *path, mode_t mode, struct fuse_file_info *fi);
int writeBlock(BsFat *pFat, size_t bIndex, unsigned char* buffer, size_t offset, size_t length);
int stegFS_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi);

extern struct fuse_operations stegfs_fuse_oper;
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