# ramdiskloader.h

This file contains the structures and function declarations for RAM disk loading and serialization.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public struct `[`__attribute__`](#group__ramdiskloader_1ga43c18e3e8d026268ff2a4e80b6e37c9d)`((__packed__))`            | Represents a packed FAT structure for serialization.
`public struct `[`SerializedFilesystem`](#structSerializedFilesystem)` `[`serialize_filesystem`](#group__ramdiskloader_1gaa3a1976cfef20abebc813bfeabee092f)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)`            | Serializes a [HiddenFat](#structHiddenFat) structure into a [SerializedFilesystem](#structSerializedFilesystem) structure.
`public `[`HiddenFat`](#structHiddenFat)` * `[`load_ramdisk`](#group__ramdiskloader_1ga0d12600694dbe9e21b394189a5c0fa6f)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` serialized_filesystem)`            | Loads a RAM disk from a serialized filesystem data.
`public size_t `[`calculate_amount_blocks`](#group__ramdiskloader_1ga9f182582224a7cc8b45be22e7596e76f)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` serialized_filesystem)`            | calculates how many blocks a serialized filesystem can hold.
`struct `[`SerializedFilesystem`](ramdiskloader.md#structSerializedFilesystem) | Represents a serialized filesystem that holds the serialized data.
`struct `[`HiddenFile`](ramdiskloader.md#structHiddenFile) | Represents a hidden file in the hidden FAT filesystem.
`struct `[`HiddenCluster`](ramdiskloader.md#structHiddenCluster) | Structure representing a hidden cluster.

## Members

#### `public struct `[`__attribute__`](#group__ramdiskloader_1ga43c18e3e8d026268ff2a4e80b6e37c9d)`((__packed__))` 

Represents a packed FAT structure for serialization.

Represents a packed file for serialization.

Represents a packed cluster for serialization.

#### `public struct `[`SerializedFilesystem`](#structSerializedFilesystem)` `[`serialize_filesystem`](#group__ramdiskloader_1gaa3a1976cfef20abebc813bfeabee092f)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat)` 

Serializes a [HiddenFat](#structHiddenFat) structure into a [SerializedFilesystem](#structSerializedFilesystem) structure.

This function takes a [HiddenFat](#structHiddenFat) structure and converts it into a serialized representation suitable for storage or transmission. This function allocates buf inside [SerializedFilesystem](#structSerializedFilesystem), which can be freed with free() by the caller of this function.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

#### Returns
A [SerializedFilesystem](#structSerializedFilesystem) structure containing the serialized data.

#### `public `[`HiddenFat`](#structHiddenFat)` * `[`load_ramdisk`](#group__ramdiskloader_1ga0d12600694dbe9e21b394189a5c0fa6f)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` serialized_filesystem)` 

Loads a RAM disk from a serialized filesystem data.

This function takes a [SerializedFilesystem](#structSerializedFilesystem) structure containing serialized data and reconstructs a [HiddenFat](#structHiddenFat) structure representing the RAM disk filesystem.

#### Parameters
* `serialized_filesystem` The [SerializedFilesystem](#structSerializedFilesystem) structure containing the serialized data. 

#### Returns
A pointer to the loaded [HiddenFat](#structHiddenFat) structure, or NULL if loading fails. This structure is allocated on the heap and can be freed with freeHiddenFat in [hiddenfat.h](#hiddenfat_8h)

#### `public size_t `[`calculate_amount_blocks`](#group__ramdiskloader_1ga9f182582224a7cc8b45be22e7596e76f)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` serialized_filesystem)` 

calculates how many blocks a serialized filesystem can hold.

This function is useful for calculating the size of unformatted raw filesystems.

#### Parameters
* `serialized_filesystem` The [SerializedFilesystem](#structSerializedFilesystem) structure containing the serialized data. 

#### Returns
Amount of blocks which will fit in this filesystem.

# struct `SerializedFilesystem` 

Represents a serialized filesystem that holds the serialized data.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public size_t `[`size`](ramdiskloader.md#structSerializedFilesystem_1a829c1e5e7c501c1baf86841d9ac668a3) | Size of the serialized data in bytes.
`public bool `[`rle`](ramdiskloader.md#structSerializedFilesystem_1a22cd8b44c2683729b44674eacf9bda11) | Flag if the Fielsystem is compressed with Run-Length Encoding flag.
`public unsigned char * `[`buf`](ramdiskloader.md#structSerializedFilesystem_1a4849c9fc8e4e5fb167c77b954277923a) | Pointer to the serialized data buffer.

## Members

#### `public size_t `[`size`](ramdiskloader.md#structSerializedFilesystem_1a829c1e5e7c501c1baf86841d9ac668a3) 

Size of the serialized data in bytes.

#### `public bool `[`rle`](ramdiskloader.md#structSerializedFilesystem_1a22cd8b44c2683729b44674eacf9bda11) 

Flag if the Fielsystem is compressed with Run-Length Encoding flag.

#### `public unsigned char * `[`buf`](ramdiskloader.md#structSerializedFilesystem_1a4849c9fc8e4e5fb167c77b954277923a) 

Pointer to the serialized data buffer.

# struct `HiddenFile` 

Represents a hidden file in the hidden FAT filesystem.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public size_t `[`filesize`](ramdiskloader.md#structHiddenFile_1abed2edf0dddffb8bf9c8658bdc06ed9a) | 
`public size_t `[`real_filesize`](ramdiskloader.md#structHiddenFile_1a4a4308f9072ed688e2f747f6645d15ed) | 
`public long `[`timestamp`](ramdiskloader.md#structHiddenFile_1a624f177eb3b7f3c6c85ff1ace59135c8) | 
`public `[`HiddenCluster`](#structHiddenCluster)` * `[`hiddenCluster`](#structHiddenFile_1aac6a40bd10600e18dab5aafe76bde7f6) | 
`public char `[`filename`](ramdiskloader.md#structHiddenFile_1a40261e5b168aa7a560d5a0120f902b60) | 

## Members

#### `public size_t `[`filesize`](ramdiskloader.md#structHiddenFile_1abed2edf0dddffb8bf9c8658bdc06ed9a) 

#### `public size_t `[`real_filesize`](ramdiskloader.md#structHiddenFile_1a4a4308f9072ed688e2f747f6645d15ed) 

#### `public long `[`timestamp`](ramdiskloader.md#structHiddenFile_1a624f177eb3b7f3c6c85ff1ace59135c8) 

#### `public `[`HiddenCluster`](#structHiddenCluster)` * `[`hiddenCluster`](#structHiddenFile_1aac6a40bd10600e18dab5aafe76bde7f6) 

#### `public char `[`filename`](ramdiskloader.md#structHiddenFile_1a40261e5b168aa7a560d5a0120f902b60) 

# struct `HiddenCluster` 

Structure representing a hidden cluster.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public size_t `[`b_index`](ramdiskloader.md#structHiddenCluster_1a96430513b3e8409b48f2a62d5b093d64) | Index of the cluster within a block.
`public size_t `[`cluster_index`](ramdiskloader.md#structHiddenCluster_1ad1ccb71186feea9c1c1dc712c6d1c0e9) | Index of the cluster within the filesystem.
`public unsigned int `[`state`](ramdiskloader.md#structHiddenCluster_1a3f0517210ea3d35ff5e7077d31557c76) | State of the cluster (enum State).
`public `[`HiddenCluster`](#structHiddenCluster)` * `[`prev`](#structHiddenCluster_1a7367a00e100cafc547b57c5bb4fe5a08) | Pointer to the previous cluster in the linked list.
`public `[`HiddenCluster`](#structHiddenCluster)` * `[`next`](#structHiddenCluster_1aa14a3e27d751de697ff9bcf576ca742c) | Pointer to the next cluster in the linked list.
`public `[`HiddenFile`](#structHiddenFile)` * `[`file`](#structHiddenCluster_1a0adad5264fc41d3af45b74c0b0abf089) | Pointer to the file associated with the cluster.

## Members

#### `public size_t `[`b_index`](ramdiskloader.md#structHiddenCluster_1a96430513b3e8409b48f2a62d5b093d64) 

Index of the cluster within a block.

#### `public size_t `[`cluster_index`](ramdiskloader.md#structHiddenCluster_1ad1ccb71186feea9c1c1dc712c6d1c0e9) 

Index of the cluster within the filesystem.

#### `public unsigned int `[`state`](ramdiskloader.md#structHiddenCluster_1a3f0517210ea3d35ff5e7077d31557c76) 

State of the cluster (enum State).

#### `public `[`HiddenCluster`](#structHiddenCluster)` * `[`prev`](#structHiddenCluster_1a7367a00e100cafc547b57c5bb4fe5a08) 

Pointer to the previous cluster in the linked list.

#### `public `[`HiddenCluster`](#structHiddenCluster)` * `[`next`](#structHiddenCluster_1aa14a3e27d751de697ff9bcf576ca742c) 

Pointer to the next cluster in the linked list.

#### `public `[`HiddenFile`](#structHiddenFile)` * `[`file`](#structHiddenCluster_1a0adad5264fc41d3af45b74c0b0abf089) 

Pointer to the file associated with the cluster.

