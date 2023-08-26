# stegano_provider.h

Header file for steganography provider selection and operations.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public struct `[`SerializedFilesystem`](#structSerializedFilesystem)` `[`stegano_provider_read`](#group__stegano__provider_1ga5e40e8362b2976ad1e8e0594f06970e6)`(const char * path)`            | Reads a serialized filesystem from a path using steganography providers.
`public bool `[`stegano_provider_write`](#group__stegano__provider_1ga3a5a8ce8130fa0ef64d4ec2497f9484f)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` serialized_filesystem,const char * path)`            | Writes a serialized filesystem to a path using steganography providers.
`struct `[`SteganoProvider`](stegano_provider.md#structSteganoProvider) | Structure to represent a steganography provider and its operations.

## Members

#### `public struct `[`SerializedFilesystem`](#structSerializedFilesystem)` `[`stegano_provider_read`](#group__stegano__provider_1ga5e40e8362b2976ad1e8e0594f06970e6)`(const char * path)` 

Reads a serialized filesystem from a path using steganography providers.

This function reads a serialized filesystem from a path, utilizing appropriate steganography providers.

#### Parameters
* `path` Path to the serialized filesystem data. 

#### Returns
[SerializedFilesystem](#structSerializedFilesystem) structure containing the read data. * This function allocates heap for buf inside [SerializedFilesystem](#structSerializedFilesystem), which can be freed with free() by the caller of this function. This buffer needs to be freed with free() by the caller of this function

#### `public bool `[`stegano_provider_write`](#group__stegano__provider_1ga3a5a8ce8130fa0ef64d4ec2497f9484f)`(struct `[`SerializedFilesystem`](#structSerializedFilesystem)` serialized_filesystem,const char * path)` 

Writes a serialized filesystem to a path using steganography providers.

This function writes a serialized filesystem to a path, utilizing appropriate steganography providers.

#### Parameters
* `serialized_filesystem` The [SerializedFilesystem](#structSerializedFilesystem) structure containing data to be written. 

* `path` Path where the data should be written. 

#### Returns
Returns true if writing is successful, false otherwise.

# struct `SteganoProvider` 

Structure to represent a steganography provider and its operations.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public const char * `[`extension`](stegano_provider.md#structSteganoProvider_1a5ddbb8f4f2ab74fa511261b47644e25f) | File extension associated with the provider.
`public `[`ProviderRead`](#group__stegano__provider_1ga04859071400c5ba02a785c74027a2932)` `[`provider_read`](#structSteganoProvider_1aa6dfd3bd103ca332cec0fe4f7386f768) | Function pointer for reading data using the provider.
`public `[`ProviderWrite`](#group__stegano__provider_1ga5750853e0972c3514e40daa381d1b339)` `[`provider_write`](#structSteganoProvider_1a996698596f3e1935348d4e057942e775) | Function pointer for writing data using the provider.

## Members

#### `public const char * `[`extension`](stegano_provider.md#structSteganoProvider_1a5ddbb8f4f2ab74fa511261b47644e25f) 

File extension associated with the provider.

#### `public `[`ProviderRead`](#group__stegano__provider_1ga04859071400c5ba02a785c74027a2932)` `[`provider_read`](#structSteganoProvider_1aa6dfd3bd103ca332cec0fe4f7386f768) 

Function pointer for reading data using the provider.

#### `public `[`ProviderWrite`](#group__stegano__provider_1ga5750853e0972c3514e40daa381d1b339)` `[`provider_write`](#structSteganoProvider_1a996698596f3e1935348d4e057942e775) 

Function pointer for writing data using the provider.

