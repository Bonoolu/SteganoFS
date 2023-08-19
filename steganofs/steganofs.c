#include "steganofs.h"

// TODO:
// errorcodes durchleifen und korrekte errorcodes setzten
// debug flag/-d verwenden um stderr etwas zu unterdruecken
// write doxygen

int stgfs_getattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi) {
    HiddenFat *hiddenFat = (HiddenFat *) fuse_get_context()->private_data;

    // Check if the path corresponds to the root directory
    if (strcmp(path, "/") == 0) {
        // Set default values for the root directory
        stbuf->st_mode = S_IFDIR | 0777; // Directory with 755 permissions
        stbuf->st_nlink = 2; // Number of hard links (including . and ..)
        stbuf->st_nlink += getAmountEntries(hiddenFat, path);
        return 0; // Return success
    } else {
        HiddenFile *hiddenFile = findFileByPath(hiddenFat, path);
        if (hiddenFile != NULL) {
            stbuf->st_mode = S_IFREG | 0666; // Regular file with 666 permissions
            stbuf->st_nlink = 1; // Number of hard links (including . and ..)
            stbuf->st_size = (__off_t) hiddenFile->real_filesize;
            stbuf->st_uid = 1000;
            stbuf->st_gid = 1000;


            // Set access time and modification time based on the Unix timestamp
            time_t timestamp = hiddenFile->timestamp;

            // Set access time (st_atim)
            stbuf->st_atim.tv_sec = timestamp;
            stbuf->st_atim.tv_nsec = 0;

            // Set modification time (st_mtim)
            stbuf->st_mtim.tv_sec = timestamp;
            stbuf->st_mtim.tv_nsec = 0;

            return 0;
        }
        return -ENOENT; // ENOENT indicates "No such file or directory"
    }
}

int stgfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi,
                  enum fuse_readdir_flags flags) {
    // Add entries for the root directory
    if (strcmp(path, "/") == 0) {
        filler(buf, "..", NULL, 0, 0);
        filler(buf, ".", NULL, 0, 0);
        HiddenFat *hiddenFat = (HiddenFat *) fuse_get_context()->private_data;
        for (HiddenFile **pFile = hiddenFat->files; pFile < hiddenFat->files + STEGANOFS_AMOUNT_ROOT_FILES; pFile++) {
            if (*pFile != NULL) {
                filler(buf, (*pFile)->filename, NULL, 0, 0);
            }
        }
        return 0;
    }
    return -ENOENT;
}

int stgfs_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
    HiddenFat *hiddenFat = (HiddenFat *) fuse_get_context()->private_data;

    mode = S_IFREG | 0666;
    if (countPathComponents(path) == 1) {
        const char *filename = path + 1;
        HiddenFile **pFile = createHiddenFile(hiddenFat, filename, time(NULL));
        if (pFile != NULL) {
            return 0;
        }
        return -ENOMEM;
    }
    return -ENOENT;
}

int stgfs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    if (countPathComponents(path) != 1) {
        return -ENOENT;
    }
    struct fuse_context *private = fuse_get_context();
    HiddenFat *hiddenFat;
    if (private != NULL) {
        hiddenFat = (HiddenFat *) (private->private_data);
    } else {
#ifdef STEGANOFS_DEBUG
        hiddenFat = (HiddenFat *) fi;
#else
        fprintf(stderr, "Couldn't get fuse context, is null!!\n");
        return -1;
#endif
    }
    HiddenFile *pFile = findFileByPath(hiddenFat, path);
    if (pFile == NULL) {
        return -ENOENT;
    }

    // Check if file is already large enough, if no, allocate
    while (offset + size > pFile->filesize) {
        if (!extendHiddenCluster(hiddenFat, pFile)) {
            return -ENOMEM;
        }
    }
    pFile->real_filesize = offset + size;
    size_t bytesWritten = 0;

    // Find correct clusterblock to write to
    HiddenCluster *hiddenCluster = pFile->hiddenCluster;
    size_t fileOffset = 0;
    int size_signed = (int) size;
    while (size_signed > 0) {
        if (hiddenCluster == NULL) {
            fprintf(stderr,
                    "Tried to write at an offset for a file which is not large enough, did you forget to allocate?");
            return -errno;
        }
        // First we search for the block where the offset is in
        if (fileOffset >= offset) {
            // Next we get the amount of blocks to write
            size_t amountBytesToWrite;
            size_t offsetInsideBlock = offset % hiddenFat->blockSize;
            if (offset + size_signed < fileOffset + hiddenFat->blockSize) {
                amountBytesToWrite = size_signed;
            } else {
                amountBytesToWrite = hiddenFat->blockSize - offsetInsideBlock;
            }
            int written = writeBlock(hiddenFat, hiddenCluster->bIndex, buf, offsetInsideBlock, amountBytesToWrite);
            if (written < 0) {
                return -errno;
            }
            bytesWritten += written;
            if (written != amountBytesToWrite) {
                fprintf(stderr, "Meant to write %zu bytes in Block %zu at block offset %zu (which is disk offset %zu),"
                                " but %d bytes were written!\n", amountBytesToWrite, hiddenCluster->bIndex,
                        offsetInsideBlock, offset, written);
                return -errno;
            }
            offset += (off_t) written;
            buf += written;
            size_signed -= (int) written;
        }
        hiddenCluster = hiddenCluster->next;
        fileOffset += hiddenFat->blockSize;
    }
    return (int) bytesWritten;
}

int stgfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    if (countPathComponents(path) != 1) {
        return -ENOENT;
    }
    struct fuse_context *private = fuse_get_context();
    HiddenFat *hiddenFat;
    if (private != NULL) {
        hiddenFat = (HiddenFat *) (private->private_data);
    } else {
#ifdef STEGANOFS_DEBUG
        hiddenFat = (HiddenFat *) fi;
#else
        fprintf(stderr, "Couldn't get fuse context, is null!!\n");
        return -1;
#endif
    }
    HiddenFile *pFile = findFileByPath(hiddenFat, path);
    if (pFile == NULL) {
        return -ENOENT;
    }

    // Check if we read outside file, if yes try to truncate size var to filesize
    if (offset + size > pFile->filesize) {
        int delta = (int)(pFile->filesize) - (int)(offset);
        if (delta >= 0) {
            size = delta;
        }else { // if even the offset is higher then the filesize, we simply return 0 bytes read
            return 0;
        }
    }
    size_t bytesRead = 0;

    // Find correct clusterblock to write to
    HiddenCluster *hiddenCluster = pFile->hiddenCluster;
    size_t fileOffset = 0;
    int size_signed = (int) size;
    while (size_signed > 0) {
        if (hiddenCluster == NULL) {
            fprintf(stderr,
                    "Tried to write at an offset for a file which is not large enough, did you forget to allocate?");
            return -errno;
        }
        // First we search for the block where the offset is in
        if (fileOffset >= offset) {
            // Next we get the amount of bytes to write
            size_t amountBytesToRead;
            size_t offsetInsideBlock = offset % hiddenFat->blockSize;
            if (offset + size_signed < fileOffset + hiddenFat->blockSize) {
                amountBytesToRead = size_signed;
            } else {
                amountBytesToRead = hiddenFat->blockSize - offsetInsideBlock;
            }
            int read_ = readBlock(hiddenFat, hiddenCluster->bIndex, buf, offsetInsideBlock, amountBytesToRead);
            if (read_ < 0) {
                return -errno;
            }
            bytesRead += read_;
            if (read_ != amountBytesToRead) {
                fprintf(stderr, "Meant to read %zu bytes from Block %zu at block offset %zu (which is disk offset %zu),"
                                " but %d bytes were read!\n", amountBytesToRead, hiddenCluster->bIndex,
                        offsetInsideBlock, offset, read_);
                return -errno;
            }
            offset += (off_t) read_;
            buf += read_;
            size_signed -= (int) read_;
        }
        hiddenCluster = hiddenCluster->next;
        fileOffset += hiddenFat->blockSize;
    }
    return (int) bytesRead;
}

int stgfs_unlink(const char *path) {
    if (countPathComponents(path) != 1) {
        return -ENOENT;
    }
    struct fuse_context *private = fuse_get_context();
    HiddenFat *hiddenFat;
    if (private != NULL) {
        hiddenFat = (HiddenFat *) (private->private_data);
    } else {
        fprintf(stderr, "Couldn't get fuse context, is null!!\n");
        return -1;
    }
    HiddenFile *pFile = findFileByPath(hiddenFat, path);
    if (pFile == NULL) {
        return -ENOENT;
    }
    const char *filename = path + 1;
    return deleteHiddenFile(hiddenFat, filename);
}

int stgfs_statfs(const char *path, struct statvfs *stbuf) {

    if (!stbuf) {
        return -EINVAL;  // Invalid argument
    }

    struct fuse_context *private = fuse_get_context();
    HiddenFat *hiddenFat;
    if (private != NULL) {
        hiddenFat = (HiddenFat *) (private->private_data);
    } else {
        fprintf(stderr, "Couldn't get fuse context, is null!!\n");
        return -1;
    }

    stbuf->f_bsize = hiddenFat->blockSize;    // Filesystem block size
    stbuf->f_frsize = hiddenFat->blockSize;   // Fundamental filesystem block size
    stbuf->f_blocks = hiddenFat->amountBlocks; // Total data blocks in filesystem
    stbuf->f_bfree = getFreeDiskSpace(hiddenFat) / hiddenFat->blockSize;   // Free blocks
    stbuf->f_bavail = getFreeDiskSpace(hiddenFat) / hiddenFat->blockSize;  // Free blocks available to non-superuser
    stbuf->f_namemax = STEGANOFS_MAX_FILENAME_LENGTH;

    return 0; // Success
}

struct fuse_operations fuseOperations = {
        .getattr = stgfs_getattr,
        .readdir = stgfs_readdir,
        .create = stgfs_create,
        .write = stgfs_write,
        .read = stgfs_read,
        .unlink = stgfs_unlink,
        .statfs = stgfs_statfs
};

struct HiddenFat *steganofs_create_new_ramdisk(size_t diskSize) {
    size_t amountBlocks = diskSize / STEGANOFS_BLOCK_SIZE;
    return createHiddenFat(amountBlocks * STEGANOFS_BLOCK_SIZE, STEGANOFS_BLOCK_SIZE);
}

struct HiddenFat *steganofs_load_ramdisk(const char *steganoImageFolder) {
    struct SerializedFilesystem serializedFilesystem = stegano_provider_read(steganoImageFolder);
    if (serializedFilesystem.size == 0) return NULL;
    return loadRamdisk(serializedFilesystem);
}

bool steganofs_unload_ramdisk(struct HiddenFat *hiddenFat, const char *steganoImageFolder) {
    struct SerializedFilesystem serializedFilesystem = serializeFilesystem(hiddenFat);
    if (serializedFilesystem.size == 0) return false;
    //run_length_encoding(serializedFilesystem);
    return stegano_provider_write(serializedFilesystem, steganoImageFolder);
}


bool steganofs_mount(struct HiddenFat *hiddenFat, const char *mnt_point) {
    int argc = 1;
    const char * argv[] = {mnt_point};

    struct fuse_args args = FUSE_ARGS_INIT(argc, (char**) argv);
    struct fuse *fuse_struct = fuse_new(&args, &fuseOperations, sizeof(fuseOperations), hiddenFat);
    if (fuse_struct == NULL) {
        return false;
    }
    int status = fuse_mount(fuse_struct, mnt_point);
    if (status != 0) {
        return false;
    }
    status = fuse_loop(fuse_struct);
    return status == 0;
}

bool steganofs_umount(const char *mnt_point) {
    return umount2(mnt_point, MNT_FORCE) == 0;
}

void steganofs_show_fragmentation(HiddenFat *hiddenFat, char *outputMessage) {
    showHiddenFat(hiddenFat, outputMessage);
}

size_t steganofs_fragmentation_array(HiddenFat *hiddenFat, size_t **array) {
    return getFragmentationArray(hiddenFat, array);
}

bool steganofs_check_integrity(HiddenFat *hiddenFat) {
    return checkIntegrity(hiddenFat);
}

float steganofs_defragmentation_percent(HiddenFat *hiddenFat) {
    return checkForFragmentation(hiddenFat);
}

void steganofs_defragmentate_filesystem(HiddenFat *hiddenFat) {
    defragmentate(hiddenFat);
}

///**
// * @brief Open a file.
// *
// * @param path The path to the file.
// * @param fi A pointer to the fuse_file_info structure containing information about the file.
// * @return 0 on success, or a negative value on failure.
// */
//static int stegFS_open(const char *path, struct fuse_file_info *fi);
//
///**
// * @brief Create a new directory.
// *
// * @param path The path to the new directory.
// * @param mode The directory mode/permissions.
// * @return 0 on success, or a negative value on failure.
// */
//static int stegFS_mkdir(const char *path, mode_t mode);
//


