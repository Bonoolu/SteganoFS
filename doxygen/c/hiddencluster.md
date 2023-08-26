# hiddencluster.h

Header file for hidden cluster operations.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`enum `[`State`](#group__hiddencluster_1ga5d74787dedbc4e11c1ab15bf487e61f8)            | Enumeration representing the state of a hidden cluster.
`public bool `[`swap_hidden_clusters`](#group__hiddencluster_1ga1736049385c7bf194f6a0fec32f0f508)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index_a,size_t b_index_b)`            | Swaps two hidden clusters within a hidden FAT.
`public bool `[`extend_hidden_cluster`](#group__hiddencluster_1ga80b5c17506983811bc3cbdee5b84ff3d)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,`[`HiddenFile`](#structHiddenFile)` * p_file)`            | Extends a hidden cluster for a hidden file.

## Members

#### `enum `[`State`](#group__hiddencluster_1ga5d74787dedbc4e11c1ab15bf487e61f8) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
FREE            | Cluster is free.
RESERVED            | Cluster is reserved.
DEFECT            | Cluster is defective.
ALLOCATED            | Cluster is allocated.

Enumeration representing the state of a hidden cluster.

#### `public bool `[`swap_hidden_clusters`](#group__hiddencluster_1ga1736049385c7bf194f6a0fec32f0f508)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,size_t b_index_a,size_t b_index_b)` 

Swaps two hidden clusters within a hidden FAT.

This function swaps two hidden clusters within a hidden FAT.

#### Parameters
* `hidden_fat` Pointer to the [HiddenFat](#structHiddenFat) structure. 

* `b_index_a` Index of the first cluster to be swapped. 

* `b_index_b` Index of the second cluster to be swapped. 

#### Returns
Returns true if the swap is successful, false otherwise.

#### `public bool `[`extend_hidden_cluster`](#group__hiddencluster_1ga80b5c17506983811bc3cbdee5b84ff3d)`(`[`HiddenFat`](#structHiddenFat)` * hidden_fat,`[`HiddenFile`](#structHiddenFile)` * p_file)` 

Extends a hidden cluster for a hidden file.

This function extends a hidden cluster for a hidden file in a hidden FAT.

#### Parameters
* `hidden_fat` Pointer to the [HiddenFat](#structHiddenFat) structure. 

* `p_file` Pointer to the [HiddenFile](#structHiddenFile) structure. 

#### Returns
Returns true if the extension is successful, false otherwise.

