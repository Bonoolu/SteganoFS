# hiddenfile.h

This file contains the structures and function declarations for hidden file operations.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int `[`delete_hidden_file`](#group__hiddenfile_1ga1b6af287c5fd23063b62c72a3bdac3ab)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * filename)`            | Deletes a hidden file from the hidden FAT filesystem.
`public int `[`count_path_components`](#group__hiddenfile_1ga15ad97f3f11ca281808f9bf0e32db5be)`(const char * path)`            | Counts the number of components in a given path.
`public `[`HiddenFile`](#structHiddenFile)` * `[`find_file_by_path`](#group__hiddenfile_1ga62a86090d8eb7104b665dda1c7ea7e58)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * path)`            | Finds a hidden file by its path.
`public `[`HiddenFile`](#structHiddenFile)` ** `[`create_hidden_file`](#group__hiddenfile_1gaf5053a4b545f4e6dad4353492493eccb)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * filename,long timestamp)`            | Creates a hidden file in the hidden FAT filesystem.

## Members

#### `public int `[`delete_hidden_file`](#group__hiddenfile_1ga1b6af287c5fd23063b62c72a3bdac3ab)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * filename)` 

Deletes a hidden file from the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `filename` The name of the file to be deleted. 

#### Returns
0 on success, or -ENOENT if the file was not found.

#### `public int `[`count_path_components`](#group__hiddenfile_1ga15ad97f3f11ca281808f9bf0e32db5be)`(const char * path)` 

Counts the number of components in a given path.

#### Parameters
* `path` The path string to be analyzed. 

#### Returns
The number of components in the path.

#### `public `[`HiddenFile`](#structHiddenFile)` * `[`find_file_by_path`](#group__hiddenfile_1ga62a86090d8eb7104b665dda1c7ea7e58)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * path)` 

Finds a hidden file by its path.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `path` The path of the file to be found. 

#### Returns
A pointer to the [HiddenFile](#structHiddenFile) structure if found, otherwise NULL.

#### `public `[`HiddenFile`](#structHiddenFile)` ** `[`create_hidden_file`](#group__hiddenfile_1gaf5053a4b545f4e6dad4353492493eccb)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,const char * filename,long timestamp)` 

Creates a hidden file in the hidden FAT filesystem.

#### Parameters
* `hidden_fat` A pointer to the [HiddenFat](#structHiddenFat) structure. 

* `filename` The name of the file to be created. 

* `timestamp` The timestamp of the file. 

#### Returns
A pointer to the [HiddenFile](#structHiddenFile) pointer if created successfully, otherwise NULL.

