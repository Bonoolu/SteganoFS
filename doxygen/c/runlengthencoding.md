# runlengthencoding.h

This file contains function declarations related to run-length encoding and decoding of serialized filesystems.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`run_length_encoding`](#group__runlengthencoding_1ga01ab5ef8f38349c9d5251cd7b3710c72)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` * serialized_filesystem)`            | Run-length encodes a serialized filesystem.
`public void `[`run_length_decoding`](#group__runlengthencoding_1gad25093650710e37c1918a1a6b2e4bac9)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` * serialized_filesystem)`            | Run-length decodes a serialized filesystem.

## Members

#### `public void `[`run_length_encoding`](#group__runlengthencoding_1ga01ab5ef8f38349c9d5251cd7b3710c72)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` * serialized_filesystem)` 

Run-length encodes a serialized filesystem.

This function performs run-length encoding on the provided serialized filesystem. It replaces consecutive zero bytes with a range specification for efficient storage.

#### Parameters
* `serialized_filesystem` A pointer to the serialized filesystem structure to be encoded.

#### `public void `[`run_length_decoding`](#group__runlengthencoding_1gad25093650710e37c1918a1a6b2e4bac9)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` * serialized_filesystem)` 

Run-length decodes a serialized filesystem.

This function performs run-length decoding on a previously run-length encoded serialized filesystem. It reconstructs the original data by expanding the zero ranges specified during encoding.

#### Parameters
* `serialized_filesystem` A pointer to the serialized filesystem structure to be decoded.

