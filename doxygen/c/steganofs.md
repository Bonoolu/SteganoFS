# steganofs.h

This file contains function declarations and structures related to the SteganoFS FUSE filesystem.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`FUSE_USE_VERSION`](#group__steganofs_1ga0919197af2e154da2c05727b6d87cbda)            | 
`define `[`STEGANOFS_AMOUNT_ROOT_FILES`](#group__steganofs_1ga64489b1f57cc01f9f3c21efeca50a378)            | 
`define `[`STEGANOFS_BLOCK_SIZE`](#group__steganofs_1ga5d1366b576fa580404ac8d71a08b1edf)            | 
`define `[`STEGANOFS_MAX_FILENAME_LENGTH`](#group__steganofs_1ga68f6206a38c0ef043621c9b9bad4aa87)            | 
`define `[`STEGANOFS_DEBUG`](#group__steganofs_1ga1d29d564950eefc26873cb8565fd5263)            | 
`public int `[`stgfs_getattr`](#group__steganofs_1ga4df3c6bd301e91ab34cf3f4e4a144d93)`(const char * path,struct stat * stbuf,`[`__attribute__`](#group__ramdiskloader_1ga43c18e3e8d026268ff2a4e80b6e37c9d)((unused))` struct fuse_file_info * fi)`            | 
`public int `[`stgfs_readdir`](#group__steganofs_1gab2dbcbcc171e6a1f10b99ea011889176)`(const char * path,void * buf,fuse_fill_dir_t filler,off_t offset,struct fuse_file_info * fi,enum fuse_readdir_flags flags)`            | 
`public int `[`stgfs_create`](#group__steganofs_1gadedceaf3ad9001890fbcc9a94c98f924)`(const char * path,mode_t mode,struct fuse_file_info * fi)`            | 
`public int `[`stgfs_write`](#group__steganofs_1gacb33aea88c4f73aa0bad5573746388cd)`(const char * path,const char * buf,size_t size,off_t offset,struct fuse_file_info * fi)`            | 
`public int `[`stgfs_read`](#group__steganofs_1ga6b7c2a0044567c0db507ed39bd6bc5f8)`(const char * path,char * buf,size_t size,off_t offset,struct fuse_file_info * fi)`            | 
`public int `[`stgfs_unlink`](#group__steganofs_1ga0643a2df6935c5f72d555234b0764043)`(const char * path)`            | 
`public int `[`stgfs_statfs`](#group__steganofs_1ga9f96362e4deea6e70e4b0d6411581a7b)`(`[`__attribute__`](#group__ramdiskloader_1ga43c18e3e8d026268ff2a4e80b6e37c9d)((unused))` const char * path,struct statvfs * stbuf)`            | 
`public struct `[`HiddenFat`](#structHiddenFat)` * `[`steganofs_create_new_ramdisk`](#group__steganofs_1gaa81009db58c5f4fca772082eaa247e6a)`(size_t disk_size)`            | Create a new RAM disk for SteganoFS.
`public size_t `[`steganofs_format`](#group__steganofs_1ga2d260be3e7055645cfd50fe72e45d1c2)`(const char * stegano_image_folder)`            | Formats a new SteganoFS Filesystem into an imagefolder.
`public struct `[`HiddenFat`](#structHiddenFat)` * `[`steganofs_load_ramdisk`](#group__steganofs_1ga7022eec647ed52c0002408d4e62aca39)`(const char * stegano_image_folder)`            | Load a SteganoFS RAM disk from an image folder.
`public bool `[`steganofs_unload_ramdisk`](#group__steganofs_1ga232a931e6eec402c4a7128a156ea2e63)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * stegano_folder)`            | Unload a SteganoFS RAM disk to an image folder.
`public bool `[`steganofs_mount`](#group__steganofs_1ga7caab2f11f17e63ca323bca9566d1779)`(struct `[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * mnt_point)`            | Mount a SteganoFS RAM disk to a mount point.
`public bool `[`steganofs_umount`](#group__steganofs_1ga3dd49e298c2132b283578ea0c27f0cfc)`(const char * mnt_point)`            | Unmount a SteganoFS RAM disk from a mount point.
`public void `[`steganofs_show_fragmentation`](#group__steganofs_1gaae5148742d37fc5acc1aabd3dda5df1b)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,char * output_message)`            | Display fragmentation information of a SteganoFS RAM disk.
`public size_t `[`steganofs_fragmentation_array`](#group__steganofs_1ga6955400d2773e0cfb6e06101648debd6)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t ** array)`            | Get an array of fragmentation information for a SteganoFS RAM disk.
`public bool `[`steganofs_check_integrity`](#group__steganofs_1gaf6a900eaf9bef00c45c6b0461438eb3e)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Check the integrity of a SteganoFS RAM disk.
`public float `[`steganofs_defragmentation_percent`](#group__steganofs_1gae49425d025ea3dbb8c12075419eb7e53)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Calculate the defragmentation percentage for a SteganoFS RAM disk.
`public void `[`steganofs_defragmentate_filesystem`](#group__steganofs_1gad42e3a83dd715bf8dce2264852cb563e)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Defragment a SteganoFS RAM disk.

## Members

#### `define `[`FUSE_USE_VERSION`](#group__steganofs_1ga0919197af2e154da2c05727b6d87cbda) 

#### `define `[`STEGANOFS_AMOUNT_ROOT_FILES`](#group__steganofs_1ga64489b1f57cc01f9f3c21efeca50a378) 

#### `define `[`STEGANOFS_BLOCK_SIZE`](#group__steganofs_1ga5d1366b576fa580404ac8d71a08b1edf) 

#### `define `[`STEGANOFS_MAX_FILENAME_LENGTH`](#group__steganofs_1ga68f6206a38c0ef043621c9b9bad4aa87) 

#### `define `[`STEGANOFS_DEBUG`](#group__steganofs_1ga1d29d564950eefc26873cb8565fd5263) 

#### `public int `[`stgfs_getattr`](#group__steganofs_1ga4df3c6bd301e91ab34cf3f4e4a144d93)`(const char * path,struct stat * stbuf,`[`__attribute__`](#group__ramdiskloader_1ga43c18e3e8d026268ff2a4e80b6e37c9d)((unused))` struct fuse_file_info * fi)` 

#### `public int `[`stgfs_readdir`](#group__steganofs_1gab2dbcbcc171e6a1f10b99ea011889176)`(const char * path,void * buf,fuse_fill_dir_t filler,off_t offset,struct fuse_file_info * fi,enum fuse_readdir_flags flags)` 

#### `public int `[`stgfs_create`](#group__steganofs_1gadedceaf3ad9001890fbcc9a94c98f924)`(const char * path,mode_t mode,struct fuse_file_info * fi)` 

#### `public int `[`stgfs_write`](#group__steganofs_1gacb33aea88c4f73aa0bad5573746388cd)`(const char * path,const char * buf,size_t size,off_t offset,struct fuse_file_info * fi)` 

#### `public int `[`stgfs_read`](#group__steganofs_1ga6b7c2a0044567c0db507ed39bd6bc5f8)`(const char * path,char * buf,size_t size,off_t offset,struct fuse_file_info * fi)` 

#### `public int `[`stgfs_unlink`](#group__steganofs_1ga0643a2df6935c5f72d555234b0764043)`(const char * path)` 

#### `public int `[`stgfs_statfs`](#group__steganofs_1ga9f96362e4deea6e70e4b0d6411581a7b)`(`[`__attribute__`](#group__ramdiskloader_1ga43c18e3e8d026268ff2a4e80b6e37c9d)((unused))` const char * path,struct statvfs * stbuf)` 

#### `public struct `[`HiddenFat`](#structHiddenFat)` * `[`steganofs_create_new_ramdisk`](#group__steganofs_1gaa81009db58c5f4fca772082eaa247e6a)`(size_t disk_size)` 

Create a new RAM disk for SteganoFS.

#### Parameters
* `disk_size` The size of the RAM disk in bytes. 

#### Returns
A pointer to the created [HiddenFat](#structHiddenFat) structure, or NULL on failure.

#### `public size_t `[`steganofs_format`](#group__steganofs_1ga2d260be3e7055645cfd50fe72e45d1c2)`(const char * stegano_image_folder)` 

Formats a new SteganoFS Filesystem into an imagefolder.

#### Parameters
* `stegano_image_folder` The path to the folder containing the image. 

#### Returns
The size of the new filesystem. zero if fails.

#### `public struct `[`HiddenFat`](#structHiddenFat)` * `[`steganofs_load_ramdisk`](#group__steganofs_1ga7022eec647ed52c0002408d4e62aca39)`(const char * stegano_image_folder)` 

Load a SteganoFS RAM disk from an image folder.

#### Parameters
* `stegano_image_folder` The path to the folder containing the image. 

#### Returns
A pointer to the loaded [HiddenFat](#structHiddenFat) structure, or NULL on failure.

#### `public bool `[`steganofs_unload_ramdisk`](#group__steganofs_1ga232a931e6eec402c4a7128a156ea2e63)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * stegano_folder)` 

Unload a SteganoFS RAM disk to an image folder.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure to unload. 

* `stegano_folder` The path to the folder where the image will be saved. 

#### Returns
True if successful, false otherwise.

#### `public bool `[`steganofs_mount`](#group__steganofs_1ga7caab2f11f17e63ca323bca9566d1779)`(struct `[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * mnt_point)` 

Mount a SteganoFS RAM disk to a mount point.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure to mount. 

* `mnt_point` The path to the mount point. 

#### Returns
True if successful, false otherwise.

#### `public bool `[`steganofs_umount`](#group__steganofs_1ga3dd49e298c2132b283578ea0c27f0cfc)`(const char * mnt_point)` 

Unmount a SteganoFS RAM disk from a mount point.

#### Parameters
* `mnt_point` The path to the mount point. 

#### Returns
True if successful, false otherwise.

#### `public void `[`steganofs_show_fragmentation`](#group__steganofs_1gaae5148742d37fc5acc1aabd3dda5df1b)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,char * output_message)` 

Display fragmentation information of a SteganoFS RAM disk.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `output_message` A pointer to the message buffer to store the output.

#### `public size_t `[`steganofs_fragmentation_array`](#group__steganofs_1ga6955400d2773e0cfb6e06101648debd6)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t ** array)` 

Get an array of fragmentation information for a SteganoFS RAM disk.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `array` A pointer to the variable where the fragmentation array will be stored. 

#### Returns
The number of entries in the fragmentation array.

#### `public bool `[`steganofs_check_integrity`](#group__steganofs_1gaf6a900eaf9bef00c45c6b0461438eb3e)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Check the integrity of a SteganoFS RAM disk.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

#### Returns
True if the RAM disk is intact, false otherwise.

#### `public float `[`steganofs_defragmentation_percent`](#group__steganofs_1gae49425d025ea3dbb8c12075419eb7e53)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Calculate the defragmentation percentage for a SteganoFS RAM disk.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

#### Returns
The percentage of fragmentation that can be defragmented.

#### `public void `[`steganofs_defragmentate_filesystem`](#group__steganofs_1gad42e3a83dd715bf8dce2264852cb563e)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Defragment a SteganoFS RAM disk.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure.

