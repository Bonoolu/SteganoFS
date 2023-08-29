### Architecture Guide


#### Key Components

1. **fuse3:** SteganoFS leverages the fuse3 library to create a virtual filesystem. This library allows users to mount and interact with a filesystem implemented in software.

2. **Filesystem Implementation:** At the core of SteganoFS is the filesystem implementation. This component is responsible for managing the structure and organization of the virtual filesystem. It handles operations such as creating directories, reading files, and managing metadata.

3. **Stegano Providers:** SteganoFS introduces the concept of Stegano Providers. These are pluggable components that enable hiding data within various types of files, following the Strategy pattern. Each provider is responsible for embedding and extracting data from its respective file type, such as BMP images. Providers allow for extensibility, enabling users to implement new methods for hiding data in different file formats.

4. **Ramdiskloader:** The Ramdiskloader module plays a crucial role in loading the virtual filesystem into memory. It uses the filesystem implementation to recreate the filesystem structure and populate it with data extracted from steganographic files.

#### Interaction Flow

1. **Loading the Filesystem:**
    - The steganographic provider reads the hidden payload from the steganographic files (e.g., BMP images).
    - The Ramdiskloader module utilizes the filesystem implementation to create the virtual filesystem structure in memory.
    - This loaded filesystem is ready to be mounted using fuse3.

2. **Mounting with fuse3:**
    - Users can mount the virtual filesystem using the fuse3 library, making it accessible through a designated mount point.
    - fuse3 handles the interactions between the operating system and the virtual filesystem, allowing users to perform operations as if they were interacting with a physical filesystem.

3. **Filesystem Interactions:**
    - Users can perform various filesystem operations such as reading files, and modifying data within the mounted filesystem. Behind the scenes, these operations are managed by the filesystem implementation module.

4. **Unmounting and Formatting:**
    - To unmount the filesystem, users can use the appropriate commands.
    - Unmounting triggers the reverse process of loading: data is written back to steganographic files, and the virtual filesystem in memory is cleared.

#### Extensibility and Future Directions

SteganoFS's architecture is designed with extensibility in mind. By introducing the Stegano Providers concept, the project allows for easy integration of new file formats for hiding data. Developers can implement their own providers following the existing template.

The architecture also separates the filesystem implementation from the steganography and mounting components. This separation enables future enhancements, such as adopting more mature filesystem implementations and integrating improved steganographic techniques.
