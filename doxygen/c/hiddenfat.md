# hiddenfat.h 

This file contains the structures and function declarations for hidden fat operations.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`HiddenFat`](#structHiddenFat)` * `[`create_hidden_fat`](#group__hiddenfat_1ga904c71f61eddd57d65ceae01c9d4378c)`(size_t disk_size,size_t block_size)`            | Creates a new hidden FAT filesystem.
`public void `[`free_hidden_fat`](#group__hiddenfat_1ga9f7586a9218be752acddeadb571a7804)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Frees the memory associated with a hidden FAT filesystem.
`public size_t `[`get_amount_entries`](#group__hiddenfat_1gac6ce3884ddeee6b87d7ad7727a602d79)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * path)`            | Gets the amount of entries (files and directories) in a given path.
`public size_t `[`get_free_disk_space`](#group__hiddenfat_1ga894c009cdba4bee0f12d0ff9dedbd822)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Gets the amount of free disk space in bytes in the hidden FAT filesystem.
`public void `[`show_hidden_fat`](#group__hiddenfat_1ga1160b2a46bcda6fc11a0e7a5315dbe30)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,char * output_message)`            | Shows the structure of the hidden FAT filesystem.
`public bool `[`check_integrity`](#group__hiddenfat_1gaa08a06a00394ffa6d3b3f7f5de0f788c)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Checks the integrity of the hidden FAT filesystem.
`public float `[`check_for_fragmentation`](#group__hiddenfat_1gaddfb4b08dfa28015d50b9b3a5f945af8)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Checks the filesystem for fragmentation and calculates the fragmentation percentage.
`public void `[`defragmentate`](#group__hiddenfat_1ga5982a0473fe70151bafc156a8798aa11)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Defragments the hidden FAT filesystem.
`public int `[`write_block`](#group__hiddenfat_1ga38b16e6c06594f8de19e978adf9f64d3)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index,const char * buffer,size_t offset,size_t length)`            | Writes data to a block in the hidden FAT filesystem.
`public int `[`read_block`](#group__hiddenfat_1ga46ee12149f2a68e98266d5731f0f7b54)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index,const char * buffer,size_t offset,size_t length)`            | Reads data from a block in the hidden FAT filesystem.
`public size_t `[`get_fragmentation_array`](#group__hiddenfat_1ga79b176f531157c6cee0550a517801164)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t ** array)`            | Gets an array indicating the fragmentation status of blocks in the hidden FAT filesystem.
`struct `[`HiddenFat`](hiddenfat.md#structHiddenFat) | Structure representing a hidden FAT filesystem.

## Members

#### `public `[`HiddenFat`](#structHiddenFat)` * `[`create_hidden_fat`](#group__hiddenfat_1ga904c71f61eddd57d65ceae01c9d4378c)`(size_t disk_size,size_t block_size)` 

Creates a new hidden FAT filesystem.

#### Parameters
* `disk_size` The total size of the disk in bytes. 

* `block_size` The size of each block in bytes. 

#### Returns
A pointer to the newly created [HiddenFat](#structHiddenFat) structure, or NULL on failure.

#### `public void `[`free_hidden_fat`](#group__hiddenfat_1ga9f7586a9218be752acddeadb571a7804)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Frees the memory associated with a hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure to be freed.

#### `public size_t `[`get_amount_entries`](#group__hiddenfat_1gac6ce3884ddeee6b87d7ad7727a602d79)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * path)` 

Gets the amount of entries (files and directories) in a given path.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `path` The path to the directory to be checked. 

#### Returns
The amount of entries in the directory.

#### `public size_t `[`get_free_disk_space`](#group__hiddenfat_1ga894c009cdba4bee0f12d0ff9dedbd822)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Gets the amount of free disk space in bytes in the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

#### Returns
The amount of free disk space in bytes.

#### `public void `[`show_hidden_fat`](#group__hiddenfat_1ga1160b2a46bcda6fc11a0e7a5315dbe30)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,char * output_message)` 

Shows the structure of the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `output_message` If not NULL, the output will be copied to this string.

#### `public bool `[`check_integrity`](#group__hiddenfat_1gaa08a06a00394ffa6d3b3f7f5de0f788c)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Checks the integrity of the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

#### Returns
True if the filesystem has integrity, false otherwise.

#### `public float `[`check_for_fragmentation`](#group__hiddenfat_1gaddfb4b08dfa28015d50b9b3a5f945af8)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Checks the filesystem for fragmentation and calculates the fragmentation percentage.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

#### Returns
The fragmentation percentage.

#### `public void `[`defragmentate`](#group__hiddenfat_1ga5982a0473fe70151bafc156a8798aa11)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Defragments the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure.

#### `public int `[`write_block`](#group__hiddenfat_1ga38b16e6c06594f8de19e978adf9f64d3)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index,const char * buffer,size_t offset,size_t length)` 

Writes data to a block in the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `b_index` The index of the block to write to. 

* `buffer` The buffer containing the data to be written. 

* `offset` The offset within the block to start writing. 

* `length` The length of data to be written. 

#### Returns
The number of bytes written, or -1 on failure.

#### `public int `[`read_block`](#group__hiddenfat_1ga46ee12149f2a68e98266d5731f0f7b54)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index,const char * buffer,size_t offset,size_t length)` 

Reads data from a block in the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `b_index` The index of the block to read from. 

* `buffer` The buffer to store the read data. 

* `offset` The offset within the block to start reading. 

* `length` The length of data to be read. 

#### Returns
The number of bytes read, or -1 on failure.

#### `public size_t `[`get_fragmentation_array`](#group__hiddenfat_1ga79b176f531157c6cee0550a517801164)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t ** array)` 

Gets an array indicating the fragmentation status of blocks in the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `array` A pointer to an array that will be allocated to hold the fragmentation data. This array is allocated on the heap an can freed with free() by the caller of this function 

#### Returns
The total number of blocks in the filesystem.

# struct `HiddenFat` 

Structure representing a hidden FAT filesystem.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public size_t `[`block_size`](hiddenfat.md#structHiddenFat_1afeb0b7a473eb138a8ddaf8bfeee30f3f) | Size of a block in bytes.
`public size_t `[`amount_blocks`](hiddenfat.md#structHiddenFat_1a144f5ab7576fc5298eefc696b22f115b) | Total number of blocks in the filesystem.
`public unsigned char * `[`disk`](hiddenfat.md#structHiddenFat_1ab6df0cd5efebf3262475c24e96461212) | Pointer to the disk data.
`public `[`HiddenCluster`](#structHiddenCluster)` * `[`clusters`](#structHiddenFat_1ac8e226121f293d809ab3926c5556b967) | Pointer to an array of [HiddenCluster](ramdiskloader.md#structHiddenCluster) structures.
`public `[`HiddenFile`](#structHiddenFile)` * `[`files`](#structHiddenFat_1abd8c32306c3ae16943bfa4234e45a32c) | Array of pointers to [HiddenFile](ramdiskloader.md#structHiddenFile) structures.

## Members

#### `public size_t `[`block_size`](hiddenfat.md#structHiddenFat_1afeb0b7a473eb138a8ddaf8bfeee30f3f) 

Size of a block in bytes.

#### `public size_t `[`amount_blocks`](hiddenfat.md#structHiddenFat_1a144f5ab7576fc5298eefc696b22f115b) 

Total number of blocks in the filesystem.

#### `public unsigned char * `[`disk`](hiddenfat.md#structHiddenFat_1ab6df0cd5efebf3262475c24e96461212) 

Pointer to the disk data.

#### `public `[`HiddenCluster`](#structHiddenCluster)` * `[`clusters`](#structHiddenFat_1ac8e226121f293d809ab3926c5556b967) 

Pointer to an array of [HiddenCluster](#structHiddenCluster) structures.

#### `public `[`HiddenFile`](#structHiddenFile)` * `[`files`](#structHiddenFat_1abd8c32306c3ae16943bfa4234e45a32c) 

Array of pointers to [HiddenFile](#structHiddenFile) structures.

