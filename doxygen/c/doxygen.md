# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`FUSE_USE_VERSION`](#steganofs_8h_1a0919197af2e154da2c05727b6d87cbda)            | 
`define `[`STEGANOFS_AMOUNT_ROOT_FILES`](#steganofs_8h_1a64489b1f57cc01f9f3c21efeca50a378)            | 
`define `[`STEGANOFS_BLOCK_SIZE`](#steganofs_8h_1a5d1366b576fa580404ac8d71a08b1edf)            | 
`define `[`STEGANOFS_MAX_FILENAME_LENGTH`](#steganofs_8h_1a68f6206a38c0ef043621c9b9bad4aa87)            | 
`define `[`STEGANOFS_DEBUG`](#steganofs_8h_1a1d29d564950eefc26873cb8565fd5263)            | 
`enum `[`State`](#hiddencluster_8h_1a5d74787dedbc4e11c1ab15bf487e61f8)            | Enumeration representing the state of a hidden cluster.
`public bool `[`swap_hidden_clusters`](#hiddencluster_8h_1a1736049385c7bf194f6a0fec32f0f508)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index_a,size_t b_index_b)`            | Swaps two hidden clusters within a hidden FAT.
`public bool `[`extend_hidden_cluster`](#hiddencluster_8h_1a80b5c17506983811bc3cbdee5b84ff3d)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,`[`HiddenFile`](#structHiddenFile)` * p_file)`            | Extends a hidden cluster for a hidden file.
`public `[`HiddenFat`](#structHiddenFat)` * `[`create_hidden_fat`](#hiddenfat_8h_1a904c71f61eddd57d65ceae01c9d4378c)`(size_t disk_size,size_t block_size)`            | Creates a new hidden FAT filesystem.
`public void `[`free_hidden_fat`](#hiddenfat_8h_1a9f7586a9218be752acddeadb571a7804)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Frees the memory associated with a hidden FAT filesystem.
`public size_t `[`get_amount_entries`](#hiddenfat_8h_1ac6ce3884ddeee6b87d7ad7727a602d79)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * path)`            | Gets the amount of entries (files and directories) in a given path.
`public size_t `[`get_free_disk_space`](#hiddenfat_8h_1a894c009cdba4bee0f12d0ff9dedbd822)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Gets the amount of free disk space in bytes in the hidden FAT filesystem.
`public void `[`show_hidden_fat`](#hiddenfat_8h_1a1160b2a46bcda6fc11a0e7a5315dbe30)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,char * output_message)`            | Shows the structure of the hidden FAT filesystem.
`public bool `[`check_integrity`](#hiddenfat_8h_1aa08a06a00394ffa6d3b3f7f5de0f788c)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Checks the integrity of the hidden FAT filesystem.
`public float `[`check_for_fragmentation`](#hiddenfat_8h_1addfb4b08dfa28015d50b9b3a5f945af8)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Checks the filesystem for fragmentation and calculates the fragmentation percentage.
`public void `[`defragmentate`](#hiddenfat_8h_1a5982a0473fe70151bafc156a8798aa11)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Defragments the hidden FAT filesystem.
`public int `[`write_block`](#hiddenfat_8h_1a38b16e6c06594f8de19e978adf9f64d3)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index,const char * buffer,size_t offset,size_t length)`            | Writes data to a block in the hidden FAT filesystem.
`public int `[`read_block`](#hiddenfat_8h_1a46ee12149f2a68e98266d5731f0f7b54)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index,const char * buffer,size_t offset,size_t length)`            | Reads data from a block in the hidden FAT filesystem.
`public size_t `[`get_fragmentation_array`](#hiddenfat_8h_1a79b176f531157c6cee0550a517801164)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t ** array)`            | Gets an array indicating the fragmentation status of blocks in the hidden FAT filesystem.
`public int `[`delete_hidden_file`](#hiddenfile_8h_1a1b6af287c5fd23063b62c72a3bdac3ab)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * filename)`            | Deletes a hidden file from the hidden FAT filesystem.
`public int `[`count_path_components`](#hiddenfile_8h_1a15ad97f3f11ca281808f9bf0e32db5be)`(const char * path)`            | Counts the number of components in a given path.
`public `[`HiddenFile`](#structHiddenFile)` * `[`find_file_by_path`](#hiddenfile_8h_1a62a86090d8eb7104b665dda1c7ea7e58)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * path)`            | Finds a hidden file by its path.
`public `[`HiddenFile`](#structHiddenFile)` ** `[`create_hidden_file`](#hiddenfile_8h_1af5053a4b545f4e6dad4353492493eccb)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * filename,long timestamp)`            | Creates a hidden file in the hidden FAT filesystem.
`public struct `[`__attribute__`](#ramdiskloader_8h_1a43c18e3e8d026268ff2a4e80b6e37c9d)`((__packed__))`            | Represents a packed FAT structure for serialization.
`public struct `[`SerializedFilesystem`](#structSerializedFilesystem)` `[`serialize_filesystem`](#ramdiskloader_8h_1aa3a1976cfef20abebc813bfeabee092f)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Serializes a [HiddenFat](#structHiddenFat) structure into a [SerializedFilesystem](#structSerializedFilesystem) structure.
`public `[`HiddenFat`](#structHiddenFat)` * `[`load_ramdisk`](#ramdiskloader_8h_1a0d12600694dbe9e21b394189a5c0fa6f)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` serialized_filesystem)`            | Loads a RAM disk from a serialized filesystem data.
`public size_t `[`calculate_amount_blocks`](#ramdiskloader_8h_1a9f182582224a7cc8b45be22e7596e76f)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` serialized_filesystem)`            | calculates how many blocks a serialized filesystem can hold.
`public void `[`run_length_encoding`](#runlengthencoding_8h_1a01ab5ef8f38349c9d5251cd7b3710c72)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` * serialized_filesystem)`            | Run-length encodes a serialized filesystem.
`public void `[`run_length_decoding`](#runlengthencoding_8h_1ad25093650710e37c1918a1a6b2e4bac9)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` * serialized_filesystem)`            | Run-length decodes a serialized filesystem.
`public int `[`stgfs_getattr`](#steganofs_8h_1a4df3c6bd301e91ab34cf3f4e4a144d93)`(const char * path,struct stat * stbuf,`[`__attribute__`](#ramdiskloader_8h_1a43c18e3e8d026268ff2a4e80b6e37c9d)((unused))` struct fuse_file_info * fi)`            | 
`public int `[`stgfs_readdir`](#steganofs_8h_1ab2dbcbcc171e6a1f10b99ea011889176)`(const char * path,void * buf,fuse_fill_dir_t filler,off_t offset,struct fuse_file_info * fi,enum fuse_readdir_flags flags)`            | 
`public int `[`stgfs_create`](#steganofs_8h_1adedceaf3ad9001890fbcc9a94c98f924)`(const char * path,mode_t mode,struct fuse_file_info * fi)`            | 
`public int `[`stgfs_write`](#steganofs_8h_1acb33aea88c4f73aa0bad5573746388cd)`(const char * path,const char * buf,size_t size,off_t offset,struct fuse_file_info * fi)`            | 
`public int `[`stgfs_read`](#steganofs_8h_1a6b7c2a0044567c0db507ed39bd6bc5f8)`(const char * path,char * buf,size_t size,off_t offset,struct fuse_file_info * fi)`            | 
`public int `[`stgfs_unlink`](#steganofs_8h_1a0643a2df6935c5f72d555234b0764043)`(const char * path)`            | 
`public int `[`stgfs_statfs`](#steganofs_8h_1a9f96362e4deea6e70e4b0d6411581a7b)`(`[`__attribute__`](#ramdiskloader_8h_1a43c18e3e8d026268ff2a4e80b6e37c9d)((unused))` const char * path,struct statvfs * stbuf)`            | 
`struct `[`HiddenCluster`](#structHiddenCluster) | Structure representing a hidden cluster.
`struct `[`HiddenFat`](#structHiddenFat) | Structure representing a hidden FAT filesystem.
`struct `[`HiddenFile`](#structHiddenFile) | Represents a hidden file in the hidden FAT filesystem.
`struct `[`SerializedFilesystem`](#structSerializedFilesystem) | Represents a serialized filesystem that holds the serialized data.

## Members

#### `define `[`FUSE_USE_VERSION`](#steganofs_8h_1a0919197af2e154da2c05727b6d87cbda) 

#### `define `[`STEGANOFS_AMOUNT_ROOT_FILES`](#steganofs_8h_1a64489b1f57cc01f9f3c21efeca50a378) 

#### `define `[`STEGANOFS_BLOCK_SIZE`](#steganofs_8h_1a5d1366b576fa580404ac8d71a08b1edf) 

#### `define `[`STEGANOFS_MAX_FILENAME_LENGTH`](#steganofs_8h_1a68f6206a38c0ef043621c9b9bad4aa87) 

#### `define `[`STEGANOFS_DEBUG`](#steganofs_8h_1a1d29d564950eefc26873cb8565fd5263) 

#### `enum `[`State`](#hiddencluster_8h_1a5d74787dedbc4e11c1ab15bf487e61f8) 

Enumeration representing the state of a hidden cluster.

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
FREE            | Cluster is free.
RESERVED            | Cluster is reserved.
DEFECT            | Cluster is defective.
ALLOCATED            | Cluster is allocated.

#### `public bool `[`swap_hidden_clusters`](#hiddencluster_8h_1a1736049385c7bf194f6a0fec32f0f508)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index_a,size_t b_index_b)` 

Swaps two hidden clusters within a hidden FAT.

This function swaps two hidden clusters within a hidden FAT.

#### Parameters
* `hidden_fat` Pointer to the [HiddenFat](#structHiddenFat) structure. 

* `b_index_a` Index of the first cluster to be swapped. 

* `b_index_b` Index of the second cluster to be swapped. 

#### Returns
Returns true if the swap is successful, false otherwise.

#### `public bool `[`extend_hidden_cluster`](#hiddencluster_8h_1a80b5c17506983811bc3cbdee5b84ff3d)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,`[`HiddenFile`](#structHiddenFile)` * p_file)` 

Extends a hidden cluster for a hidden file.

This function extends a hidden cluster for a hidden file in a hidden FAT.

#### Parameters
* `hidden_fat` Pointer to the [HiddenFat](#structHiddenFat) structure. 

* `p_file` Pointer to the [HiddenFile](#structHiddenFile) structure. 

#### Returns
Returns true if the extension is successful, false otherwise.

#### `public `[`HiddenFat`](#structHiddenFat)` * `[`create_hidden_fat`](#hiddenfat_8h_1a904c71f61eddd57d65ceae01c9d4378c)`(size_t disk_size,size_t block_size)` 

Creates a new hidden FAT filesystem.

#### Parameters
* `disk_size` The total size of the disk in bytes. 

* `block_size` The size of each block in bytes. 

#### Returns
A pointer to the newly created [HiddenFat](#structHiddenFat) structure, or NULL on failure.

#### `public void `[`free_hidden_fat`](#hiddenfat_8h_1a9f7586a9218be752acddeadb571a7804)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Frees the memory associated with a hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure to be freed.

#### `public size_t `[`get_amount_entries`](#hiddenfat_8h_1ac6ce3884ddeee6b87d7ad7727a602d79)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * path)` 

Gets the amount of entries (files and directories) in a given path.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `path` The path to the directory to be checked. 

#### Returns
The amount of entries in the directory.

#### `public size_t `[`get_free_disk_space`](#hiddenfat_8h_1a894c009cdba4bee0f12d0ff9dedbd822)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Gets the amount of free disk space in bytes in the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

#### Returns
The amount of free disk space in bytes.

#### `public void `[`show_hidden_fat`](#hiddenfat_8h_1a1160b2a46bcda6fc11a0e7a5315dbe30)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,char * output_message)` 

Shows the structure of the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `output_message` If not NULL, the output will be copied to this string.

#### `public bool `[`check_integrity`](#hiddenfat_8h_1aa08a06a00394ffa6d3b3f7f5de0f788c)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Checks the integrity of the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

#### Returns
True if the filesystem has integrity, false otherwise.

#### `public float `[`check_for_fragmentation`](#hiddenfat_8h_1addfb4b08dfa28015d50b9b3a5f945af8)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Checks the filesystem for fragmentation and calculates the fragmentation percentage.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

#### Returns
The fragmentation percentage.

#### `public void `[`defragmentate`](#hiddenfat_8h_1a5982a0473fe70151bafc156a8798aa11)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Defragments the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure.

#### `public int `[`write_block`](#hiddenfat_8h_1a38b16e6c06594f8de19e978adf9f64d3)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index,const char * buffer,size_t offset,size_t length)` 

Writes data to a block in the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `b_index` The index of the block to write to. 

* `buffer` The buffer containing the data to be written. 

* `offset` The offset within the block to start writing. 

* `length` The length of data to be written. 

#### Returns
The number of bytes written, or -1 on failure.

#### `public int `[`read_block`](#hiddenfat_8h_1a46ee12149f2a68e98266d5731f0f7b54)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index,const char * buffer,size_t offset,size_t length)` 

Reads data from a block in the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `b_index` The index of the block to read from. 

* `buffer` The buffer to store the read data. 

* `offset` The offset within the block to start reading. 

* `length` The length of data to be read. 

#### Returns
The number of bytes read, or -1 on failure.

#### `public size_t `[`get_fragmentation_array`](#hiddenfat_8h_1a79b176f531157c6cee0550a517801164)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t ** array)` 

Gets an array indicating the fragmentation status of blocks in the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `array` A pointer to an array that will be allocated to hold the fragmentation data. This array is allocated on the heap an can freed with free() by the caller of this function 

#### Returns
The total number of blocks in the filesystem.

#### `public int `[`delete_hidden_file`](#hiddenfile_8h_1a1b6af287c5fd23063b62c72a3bdac3ab)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * filename)` 

Deletes a hidden file from the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `filename` The name of the file to be deleted. 

#### Returns
0 on success, or -ENOENT if the file was not found.

#### `public int `[`count_path_components`](#hiddenfile_8h_1a15ad97f3f11ca281808f9bf0e32db5be)`(const char * path)` 

Counts the number of components in a given path.

#### Parameters
* `path` The path string to be analyzed. 

#### Returns
The number of components in the path.

#### `public `[`HiddenFile`](#structHiddenFile)` * `[`find_file_by_path`](#hiddenfile_8h_1a62a86090d8eb7104b665dda1c7ea7e58)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * path)` 

Finds a hidden file by its path.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `path` The path of the file to be found. 

#### Returns
A pointer to the [HiddenFile](#structHiddenFile) structure if found, otherwise NULL.

#### `public `[`HiddenFile`](#structHiddenFile)` ** `[`create_hidden_file`](#hiddenfile_8h_1af5053a4b545f4e6dad4353492493eccb)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * filename,long timestamp)` 

Creates a hidden file in the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `filename` The name of the file to be created. 

* `timestamp` The timestamp of the file. 

#### Returns
A pointer to the [HiddenFile](#structHiddenFile) pointer if created successfully, otherwise NULL.

#### `public struct `[`__attribute__`](#ramdiskloader_8h_1a43c18e3e8d026268ff2a4e80b6e37c9d)`((__packed__))` 

Represents a packed FAT structure for serialization.

Represents a packed file for serialization.

Represents a packed cluster for serialization.

#### `public struct `[`SerializedFilesystem`](#structSerializedFilesystem)` `[`serialize_filesystem`](#ramdiskloader_8h_1aa3a1976cfef20abebc813bfeabee092f)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Serializes a [HiddenFat](#structHiddenFat) structure into a [SerializedFilesystem](#structSerializedFilesystem) structure.

This function takes a [HiddenFat](#structHiddenFat) structure and converts it into a serialized representation suitable for storage or transmission. This function allocates buf inside [SerializedFilesystem](#structSerializedFilesystem), which can be freed with free() by the caller of this function.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

#### Returns
A [SerializedFilesystem](#structSerializedFilesystem) structure containing the serialized data.

#### `public `[`HiddenFat`](#structHiddenFat)` * `[`load_ramdisk`](#ramdiskloader_8h_1a0d12600694dbe9e21b394189a5c0fa6f)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` serialized_filesystem)` 

Loads a RAM disk from a serialized filesystem data.

This function takes a [SerializedFilesystem](#structSerializedFilesystem) structure containing serialized data and reconstructs a [HiddenFat](#structHiddenFat) structure representing the RAM disk filesystem.

#### Parameters
* `serialized_filesystem` The [SerializedFilesystem](#structSerializedFilesystem) structure containing the serialized data. 

#### Returns
A pointer to the loaded [HiddenFat](#structHiddenFat) structure, or NULL if loading fails. This structure is allocated on the heap and can be freed with freeHiddenFat in [hiddenfat.h](#hiddenfat_8h_source)

#### `public size_t `[`calculate_amount_blocks`](#ramdiskloader_8h_1a9f182582224a7cc8b45be22e7596e76f)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` serialized_filesystem)` 

calculates how many blocks a serialized filesystem can hold.

This function is useful for calculating the size of unformatted raw filesystems.

#### Parameters
* `serialized_filesystem` The [SerializedFilesystem](#structSerializedFilesystem) structure containing the serialized data. 

#### Returns
Amount of blocks which will fit in this filesystem.

#### `public void `[`run_length_encoding`](#runlengthencoding_8h_1a01ab5ef8f38349c9d5251cd7b3710c72)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` * serialized_filesystem)` 

Run-length encodes a serialized filesystem.

This function performs run-length encoding on the provided serialized filesystem. It replaces consecutive zero bytes with a range specification for efficient storage.

#### Parameters
* `serialized_filesystem` A pointer to the serialized filesystem structure to be encoded.

#### `public void `[`run_length_decoding`](#runlengthencoding_8h_1ad25093650710e37c1918a1a6b2e4bac9)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` * serialized_filesystem)` 

Run-length decodes a serialized filesystem.

This function performs run-length decoding on a previously run-length encoded serialized filesystem. It reconstructs the original data by expanding the zero ranges specified during encoding.

#### Parameters
* `serialized_filesystem` A pointer to the serialized filesystem structure to be decoded.

#### `public int `[`stgfs_getattr`](#steganofs_8h_1a4df3c6bd301e91ab34cf3f4e4a144d93)`(const char * path,struct stat * stbuf,`[`__attribute__`](#ramdiskloader_8h_1a43c18e3e8d026268ff2a4e80b6e37c9d)((unused))` struct fuse_file_info * fi)` 

#### `public int `[`stgfs_readdir`](#steganofs_8h_1ab2dbcbcc171e6a1f10b99ea011889176)`(const char * path,void * buf,fuse_fill_dir_t filler,off_t offset,struct fuse_file_info * fi,enum fuse_readdir_flags flags)` 

#### `public int `[`stgfs_create`](#steganofs_8h_1adedceaf3ad9001890fbcc9a94c98f924)`(const char * path,mode_t mode,struct fuse_file_info * fi)` 

#### `public int `[`stgfs_write`](#steganofs_8h_1acb33aea88c4f73aa0bad5573746388cd)`(const char * path,const char * buf,size_t size,off_t offset,struct fuse_file_info * fi)` 

#### `public int `[`stgfs_read`](#steganofs_8h_1a6b7c2a0044567c0db507ed39bd6bc5f8)`(const char * path,char * buf,size_t size,off_t offset,struct fuse_file_info * fi)` 

#### `public int `[`stgfs_unlink`](#steganofs_8h_1a0643a2df6935c5f72d555234b0764043)`(const char * path)` 

#### `public int `[`stgfs_statfs`](#steganofs_8h_1a9f96362e4deea6e70e4b0d6411581a7b)`(`[`__attribute__`](#ramdiskloader_8h_1a43c18e3e8d026268ff2a4e80b6e37c9d)((unused))` const char * path,struct statvfs * stbuf)` 

# struct `HiddenCluster` 

Structure representing a hidden cluster.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public size_t `[`b_index`](#structHiddenCluster_1a96430513b3e8409b48f2a62d5b093d64) | Index of the cluster within a block.
`public size_t `[`cluster_index`](#structHiddenCluster_1ad1ccb71186feea9c1c1dc712c6d1c0e9) | Index of the cluster within the filesystem.
`public unsigned int `[`state`](#structHiddenCluster_1a3f0517210ea3d35ff5e7077d31557c76) | State of the cluster (enum State).
`public `[`HiddenCluster`](#structHiddenCluster)` * `[`prev`](#structHiddenCluster_1a7367a00e100cafc547b57c5bb4fe5a08) | Pointer to the previous cluster in the linked list.
`public `[`HiddenCluster`](#structHiddenCluster)` * `[`next`](#structHiddenCluster_1aa14a3e27d751de697ff9bcf576ca742c) | Pointer to the next cluster in the linked list.
`public `[`HiddenFile`](#structHiddenFile)` * `[`file`](#structHiddenCluster_1a0adad5264fc41d3af45b74c0b0abf089) | Pointer to the file associated with the cluster.

## Members

#### `public size_t `[`b_index`](#structHiddenCluster_1a96430513b3e8409b48f2a62d5b093d64) 

Index of the cluster within a block.

#### `public size_t `[`cluster_index`](#structHiddenCluster_1ad1ccb71186feea9c1c1dc712c6d1c0e9) 

Index of the cluster within the filesystem.

#### `public unsigned int `[`state`](#structHiddenCluster_1a3f0517210ea3d35ff5e7077d31557c76) 

State of the cluster (enum State).

#### `public `[`HiddenCluster`](#structHiddenCluster)` * `[`prev`](#structHiddenCluster_1a7367a00e100cafc547b57c5bb4fe5a08) 

Pointer to the previous cluster in the linked list.

#### `public `[`HiddenCluster`](#structHiddenCluster)` * `[`next`](#structHiddenCluster_1aa14a3e27d751de697ff9bcf576ca742c) 

Pointer to the next cluster in the linked list.

#### `public `[`HiddenFile`](#structHiddenFile)` * `[`file`](#structHiddenCluster_1a0adad5264fc41d3af45b74c0b0abf089) 

Pointer to the file associated with the cluster.

# struct `HiddenFat` 

Structure representing a hidden FAT filesystem.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public size_t `[`block_size`](#structHiddenFat_1afeb0b7a473eb138a8ddaf8bfeee30f3f) | Size of a block in bytes.
`public size_t `[`amount_blocks`](#structHiddenFat_1a144f5ab7576fc5298eefc696b22f115b) | Total number of blocks in the filesystem.
`public unsigned char * `[`disk`](#structHiddenFat_1ab6df0cd5efebf3262475c24e96461212) | Pointer to the disk data.
`public `[`HiddenCluster`](#structHiddenCluster)` * `[`clusters`](#structHiddenFat_1ac8e226121f293d809ab3926c5556b967) | Pointer to an array of [HiddenCluster](#structHiddenCluster) structures.
`public `[`HiddenFile`](#structHiddenFile)` * `[`files`](#structHiddenFat_1abd8c32306c3ae16943bfa4234e45a32c) | Array of pointers to [HiddenFile](#structHiddenFile) structures.

## Members

#### `public size_t `[`block_size`](#structHiddenFat_1afeb0b7a473eb138a8ddaf8bfeee30f3f) 

Size of a block in bytes.

#### `public size_t `[`amount_blocks`](#structHiddenFat_1a144f5ab7576fc5298eefc696b22f115b) 

Total number of blocks in the filesystem.

#### `public unsigned char * `[`disk`](#structHiddenFat_1ab6df0cd5efebf3262475c24e96461212) 

Pointer to the disk data.

#### `public `[`HiddenCluster`](#structHiddenCluster)` * `[`clusters`](#structHiddenFat_1ac8e226121f293d809ab3926c5556b967) 

Pointer to an array of [HiddenCluster](#structHiddenCluster) structures.

#### `public `[`HiddenFile`](#structHiddenFile)` * `[`files`](#structHiddenFat_1abd8c32306c3ae16943bfa4234e45a32c) 

Array of pointers to [HiddenFile](#structHiddenFile) structures.

# struct `HiddenFile` 

Represents a hidden file in the hidden FAT filesystem.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public size_t `[`filesize`](#structHiddenFile_1abed2edf0dddffb8bf9c8658bdc06ed9a) | 
`public size_t `[`real_filesize`](#structHiddenFile_1a4a4308f9072ed688e2f747f6645d15ed) | 
`public long `[`timestamp`](#structHiddenFile_1a624f177eb3b7f3c6c85ff1ace59135c8) | 
`public `[`HiddenCluster`](#structHiddenCluster)` * `[`hiddenCluster`](#structHiddenFile_1aac6a40bd10600e18dab5aafe76bde7f6) | 
`public char `[`filename`](#structHiddenFile_1a40261e5b168aa7a560d5a0120f902b60) | 

## Members

#### `public size_t `[`filesize`](#structHiddenFile_1abed2edf0dddffb8bf9c8658bdc06ed9a) 

#### `public size_t `[`real_filesize`](#structHiddenFile_1a4a4308f9072ed688e2f747f6645d15ed) 

#### `public long `[`timestamp`](#structHiddenFile_1a624f177eb3b7f3c6c85ff1ace59135c8) 

#### `public `[`HiddenCluster`](#structHiddenCluster)` * `[`hiddenCluster`](#structHiddenFile_1aac6a40bd10600e18dab5aafe76bde7f6) 

#### `public char `[`filename`](#structHiddenFile_1a40261e5b168aa7a560d5a0120f902b60) 

# struct `SerializedFilesystem` 

Represents a serialized filesystem that holds the serialized data.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public size_t `[`size`](#structSerializedFilesystem_1a829c1e5e7c501c1baf86841d9ac668a3) | Size of the serialized data in bytes.
`public bool `[`rle`](#structSerializedFilesystem_1a22cd8b44c2683729b44674eacf9bda11) | Flag if the Fielsystem is compressed with Run-Length Encoding flag.
`public unsigned char * `[`buf`](#structSerializedFilesystem_1a4849c9fc8e4e5fb167c77b954277923a) | Pointer to the serialized data buffer.

## Members

#### `public size_t `[`size`](#structSerializedFilesystem_1a829c1e5e7c501c1baf86841d9ac668a3) 

Size of the serialized data in bytes.

#### `public bool `[`rle`](#structSerializedFilesystem_1a22cd8b44c2683729b44674eacf9bda11) 

Flag if the Fielsystem is compressed with Run-Length Encoding flag.

#### `public unsigned char * `[`buf`](#structSerializedFilesystem_1a4849c9fc8e4e5fb167c77b954277923a) 

Pointer to the serialized data buffer.

Generated by [Moxygen](https://sourcey.com/moxygen)