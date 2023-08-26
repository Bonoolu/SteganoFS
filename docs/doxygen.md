# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`FUSE_USE_VERSION`](#steganofs_8h_1a0919197af2e154da2c05727b6d87cbda)            | 
`define `[`STEGANOFS_AMOUNT_ROOT_FILES`](#steganofs_8h_1a64489b1f57cc01f9f3c21efeca50a378)            | 
`define `[`STEGANOFS_BLOCK_SIZE`](#steganofs_8h_1a5d1366b576fa580404ac8d71a08b1edf)            | 
`define `[`STEGANOFS_MAX_FILENAME_LENGTH`](#steganofs_8h_1a68f6206a38c0ef043621c9b9bad4aa87)            | 
`define `[`STEGANOFS_DEBUG`](#steganofs_8h_1a1d29d564950eefc26873cb8565fd5263)            | 
`enum `[`State`](#hiddencluster_8h_1a5d74787dedbc4e11c1ab15bf487e61f8)            | Enumeration representing the state of a hidden cluster.
`public int `[`main`](#main_8cpp_1a0ddf1224851353fc92bfbff6f499fa97)`(int argc,char * argv)`            | 
`public bool `[`extend_hidden_cluster`](#hiddencluster_8c_1a80b5c17506983811bc3cbdee5b84ff3d)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,`[`HiddenFile`](#structHiddenFile)` * p_file)`            | Extends a hidden cluster for a hidden file.
`public bool `[`swap_hidden_clusters`](#hiddencluster_8c_1a1736049385c7bf194f6a0fec32f0f508)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index_a,size_t b_index_b)`            | Swaps two hidden clusters within a hidden FAT.
`public bool `[`swap_hidden_clusters`](#hiddencluster_8h_1a1736049385c7bf194f6a0fec32f0f508)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index_a,size_t b_index_b)`            | Swaps two hidden clusters within a hidden FAT.
`public bool `[`extend_hidden_cluster`](#hiddencluster_8h_1a80b5c17506983811bc3cbdee5b84ff3d)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,`[`HiddenFile`](#structHiddenFile)` * p_file)`            | Extends a hidden cluster for a hidden file.
`public `[`HiddenFat`](#structHiddenFat)` * `[`create_hidden_fat`](#hiddenfat_8c_1a904c71f61eddd57d65ceae01c9d4378c)`(size_t disk_size,size_t block_size)`            | Creates a new hidden FAT filesystem.
`public void `[`free_hidden_fat`](#hiddenfat_8c_1a9f7586a9218be752acddeadb571a7804)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Frees the memory associated with a hidden FAT filesystem.
`public size_t `[`get_free_disk_space`](#hiddenfat_8c_1a894c009cdba4bee0f12d0ff9dedbd822)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Gets the amount of free disk space in bytes in the hidden FAT filesystem.
`public void `[`show_hidden_fat`](#hiddenfat_8c_1a1160b2a46bcda6fc11a0e7a5315dbe30)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,char * output_message)`            | Shows the structure of the hidden FAT filesystem.
`public bool `[`check_integrity`](#hiddenfat_8c_1aa08a06a00394ffa6d3b3f7f5de0f788c)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Checks the integrity of the hidden FAT filesystem.
`public float `[`check_for_fragmentation`](#hiddenfat_8c_1addfb4b08dfa28015d50b9b3a5f945af8)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Checks the filesystem for fragmentation and calculates the fragmentation percentage.
`public void `[`defragmentate`](#hiddenfat_8c_1a5982a0473fe70151bafc156a8798aa11)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Defragments the hidden FAT filesystem.
`public size_t `[`get_fragmentation_array`](#hiddenfat_8c_1a79b176f531157c6cee0550a517801164)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t ** array)`            | Gets an array indicating the fragmentation status of blocks in the hidden FAT filesystem.
`public size_t `[`get_amount_entries`](#hiddenfat_8c_1ac6ce3884ddeee6b87d7ad7727a602d79)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * path)`            | Gets the amount of entries (files and directories) in a given path.
`public int `[`write_block`](#hiddenfat_8c_1a38b16e6c06594f8de19e978adf9f64d3)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index,const char * buffer,size_t offset,size_t length)`            | Writes data to a block in the hidden FAT filesystem.
`public int `[`read_block`](#hiddenfat_8c_1a46ee12149f2a68e98266d5731f0f7b54)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index,const char * buffer,size_t offset,size_t length)`            | Reads data from a block in the hidden FAT filesystem.
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
`public int `[`delete_hidden_file`](#hiddenfile_8c_1a1b6af287c5fd23063b62c72a3bdac3ab)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * filename)`            | Deletes a hidden file from the hidden FAT filesystem.
`public int `[`count_path_components`](#hiddenfile_8c_1a15ad97f3f11ca281808f9bf0e32db5be)`(const char * path)`            | Counts the number of components in a given path.
`public `[`HiddenFile`](#structHiddenFile)` * `[`find_file_by_path`](#hiddenfile_8c_1a62a86090d8eb7104b665dda1c7ea7e58)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * path)`            | Finds a hidden file by its path.
`public `[`HiddenFile`](#structHiddenFile)` ** `[`create_hidden_file`](#hiddenfile_8c_1af5053a4b545f4e6dad4353492493eccb)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * filename,long timestamp)`            | Creates a hidden file in the hidden FAT filesystem.
`public int `[`delete_hidden_file`](#hiddenfile_8h_1a1b6af287c5fd23063b62c72a3bdac3ab)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * filename)`            | Deletes a hidden file from the hidden FAT filesystem.
`public int `[`count_path_components`](#hiddenfile_8h_1a15ad97f3f11ca281808f9bf0e32db5be)`(const char * path)`            | Counts the number of components in a given path.
`public `[`HiddenFile`](#structHiddenFile)` * `[`find_file_by_path`](#hiddenfile_8h_1a62a86090d8eb7104b665dda1c7ea7e58)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * path)`            | Finds a hidden file by its path.
`public `[`HiddenFile`](#structHiddenFile)` ** `[`create_hidden_file`](#hiddenfile_8h_1af5053a4b545f4e6dad4353492493eccb)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * filename,long timestamp)`            | Creates a hidden file in the hidden FAT filesystem.
`public struct `[`SerializedFilesystem`](#structSerializedFilesystem)` `[`serialize_filesystem`](#ramdiskloader_8c_1aa3a1976cfef20abebc813bfeabee092f)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Serializes a [HiddenFat](#structHiddenFat) structure into a [SerializedFilesystem](#structSerializedFilesystem) structure.
`public `[`HiddenFat`](#structHiddenFat)` * `[`load_ramdisk`](#ramdiskloader_8c_1a0d12600694dbe9e21b394189a5c0fa6f)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` serialized_filesystem)`            | Loads a RAM disk from a serialized filesystem data.
`public size_t `[`calculate_amount_blocks`](#ramdiskloader_8c_1a9f182582224a7cc8b45be22e7596e76f)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` serialized_filesystem)`            | calculates how many blocks a serialized filesystem can hold.
`public struct `[`__attribute__`](#ramdiskloader_8h_1a43c18e3e8d026268ff2a4e80b6e37c9d)`((__packed__))`            | Represents a packed FAT structure for serialization.
`public struct `[`SerializedFilesystem`](#structSerializedFilesystem)` `[`serialize_filesystem`](#ramdiskloader_8h_1aa3a1976cfef20abebc813bfeabee092f)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Serializes a [HiddenFat](#structHiddenFat) structure into a [SerializedFilesystem](#structSerializedFilesystem) structure.
`public `[`HiddenFat`](#structHiddenFat)` * `[`load_ramdisk`](#ramdiskloader_8h_1a0d12600694dbe9e21b394189a5c0fa6f)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` serialized_filesystem)`            | Loads a RAM disk from a serialized filesystem data.
`public size_t `[`calculate_amount_blocks`](#ramdiskloader_8h_1a9f182582224a7cc8b45be22e7596e76f)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` serialized_filesystem)`            | calculates how many blocks a serialized filesystem can hold.
`public void `[`run_length_encoding`](#runlengthencoding_8c_1a01ab5ef8f38349c9d5251cd7b3710c72)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` * serialized_filesystem)`            | Run-length encodes a serialized filesystem.
`public void `[`run_length_decoding`](#runlengthencoding_8c_1ad25093650710e37c1918a1a6b2e4bac9)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` * serialized_filesystem)`            | Run-length decodes a serialized filesystem.
`public void `[`run_length_encoding`](#runlengthencoding_8h_1a01ab5ef8f38349c9d5251cd7b3710c72)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` * serialized_filesystem)`            | Run-length encodes a serialized filesystem.
`public void `[`run_length_decoding`](#runlengthencoding_8h_1ad25093650710e37c1918a1a6b2e4bac9)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` * serialized_filesystem)`            | Run-length decodes a serialized filesystem.
`public int `[`stgfs_getattr`](#steganofs_8c_1a4df3c6bd301e91ab34cf3f4e4a144d93)`(const char * path,struct stat * stbuf,`[`__attribute__`](#ramdiskloader_8h_1a43c18e3e8d026268ff2a4e80b6e37c9d)((unused))` struct fuse_file_info * fi)`            | 
`public int `[`stgfs_readdir`](#steganofs_8c_1ab2dbcbcc171e6a1f10b99ea011889176)`(const char * path,void * buf,fuse_fill_dir_t filler,off_t offset,struct fuse_file_info * fi,enum fuse_readdir_flags flags)`            | 
`public int `[`stgfs_create`](#steganofs_8c_1adedceaf3ad9001890fbcc9a94c98f924)`(const char * path,mode_t mode,struct fuse_file_info * fi)`            | 
`public int `[`stgfs_write`](#steganofs_8c_1acb33aea88c4f73aa0bad5573746388cd)`(const char * path,const char * buf,size_t size,off_t offset,struct fuse_file_info * fi)`            | 
`public int `[`stgfs_read`](#steganofs_8c_1a6b7c2a0044567c0db507ed39bd6bc5f8)`(const char * path,char * buf,size_t size,off_t offset,struct fuse_file_info * fi)`            | 
`public int `[`stgfs_unlink`](#steganofs_8c_1a0643a2df6935c5f72d555234b0764043)`(const char * path)`            | 
`public int `[`stgfs_statfs`](#steganofs_8c_1a9f96362e4deea6e70e4b0d6411581a7b)`(`[`__attribute__`](#ramdiskloader_8h_1a43c18e3e8d026268ff2a4e80b6e37c9d)((unused))` const char * path,struct statvfs * stbuf)`            | 
`public int `[`stgfs_getattr`](#steganofs_8h_1a4df3c6bd301e91ab34cf3f4e4a144d93)`(const char * path,struct stat * stbuf,`[`__attribute__`](#ramdiskloader_8h_1a43c18e3e8d026268ff2a4e80b6e37c9d)((unused))` struct fuse_file_info * fi)`            | 
`public int `[`stgfs_readdir`](#steganofs_8h_1ab2dbcbcc171e6a1f10b99ea011889176)`(const char * path,void * buf,fuse_fill_dir_t filler,off_t offset,struct fuse_file_info * fi,enum fuse_readdir_flags flags)`            | 
`public int `[`stgfs_create`](#steganofs_8h_1adedceaf3ad9001890fbcc9a94c98f924)`(const char * path,mode_t mode,struct fuse_file_info * fi)`            | 
`public int `[`stgfs_write`](#steganofs_8h_1acb33aea88c4f73aa0bad5573746388cd)`(const char * path,const char * buf,size_t size,off_t offset,struct fuse_file_info * fi)`            | 
`public int `[`stgfs_read`](#steganofs_8h_1a6b7c2a0044567c0db507ed39bd6bc5f8)`(const char * path,char * buf,size_t size,off_t offset,struct fuse_file_info * fi)`            | 
`public int `[`stgfs_unlink`](#steganofs_8h_1a0643a2df6935c5f72d555234b0764043)`(const char * path)`            | 
`public int `[`stgfs_statfs`](#steganofs_8h_1a9f96362e4deea6e70e4b0d6411581a7b)`(`[`__attribute__`](#ramdiskloader_8h_1a43c18e3e8d026268ff2a4e80b6e37c9d)((unused))` const char * path,struct statvfs * stbuf)`            | 
`public bool `[`test_generic_buffer`](#test__bmp__provider_8c_1a21eda67d5e365dc3dadf8a0fa874e15b)`()`            | Test the functions for generic buffer manipulation.
`public bool `[`test_single_bmp_file`](#test__bmp__provider_8c_1a881b9c7c20039d4d5e2e08f7481af2e9)`()`            | Test embedding and extracting a single file within a BMP image.
`public bool `[`test_bmp_folder`](#test__bmp__provider_8c_1a297cd624ee85b7efd9b8777a3418ec0b)`()`            | Test creating a folder with files and integrity check in a BMP image.
`public bool `[`test_format_bmp_folder`](#test__bmp__provider_8c_1a45dc01ae5329657fa7021eb8767bc9a7)`()`            | Test formatting a filesystem.
`public int `[`main`](#test__bmp__provider_8c_1a3c04138a5bfe5d72780bb7e82a18e627)`(int argc,char ** argv)`            | The main entry point for the test suite.
`public int `[`main`](#test__cpp__wrapper_8cpp_1a3c04138a5bfe5d72780bb7e82a18e627)`(int argc,char ** argv)`            | The main entry point for the test suite.
`public bool `[`test_create_hidden_fat`](#test__steganofs_8c_1ab09bc0aa38d2881c0d0343780d3a2474)`()`            | Test function for creating a hidden FAT structure.
`public bool `[`test_get_free_disk_space_empty_fat`](#test__steganofs_8c_1a2d0cb90893acb071c5097552df44e0cc)`()`            | Test function for getting free disk space on an empty hidden FAT.
`public bool `[`test_get_free_disk_space_with_allocated_blocks`](#test__steganofs_8c_1a89dd234b6cd0cf5da2dba20419fead6f)`()`            | Test function for getting free disk space with allocated blocks/files.
`public bool `[`test_get_free_disk_space_full_disk`](#test__steganofs_8c_1a5c9497bfcadacc10dcd3c3b7ee2b0825)`()`            | Test function for getting free disk space on a completely filled disk.
`public bool `[`test_create_file_valid`](#test__steganofs_8c_1a1ea1a1af772c09211ad18650a2c2f047)`()`            | Test function for creating a hidden file with valid parameters.
`public bool `[`test_create_file_insufficient_memory`](#test__steganofs_8c_1a7015b8ceb767d9f391baf8201ffc682d)`()`            | Test function for creating a hidden file with insufficient memory.
`public bool `[`test_create_file_no_available_file_slot`](#test__steganofs_8c_1abfe4c0102a6b3f61f08140914b4e2b2a)`()`            | Test function for creating a hidden file when no available file slots remain.
`public bool `[`test_create_file_linked_list`](#test__steganofs_8c_1adf6a4a81526c80e11309dc2fc3ac802c)`()`            | Test function for creating a hidden file with linked cluster blocks.
`public bool `[`test_delete_file_valid`](#test__steganofs_8c_1ab4b7e8205350d2f85b6c07e5bf453055)`()`            | Test function for deleting a valid hidden file.
`public bool `[`test_delete_file_non_existent`](#test__steganofs_8c_1afdb8612dbaeacec408c292e663fe65b7)`()`            | Test function for deleting a non-existent hidden file.
`public bool `[`test_delete_file_with_clusters`](#test__steganofs_8c_1ac2ac13b38a6fbcbbca3994df67002f94)`()`            | Test function for deleting a non-existent hidden file.
`public bool `[`test_show_n_block_fat`](#test__steganofs_8c_1a33bb12805d4b334de19b1fb83e351d37)`(size_t n,size_t output_len)`            | Test function for displaying the FAT structure for a specified number of blocks.
`public bool `[`test_swap_hidden_clusters_integrity`](#test__steganofs_8c_1a8c37c470ced0373a756450ddefb21219)`()`            | Tests the integrity of hidden clusters swapping.
`public bool `[`test_defragmentation`](#test__steganofs_8c_1a80eee95d6aa81e6ccf8de05cd0f03adf)`()`            | Test function for defragmenting the filesystem.
`public bool `[`test_write_read`](#test__steganofs_8c_1af9a2a487396b06272229916c0d086dd0)`(int argc,char ** argv)`            | Test function for writing and reading data from the filesystem.
`public bool `[`test_ramdiskloader`](#test__steganofs_8c_1a50b57bdcfc2f412c871c924680953175)`()`            | Test function for loading and unloading a RAM disk image.
`public bool `[`test_rle`](#test__steganofs_8c_1a532692d77a2f625359c711c983dd3edb)`()`            | Test function for testing Run Length Encoding (RLE).
`public void `[`run_tests`](#test__steganofs_8c_1a7f62816c73ea8fbfaf03ec5610a42cda)`(int argc,char ** argv)`            | Runs the test suite.
`public int `[`test_fuse`](#test__steganofs_8c_1a79ab4544a28f6a86eb494d74e4b3b4a2)`(int argc,char ** argv)`            | Tests the fusion of two or more argc clusters into one cluster.
`public int `[`main`](#test__steganofs_8c_1a3c04138a5bfe5d72780bb7e82a18e627)`(int argc,char ** argv)`            | The main entry point for the test suite.
`class `[`DefragmentDialog`](#classDefragmentDialog) | The [DefragmentDialog](#classDefragmentDialog) class represents a dialog for defragmentation settings.
`class `[`FormatFileSystemDialog`](#classFormatFileSystemDialog) | Dialog for mounting a filesystem from a specific path.
`class `[`FragmentationDiagram`](#classFragmentationDiagram) | 
`class `[`FragmentationDialog`](#classFragmentationDialog) | 
`class `[`FragmentTile`](#classFragmentTile) | 
`class `[`MainWindow`](#classMainWindow) | The [MainWindow](#classMainWindow) class is the main GUI window for the application.
`class `[`MountFromPathDialog`](#classMountFromPathDialog) | Dialog for mounting a filesystem from a specific path.
`class `[`PreviewGraphicsView`](#classPreviewGraphicsView) | The [PreviewGraphicsView](#classPreviewGraphicsView) class provides a custom QGraphicsView for previewing graphics.
`class `[`ShowFileSystemInfoDialog`](#classShowFileSystemInfoDialog) | 
`class `[`SteganoFsAdapter`](#classSteganoFsAdapter) | Adapter class for interacting with the SteganoFS filesystem.
`class `[`Worker`](#classWorker) | The [Worker](#classWorker) class represents a worker object that performs tasks asynchronously.
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

#### `public int `[`main`](#main_8cpp_1a0ddf1224851353fc92bfbff6f499fa97)`(int argc,char * argv)` 

#### `public bool `[`extend_hidden_cluster`](#hiddencluster_8c_1a80b5c17506983811bc3cbdee5b84ff3d)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,`[`HiddenFile`](#structHiddenFile)` * p_file)` 

Extends a hidden cluster for a hidden file.

This function extends a hidden cluster for a hidden file in a hidden FAT.

#### Parameters
* `hidden_fat` Pointer to the [HiddenFat](#structHiddenFat) structure. 

* `p_file` Pointer to the [HiddenFile](#structHiddenFile) structure. 

#### Returns
Returns true if the extension is successful, false otherwise.

#### `public bool `[`swap_hidden_clusters`](#hiddencluster_8c_1a1736049385c7bf194f6a0fec32f0f508)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index_a,size_t b_index_b)` 

Swaps two hidden clusters within a hidden FAT.

This function swaps two hidden clusters within a hidden FAT.

#### Parameters
* `hidden_fat` Pointer to the [HiddenFat](#structHiddenFat) structure. 

* `b_index_a` Index of the first cluster to be swapped. 

* `b_index_b` Index of the second cluster to be swapped. 

#### Returns
Returns true if the swap is successful, false otherwise.

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

#### `public `[`HiddenFat`](#structHiddenFat)` * `[`create_hidden_fat`](#hiddenfat_8c_1a904c71f61eddd57d65ceae01c9d4378c)`(size_t disk_size,size_t block_size)` 

Creates a new hidden FAT filesystem.

#### Parameters
* `disk_size` The total size of the disk in bytes. 

* `block_size` The size of each block in bytes. 

#### Returns
A pointer to the newly created [HiddenFat](#structHiddenFat) structure, or NULL on failure.

#### `public void `[`free_hidden_fat`](#hiddenfat_8c_1a9f7586a9218be752acddeadb571a7804)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Frees the memory associated with a hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure to be freed.

#### `public size_t `[`get_free_disk_space`](#hiddenfat_8c_1a894c009cdba4bee0f12d0ff9dedbd822)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Gets the amount of free disk space in bytes in the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

#### Returns
The amount of free disk space in bytes.

#### `public void `[`show_hidden_fat`](#hiddenfat_8c_1a1160b2a46bcda6fc11a0e7a5315dbe30)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,char * output_message)` 

Shows the structure of the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `output_message` If not NULL, the output will be copied to this string.

#### `public bool `[`check_integrity`](#hiddenfat_8c_1aa08a06a00394ffa6d3b3f7f5de0f788c)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Checks the integrity of the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

#### Returns
True if the filesystem has integrity, false otherwise.

#### `public float `[`check_for_fragmentation`](#hiddenfat_8c_1addfb4b08dfa28015d50b9b3a5f945af8)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Checks the filesystem for fragmentation and calculates the fragmentation percentage.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

#### Returns
The fragmentation percentage.

#### `public void `[`defragmentate`](#hiddenfat_8c_1a5982a0473fe70151bafc156a8798aa11)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Defragments the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure.

#### `public size_t `[`get_fragmentation_array`](#hiddenfat_8c_1a79b176f531157c6cee0550a517801164)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t ** array)` 

Gets an array indicating the fragmentation status of blocks in the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `array` A pointer to an array that will be allocated to hold the fragmentation data. This array is allocated on the heap an can freed with free() by the caller of this function 

#### Returns
The total number of blocks in the filesystem.

#### `public size_t `[`get_amount_entries`](#hiddenfat_8c_1ac6ce3884ddeee6b87d7ad7727a602d79)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * path)` 

Gets the amount of entries (files and directories) in a given path.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `path` The path to the directory to be checked. 

#### Returns
The amount of entries in the directory.

#### `public int `[`write_block`](#hiddenfat_8c_1a38b16e6c06594f8de19e978adf9f64d3)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index,const char * buffer,size_t offset,size_t length)` 

Writes data to a block in the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `b_index` The index of the block to write to. 

* `buffer` The buffer containing the data to be written. 

* `offset` The offset within the block to start writing. 

* `length` The length of data to be written. 

#### Returns
The number of bytes written, or -1 on failure.

#### `public int `[`read_block`](#hiddenfat_8c_1a46ee12149f2a68e98266d5731f0f7b54)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index,const char * buffer,size_t offset,size_t length)` 

Reads data from a block in the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `b_index` The index of the block to read from. 

* `buffer` The buffer to store the read data. 

* `offset` The offset within the block to start reading. 

* `length` The length of data to be read. 

#### Returns
The number of bytes read, or -1 on failure.

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

#### `public int `[`delete_hidden_file`](#hiddenfile_8c_1a1b6af287c5fd23063b62c72a3bdac3ab)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * filename)` 

Deletes a hidden file from the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `filename` The name of the file to be deleted. 

#### Returns
0 on success, or -ENOENT if the file was not found.

#### `public int `[`count_path_components`](#hiddenfile_8c_1a15ad97f3f11ca281808f9bf0e32db5be)`(const char * path)` 

Counts the number of components in a given path.

#### Parameters
* `path` The path string to be analyzed. 

#### Returns
The number of components in the path.

#### `public `[`HiddenFile`](#structHiddenFile)` * `[`find_file_by_path`](#hiddenfile_8c_1a62a86090d8eb7104b665dda1c7ea7e58)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * path)` 

Finds a hidden file by its path.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `path` The path of the file to be found. 

#### Returns
A pointer to the [HiddenFile](#structHiddenFile) structure if found, otherwise NULL.

#### `public `[`HiddenFile`](#structHiddenFile)` ** `[`create_hidden_file`](#hiddenfile_8c_1af5053a4b545f4e6dad4353492493eccb)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * filename,long timestamp)` 

Creates a hidden file in the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `filename` The name of the file to be created. 

* `timestamp` The timestamp of the file. 

#### Returns
A pointer to the [HiddenFile](#structHiddenFile) pointer if created successfully, otherwise NULL.

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

#### `public struct `[`SerializedFilesystem`](#structSerializedFilesystem)` `[`serialize_filesystem`](#ramdiskloader_8c_1aa3a1976cfef20abebc813bfeabee092f)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Serializes a [HiddenFat](#structHiddenFat) structure into a [SerializedFilesystem](#structSerializedFilesystem) structure.

This function takes a [HiddenFat](#structHiddenFat) structure and converts it into a serialized representation suitable for storage or transmission. This function allocates buf inside [SerializedFilesystem](#structSerializedFilesystem), which can be freed with free() by the caller of this function.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

#### Returns
A [SerializedFilesystem](#structSerializedFilesystem) structure containing the serialized data.

#### `public `[`HiddenFat`](#structHiddenFat)` * `[`load_ramdisk`](#ramdiskloader_8c_1a0d12600694dbe9e21b394189a5c0fa6f)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` serialized_filesystem)` 

Loads a RAM disk from a serialized filesystem data.

This function takes a [SerializedFilesystem](#structSerializedFilesystem) structure containing serialized data and reconstructs a [HiddenFat](#structHiddenFat) structure representing the RAM disk filesystem.

#### Parameters
* `serialized_filesystem` The [SerializedFilesystem](#structSerializedFilesystem) structure containing the serialized data. 

#### Returns
A pointer to the loaded [HiddenFat](#structHiddenFat) structure, or NULL if loading fails. This structure is allocated on the heap and can be freed with freeHiddenFat in [hiddenfat.h](#hiddenfat_8h_source)

#### `public size_t `[`calculate_amount_blocks`](#ramdiskloader_8c_1a9f182582224a7cc8b45be22e7596e76f)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` serialized_filesystem)` 

calculates how many blocks a serialized filesystem can hold.

This function is useful for calculating the size of unformatted raw filesystems.

#### Parameters
* `serialized_filesystem` The [SerializedFilesystem](#structSerializedFilesystem) structure containing the serialized data. 

#### Returns
Amount of blocks which will fit in this filesystem.

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

#### `public void `[`run_length_encoding`](#runlengthencoding_8c_1a01ab5ef8f38349c9d5251cd7b3710c72)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` * serialized_filesystem)` 

Run-length encodes a serialized filesystem.

This function performs run-length encoding on the provided serialized filesystem. It replaces consecutive zero bytes with a range specification for efficient storage.

#### Parameters
* `serialized_filesystem` A pointer to the serialized filesystem structure to be encoded.

#### `public void `[`run_length_decoding`](#runlengthencoding_8c_1ad25093650710e37c1918a1a6b2e4bac9)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` * serialized_filesystem)` 

Run-length decodes a serialized filesystem.

This function performs run-length decoding on a previously run-length encoded serialized filesystem. It reconstructs the original data by expanding the zero ranges specified during encoding.

#### Parameters
* `serialized_filesystem` A pointer to the serialized filesystem structure to be decoded.

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

#### `public int `[`stgfs_getattr`](#steganofs_8c_1a4df3c6bd301e91ab34cf3f4e4a144d93)`(const char * path,struct stat * stbuf,`[`__attribute__`](#ramdiskloader_8h_1a43c18e3e8d026268ff2a4e80b6e37c9d)((unused))` struct fuse_file_info * fi)` 

#### `public int `[`stgfs_readdir`](#steganofs_8c_1ab2dbcbcc171e6a1f10b99ea011889176)`(const char * path,void * buf,fuse_fill_dir_t filler,off_t offset,struct fuse_file_info * fi,enum fuse_readdir_flags flags)` 

#### `public int `[`stgfs_create`](#steganofs_8c_1adedceaf3ad9001890fbcc9a94c98f924)`(const char * path,mode_t mode,struct fuse_file_info * fi)` 

#### `public int `[`stgfs_write`](#steganofs_8c_1acb33aea88c4f73aa0bad5573746388cd)`(const char * path,const char * buf,size_t size,off_t offset,struct fuse_file_info * fi)` 

#### `public int `[`stgfs_read`](#steganofs_8c_1a6b7c2a0044567c0db507ed39bd6bc5f8)`(const char * path,char * buf,size_t size,off_t offset,struct fuse_file_info * fi)` 

#### `public int `[`stgfs_unlink`](#steganofs_8c_1a0643a2df6935c5f72d555234b0764043)`(const char * path)` 

#### `public int `[`stgfs_statfs`](#steganofs_8c_1a9f96362e4deea6e70e4b0d6411581a7b)`(`[`__attribute__`](#ramdiskloader_8h_1a43c18e3e8d026268ff2a4e80b6e37c9d)((unused))` const char * path,struct statvfs * stbuf)` 

#### `public int `[`stgfs_getattr`](#steganofs_8h_1a4df3c6bd301e91ab34cf3f4e4a144d93)`(const char * path,struct stat * stbuf,`[`__attribute__`](#ramdiskloader_8h_1a43c18e3e8d026268ff2a4e80b6e37c9d)((unused))` struct fuse_file_info * fi)` 

#### `public int `[`stgfs_readdir`](#steganofs_8h_1ab2dbcbcc171e6a1f10b99ea011889176)`(const char * path,void * buf,fuse_fill_dir_t filler,off_t offset,struct fuse_file_info * fi,enum fuse_readdir_flags flags)` 

#### `public int `[`stgfs_create`](#steganofs_8h_1adedceaf3ad9001890fbcc9a94c98f924)`(const char * path,mode_t mode,struct fuse_file_info * fi)` 

#### `public int `[`stgfs_write`](#steganofs_8h_1acb33aea88c4f73aa0bad5573746388cd)`(const char * path,const char * buf,size_t size,off_t offset,struct fuse_file_info * fi)` 

#### `public int `[`stgfs_read`](#steganofs_8h_1a6b7c2a0044567c0db507ed39bd6bc5f8)`(const char * path,char * buf,size_t size,off_t offset,struct fuse_file_info * fi)` 

#### `public int `[`stgfs_unlink`](#steganofs_8h_1a0643a2df6935c5f72d555234b0764043)`(const char * path)` 

#### `public int `[`stgfs_statfs`](#steganofs_8h_1a9f96362e4deea6e70e4b0d6411581a7b)`(`[`__attribute__`](#ramdiskloader_8h_1a43c18e3e8d026268ff2a4e80b6e37c9d)((unused))` const char * path,struct statvfs * stbuf)` 

#### `public bool `[`test_generic_buffer`](#test__bmp__provider_8c_1a21eda67d5e365dc3dadf8a0fa874e15b)`()` 

Test the functions for generic buffer manipulation.

#### Returns
True if the test passes, false otherwise.

#### `public bool `[`test_single_bmp_file`](#test__bmp__provider_8c_1a881b9c7c20039d4d5e2e08f7481af2e9)`()` 

Test embedding and extracting a single file within a BMP image.

#### Returns
True if the test passes, false otherwise.

#### `public bool `[`test_bmp_folder`](#test__bmp__provider_8c_1a297cd624ee85b7efd9b8777a3418ec0b)`()` 

Test creating a folder with files and integrity check in a BMP image.

#### Returns
True if the test passes, false otherwise.

#### `public bool `[`test_format_bmp_folder`](#test__bmp__provider_8c_1a45dc01ae5329657fa7021eb8767bc9a7)`()` 

Test formatting a filesystem.

#### Returns
True if the test passes, false otherwise.

#### `public int `[`main`](#test__bmp__provider_8c_1a3c04138a5bfe5d72780bb7e82a18e627)`(int argc,char ** argv)` 

The main entry point for the test suite.

#### Parameters
* `argc` The number of command-line arguments. 

* `argv` An array of pointers to command-line arguments. 

#### Returns
0 on successful execution.

#### `public int `[`main`](#test__cpp__wrapper_8cpp_1a3c04138a5bfe5d72780bb7e82a18e627)`(int argc,char ** argv)` 

The main entry point for the test suite.

#### Parameters
* `argc` The number of command-line arguments. 

* `argv` An array of pointers to command-line arguments. 

#### Returns
0 on successful execution.

#### `public bool `[`test_create_hidden_fat`](#test__steganofs_8c_1ab09bc0aa38d2881c0d0343780d3a2474)`()` 

Test function for creating a hidden FAT structure.

#### Returns
`true` if the test passes, otherwise `false`.

#### `public bool `[`test_get_free_disk_space_empty_fat`](#test__steganofs_8c_1a2d0cb90893acb071c5097552df44e0cc)`()` 

Test function for getting free disk space on an empty hidden FAT.

#### Returns
`true` if the test passes, otherwise `false`.

#### `public bool `[`test_get_free_disk_space_with_allocated_blocks`](#test__steganofs_8c_1a89dd234b6cd0cf5da2dba20419fead6f)`()` 

Test function for getting free disk space with allocated blocks/files.

#### Returns
`true` if the test passes, otherwise `false`.

#### `public bool `[`test_get_free_disk_space_full_disk`](#test__steganofs_8c_1a5c9497bfcadacc10dcd3c3b7ee2b0825)`()` 

Test function for getting free disk space on a completely filled disk.

#### Returns
`true` if the test passes, otherwise `false`.

#### `public bool `[`test_create_file_valid`](#test__steganofs_8c_1a1ea1a1af772c09211ad18650a2c2f047)`()` 

Test function for creating a hidden file with valid parameters.

#### Returns
`true` if the test passes, otherwise `false`.

#### `public bool `[`test_create_file_insufficient_memory`](#test__steganofs_8c_1a7015b8ceb767d9f391baf8201ffc682d)`()` 

Test function for creating a hidden file with insufficient memory.

#### Returns
`true` if the test passes, otherwise `false`.

#### `public bool `[`test_create_file_no_available_file_slot`](#test__steganofs_8c_1abfe4c0102a6b3f61f08140914b4e2b2a)`()` 

Test function for creating a hidden file when no available file slots remain.

#### Returns
`true` if the test passes, otherwise `false`.

#### `public bool `[`test_create_file_linked_list`](#test__steganofs_8c_1adf6a4a81526c80e11309dc2fc3ac802c)`()` 

Test function for creating a hidden file with linked cluster blocks.

#### Returns
`true` if the test passes, otherwise `false`.

#### `public bool `[`test_delete_file_valid`](#test__steganofs_8c_1ab4b7e8205350d2f85b6c07e5bf453055)`()` 

Test function for deleting a valid hidden file.

#### Returns
`true` if the test passes, otherwise `false`.

#### `public bool `[`test_delete_file_non_existent`](#test__steganofs_8c_1afdb8612dbaeacec408c292e663fe65b7)`()` 

Test function for deleting a non-existent hidden file.

#### Returns
`true` if the test passes, otherwise `false`.

#### `public bool `[`test_delete_file_with_clusters`](#test__steganofs_8c_1ac2ac13b38a6fbcbbca3994df67002f94)`()` 

Test function for deleting a non-existent hidden file.

#### Returns
`true` if the test passes, otherwise `false`.

#### `public bool `[`test_show_n_block_fat`](#test__steganofs_8c_1a33bb12805d4b334de19b1fb83e351d37)`(size_t n,size_t output_len)` 

Test function for displaying the FAT structure for a specified number of blocks.

#### Parameters
* `n` The number of blocks in the FAT. 

* `output_len` The expected length of the output. 

#### Returns
`true` if the test passes, otherwise `false`.

#### `public bool `[`test_swap_hidden_clusters_integrity`](#test__steganofs_8c_1a8c37c470ced0373a756450ddefb21219)`()` 

Tests the integrity of hidden clusters swapping.

This function tests whether swapping of hidden clusters maintains the integrity of the data structure.

#### Returns
`true` if hidden cluster swapping passes integrity check, otherwise `false`.

#### `public bool `[`test_defragmentation`](#test__steganofs_8c_1a80eee95d6aa81e6ccf8de05cd0f03adf)`()` 

Test function for defragmenting the filesystem.

#### Returns
`true` if the test passes, otherwise `false`.

#### `public bool `[`test_write_read`](#test__steganofs_8c_1af9a2a487396b06272229916c0d086dd0)`(int argc,char ** argv)` 

Test function for writing and reading data from the filesystem.

#### Parameters
* `argc` Number of command-line arguments. 

* `argv` Array of command-line argument strings. 

#### Returns
`true` if the test passes, otherwise `false`.

#### `public bool `[`test_ramdiskloader`](#test__steganofs_8c_1a50b57bdcfc2f412c871c924680953175)`()` 

Test function for loading and unloading a RAM disk image.

#### Returns
`true` if the test passes, otherwise `false`.

#### `public bool `[`test_rle`](#test__steganofs_8c_1a532692d77a2f625359c711c983dd3edb)`()` 

Test function for testing Run Length Encoding (RLE).

#### Returns
`true` if the test passes, otherwise `false`.

#### `public void `[`run_tests`](#test__steganofs_8c_1a7f62816c73ea8fbfaf03ec5610a42cda)`(int argc,char ** argv)` 

Runs the test suite.

This function initializes the test framework and runs the test suite based on the provided command line arguments.

#### Parameters
* `argc` The number of command line arguments. 

* `argv` An array of C-style strings containing the command line arguments.

#### `public int `[`test_fuse`](#test__steganofs_8c_1a79ab4544a28f6a86eb494d74e4b3b4a2)`(int argc,char ** argv)` 

Tests the fusion of two or more argc clusters into one cluster.

This function performs testing of argc cluster fusion operation. It takes argc and argv as input, performs the testing, and returns the result.

#### Parameters
* `argc` The number of command line arguments. 

* `argv` An array of C-style strings containing the command line arguments. 

#### Returns
The result code of the test_fuse operation.

#### `public int `[`main`](#test__steganofs_8c_1a3c04138a5bfe5d72780bb7e82a18e627)`(int argc,char ** argv)` 

The main entry point for the test suite.

#### Parameters
* `argc` The number of command-line arguments. 

* `argv` An array of pointers to command-line arguments. 

#### Returns
0 on successful execution.

# class `DefragmentDialog` 

```
class DefragmentDialog
  : public QDialog
```  

The [DefragmentDialog](#classDefragmentDialog) class represents a dialog for defragmentation settings.

This class provides a dialog window to configure defragmentation settings for the application.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`DefragmentDialog`](#classDefragmentDialog_1a36555d7df2bd9665e0e23ff33f318b1a)`(QWidget * parent)` | Constructs a [DefragmentDialog](#classDefragmentDialog) object.
`public  `[`~DefragmentDialog`](#classDefragmentDialog_1ad9228d774583b1de71e35ea6c89975a8)`()` | Destroys the [DefragmentDialog](#classDefragmentDialog) object.
`public void `[`setLightmodeOn`](#classDefragmentDialog_1a35d90d7a9065c8b5bdbf07c52469048e)`(bool newLightmodeOn)` | Sets the light mode on/off.
`public bool `[`lightmodeOn`](#classDefragmentDialog_1ad4aff2a176ddc99ac526395e63bac6e6)`() const` | Checks if light mode is on.
`public void `[`setFragmentation`](#classDefragmentDialog_1ab2bb749a237464fed7a328be447c83a4)`(float f)` | Sets the fragmentation level.
`public void `[`setAdapter`](#classDefragmentDialog_1afcab0648f64b6f802d6ea226864365a3)`(`[`SteganoFsAdapter`](#classSteganoFsAdapter)` * newAdapter)` | Sets the adapter for the defragmentation dialog.

## Members

#### `public  explicit `[`DefragmentDialog`](#classDefragmentDialog_1a36555d7df2bd9665e0e23ff33f318b1a)`(QWidget * parent)` 

Constructs a [DefragmentDialog](#classDefragmentDialog) object.

#### Parameters
* `parent` The parent widget.

#### `public  `[`~DefragmentDialog`](#classDefragmentDialog_1ad9228d774583b1de71e35ea6c89975a8)`()` 

Destroys the [DefragmentDialog](#classDefragmentDialog) object.

#### `public void `[`setLightmodeOn`](#classDefragmentDialog_1a35d90d7a9065c8b5bdbf07c52469048e)`(bool newLightmodeOn)` 

Sets the light mode on/off.

#### Parameters
* `newLightmodeOn` Whether light mode should be turned on.

#### `public bool `[`lightmodeOn`](#classDefragmentDialog_1ad4aff2a176ddc99ac526395e63bac6e6)`() const` 

Checks if light mode is on.

#### Returns
True if light mode is on, otherwise false.

#### `public void `[`setFragmentation`](#classDefragmentDialog_1ab2bb749a237464fed7a328be447c83a4)`(float f)` 

Sets the fragmentation level.

#### Parameters
* `f` The new fragmentation level.

#### `public void `[`setAdapter`](#classDefragmentDialog_1afcab0648f64b6f802d6ea226864365a3)`(`[`SteganoFsAdapter`](#classSteganoFsAdapter)` * newAdapter)` 

Sets the adapter for the defragmentation dialog.

#### Parameters
* `newAdapter` The adapter to be set.

# class `FormatFileSystemDialog` 

```
class FormatFileSystemDialog
  : public QDialog
```  

Dialog for mounting a filesystem from a specific path.

This class provides a dialog for selecting a mounting path and filesystem path, along with additional settings like light mode. It also allows connecting a [SteganoFsAdapter](#classSteganoFsAdapter) to handle the mounting process.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`FormatFileSystemDialog`](#classFormatFileSystemDialog_1aaba29f0e2d89c8822c1a53fbcec16a3c)`(QWidget * parent)` | 
`public  `[`~FormatFileSystemDialog`](#classFormatFileSystemDialog_1abbfaf02cde260941c5b03f5ba17b1a90)`()` | Destructs the [FormatFileSystemDialog](#classFormatFileSystemDialog).
`public bool `[`lightmodeOn`](#classFormatFileSystemDialog_1afecfd82a5095388be528f89a2eb37c99)`() const` | Checks if light mode is enabled.
`public void `[`setLightmodeOn`](#classFormatFileSystemDialog_1a20822de12d768b26a74311d156bc4349)`(bool newLightmodeOn)` | Sets the light mode.
`public QString `[`filesystemPath`](#classFormatFileSystemDialog_1af22d96618f70f44242656405a580370b)`() const` | Returns the selected filesystem path.
`public void `[`setFilesystemPath`](#classFormatFileSystemDialog_1a95011a39226ae36584ffc95fd276080a)`(const QString & newFilesystemPath)` | Sets the filesystem path.
`public `[`SteganoFsAdapter`](#classSteganoFsAdapter)` * `[`adapter`](#classFormatFileSystemDialog_1a5a1a3f337eeb4998e6182ef1ad348b51)`() const` | Returns the associated [SteganoFsAdapter](#classSteganoFsAdapter).
`public void `[`setAdapter`](#classFormatFileSystemDialog_1addcb99c6141a0e15df6565dc5f8b806b)`(`[`SteganoFsAdapter`](#classSteganoFsAdapter)` * newAdapter)` | Sets the [SteganoFsAdapter](#classSteganoFsAdapter).

## Members

#### `public  explicit `[`FormatFileSystemDialog`](#classFormatFileSystemDialog_1aaba29f0e2d89c8822c1a53fbcec16a3c)`(QWidget * parent)` 

#### `public  `[`~FormatFileSystemDialog`](#classFormatFileSystemDialog_1abbfaf02cde260941c5b03f5ba17b1a90)`()` 

Destructs the [FormatFileSystemDialog](#classFormatFileSystemDialog).

#### `public bool `[`lightmodeOn`](#classFormatFileSystemDialog_1afecfd82a5095388be528f89a2eb37c99)`() const` 

Checks if light mode is enabled.

#### Returns
True if light mode is enabled, false otherwise.

#### `public void `[`setLightmodeOn`](#classFormatFileSystemDialog_1a20822de12d768b26a74311d156bc4349)`(bool newLightmodeOn)` 

Sets the light mode.

#### Parameters
* `newLightmodeOn` True to enable light mode, false to disable.

#### `public QString `[`filesystemPath`](#classFormatFileSystemDialog_1af22d96618f70f44242656405a580370b)`() const` 

Returns the selected filesystem path.

#### Returns
The selected filesystem path.

#### `public void `[`setFilesystemPath`](#classFormatFileSystemDialog_1a95011a39226ae36584ffc95fd276080a)`(const QString & newFilesystemPath)` 

Sets the filesystem path.

#### Parameters
* `newFilesystemPath` The new filesystem path.

#### `public `[`SteganoFsAdapter`](#classSteganoFsAdapter)` * `[`adapter`](#classFormatFileSystemDialog_1a5a1a3f337eeb4998e6182ef1ad348b51)`() const` 

Returns the associated [SteganoFsAdapter](#classSteganoFsAdapter).

#### Returns
The associated [SteganoFsAdapter](#classSteganoFsAdapter).

#### `public void `[`setAdapter`](#classFormatFileSystemDialog_1addcb99c6141a0e15df6565dc5f8b806b)`(`[`SteganoFsAdapter`](#classSteganoFsAdapter)` * newAdapter)` 

Sets the [SteganoFsAdapter](#classSteganoFsAdapter).

#### Parameters
* `newAdapter` The new [SteganoFsAdapter](#classSteganoFsAdapter).

# class `FragmentationDiagram` 

```
class FragmentationDiagram
  : public QWidget
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`FragmentationDiagram`](#classFragmentationDiagram_1aae4ee9ece57258ffb064fc0d7e1f2f24)`(QWidget * parent)` | 
`public  `[`~FragmentationDiagram`](#classFragmentationDiagram_1acdffba03285bc7e7eaea907d561a097b)`()` | 

## Members

#### `public  explicit `[`FragmentationDiagram`](#classFragmentationDiagram_1aae4ee9ece57258ffb064fc0d7e1f2f24)`(QWidget * parent)` 

#### `public  `[`~FragmentationDiagram`](#classFragmentationDiagram_1acdffba03285bc7e7eaea907d561a097b)`()` 

# class `FragmentationDialog` 

```
class FragmentationDialog
  : public QDialog
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`FragmentationDialog`](#classFragmentationDialog_1ac7cce577cee2b686bafcd1e32cfa6e34)`(QWidget * parent)` | 
`public  `[`~FragmentationDialog`](#classFragmentationDialog_1a70760f655d540eb0ace1a951de0e8311)`()` | 

## Members

#### `public  explicit `[`FragmentationDialog`](#classFragmentationDialog_1ac7cce577cee2b686bafcd1e32cfa6e34)`(QWidget * parent)` 

#### `public  `[`~FragmentationDialog`](#classFragmentationDialog_1a70760f655d540eb0ace1a951de0e8311)`()` 

# class `FragmentTile` 

```
class FragmentTile
  : public QWidget
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`FragmentTile`](#classFragmentTile_1ae2e01b74ff0ac19c82aeef4c19d68edd)`(QWidget * parent,const QColor & color)` | 
`public void `[`setColor`](#classFragmentTile_1a20ec9f6c163c9f5f2c5b054776cfbf6a)`(const QColor & color)` | 
`public  `[`~FragmentTile`](#classFragmentTile_1a2ad9a8b38100a34f066f65fea6124782)`()` | 

## Members

#### `public  explicit `[`FragmentTile`](#classFragmentTile_1ae2e01b74ff0ac19c82aeef4c19d68edd)`(QWidget * parent,const QColor & color)` 

#### `public void `[`setColor`](#classFragmentTile_1a20ec9f6c163c9f5f2c5b054776cfbf6a)`(const QColor & color)` 

#### `public  `[`~FragmentTile`](#classFragmentTile_1a2ad9a8b38100a34f066f65fea6124782)`()` 

# class `MainWindow` 

```
class MainWindow
  : public QMainWindow
```  

The [MainWindow](#classMainWindow) class is the main GUI window for the application.

This class handles various UI interactions, signals, and slots.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`MainWindow`](#classMainWindow_1a996c5a2b6f77944776856f08ec30858d)`(QWidget * parent)` | Constructor for the [MainWindow](#classMainWindow) class.
`public  `[`~MainWindow`](#classMainWindow_1a1f7d2c56410fc1bfa135bb907d43313f)`()` | Destructor for the [MainWindow](#classMainWindow) class.
`{signal} public void `[`pathChanged`](#classMainWindow_1ace748f1515a0654d9f2325d7bca9a02b)`()` | Signal emitted when the path is changed.

## Members

#### `public  explicit `[`MainWindow`](#classMainWindow_1a996c5a2b6f77944776856f08ec30858d)`(QWidget * parent)` 

Constructor for the [MainWindow](#classMainWindow) class.

#### Parameters
* `parent` The parent widget.

#### `public  `[`~MainWindow`](#classMainWindow_1a1f7d2c56410fc1bfa135bb907d43313f)`()` 

Destructor for the [MainWindow](#classMainWindow) class.

#### `{signal} public void `[`pathChanged`](#classMainWindow_1ace748f1515a0654d9f2325d7bca9a02b)`()` 

Signal emitted when the path is changed.

# class `MountFromPathDialog` 

```
class MountFromPathDialog
  : public QDialog
```  

Dialog for mounting a filesystem from a specific path.

This class provides a dialog for selecting a mounting path and filesystem path, along with additional settings like light mode. It also allows connecting a [SteganoFsAdapter](#classSteganoFsAdapter) to handle the mounting process.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`MountFromPathDialog`](#classMountFromPathDialog_1ac0ffa4a61c9a0d1598cff9b0a925b755)`(QWidget * parent)` | Constructs a [MountFromPathDialog](#classMountFromPathDialog).
`public  `[`~MountFromPathDialog`](#classMountFromPathDialog_1ad0c342390443b00e9887a0d51bd5c190)`()` | Destructs the [MountFromPathDialog](#classMountFromPathDialog).
`public void `[`setMountingPath`](#classMountFromPathDialog_1ad44022ed4523176f59bd94e7b07fe763)`(const QString & newMountingPath)` | Sets the mounting path.
`public QString `[`mountingPath`](#classMountFromPathDialog_1a00e9bca483eb6268bce54510722050ab)`() const` | Returns the selected mounting path.
`public bool `[`lightmodeOn`](#classMountFromPathDialog_1ac67393a1ccbb1ea0e2bd8647e11a7fc4)`() const` | Checks if light mode is enabled.
`public void `[`setLightmodeOn`](#classMountFromPathDialog_1a3e4e30fae568277d4ade30ff744da027)`(bool newLightmodeOn)` | Sets the light mode.
`public QString `[`filesystemPath`](#classMountFromPathDialog_1a0d39744eee257c6e1664cf9b8b724c8e)`() const` | Returns the selected filesystem path.
`public void `[`setFilesystemPath`](#classMountFromPathDialog_1ad1dee511ad5ab72a032ad1e651bf567e)`(const QString & newFilesystemPath)` | Sets the filesystem path.
`public `[`SteganoFsAdapter`](#classSteganoFsAdapter)` * `[`adapter`](#classMountFromPathDialog_1ac6cbcc62f1d2113a475348ba715f16c1)`() const` | Returns the associated [SteganoFsAdapter](#classSteganoFsAdapter).
`public void `[`setAdapter`](#classMountFromPathDialog_1aeaf4590f25a8bf5c44e77f70c6858e3b)`(`[`SteganoFsAdapter`](#classSteganoFsAdapter)` * newAdapter)` | Sets the [SteganoFsAdapter](#classSteganoFsAdapter).
`{signal} public void `[`finishedMounting`](#classMountFromPathDialog_1a02fabdeb1840a462564166b95fdf5722)`()` | Signal emitted when the mounting process is finished.

## Members

#### `public  explicit `[`MountFromPathDialog`](#classMountFromPathDialog_1ac0ffa4a61c9a0d1598cff9b0a925b755)`(QWidget * parent)` 

Constructs a [MountFromPathDialog](#classMountFromPathDialog).

#### Parameters
* `parent` The parent widget.

#### `public  `[`~MountFromPathDialog`](#classMountFromPathDialog_1ad0c342390443b00e9887a0d51bd5c190)`()` 

Destructs the [MountFromPathDialog](#classMountFromPathDialog).

#### `public void `[`setMountingPath`](#classMountFromPathDialog_1ad44022ed4523176f59bd94e7b07fe763)`(const QString & newMountingPath)` 

Sets the mounting path.

#### Parameters
* `newMountingPath` The new mounting path.

#### `public QString `[`mountingPath`](#classMountFromPathDialog_1a00e9bca483eb6268bce54510722050ab)`() const` 

Returns the selected mounting path.

#### Returns
The selected mounting path.

#### `public bool `[`lightmodeOn`](#classMountFromPathDialog_1ac67393a1ccbb1ea0e2bd8647e11a7fc4)`() const` 

Checks if light mode is enabled.

#### Returns
True if light mode is enabled, false otherwise.

#### `public void `[`setLightmodeOn`](#classMountFromPathDialog_1a3e4e30fae568277d4ade30ff744da027)`(bool newLightmodeOn)` 

Sets the light mode.

#### Parameters
* `newLightmodeOn` True to enable light mode, false to disable.

#### `public QString `[`filesystemPath`](#classMountFromPathDialog_1a0d39744eee257c6e1664cf9b8b724c8e)`() const` 

Returns the selected filesystem path.

#### Returns
The selected filesystem path.

#### `public void `[`setFilesystemPath`](#classMountFromPathDialog_1ad1dee511ad5ab72a032ad1e651bf567e)`(const QString & newFilesystemPath)` 

Sets the filesystem path.

#### Parameters
* `newFilesystemPath` The new filesystem path.

#### `public `[`SteganoFsAdapter`](#classSteganoFsAdapter)` * `[`adapter`](#classMountFromPathDialog_1ac6cbcc62f1d2113a475348ba715f16c1)`() const` 

Returns the associated [SteganoFsAdapter](#classSteganoFsAdapter).

#### Returns
The associated [SteganoFsAdapter](#classSteganoFsAdapter).

#### `public void `[`setAdapter`](#classMountFromPathDialog_1aeaf4590f25a8bf5c44e77f70c6858e3b)`(`[`SteganoFsAdapter`](#classSteganoFsAdapter)` * newAdapter)` 

Sets the [SteganoFsAdapter](#classSteganoFsAdapter).

#### Parameters
* `newAdapter` The new [SteganoFsAdapter](#classSteganoFsAdapter).

#### `{signal} public void `[`finishedMounting`](#classMountFromPathDialog_1a02fabdeb1840a462564166b95fdf5722)`()` 

Signal emitted when the mounting process is finished.

# class `PreviewGraphicsView` 

```
class PreviewGraphicsView
  : public QGraphicsView
```  

The [PreviewGraphicsView](#classPreviewGraphicsView) class provides a custom QGraphicsView for previewing graphics.

This class extends QGraphicsView and adds functionality for handling resize events and emitting a signal to request a scene refresh.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`PreviewGraphicsView`](#classPreviewGraphicsView_1a45c98cad2a7523214a55490496da6d44)`(QWidget * parent)` | Constructs a [PreviewGraphicsView](#classPreviewGraphicsView).
`public void `[`resizeEvent`](#classPreviewGraphicsView_1afa9e61b3319db87c1d9abc57bad6b539)`(QResizeEvent * event)` | Handles resize events for the view.
`{signal} public void `[`refreshScene`](#classPreviewGraphicsView_1a35941b72b1cf7893aa7f9e3e36bf2836)`()` | Signal emitted when the scene needs to be refreshed.

## Members

#### `public  explicit `[`PreviewGraphicsView`](#classPreviewGraphicsView_1a45c98cad2a7523214a55490496da6d44)`(QWidget * parent)` 

Constructs a [PreviewGraphicsView](#classPreviewGraphicsView).

#### Parameters
* `parent` The parent QWidget of this view.

#### `public void `[`resizeEvent`](#classPreviewGraphicsView_1afa9e61b3319db87c1d9abc57bad6b539)`(QResizeEvent * event)` 

Handles resize events for the view.

#### Parameters
* `event` A pointer to the QResizeEvent object containing event details.

#### `{signal} public void `[`refreshScene`](#classPreviewGraphicsView_1a35941b72b1cf7893aa7f9e3e36bf2836)`()` 

Signal emitted when the scene needs to be refreshed.

# class `ShowFileSystemInfoDialog` 

```
class ShowFileSystemInfoDialog
  : public QDialog
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`ShowFileSystemInfoDialog`](#classShowFileSystemInfoDialog_1a6dbcf3f3fb4799581ea35d8c13d2a320)`(QWidget * parent)` | Constructs a [ShowFileSystemInfoDialog](#classShowFileSystemInfoDialog).
`public  `[`~ShowFileSystemInfoDialog`](#classShowFileSystemInfoDialog_1a15669c5dfeeb0d78c07d52868cd63142)`()` | Destructor for [ShowFileSystemInfoDialog](#classShowFileSystemInfoDialog).
`public void `[`setLightmodeOn`](#classShowFileSystemInfoDialog_1a6aa47a76fc6b885456ada85780966c00)`(bool newLightmodeOn)` | Sets the light mode state.
`public void `[`showFilesystemInfo`](#classShowFileSystemInfoDialog_1a0510202431ad37d11d18c0e72216eb89)`(`[`SteganoFsAdapter`](#classSteganoFsAdapter)` & sfa)` | Displays filesystem information.

## Members

#### `public  explicit `[`ShowFileSystemInfoDialog`](#classShowFileSystemInfoDialog_1a6dbcf3f3fb4799581ea35d8c13d2a320)`(QWidget * parent)` 

Constructs a [ShowFileSystemInfoDialog](#classShowFileSystemInfoDialog).

#### Parameters
* `parent` The parent widget.

#### `public  `[`~ShowFileSystemInfoDialog`](#classShowFileSystemInfoDialog_1a15669c5dfeeb0d78c07d52868cd63142)`()` 

Destructor for [ShowFileSystemInfoDialog](#classShowFileSystemInfoDialog).

#### `public void `[`setLightmodeOn`](#classShowFileSystemInfoDialog_1a6aa47a76fc6b885456ada85780966c00)`(bool newLightmodeOn)` 

Sets the light mode state.

#### Parameters
* `newLightmodeOn` The new light mode state.

#### `public void `[`showFilesystemInfo`](#classShowFileSystemInfoDialog_1a0510202431ad37d11d18c0e72216eb89)`(`[`SteganoFsAdapter`](#classSteganoFsAdapter)` & sfa)` 

Displays filesystem information.

#### Parameters
* `sfa` The [SteganoFsAdapter](#classSteganoFsAdapter) for filesystem access.

# class `SteganoFsAdapter` 

Adapter class for interacting with the SteganoFS filesystem.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`SteganoFsAdapter`](#classSteganoFsAdapter_1a8b16a46ebc14456614ec45e33b31d651)`(std::string steganoImageFolder)` | Constructor for [SteganoFsAdapter](#classSteganoFsAdapter).
`public  `[`~SteganoFsAdapter`](#classSteganoFsAdapter_1abe270fd7364b981e11ca8b95629d4d57)`()` | Destructor for [SteganoFsAdapter](#classSteganoFsAdapter).
`public size_t `[`formatNewFilesystem`](#classSteganoFsAdapter_1ab90da955cdb155d8c7ffdca00983ba38)`()` | Creates a new filesystem the specified path of steganographic files.
`public bool `[`createNewFilesystem`](#classSteganoFsAdapter_1ad1064d64fa6aafa0561e4a83e044c7b2)`(size_t diskSize)` | Creates a new filesystem with the given disk size.
`public bool `[`loadFilesytemFromSteganoProvider`](#classSteganoFsAdapter_1ad7a36c1a7ac2f3be193e20c706c40f7a)`()` | Load the hidden filesystem from the steganographic image provider.
`public bool `[`mount`](#classSteganoFsAdapter_1ad79d549ad56dd0b3a1c9a85ed3a941f3)`(const std::string & mntPoint)` | Mount the hidden filesystem to the given mount point.
`public bool `[`writeFilesystemToSteganoProvider`](#classSteganoFsAdapter_1a8d668990c752bf8e3386ee1f80a59fa8)`()` | Write the hidden filesystem back to the steganographic image provider.
`public bool `[`umount`](#classSteganoFsAdapter_1aa1e0bd5984e477759b299c354f682ab5)`(std::string mntPoint)` | Unmount the hidden filesystem.
`public float `[`getFragmentationInPercent`](#classSteganoFsAdapter_1afd4cb6d986578c8ae3818fbe04d593e1)`()` | Get the fragmentation of the hidden filesystem in percentage.
`public std::vector< size_t > `[`getFilesystemVector`](#classSteganoFsAdapter_1a44ebcbf79df3e7aaf3c8bb126c980fc6)`()` | Get a vector containing fragmentation information of the filesystem.
`public bool `[`checkFilesystemIntegrity`](#classSteganoFsAdapter_1a1899628c9e7216a10172d8fde47b6f23)`()` | Check the integrity of the hidden filesystem.
`public bool `[`defragmentateFilesystem`](#classSteganoFsAdapter_1a0a59bee7c6dd614233441e77d18648b9)`()` | Defragment the hidden filesystem.
`public struct statvfs `[`getFilesystemInfo`](#classSteganoFsAdapter_1abb2a12ee096914a0b6983596ce93c1e1)`()` | Get information about the hidden filesystem.
`public std::string `[`steganoImageFolder`](#classSteganoFsAdapter_1acd82f4904fdb30b50cf05416388cf395)`() const` | Get the steganographic image folder path.
`public bool `[`isMounted`](#classSteganoFsAdapter_1a9dc809dc804b9c51ec834ae27c2f8c0d)`() const` | Check if the filesystem is mounted.
`public bool `[`isLoaded`](#classSteganoFsAdapter_1a8cff00edd53804553a0c47f3cd54b3b1)`() const` | Check if the filesystem is loaded.
`public std::string `[`mountPath`](#classSteganoFsAdapter_1ac30e2ac223e1f7f4a650ff411ce10594)`() const` | Get the mount path of the filesystem.

## Members

#### `public  explicit `[`SteganoFsAdapter`](#classSteganoFsAdapter_1a8b16a46ebc14456614ec45e33b31d651)`(std::string steganoImageFolder)` 

Constructor for [SteganoFsAdapter](#classSteganoFsAdapter).

#### Parameters
* `steganoImageFolder` Path to the stegano image folder.

#### `public  `[`~SteganoFsAdapter`](#classSteganoFsAdapter_1abe270fd7364b981e11ca8b95629d4d57)`()` 

Destructor for [SteganoFsAdapter](#classSteganoFsAdapter).

#### `public size_t `[`formatNewFilesystem`](#classSteganoFsAdapter_1ab90da955cdb155d8c7ffdca00983ba38)`()` 

Creates a new filesystem the specified path of steganographic files.

#### Returns
The size of the new filesystem. 0 if fails.

#### `public bool `[`createNewFilesystem`](#classSteganoFsAdapter_1ad1064d64fa6aafa0561e4a83e044c7b2)`(size_t diskSize)` 

Creates a new filesystem with the given disk size.

#### Parameters
* `diskSize` Size of the disk in bytes. 

#### Returns
True if successful, false otherwise.

#### `public bool `[`loadFilesytemFromSteganoProvider`](#classSteganoFsAdapter_1ad7a36c1a7ac2f3be193e20c706c40f7a)`()` 

Load the hidden filesystem from the steganographic image provider.

#### Returns
True if the filesystem was loaded successfully, false otherwise.

#### `public bool `[`mount`](#classSteganoFsAdapter_1ad79d549ad56dd0b3a1c9a85ed3a941f3)`(const std::string & mntPoint)` 

Mount the hidden filesystem to the given mount point.

#### Parameters
* `mntPoint` Mount point for the filesystem. 

#### Returns
True if the filesystem was mounted successfully, false otherwise.

#### `public bool `[`writeFilesystemToSteganoProvider`](#classSteganoFsAdapter_1a8d668990c752bf8e3386ee1f80a59fa8)`()` 

Write the hidden filesystem back to the steganographic image provider.

#### Returns
True if the filesystem was written successfully, false otherwise.

#### `public bool `[`umount`](#classSteganoFsAdapter_1aa1e0bd5984e477759b299c354f682ab5)`(std::string mntPoint)` 

Unmount the hidden filesystem.

#### Parameters
* `mntPoint` Mount point for the filesystem. Can be omitted if set as member 

#### Returns
True if the filesystem was unmounted successfully, false otherwise.

#### `public float `[`getFragmentationInPercent`](#classSteganoFsAdapter_1afd4cb6d986578c8ae3818fbe04d593e1)`()` 

Get the fragmentation of the hidden filesystem in percentage.

#### Returns
Fragmentation percentage if the filesystem is loaded, otherwise -1.

#### `public std::vector< size_t > `[`getFilesystemVector`](#classSteganoFsAdapter_1a44ebcbf79df3e7aaf3c8bb126c980fc6)`()` 

Get a vector containing fragmentation information of the filesystem.

#### Returns
Vector of fragmentation data if the filesystem is loaded, otherwise an empty vector.

#### `public bool `[`checkFilesystemIntegrity`](#classSteganoFsAdapter_1a1899628c9e7216a10172d8fde47b6f23)`()` 

Check the integrity of the hidden filesystem.

#### Returns
True if the filesystem is intact, false if integrity check fails.

#### `public bool `[`defragmentateFilesystem`](#classSteganoFsAdapter_1a0a59bee7c6dd614233441e77d18648b9)`()` 

Defragment the hidden filesystem.

#### Returns
True if defragmentation was successful, false otherwise.

#### `public struct statvfs `[`getFilesystemInfo`](#classSteganoFsAdapter_1abb2a12ee096914a0b6983596ce93c1e1)`()` 

Get information about the hidden filesystem.

#### Returns
Structure containing filesystem information.

#### `public std::string `[`steganoImageFolder`](#classSteganoFsAdapter_1acd82f4904fdb30b50cf05416388cf395)`() const` 

Get the steganographic image folder path.

#### Returns
Steganographic image folder path.

#### `public bool `[`isMounted`](#classSteganoFsAdapter_1a9dc809dc804b9c51ec834ae27c2f8c0d)`() const` 

Check if the filesystem is mounted.

#### Returns
True if the filesystem is mounted, false otherwise.

#### `public bool `[`isLoaded`](#classSteganoFsAdapter_1a8cff00edd53804553a0c47f3cd54b3b1)`() const` 

Check if the filesystem is loaded.

#### Returns
True if the filesystem is loaded, false otherwise.

#### `public std::string `[`mountPath`](#classSteganoFsAdapter_1ac30e2ac223e1f7f4a650ff411ce10594)`() const` 

Get the mount path of the filesystem.

#### Returns
Mount path of the filesystem.

# class `Worker` 

```
class Worker
  : public QObject
```  

The [Worker](#classWorker) class represents a worker object that performs tasks asynchronously.

This class inherits from QObject and provides slots for performing various tasks.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`Worker`](#classWorker_1a013acfa37bedf294ece993aa4fcfb59f)`(QObject * parent)` | Constructor for the [Worker](#classWorker) class.
`{slot} public void `[`mountFolder`](#classWorker_1a9de036625c9508479d832b6b20a30f76)`(const QVariant & qAdapt,const QString & s)` | Mounts a folder using the provided adapter and path.

## Members

#### `public  explicit `[`Worker`](#classWorker_1a013acfa37bedf294ece993aa4fcfb59f)`(QObject * parent)` 

Constructor for the [Worker](#classWorker) class.

#### Parameters
* `parent` The parent QObject for this worker.

#### `{slot} public void `[`mountFolder`](#classWorker_1a9de036625c9508479d832b6b20a30f76)`(const QVariant & qAdapt,const QString & s)` 

Mounts a folder using the provided adapter and path.

#### Parameters
* `qAdapt` The QVariant containing a pointer to the [SteganoFsAdapter](#classSteganoFsAdapter). 

* `s` The path to the folder to be mounted.

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